#define DIM 100

class Tipo_Evento {
	private :
					int ID_TIPO_EVENTO;
					string Descrizione;
public:
				Tipo_Evento(){}
				Tipo_Evento(int ID_TIPO_EVENTO,string Descrizione);
				void setID_TIPO_EVENTO(int ID_TIPO_EVENTO) {this->ID_TIPO_EVENTO =ID_TIPO_EVENTO;}
				void setDescrizione(const string& Descrizione) {this->Descrizione = Descrizione;}
				const string& getDescrizione() const {return Descrizione;}
				int getID_TIPO_EVENTO()  {return ID_TIPO_EVENTO;}
				void stampa();
				void aggiungi_tipo_evento();
				void modifica_tipo_evento();
				void cancella_tipo_evento();
};