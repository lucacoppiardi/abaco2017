#include <iostream>
using namespace std;
#include <sqlite3.h>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#define DIM 100

char *zErrMsg = 0;
int rc; // return code
sqlite3 *database;
const char *comando;
sqlite3_stmt *stmt;
const char *pzTest;

void menu();
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
void aggiungi_persona();
void modifica_persona();
void cancella_persona();
void aggiungi_tipo_evento();
void modifica_tipo_evento();
void cancella_tipo_evento();
void aggiungi_evento();
void modifica_evento();
void cancella_evento();
void mostra_persone();
void mostra_tipo_evento();
void mostra_eventi();
void mostra_eventi_ordine_cronologico();
void mostra_eventi_IDtipo();
void log_query(const char* txt);
string orario();

int main(int argc, char **argv) {
	
	ofstream log; // Pulizia log prima di nuova esecuzione programma
	log.open("query.log"); 
	if (!log.is_open()) {
		cout << "Impossibile creare il log!" << endl;
		return -1;
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
	
	menu();
	
	/* // INSERIMENTI DI PROVA
	comando = "INSERT INTO PERSONE (ID_PERSONA, NOME, COGNOME) VALUES (1, 'SARA', 'CINESCA');";
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	} else {
		cout << "Dati inseriti in PERSONE" << endl;
	}
	
	comando = "INSERT INTO TIPO_EVENTO (ID_TIPO_EVENTO, DESCRIZIONE) VALUES (1, 'DESCRIZIONE DI PROVA');";
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	} else {
		cout << "Dati inseriti in TIPO_EVENTO" << endl;
	}
	
	comando = "INSERT INTO EVENTI (ID_PERSONA, ID_TIPO_EVENTO, DATA_ORA_EVENTO) VALUES (1, 1, '2017-06-12 16:03:45');";
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	} else {
		cout << "Dati inseriti in EVENTI" << endl;
	}
	*/
	
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

void menu() {
	
	int scelta = 0;
	
	do {
		cout << endl << "\tOPZIONI DISPONIBILI:" << endl << endl;
		
		cout << "\t0. Esci" << endl;
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
		while(cin.get()!='\n');
		cout << endl;
		
		switch (scelta) {
			case 0:
				return;
			case 1:
				aggiungi_persona();
				break;
			case 2:
				modifica_persona();
				break;
			case 3:
				cancella_persona();
				break;
			case 4:
				aggiungi_tipo_evento();
				break;
			case 5:
				modifica_tipo_evento();
				break;
			case 6:
				cancella_tipo_evento();
				break;
			case 7:
				aggiungi_evento();
				break;
			case 8:
				modifica_evento();
				break;
			case 9:
				cancella_evento();
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
		
	} while (scelta!=0);
	
	return;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	
	for(i = 0; i < argc; i++) {
		cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
	}
	cout << endl;
	
	return 0;
}

void aggiungi_persona() {
	
	int ID_PERSONA = 0;
	char *NOME = new char[DIM];
	char *COGNOME = new char[DIM];
	
	cout << "Inserimento persona: " << endl;
	
	cout << "ID: ";
	cin >> ID_PERSONA;
	while(cin.get()!='\n');
	
	cout << "Nome: ";
	cin.getline(NOME,DIM);
	
	cout << "Cognome: ";	
	cin.getline(COGNOME,DIM);
	
	comando = "INSERT INTO PERSONE (ID_PERSONA, NOME, COGNOME) VALUES (?,?,?)";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, ID_PERSONA);
		sqlite3_bind_text(stmt, 2, NOME, strlen(NOME), 0);
		sqlite3_bind_text(stmt, 3, COGNOME, strlen(COGNOME), 0);
		sqlite3_step(stmt);
		log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Persona n." << ID_PERSONA << " inserita in tabella PERSONE" << endl;
	} else {
		cout << "ERRORE aggiungi_persona: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	delete NOME;
	delete COGNOME;
	
	return;
}

void modifica_persona() {
	
	int ID_PERSONA = 0;
	char *NOME = new char[DIM];
	char *COGNOME = new char[DIM];
	
	cout << "Modifica persona: " << endl;
	
	cout << "ID persona da modificare: ";
	cin >> ID_PERSONA;
	while(cin.get()!='\n');
	
	cout << "Nuovo nome: ";
	cin.getline(NOME,DIM);
	
	cout << "Nuovo cognome: ";
	cin.getline(COGNOME,DIM);
	
	comando = "UPDATE PERSONE SET NOME = ?, COGNOME = ? WHERE ID_PERSONA = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, NOME, strlen(NOME), 0);
		sqlite3_bind_text(stmt, 2, COGNOME, strlen(COGNOME), 0);
		sqlite3_bind_int(stmt, 3, ID_PERSONA);
		sqlite3_step(stmt);
		log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Persona " << ID_PERSONA << " aggiornata in tabella PERSONE" << endl;
	} else {
		cout << "ERRORE modifica_persona: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	delete NOME;
	delete COGNOME;
	
	return;
}

void cancella_persona() {
	
	int ID_PERSONA = 0;
	
	cout << "Eliminazione persona: " << endl;
	
	cout << "ID persona da eliminare: ";
	cin >> ID_PERSONA;
	while(cin.get()!='\n');
	
	comando = "DELETE FROM PERSONE WHERE ID_PERSONA = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, ID_PERSONA);
		sqlite3_step(stmt);
		log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Persona n." << ID_PERSONA << " cancellata da tabella PERSONE" << endl;
	} else {
		cout << "ERRORE cancella_persona: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	return;
}

void aggiungi_tipo_evento() {
	
	int ID_TIPO_EVENTO = 0;
	char *DESCRIZIONE = new char[DIM];
	
	cout << "Aggiunta tipo evento: " << endl;
	
	cout << "ID: ";
	cin >> ID_TIPO_EVENTO;
	while(cin.get()!='\n');
	
	cout << "Descrizione: ";
	cin.getline(DESCRIZIONE,DIM);
	
	comando = "INSERT INTO TIPO_EVENTO (ID_TIPO_EVENTO, DESCRIZIONE) VALUES (?,?)";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, ID_TIPO_EVENTO);
		sqlite3_bind_text(stmt, 2, DESCRIZIONE, strlen(DESCRIZIONE), 0);
		sqlite3_step(stmt);
		log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Tipo evento " << ID_TIPO_EVENTO << " inserito in tabella TIPO_EVENTO" << endl;
	} else {
		cout << "ERRORE aggiungi_tipo_evento: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	delete DESCRIZIONE;
	
	return;
}

void modifica_tipo_evento() {
	
	int ID_TIPO_EVENTO = 0;
	char *DESCRIZIONE = new char[DIM];
	
	cout << "Modifica tipo evento: " << endl;
	
	cout << "ID tipo evento da modificare: ";
	cin >> ID_TIPO_EVENTO;
	while(cin.get()!='\n');
	
	cout << "Nuova descrizione: ";
	cin.getline(DESCRIZIONE,DIM);
	
	comando = "UPDATE TIPO_EVENTO SET DESCRIZIONE = ? WHERE ID_TIPO_EVENTO = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, DESCRIZIONE, strlen(DESCRIZIONE), 0);
		sqlite3_bind_int(stmt, 2, ID_TIPO_EVENTO);
		sqlite3_step(stmt);
		log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Tipo evento " << ID_TIPO_EVENTO << " aggiornato in tabella TIPO_EVENTI" << endl;
	} else {
		cout << "ERRORE modifica_tipo_evento: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	delete DESCRIZIONE;
	
	return;
}

void cancella_tipo_evento() {
	
	int ID_TIPO_EVENTO = 0;
	
	cout << "Eliminazione tipo evento: " << endl;
	
	cout << "ID tipo evento da eliminare: ";
	cin >> ID_TIPO_EVENTO;
	while(cin.get()!='\n');
	
	comando = "DELETE FROM TIPO_EVENTO WHERE ID_TIPO_EVENTO = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, ID_TIPO_EVENTO);
		sqlite3_step(stmt);
		log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Tipo evento " << ID_TIPO_EVENTO << " cancellato da tabella TIPO_EVENTO" << endl;
	} else {
		cout << "ERRORE cancella_tipo_evento: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	return;
}

void aggiungi_evento() {
	
	int ID_PERSONA = 0;
	int ID_TIPO_EVENTO = 0;
	char *DATA_ORA_EVENTO = new char[DIM];
	
	cout << "Inserimento evento: " << endl;
	
	cout << "ID persona: ";
	cin >> ID_PERSONA;
	while(cin.get()!='\n');
	
	cout << "ID tipo evento: ";
	cin >> ID_TIPO_EVENTO;
	while(cin.get()!='\n');
	
	cout << "Data/ora evento: ";
	cin.getline(DATA_ORA_EVENTO,DIM);
	
	comando = "INSERT INTO EVENTI (ID_PERSONA, ID_TIPO_EVENTO, DATA_ORA_EVENTO) VALUES (?,?,?)";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, ID_PERSONA);
		sqlite3_bind_int(stmt, 2, ID_TIPO_EVENTO);
		sqlite3_bind_text(stmt, 3, DATA_ORA_EVENTO, strlen(DATA_ORA_EVENTO), 0);
		sqlite3_step(stmt);
		log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Evento inserito in tabella EVENTI" << endl;
	} else {
		cout << "ERRORE aggiungi_evento: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	delete DATA_ORA_EVENTO;
	
	return;
}

