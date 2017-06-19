#include <iostream>
#include <sqlite3.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <ctime>
using namespace std;


#define DIM 100

char *zErrMsg = 0;
int rc; // return code
sqlite3 *database;
const char *comando;
sqlite3_stmt *stmt;
const char *pzTest;


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	
	for(i = 0; i < argc; i++) {
		cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
	}
	cout << endl;
	
	return 0;
}

class Evento{
	private : 
					int ID_PERSONA;
					int ID_TIPO_EVENTO;
					char* DATA_ORA_EVENTO;
	public	:
					Evento(){}
					Evento(int ID_PERSONA,int ID_TIPO_EVENTO,char* Descrizione);
					void SetID_PERSONA(int ID_PERSONA) {this->ID_PERSONA = ID_PERSONA;}
					void SetID_TIPO_EVENTO(int ID_TIPO_EVENTO) {this->ID_TIPO_EVENTO = ID_TIPO_EVENTO;}
					void SetDATA_ORA_EVENTO(char* DATA_ORA_EVENTO) {this->DATA_ORA_EVENTO = DATA_ORA_EVENTO;}
					char* GetDATA_ORA_EVENTO() {return DATA_ORA_EVENTO;}
					int GetID_PERSONA()  {return ID_PERSONA;}
					int GetID_TIPO_EVENTO()  {return ID_TIPO_EVENTO;}
					void stampa();
					void aggiungi_evento();
					void modifica_evento();
					void cancella_evento();
};

Evento :: Evento(int ID_PERSONA,int ID_TIPO_EVENTO,char* DATA_ORA_EVENTO){
	this->ID_PERSONA=ID_PERSONA;
	this->ID_TIPO_EVENTO=ID_TIPO_EVENTO;
	this->DATA_ORA_EVENTO=DATA_ORA_EVENTO;
}

void Evento :: stampa(){
	cout<<"Stampa Evento"<<endl;
	cout<<"ID PERSONA:"<<this->GetID_PERSONA()<<endl;
	cout<<"ID TIPO EVENTO:"<<this->GetID_TIPO_EVENTO()<<endl;
	cout<<"DATA E ORA EVENTO:"<<this->GetDATA_ORA_EVENTO()<<endl;
}

void Evento :: aggiungi_evento(){
	cout << "Inserimento evento: " << endl;
	
	comando = "INSERT INTO EVENTI (ID_PERSONA, ID_TIPO_EVENTO, DATA_ORA_EVENTO) VALUES (?,?,?)";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1,this->GetID_PERSONA());
		sqlite3_bind_int(stmt, 2, this->GetID_TIPO_EVENTO());
		sqlite3_bind_text(stmt, 3, this->GetDATA_ORA_EVENTO(),strlen(this->GetDATA_ORA_EVENTO()), 0);
		sqlite3_step(stmt);
		//log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Evento inserito in tabella EVENTI" << endl;
	} else {
		cout << "ERRORE aggiungi_evento: " << zErrMsg << endl;
		//log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void Evento :: modifica_evento(){
	int  NEW_ID_TIPO_EVENTO;
	char* NEW_DATA_ORA_EVENTO = new char[DIM];
	
	cout << "Modifica evento: " << endl;
	
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
		sqlite3_bind_int(stmt, 3,this->GetID_PERSONA());
		sqlite3_bind_int(stmt, 4,this->GetID_TIPO_EVENTO());
		sqlite3_bind_text(stmt, 5, this->GetDATA_ORA_EVENTO(), strlen(this->GetDATA_ORA_EVENTO()), 0);
		sqlite3_step(stmt);
		//log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Evento aggiornato in tabella EVENTI" << endl;
	} else {
		cout << "ERRORE modifica_evento: " << zErrMsg << endl;
		//log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	
	this->SetDATA_ORA_EVENTO(NEW_DATA_ORA_EVENTO);
	this->SetID_TIPO_EVENTO(NEW_ID_TIPO_EVENTO);
	delete NEW_DATA_ORA_EVENTO;
}
void Evento ::  cancella_evento(){
	cout << "Eliminazione evento: " << endl;
	
	comando = "DELETE FROM EVENTI WHERE ID_PERSONA = ? AND ID_TIPO_EVENTO = ? AND DATA_ORA_EVENTO = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, this->GetID_PERSONA());
		sqlite3_bind_int(stmt, 2, this->GetID_TIPO_EVENTO());
		sqlite3_bind_text(stmt, 3, this->GetDATA_ORA_EVENTO(), strlen(this->GetDATA_ORA_EVENTO()), 0);
		sqlite3_step(stmt);
		cout<<sqlite3_expanded_sql(stmt);
		sqlite3_finalize(stmt);
		cout << "Evento cancellato da tabella EVENTI" << endl;
	} else {
		cout << "ERRORE cancella_evento: " << zErrMsg << endl;
		//log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
}