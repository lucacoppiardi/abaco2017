#include <iostream>
using namespace std;
#include <sqlite3.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>
#include <ctime>
#include "Persona.h"
#include "Tipo_Evento.h"
#include "Evento.h"
#include "main.h"
#define DIM 100

char *zErrMsg = 0;
int rc; // return code
sqlite3 *database;
const char *comando;
sqlite3_stmt *stmt;
const char *pzTest;

void mostra_eventi();
void mostra_tipo_evento();
void mostra_eventi_IDtipo();
void mostra_eventi_ordine_cronologico();
void mostra_persone();
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
void log_query(string txt);
string orario();
void log_statoDB(string txt);

int main(int argc, char **argv) {
	
	ofstream log; // Pulizia log prima di nuova esecuzione programma
	log.open("query.log"); 
	if (!log.is_open()) {
		cout << "Impossibile creare il log!" << endl;
		return 0;
	}
	log.close();
	
	rc = sqlite3_open("database.sqlite", &database);
	if (rc != SQLITE_OK) {
		cout << "ERRORE nell'apertura del database: " << sqlite3_errmsg(database) << endl;
		log_query("ERRORE nell'apertura del database: ");
		log_query(sqlite3_errmsg(database));
		return -1;
	} else {
		cout << "Database aperto" << endl << endl;
		log_query("Database aperto");
	}
	
	log.open("db.log"); // Pulizia log prima di nuova esecuzione programma
	if (!log.is_open()) {
		cout << "Impossibile creare il log DB!" << endl;
		return -1;
	}
	log.close();
	log_statoDB("********Database all'apertura del programma:********");
	
	comando = "CREATE TABLE IF NOT EXISTS PERSONE (ID_PERSONA INTEGER, NOME STRING, COGNOME STRING)";
	log_query(comando);
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		cout << "ERRORE tabella PERSONE: " << zErrMsg << endl;
		log_query("ERRORE tabella PERSONE: ");
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	} else {
		cout << "Tabella PERSONE pronta" << endl;
	}
	
	comando = "CREATE TABLE IF NOT EXISTS TIPO_EVENTO (ID_TIPO_EVENTO INTEGER, DESCRIZIONE STRING)";
	log_query(comando);
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		cout << "ERRORE tabella TIPO_EVENTO: " << zErrMsg << endl;
		log_query("ERRORE tabella TIPO_EVENTO: ");
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	} else {
		cout << "Tabella TIPO_EVENTO pronta" << endl;
	}
	
	comando = "CREATE TABLE IF NOT EXISTS EVENTI (ID_PERSONA INTEGER, ID_TIPO_EVENTO INTEGER, DATA_ORA_EVENTO DATETIME)";
	log_query(comando);
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)  {
		cout << "ERRORE tabella EVENTI: " << zErrMsg << endl;
		log_query("ERRORE tabella EVENTI:");
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	} else {
		cout << "Tabella EVENTI pronta" << endl;
	}
	
	Persona p;
	Tipo_Evento t;
	Evento e;
	string nome;
	string cognome;
	int id_persona;
	int id_tipo_evento;
	string descrizione;
	string data_ora_evento;
	int scelta = 0;
	
	cout << endl << "\tOPZIONI DISPONIBILI:" << endl << endl;
		
	cout << "\t1. Aggiungi persona" << endl;
	cout << "\t2. Modifica persona" << endl;
	cout << "\t3. Cancella persona" << endl;
	cout << "\t4. Aggiungi tipo evento" << endl;
	cout << "\t5. Modifica tipo evento" << endl;
	cout << "\t6. Cancella tipo evento" << endl;
	cout << "\t7. Aggiungi evento" << endl;
	cout << "\t8. Modifica evento" << endl;
	cout << "\t9. Elimina evento" << endl;
	cout << "\t10. Mostra tabella persone" << endl;
	cout << "\t11. Mostra tabella tipo evento" << endl;
	cout << "\t12. Mostra tabella eventi" << endl;
	cout << "\t13. Estrai eventi in ordine cronologico relativi ad una persona" << endl;
	cout << "\t14. Estrai eventi dato ID tipo evento" << endl;
	
	cout << endl << "\tSCELTA: ";
	cin >> scelta;
	cout << endl;
	
	switch (scelta) {
		case 0:
			return 0;
		case 1:
			cout<<"Inserisci id persona:";
			cin>>id_persona;
			while(cin.get()!='\n');
			
			cout<<"Inserisci cognome persona:";
			getline(cin,cognome);
			
			cout<<"Inserici nome persona:";
			getline(cin,nome);
			
			p.setNome(nome);
			p.setCognome(cognome);
			p.setID_PERSONA(id_persona);
			p.aggiungi_persona();
			break;
		case 2:
			p.modifica_persona();
			break;
		case 3:
			p.cancella_persona();
			break;
		case 4:
			cout<<"Inserisci id tipo evento:";
			cin>>id_tipo_evento;
			while(cin.get()!='\n');
			
			cout<<"Inserisci descrizione:";
			getline(cin,descrizione);
			
			t.setID_TIPO_EVENTO(id_tipo_evento);
			t.setDescrizione(descrizione);
			t.aggiungi_tipo_evento();
			break;
		case 5:
			t.modifica_tipo_evento();
			break;
		case 6:
			t.cancella_tipo_evento();
			break;
		case 7:
			cout<<"Inserisci id della persona:";
			cin>>id_persona;
			while(cin.get()!='\n');
			
			cout<<"Inserisci id tipo evento:";
			cin>>id_tipo_evento;
			while(cin.get()!='\n');
			
			cout<<"Inserisci data  e ora evento:";
			getline(cin,data_ora_evento);
			
			e.SetDATA_ORA_EVENTO(data_ora_evento);
			e.SetID_PERSONA(id_persona);
			e.SetID_TIPO_EVENTO(id_tipo_evento);
			e.aggiungi_evento();
			break;
		case 8:
			e.modifica_evento();
			break;
		case 9:
			e.cancella_evento();
			break;
		case 10:
			mostra_persone();
			break;
		case 11:
			mostra_tipo_evento();
			break;
		case 12:
			mostra_eventi();
			break;
		case 13:
			mostra_eventi_ordine_cronologico();
			break;
		case 14:
			mostra_eventi_IDtipo();
			break;
		default:
			cout << "SCELTA NON VALIDA!" << endl;
			break;
	}
	
	log_statoDB("********Database alla chiusura del programma:********");
	rc = sqlite3_close(database);
	if (rc != SQLITE_OK) {
		cout << "ERRORE nella chiusura del database: " << sqlite3_errmsg(database) << endl;
		log_query("ERRORE nella chiusura del database: ");
		log_query(zErrMsg);
		return -1;
	} else {
		cout << "Database chiuso" << endl;
		log_query("Database chiuso");
	}

	return 0;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	
	for(i = 0; i < argc; i++) {
		cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
	}
	cout << endl;
	
	return 0;
}


