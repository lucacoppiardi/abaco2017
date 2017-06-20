#include <Persona.h>
 //class Sqlite3{
//	private:
//			char *zErrMsg;
//			int rc; // return code
//			sqlite3 *database;
//			char *comando;
//			sqlite3_stmt *stmt;
//			char *pzTest;
//	public:
//			Sqlite3(){}
//			Sqlite3(char *zErrMsg,int rc,sqlite3 *database,char *comando,sqlite3_stmt *stmt,char *pzTest);
//			void SetComando(char* comando) {this->comando = comando;}
//			void SetDatabase(sqlite3* database) {this->database = database;}
//			void SetPzTest(char* pzTest) {this->pzTest = pzTest;}
//			void SetRc(int rc) {this->rc = rc;}
//			void SetStmt(sqlite3_stmt* stmt) {this->stmt = stmt;}
//			void SetZErrMsg(char* zErrMsg) {this->zErrMsg = zErrMsg;}
//			char* GetComando() {return comando;}
//			sqlite3* GetDatabase() {return database;}
//			char* GetPzTest() {return pzTest;}
//			int GetRc() const {return rc;}
//			sqlite3_stmt* GetStmt() {return stmt;}
//			char* GetZErrMsg() {return zErrMsg;}
//};
//
//Sqlite3 :: Sqlite3(char *zErrMsg,int rc,sqlite3 *database,char *comando,sqlite3_stmt *stmt,char *pzTest){
//		this->zErrMsg = zErrMsg;
//		this->rc = rc;
//		this->database = database;
//		this->comando = comando;
//		this->stmt = stmt;
//		this->pzTest = pzTest;
//}
//

/*
class Persona{
	private:
			int ID_PERSONA;
			string NOME;
			string COGNOME;
	public:
			Persona(){}
			Persona(int ID_PERSONA,string  NOME,string COGNOME);
			void setCognome(const string& COGNOME) {this->COGNOME = COGNOME;}
			void setID_PERSONA(int ID_PERSONA) {this->ID_PERSONA = ID_PERSONA;}
			void setNome(const string& NOME) {this->NOME = NOME;}
			const string& getCognome() const {return COGNOME;}
			int getID_PERSONA() const {return ID_PERSONA;}
			const string& getNome() const {return NOME;}
			void stampa();
			void aggiungi_persona(); 
			void modifica_persona();
			void cancella_persona();
};
*/
Persona :: Persona(int ID_PERSONA,string NOME,string COGNOME){
	this->ID_PERSONA=ID_PERSONA;
	this->NOME=NOME;
	this->COGNOME=COGNOME;
}

void Persona :: stampa(){
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
			sqlite3_bind_text(stmt, 2, this->getNome().c_str(), strlen(this->getNome().c_str()), 0);
			sqlite3_bind_text(stmt, 3,this->getCognome().c_str(), strlen(this->getCognome().c_str()), 0);
			sqlite3_step(stmt);
			//log_query(sqlite3_expanded_sql(stmt));
			sqlite3_finalize(stmt);
			cout << "Persona n." << this->getID_PERSONA()<< " inserita in tabella PERSONE" << endl;
		} else {
			cout << "ERRORE aggiungi_persona: " << zErrMsg << endl;
			//og_query(zErrMsg);
			sqlite3_free(zErrMsg);
		}
	 
}

void Persona :: modifica_persona(){
	cout << "Modifica persona: " << endl;
	
	string nuovoNome;
	string nuovoCognome;
	
	cout << "Nuovo nome: ";
	getline(cin,nuovoNome);
    
	
	cout << "Nuovo cognome: ";
	getline(cin,nuovoCognome);

	this->setNome(nuovoNome);
	this->setCognome(nuovoCognome);
	
	comando = "UPDATE PERSONE SET NOME = ?, COGNOME = ? WHERE ID_PERSONA = ?";
	rc = sqlite3_prepare(database, comando, strlen(comando), &stmt, &pzTest);
	
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1,this->getNome().c_str(), strlen(this->getNome().c_str()), 0);
		sqlite3_bind_text(stmt, 2, this->getCognome().c_str(), strlen(this->getCognome().c_str()), 0);
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

