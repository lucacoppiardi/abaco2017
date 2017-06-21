#include "Evento.h"
#include "main.h"
#include <cstring>

Evento :: Evento(int ID_PERSONA,int ID_TIPO_EVENTO,string DATA_ORA_EVENTO){
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
		sqlite3_bind_text(stmt, 3, this->GetDATA_ORA_EVENTO().c_str(),strlen(this->GetDATA_ORA_EVENTO().c_str()), 0);
		sqlite3_step(stmt);
		log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Evento inserito in tabella EVENTI" << endl;
	} else {
		cout << "ERRORE aggiungi_evento: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void Evento :: modifica_evento(){
	int  NEW_ID_TIPO_EVENTO;
	string NEW_DATA_ORA_EVENTO;
	
	cout << "Modifica evento: " << endl;
	
	cout << "Nuovo ID tipo evento: ";
	cin >> NEW_ID_TIPO_EVENTO;
	while(cin.get()!='\n');
	
	cout << "Nuova data/ora evento: ";
	getline(cin,NEW_DATA_ORA_EVENTO);
	
	comando = "UPDATE EVENTI SET ID_TIPO_EVENTO = ?, DATA_ORA_EVENTO = ? WHERE ID_PERSONA = ? AND ID_TIPO_EVENTO = ? AND DATA_ORA_EVENTO = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, NEW_ID_TIPO_EVENTO);
		sqlite3_bind_text(stmt, 2, NEW_DATA_ORA_EVENTO.c_str(), strlen(NEW_DATA_ORA_EVENTO.c_str()), 0);
		sqlite3_bind_int(stmt, 3,this->GetID_PERSONA());
		sqlite3_bind_int(stmt, 4,this->GetID_TIPO_EVENTO());
		sqlite3_bind_text(stmt, 5, this->GetDATA_ORA_EVENTO().c_str(), strlen(this->GetDATA_ORA_EVENTO().c_str()), 0);
		sqlite3_step(stmt);
		log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Evento aggiornato in tabella EVENTI" << endl;
	} else {
		cout << "ERRORE modifica_evento: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
	
	
	this->SetDATA_ORA_EVENTO(NEW_DATA_ORA_EVENTO);
	this->SetID_TIPO_EVENTO(NEW_ID_TIPO_EVENTO);
	cout<<this->GetDATA_ORA_EVENTO()<<endl;
}
void Evento ::  cancella_evento(){
	cout << "Eliminazione evento: " << endl;
	
	comando = "DELETE FROM EVENTI WHERE ID_PERSONA = ? AND ID_TIPO_EVENTO = ? AND DATA_ORA_EVENTO = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, this->GetID_PERSONA());
		sqlite3_bind_int(stmt, 2, this->GetID_TIPO_EVENTO());
		sqlite3_bind_text(stmt, 3, this->GetDATA_ORA_EVENTO().c_str(), strlen(this->GetDATA_ORA_EVENTO().c_str()), 0);
		sqlite3_step(stmt);
		log_query(sqlite3_expanded_sql(stmt));
		sqlite3_finalize(stmt);
		cout << "Evento cancellato da tabella EVENTI" << endl;
	} else {
		cout << "ERRORE cancella_evento: " << zErrMsg << endl;
		log_query(zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