void mostra_persone() {
	
	cout << "Lettura tabella Persone: " << endl;
	
	int i = 0;
	int row = 1;
	int bytes1 = 0;
	int bytes2 = 0;
	int bytes3 = 0;
	const unsigned char * text1;
	const unsigned char * text2;
	const unsigned char * text3;
	
	comando = "SELECT * FROM PERSONE";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc != SQLITE_OK) {
		cout << "ERRORE mostra_persone: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	cout << "ID\t\tNOME\t\tCOGNOME" << endl;
	
	while (1) {
		
		int s;
		s = sqlite3_step (stmt);
		
		if (s == SQLITE_ROW) {
			bytes1 = sqlite3_column_bytes(stmt, 0);
			text1 = sqlite3_column_text(stmt, 0);
			
			bytes2 = sqlite3_column_bytes(stmt, 1);
			text2 = sqlite3_column_text(stmt, 1);
			
			bytes3 = sqlite3_column_bytes(stmt, 2);
			text3 = sqlite3_column_text(stmt, 2);
			
			cout << text1 << "\t\t" << text2 << "\t\t" << text3 << endl;
			row++;
		}
		else if (s == SQLITE_DONE) {
			break;
		}
		else {
			cout << "ERRORE" << endl;
			return;
		}
		
	}
	
	log_query(sqlite3_expanded_sql(stmt));
	
	sqlite3_finalize(stmt);
	
	cout << "Fine lettura tabella Persone" << endl;
	
	return;
	
}

void mostra_tipo_evento() {
	
	cout << "Lettura tabella Tipo evento: " << endl;
	
	int i = 0;
	int row = 1;
	int bytes1 = 0;
	int bytes2 = 0;
	const unsigned char * text1;
	const unsigned char * text2;
	
	comando = "SELECT * FROM TIPO_EVENTO";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc != SQLITE_OK) {
		cout << "ERRORE mostra_tipo_evento: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	cout << "TIPO EVENTO\tDESCRIZIONE" << endl;
	
	while (1) {
		
		int s;
		s = sqlite3_step (stmt);
		
		if (s == SQLITE_ROW) {
			bytes1 = sqlite3_column_bytes(stmt, 0);
			text1 = sqlite3_column_text(stmt, 0);
			
			bytes2 = sqlite3_column_bytes(stmt, 1);
			text2 = sqlite3_column_text(stmt, 1);
			
			cout << text1 << "\t\t" << text2 << endl;
			row++;
		}
		else if (s == SQLITE_DONE) {
			break;
		}
		else {
			cout << "ERRORE" << endl;
			return;
		}
		
	}
	
	log_query(sqlite3_expanded_sql(stmt));
	
	sqlite3_finalize(stmt);
	
	cout << "Fine lettura tabella Tipo evento" << endl;
	
	return;
	
}