void modifica_evento() {
	
	int ID_PERSONA = 0;
	int ID_TIPO_EVENTO = 0;
	int NEW_ID_TIPO_EVENTO = 0;
	char *DATA_ORA_EVENTO = new char[DIM];
	char *NEW_DATA_ORA_EVENTO = new char[DIM];
	
	cout << "Modifica evento: " << endl;
	
	cout << "ID persona di cui modificare un evento: ";
	cin >> ID_PERSONA;
	while(cin.get()!='\n');
	
	cout << "ID tipo evento da modificare: ";
	cin >> ID_TIPO_EVENTO;
	while(cin.get()!='\n');
	
	cout << "Data/ora evento da modificare: ";
	cin.getline(DATA_ORA_EVENTO,DIM);
	
	
	cout << "Nuovo ID tipo evento: ";
	cin >> NEW_ID_TIPO_EVENTO;
	while(cin.get()!='\n');
	
	cout << "Nuova data/ora evento: ";
	cin.getline(NEW_DATA_ORA_EVENTO,DIM);
	
	
	comando = "UPDATE EVENTI SET ID_TIPO_EVENTO = ?, DATA_ORA_EVENTO = ? WHERE ID_PERSONA = ? AND ID_TIPO_EVENTO = ? AND DATA_ORA_EVENTO = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, NEW_ID_TIPO_EVENTO);
		sqlite3_bind_text(stmt, 2, NEW_DATA_ORA_EVENTO, strlen(NEW_DATA_ORA_EVENTO), 0);
		sqlite3_bind_int(stmt, 3, ID_PERSONA);
		sqlite3_bind_int(stmt, 4, ID_TIPO_EVENTO);
		sqlite3_bind_text(stmt, 5, DATA_ORA_EVENTO, strlen(DATA_ORA_EVENTO), 0);
		sqlite3_step(stmt);
		log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Evento aggiornato in tabella EVENTI" << endl;
	} else {
		cout << "ERRORE modifica_evento: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	delete DATA_ORA_EVENTO;
	delete NEW_DATA_ORA_EVENTO;
	
	return;
}

