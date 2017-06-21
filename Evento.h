#include <iostream>
using namespace std;

class Evento{
	private : 
					int ID_PERSONA;
					int ID_TIPO_EVENTO;
					string DATA_ORA_EVENTO;
	public	:
					Evento(){}
					Evento(int ID_PERSONA,int ID_TIPO_EVENTO,string DATA_ORA_EVENTO);
					void SetID_PERSONA(int ID_PERSONA) {this->ID_PERSONA = ID_PERSONA;}
					void SetID_TIPO_EVENTO(int ID_TIPO_EVENTO) {this->ID_TIPO_EVENTO = ID_TIPO_EVENTO;}
					void SetDATA_ORA_EVENTO(const string& DATA_ORA_EVENTO) {this->DATA_ORA_EVENTO = DATA_ORA_EVENTO;}
					const string& GetDATA_ORA_EVENTO() const {return DATA_ORA_EVENTO;}
					int GetID_PERSONA()  {return ID_PERSONA;}
					int GetID_TIPO_EVENTO()  {return ID_TIPO_EVENTO;}
					void stampa();
					void aggiungi_evento();
					void modifica_evento();
					void cancella_evento();
};