void mostra_eventi() {
	
	cout << "Lettura tabella Eventi: " << endl;
	
	int i = 0;
	int row = 1;
	int bytes1 = 0;
	int bytes2 = 0;
	int bytes3 = 0;
	const unsigned char * text1;
	const unsigned char * text2;
	const unsigned char * text3;
	
	comando = "SELECT * FROM EVENTI";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc != SQLITE_OK) {
		cout << "ERRORE mostra_eventi: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	cout << "PERSONA\t\tTIPO EVENTO\tDATA-ORA" << endl;
	
	while (1) {
		
		int s;
		s = sqlite3_step (stmt);
		
		if (s == SQLITE_ROW) {
			bytes1 = sqlite3_column_bytes(stmt, 0);
			text1 = sqlite3_column_text(stmt, 0);
			
			bytes2 = sqlite3_column_bytes(stmt,1);
			text2 = sqlite3_column_text(stmt, 1);
			
			bytes3 = sqlite3_column_bytes(stmt,2);
			text3 = sqlite3_column_text(stmt, 2);
			
			cout << text1 << "\t\t" << text2 << "\t\t" << text3 << endl;
			row++;
		}
		else if (s == SQLITE_DONE) {
			break;
		}
		else {
			cout << "ERRORE" << endl;
			return;
		}
		
	}
	
	log_query(sqlite3_expanded_sql(stmt));
	
	sqlite3_finalize(stmt);
	
	cout << "Fine lettura tabella Eventi" << endl;
	
	return;
	
}

void mostra_eventi_ordine_cronologico() {
	
	cout << "Elenco cronologico degli eventi: " << endl;
	
	int ID_PERSONA = 0;
	cout << "ID persona di cui vedere gli eventi: " ;
	cin >> ID_PERSONA;
	
	int i = 0;
	int row = 1;
	int bytes1 = 0;
	int bytes2 = 0;
	int bytes3 = 0;
	const unsigned char * text1;
	const unsigned char * text2;
	const unsigned char * text3;
	
	comando = "SELECT * FROM EVENTI WHERE ID_PERSONA = ? ORDER BY DATA_ORA_EVENTO ASC";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	
	if (rc != SQLITE_OK) {
		cout << "ERRORE mostra_eventi_ordine_cronologico: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
		return;
	}
	
	sqlite3_bind_int(stmt,1, ID_PERSONA);
	
	cout << "ID persona\tID tipo evento\tData/ora" << endl;
	
	while (1) {
		
		int s;
		s = sqlite3_step (stmt);
		
		if (s == SQLITE_ROW) {
			bytes1 = sqlite3_column_bytes(stmt, 0);
			text1 = sqlite3_column_text (stmt, 0);
			
			bytes2 = sqlite3_column_bytes(stmt, 1);
			text2 = sqlite3_column_text (stmt, 1);
			
			bytes3 = sqlite3_column_bytes(stmt, 2);
			text3 = sqlite3_column_text (stmt, 2);
			
			cout << text1 << "\t\t" << text2 << "\t\t" << text3 << endl;
			row++;
		}
		else if (s == SQLITE_DONE) {
			break;
		}
		else {
			cout << "ERRORE" << endl;
			return;
		}
		
	}
	
	log_query(sqlite3_expanded_sql(stmt));
	
	sqlite3_finalize(stmt);
	
	cout << "Fine lettura" << endl;
	
	delete text1;
	delete text2;
	delete text3;
	
	return;
}

void mostra_eventi_IDtipo() {
	
	cout << "Elenco degli eventi dato ID: " << endl;
	
	int ID_TIPO_EVENTO = 0;
	cout << "ID tipo di evento da visualizzare: " ;
	cin >> ID_TIPO_EVENTO;
	
	cout << "Elenco degli eventi con ID tipo " << ID_TIPO_EVENTO << endl;
	
	int i = 0;
	int row = 1;
	int bytes1 = 0;
	int bytes2 = 0;
	int bytes3 = 0;
	const unsigned char * text1;
	const unsigned char * text2;
	const unsigned char * text3;
	
	comando = "SELECT * FROM EVENTI WHERE ID_TIPO_EVENTO = ? ORDER BY DATA_ORA_EVENTO ASC";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	
	if (rc != SQLITE_OK) {
		cout << "ERRORE mostra_eventi_IDtipo: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
		return;
	}
	
	sqlite3_bind_int(stmt, 1, ID_TIPO_EVENTO);
	
	cout << "ID persona\tID tipo evento\tData/ora" << endl;
	
	while (1) {
		
		int s;
		s = sqlite3_step (stmt);
		
		if (s == SQLITE_ROW) {
			bytes1 = sqlite3_column_bytes(stmt, 0);
			text1 = sqlite3_column_text (stmt, 0);
			
			bytes2 = sqlite3_column_bytes(stmt, 1);
			text2 = sqlite3_column_text (stmt, 1);
			
			bytes3 = sqlite3_column_bytes(stmt, 2);
			text3 = sqlite3_column_text (stmt, 2);
			
			cout << text1 << "\t\t" << text2 << "\t\t" << text3 << endl;
			row++;
		}
		else if (s == SQLITE_DONE) {
			break;
		}
		else {
			cout << "ERRORE" << endl;
			return;
		}
		
	}
	
	log_query(sqlite3_expanded_sql(stmt));
	
	sqlite3_finalize(stmt);
	
	cout << "Fine lettura" << endl;
	
	delete text1;
	delete text2;
	delete text3;
	
	return;
}

