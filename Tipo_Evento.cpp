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

class Tipo_Evento {
	private :
		 int ID_TIPO_EVENTO;
		 char* Descrizione;
	public  :
		 Tipo_Evento(){}
		 Tipo_Evento(int ID_TIPO_EVENTO,char* Descrizione);
		 void setDescrizione(char* Descrizione) {this->Descrizione = Descrizione;}
		 void setID_TIPO_EVENTO(int ID_TIPO_EVENTO) {this->ID_TIPO_EVENTO =ID_TIPO_EVENTO;}
		 char* getDescrizione() {return Descrizione;}
		 int getID_TIPO_EVENTO()  {return ID_TIPO_EVENTO;}
		 void stampa();
		 void aggiungi_tipo_evento();
		 void modifica_tipo_evento();
		 void cancella_tipo_evento();
};

Tipo_Evento :: Tipo_Evento (int ID_TIPO_EVENTO,char* Descrizione){
	this->ID_TIPO_EVENTO=ID_TIPO_EVENTO;
	this->Descrizione=Descrizione;
}

void Tipo_Evento :: stampa(){
	cout<<"STAMPA TIPO EVENTO"<<endl;
	cout<<"ID TIPO EVENTO:"<<this->getID_TIPO_EVENTO()<<endl;
	cout<<"DESCRIZIONE:"<<this->getDescrizione()<<endl;
}

void Tipo_Evento :: aggiungi_tipo_evento(){
	cout << "Aggiunta tipo evento: " << endl;
	
	comando = "INSERT INTO TIPO_EVENTO (ID_TIPO_EVENTO, DESCRIZIONE) VALUES (?,?)";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1,this->getID_TIPO_EVENTO());
		sqlite3_bind_text(stmt, 2, this->getDescrizione(), strlen(this->getDescrizione()), 0);
		sqlite3_step(stmt);
		//log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Tipo evento " << this->getID_TIPO_EVENTO()<< " inserito in tabella TIPO_EVENTO" << endl;
	} else {
		cout << "ERRORE aggiungi_tipo_evento: " << zErrMsg << endl;
		//log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void Tipo_Evento :: modifica_tipo_evento(){
	int idNuovo = 0;
	char *descrizioneNuova = new char[DIM];
	
	cout << "Modifica tipo evento: " << endl;
		
	cout << "Nuova descrizione: ";
	cin.getline(descrizioneNuova,DIM);
	
	this->setDescrizione(descrizioneNuova);
	
	comando = "UPDATE TIPO_EVENTO SET DESCRIZIONE = ? WHERE ID_TIPO_EVENTO = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1,this->getDescrizione(), strlen(this->getDescrizione()), 0);
		sqlite3_bind_int(stmt, 2, this->getID_TIPO_EVENTO());
		sqlite3_step(stmt);
		//log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Tipo evento " << this->getID_TIPO_EVENTO()<< " aggiornato in tabella TIPO_EVENTI" << endl;
	} else {
		cout << "ERRORE modifica_tipo_evento: " << zErrMsg << endl;
		//log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void Tipo_Evento :: cancella_tipo_evento(){
	cout << "Eliminazione tipo evento: " << endl;
	
	comando = "DELETE FROM TIPO_EVENTO WHERE ID_TIPO_EVENTO = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, this->getID_TIPO_EVENTO());
		sqlite3_step(stmt);
		//log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Tipo evento " << this->getID_TIPO_EVENTO() << " cancellato da tabella TIPO_EVENTO" << endl;
	} else {
		cout << "ERRORE cancella_tipo_evento: " << zErrMsg << endl;
		//log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
}