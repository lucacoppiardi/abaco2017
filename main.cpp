#include <iostream>
using namespace std;
#include <sqlite3.h>
#include <cstdio>
#include <cstring>

char *zErrMsg = 0;
int rc; // return code
sqlite3 *database;
const char *comando;
sqlite3_stmt *stmt;
const char *pzTest;

int id = 0;
char *nome = new char[100];
char *cognome = new char[100];

void menu();
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
void aggiungi_persona();
void modifica_persona();
void cancella_persona();

int main(int argc, char **argv) {
	rc = sqlite3_open("database.sqlite", &database);
	if (rc) {
		cout << "Errore nell'apertura del database: " << sqlite3_errmsg(database) << endl;
		return 1;
	} else {
		cout << "Database aperto" << endl;
	}
	
	comando = "CREATE TABLE IF NOT EXISTS PERSONE (ID_PERSONA INTEGER, NOME STRING, COGNOME STRING);";
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if ( rc != SQLITE_OK ) {
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	} else {
		cout << "Tabella PERSONE pronta" << endl;
	}
	
	comando = "CREATE TABLE IF NOT EXISTS TIPO_EVENTO (ID_TIPO_EVENTO INTEGER, DESCRIZIONE STRING);";
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if ( rc != SQLITE_OK ) {
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	} else {
		cout << "Tabella TIPO_EVENTO pronta" << endl;
	}
	
	comando = "CREATE TABLE IF NOT EXISTS EVENTI (ID_PERSONA INTEGER, ID_TIPO_EVENTO INTEGER, DATA_ORA_EVENTO DATETIME);";
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if ( rc != SQLITE_OK ) {
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
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
	
	cout << "Lettura dati: " << endl;
	comando = "SELECT * FROM PERSONE";
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	} else {
		cout << "Fine lettura" << endl;
	}
	
	sqlite3_close(database);
	
	delete nome;
	delete cognome;
	
	return 0;
}

void menu() {
	int scelta = 0;
	
	do {
		
		cout << "Scelta: " << endl;
		cout << "0. Esci" << endl;
		cout << "1. Aggiungi persona" << endl;
		cout << "2. Modifica persona" << endl;
		cout << "3. Cancella persona" << endl;
		cin >> scelta;
		
		switch (scelta) {
			case 1:
				aggiungi_persona();
				break;
			case 2:
				modifica_persona();
				break;
			case 3:
				cancella_persona();
				break;
			
			default:
				return;
		}
		
	} while (scelta!=0);
	
	return;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i < argc; i++) {
	  cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
   }
   return 0;
}

void aggiungi_persona () {
	cout << "ID: ";
	cin >> id;
	cout << "Nome: ";
	cin >> nome;
	cout << "Cognome: ";
	cin >> cognome;
	comando = "INSERT INTO PERSONE (ID_PERSONA, NOME, COGNOME) VALUES (?,?,?)";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if( rc == SQLITE_OK ){
		sqlite3_bind_int(stmt, 1, id);
		sqlite3_bind_text(stmt, 2, nome, strlen(nome), 0);
		sqlite3_bind_text(stmt, 3, cognome, strlen(cognome), 0);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		cout << "Dati inseriti in tabella PERSONE" << endl;
	} else {
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return;
}

void modifica_persona () {
	cout << "ID: ";
	cin >> id;
	cout << "Nome: ";
	cin >> nome;
	cout << "Cognome: ";
	cin >> cognome;
	comando = "UPDATE PERSONE SET NOME = ?, COGNOME = ? WHERE ID_PERSONA = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if( rc == SQLITE_OK ){
		sqlite3_bind_text(stmt, 1, nome, strlen(nome), 0);
		sqlite3_bind_text(stmt, 2, cognome, strlen(cognome), 0);
		sqlite3_bind_int(stmt, 3, id);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		cout << "Persona n." << id << " aggiornata in tabella PERSONE" << endl;
	} else {
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}

void cancella_persona () {
	cout << "ID: ";
	cin >> id;
	comando = "DELETE FROM PERSONE WHERE ID_PERSONA = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if( rc == SQLITE_OK ){
		sqlite3_bind_int(stmt, 1, id);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		cout << "Persona n." << id << " cancellata da tabella PERSONE" << endl;
	} else {
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