void log_statoDB(string txt) {
	
	int i = 0;
	int row = 1;
	int bytes1 = 0;
	int bytes2 = 0;
	int bytes3 = 0;
	const unsigned char * text1;
	const unsigned char * text2;
	const unsigned char * text3;
	ofstream log;
	
	log.open("db.log",ios::app); 
	if (!log.is_open()) {
		cout << "Impossibile creare il log!" << endl;
		return;
	}
	log << orario() << txt << endl;
	
	log << orario() << "Tabella PERSONE:" << endl;
	comando = "SELECT * FROM PERSONE";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc != SQLITE_OK) {
		cout << "ERRORE: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
		return;
	}
	log << "ID\t\tNOME\t\tCOGNOME" << endl;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {
			bytes1 = sqlite3_column_bytes(stmt, 0);
			text1 = sqlite3_column_text(stmt, 0);
			bytes2 = sqlite3_column_bytes(stmt, 1);
			text2 = sqlite3_column_text(stmt, 1);
			bytes3 = sqlite3_column_bytes(stmt, 2);
			text3 = sqlite3_column_text(stmt, 2);
			log << text1 << "\t\t" << text2 << "\t\t" << text3 << endl;
			row++;
		}
		else if (s == SQLITE_DONE) {
			break;
		}
		else {
			cout << "ERRORE" << endl;
			return;
		}
	}
	sqlite3_finalize(stmt);
	log << orario() <<  "Fine lettura tabella PERSONE" << endl << endl;
	
	log << orario() << "Tabella TIPO_EVENTO:" << endl;
	comando = "SELECT * FROM TIPO_EVENTO";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc != SQLITE_OK) {
		cout << "ERRORE: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
		return;
	}
	log << "ID\t\tTIPO_EVENTO" << endl;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {
			bytes1 = sqlite3_column_bytes(stmt, 0);
			text1 = sqlite3_column_text(stmt, 0);
			bytes2 = sqlite3_column_bytes(stmt, 1);
			text2 = sqlite3_column_text(stmt, 1);
			log << text1 << "\t\t" << text2 << endl;
			row++;
		}
		else if (s == SQLITE_DONE) {
			break;
		}
		else {
			cout << "ERRORE" << endl;
			return;
		}
	}
	sqlite3_finalize(stmt);
	log << orario() << "Fine lettura tabella TIPO_EVENTI" << endl << endl;
	
	log << orario() << "Tabella EVENTI:" << endl;
	comando = "SELECT * FROM EVENTI";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc != SQLITE_OK) {
		cout << "ERRORE: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
		return;
	}
	log << "ID_PERSONA\tID_TIPO_EVENTO\t\tDATA_ORA_EVENTO" << endl;
	while (1) {
		int s;
		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {
			bytes1 = sqlite3_column_bytes(stmt, 0);
			text1 = sqlite3_column_text(stmt, 0);
			bytes2 = sqlite3_column_bytes(stmt, 1);
			text2 = sqlite3_column_text(stmt, 1);
			bytes3 = sqlite3_column_bytes(stmt, 2);
			text3 = sqlite3_column_text(stmt, 2);
			log << text1 << "\t\t" << text2 << "\t\t\t" << text3 << endl;
			row++;
		}
		else if (s == SQLITE_DONE) {
			break;
		}
		else {
			cout << "ERRORE" << endl;
			return;
		}
	}
	sqlite3_finalize(stmt);
	log << orario() <<  "Fine lettura tabella EVENTI" << endl << endl;
	
	log.close();
}

void log_query(string txt) {
	ofstream log;
	log.open("query.log",ios::app); 
	if (!log.is_open()) {
		cout << "Impossibile creare il log!" << endl;
		return;
	}
	log << orario() << txt << endl;
	log.close();
}

string orario() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[DIM];
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,sizeof(buffer),"%Y-%m-%d %H:%M:%S",timeinfo);
	string str(buffer);
	return str + " - ";
}