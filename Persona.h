#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
using namespace std;

class Persona{
	private:
			int ID_PERSONA;
			string NOME;
			string COGNOME;
	public:
			Persona(){};
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
#endif