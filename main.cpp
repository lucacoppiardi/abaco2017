#include <iostream>
using namespace std;
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i < argc; i++) {
	  cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
   }
   cout << endl;
   return 0;
}

int main(int argc, char **argv)
{
	char *zErrMsg = 0;
	int rc;
	sqlite3 *database;
	char *comando;
	
	rc = sqlite3_open("database.sqlite", &database);
	if (rc) {
		cout << "Errore nell'apertura del database: " << sqlite3_errmsg(database) << endl;
		return 1;
	} else {
		cout << "Database aperto" << endl;
	}
	
	comando = "CREATE TABLE PERSONE (ID_PERSONA INTEGER, NOME STRING, COGNOME STRING);";
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if ( rc != SQLITE_OK ) {
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	} else {
		cout << "Tabella creata" << endl;
	}
	
	comando = "CREATE TABLE TIPO_EVENTO (ID_TIPO_EVENTO INTEGER, DESCRIZIONE STRING);";
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if ( rc != SQLITE_OK ) {
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	} else {
		cout << "Tabella creata" << endl;
	}
	
	comando = "CREATE TABLE EVENTI (ID_PERSONA INTEGER, ID_TIPO_EVENTO INTEGER, DATA_ORA_EVENTO);";
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if ( rc != SQLITE_OK ) {
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	} else {
		cout << "Tabella creata" << endl;
	}
	
	comando = "INSERT INTO PERSONE (ID_PERSONA, NOME, COGNOME) VALUES (1000, 'SARA', 'CINESCA');";
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	} else {
		cout << "Dati inseriti in tabella" << endl;
	}
	
	comando = "SELECT * FROM PERSONE";
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		cout << "ERRORE: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	} else {
		cout << "Dati letti" << endl;
	}
	
	sqlite3_close(database);
	return 0;
}