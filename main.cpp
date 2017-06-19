int main(){
rc = sqlite3_open("database.sqlite", &database);
	if (rc != SQLITE_OK) {
		cout << "ERRORE nell'apertura del database: " << sqlite3_errmsg(database) << endl;
		//log_query("ERRORE nell'apertura del database: ");
		//log_query(sqlite3_errmsg(database));
		return -1;
	} else {
		cout << "Database aperto" << endl << endl;
		//log_query("Database aperto");
	}
	
	comando = "CREATE TABLE IF NOT EXISTS PERSONE (ID_PERSONA INTEGER, NOME STRING, COGNOME STRING)";
	//log_query(comando);
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		cout << "ERRORE tabella PERSONE: " << zErrMsg << endl;
		//log_query("ERRORE tabella PERSONE: ");
//		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	} else {
		cout << "Tabella PERSONE pronta" << endl;
	}

	comando = "CREATE TABLE IF NOT EXISTS TIPO_EVENTO (ID_TIPO_EVENTO INTEGER, DESCRIZIONE STRING)";
//	log_query(comando);
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		cout << "ERRORE tabella TIPO_EVENTO: " << zErrMsg << endl;
		//log_query("ERRORE tabella TIPO_EVENTO: ");
		//log_query(zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	} else {
		cout << "Tabella TIPO_EVENTO pronta" << endl;
	}
	
	comando = "CREATE TABLE IF NOT EXISTS EVENTI (ID_PERSONA INTEGER, ID_TIPO_EVENTO INTEGER, DATA_ORA_EVENTO DATETIME)";
	//log_query(comando);
	rc = sqlite3_exec(database, comando, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)  {
		cout << "ERRORE tabella EVENTI: " << zErrMsg << endl;
		//log_query("ERRORE tabella EVENTI:");
		//log_query(zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	} 
	else {
		cout << "Tabella EVENTI pronta" << endl;
	}
	

//PROVA LE CLASSI QUI_-------------------------------------------//////////////////////////


rc = sqlite3_close(database);
	if (rc != SQLITE_OK) {
		cout << "ERRORE nella chiusura del database: " << sqlite3_errmsg(database) << endl;
		//log_query("ERRORE nella chiusura del database: ");
		//log_query(zErrMsg);
		return -1;
	} else {
		cout << "Database chiuso" << endl;
		//log_query("Database chiuso");
	}
	
return 0;




}