void cancella_evento() {
	
	int ID_PERSONA = 0;
	int ID_TIPO_EVENTO = 0;
	char *DATA_ORA_EVENTO = new char[DIM];
	
	cout << "Eliminazione evento: " << endl;
	
	cout << "ID persona da cui eliminare evento: ";
	cin >> ID_PERSONA;
	while(cin.get()!='\n');
	
	cout << "ID tipo evento da eliminare: ";
	cin >> ID_TIPO_EVENTO;
	while(cin.get()!='\n');
	
	cout << "Data/ora evento da eliminare: ";
	cin.getline(DATA_ORA_EVENTO,DIM);
	
	comando = "DELETE FROM EVENTI WHERE ID_PERSONA = ? AND ID_TIPO_EVENTO = ? AND DATA_ORA_EVENTO = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, ID_PERSONA);
		sqlite3_bind_int(stmt, 2, ID_TIPO_EVENTO);
		sqlite3_bind_text(stmt, 3, DATA_ORA_EVENTO, strlen(DATA_ORA_EVENTO), 0);
		sqlite3_step(stmt);
		log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Evento cancellato da tabella EVENTI" << endl;
	} else {
		cout << "ERRORE cancella_evento: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	delete DATA_ORA_EVENTO;
	
	return;
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
	
	cout << "PERSONA\t\tTIPO EVENTO\t\DATA-ORA" << endl;
	
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
	while(cin.get()!='\n');
	
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
	while(cin.get()!='\n');
	
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

void log_query(const char* txt) {
	ofstream log;
	log.open("query.log",ios::app); 
	if (!log.is_open()) {
		cout << "Impossibile creare il log!" << endl;
		return;
	}
	log << orario() << " - " << txt << endl;
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
	return str;
}
