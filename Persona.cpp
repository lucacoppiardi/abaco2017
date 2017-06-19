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

class Persona{
	private:
			int ID_PERSONA;
			char* NOME;
			char* COGNOME;
	public:
			Persona(){}
			Persona(int ID_PERSONA,char* NOME,char* COGNOME);
			void setNome(char* NOME){this->NOME=NOME;} 
			void setCognome(char* COGNOME){this->COGNOME=COGNOME;}
			void setID_PERSONA(int ID_PERSONA){this->ID_PERSONA=ID_PERSONA;}
			char* getNome(){return NOME;}
			char* getCognome(){return COGNOME;}
			int getID_PERSONA(){return ID_PERSONA;}
			void stampa();
			void aggiungi_persona(); 
			void modifica_persona();
			void cancella_persona();
};

Persona :: Persona(int ID_PERSONA,char* NOME,char* COGNOME){
	this->ID_PERSONA=ID_PERSONA;
	this->NOME=NOME;
	this->COGNOME=COGNOME;
}

void Persona :: stampa(){
	cout<<"STAMPA PERSONA"<<endl;
	cout<<"ID PERSONA:"<<ID_PERSONA<<endl;
	cout<<"NOME:"<<NOME<<endl;
	cout<<"COGNOME:"<<COGNOME<<endl;
}

void Persona::aggiungi_persona(){
	    cout << "Inserimento persona: " << endl;
	    comando = "INSERT INTO PERSONE (ID_PERSONA, NOME, COGNOME) VALUES (?,?,?)";
	    rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	    if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1,this->getID_PERSONA());
		sqlite3_bind_text(stmt, 2, this->getNome(), strlen(this->getNome()), 0);
		sqlite3_bind_text(stmt, 3,this->getCognome(), strlen(this->getCognome()), 0);
		sqlite3_step(stmt);
		//log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Persona n." << this->getID_PERSONA()<< " inserita in tabella PERSONE" << endl;
	     } else {
		   cout << "ERRORE aggiungi_persona: " << zErrMsg << endl;
		   //log_query(zErrMsg);
		   sqlite3_free(zErrMsg);
		}
	 
}

void Persona :: modifica_persona(){
	cout << "Modifica persona: " << endl;

	char* nomeNuovo = new char[DIM];
	char* cognomeNuovo = new char[DIM];
	
	cout << "Nuovo nome: ";
	cin.getline(nomeNuovo,DIM);
    
	
	cout << "Nuovo cognome: ";
	cin.getline(cognomeNuovo,DIM);
	
	this->setNome(nomeNuovo);
	this->setCognome(cognomeNuovo);
	
	comando = "UPDATE PERSONE SET NOME = ?, COGNOME = ? WHERE ID_PERSONA = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1,this->getNome(), strlen(this->getNome()), 0);
		sqlite3_bind_text(stmt, 2, this->getCognome(), strlen(this->getCognome()), 0);
		sqlite3_bind_int(stmt, 3,this->getID_PERSONA());
		sqlite3_step(stmt);
		//log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Persona " << this->getID_PERSONA() << " aggiornata in tabella PERSONE" << endl;
	} else {
		cout << "ERRORE modifica_persona: " << zErrMsg << endl;
		//log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	delete nomeNuovo;
	delete cognomeNuovo;
}

void Persona :: cancella_persona(){
	cout << "Eliminazione persona: " << endl;

	comando = "DELETE FROM PERSONE WHERE ID_PERSONA = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, this->getID_PERSONA());
		sqlite3_step(stmt);
		//log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Persona n." << this->getID_PERSONA ()<< " cancellata da tabella PERSONE" << endl;
	} else {
		cout << "ERRORE cancella_persona: " << zErrMsg << endl;
		//log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
