#include <iostream>
using namespace std;
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#include <fstream>

//#define BENCH_ITERATIONS 1000000

bool checkPalindrome_v1(const string& theString); // ciclo for
bool checkPalindrome_v2(const string& theString); // stringa iteratori inversi
bool checkPalindrome_v3(const string& theString); // equal
//bool checkPalindrome_exv3 (const string& theString); // equal non ottimizzato
int doTest(const vector<string>& toCheck, bool(*checkPalindromeFunz)(const string&)); // benchmark
void salva_dati_CSV(int t1, int t2, int t3); // salva dati in un file CSV
void generaHeadHTML();
void insert_in_table(vector<int> tempi);
void chiudiHTML();
void genera_immagine_grafico(); // genera grafico con gnuplot

unsigned int BENCH_ITERATIONS = 100000;

int main (int argc, char **argv) {
	
//	// PROVA DI TUTTE LE FUNZIONI SU UNA SOLA STRINGA
//	string str;
//	cout << "Inserire stringa palindroma: ";
//	cin >> str;
//	cout << "Stringa inserita: " << str <<endl;
//	checkPalindrome_v1(str);
//	checkPalindrome_v2(str);
//	checkPalindrome_equals(str);
	
	vector<string> v1;
	
	v1.push_back("ciao"); // corta
	v1.push_back("anna"); // corta palindroma
	v1.push_back("inipotinonavevanotopi"); // lunga
	v1.push_back("itopinonavevanonipoti"); // lunga palindroma
	
//	// PROVA DI TUTTE LE FUNZIONI SU UN VECTOR DI STRING
//	for (unsigned int i=0;i<v1.size(); i++) {
//		cout<<v1[i]<<endl;
//	}
//	
//	cout<<endl<<"v1"<<endl;
//	for (unsigned int i=0;i<v1.size();i++) {
//		checkPalindrome_v1(v1[i]);
//	}
//	
//	cout<<endl<<"v2"<<endl;
//	for (unsigned int i=0;i<v1.size();i++) {
//		checkPalindrome_v2(v1[i]);
//	}
//	
//	cout<<endl<<"v3"<<endl;
//	for (unsigned int i=0;i<v1.size();i++) {
//		if (checkPalindrome_v3(v1[i]) == true) {
//			cout << v1[i] << " e' palindroma" << endl;
//		} else {
//			cout << v1[i] << " non e' palindroma" << endl;
//		}
//	}
//	
//	cout<<endl;
	
//	// BENCHMARK
//	cout<<"Premere invio per iniziare il benchmark...";
//	cin.get();
//	cout<<"BENCH_ITERATIONS = "<<BENCH_ITERATIONS<<endl;
	
//	// BENCHMARK (SENZA FUNZIONE DoTest)
//	bool test1 = true;
//	bool ritorno1 = false;
//	int count=0;
//	clock_t t1_start = clock();
//	//cout<<endl<<"v1"<<endl;
//	for(unsigned int i = 0; i < BENCH_ITERATIONS; i++) {
//		for (unsigned int j=0;j<v1.size();j++) {
//			ritorno1=checkPalindrome_v1(v1[j]);
//			if (ritorno1==test1) {
//				count++;
//			}
//			/*
//			if (checkPalindrome_v1(v1[j])==true) {
//				cout << theString << " e' palindroma" << endl;
//			} else {
//				cout << theString << " non e' palindroma" << endl;
//			}
//			*/
//		}
//	}
//	clock_t t1_stop = clock();
//	
//	//cout<<endl<<"v2"<<endl;
//	clock_t t2_start = clock();
//	for(unsigned int i = 0; i < BENCH_ITERATIONS; i++) {
//		for (unsigned int j=0;j<v1.size();j++) {
//			checkPalindrome_v2(v1[j]);
//			/*
//			if (checkPalindrome_v2(v1[j]);==true) {
//				cout << theString << " e' palindroma" << endl;
//			} else {
//				cout << theString << " non e' palindroma" << endl;
//			}
//			*/
//		}
//	}
//	clock_t t2_stop = clock();
//
//	//cout<<endl<<"v3"<<endl;
//	bool test3 = true;
//	bool ritorno3 = false;
//	clock_t t3_start = clock();
//	for(unsigned int i = 0; i < BENCH_ITERATIONS; i++) {
//		for (unsigned int j=0;j<v1.size();j++) {
//			ritorno3=checkPalindrome_v3(v1[j]);
//			if (ritorno3==test3) {
//				count++;
//			}
//			/*
//			if (checkPalindrome_v3(v1[j]) == true) {
//				cout << v1[j] << " e' palindroma" << endl;
//			} else {
//				cout << v1[j] << " non e' palindroma" << endl;
//			}
//			*/
//		}
//	}
//	clock_t t3_stop = clock();
//
//	double runTimeMillisec_1 = (((double)(t1_stop - t1_start))/CLOCKS_PER_SEC)*1000;
//	double runTimeMillisec_2 = (((double)(t2_stop - t2_start))/CLOCKS_PER_SEC)*1000;
//	double runTimeMillisec_3 = (((double)(t3_stop - t3_start))/CLOCKS_PER_SEC)*1000;
	
	// BENCHMARK - FUNZIONE DoTest
	
	ofstream filecsv; // prepariamo il file csv prima che vengano salvati i nuovi tempi
	filecsv.open("benchmark.csv");
	if (!filecsv.is_open()) {
		cout << "Problemi con il file CSV!" << endl;
		return 1;
	}
	filecsv << "BENCH_ITERATIONS;METODO1;METODO2;METODO3\n"; 
	filecsv.close();
	
	int runTimeMillisec_1; 
	int runTimeMillisec_2; 
	int runTimeMillisec_3;
		
	generaHeadHTML();
	
	for (int i = 0; i < 3; i++) {
		if (i==1) {
			BENCH_ITERATIONS*=10;
		} else if (i==2) {
			BENCH_ITERATIONS*=2;
		}
		cout << "BENCH_ITERATIONS = " << BENCH_ITERATIONS << endl;
		runTimeMillisec_1 = doTest(v1, checkPalindrome_v1);
		runTimeMillisec_2 = doTest(v1, checkPalindrome_v2);
		runTimeMillisec_3 = doTest(v1, checkPalindrome_v3);
		cout << "T1: " << runTimeMillisec_1 << endl;
		cout << "T2: " << runTimeMillisec_2 << endl;
		cout << "T3: " << runTimeMillisec_3 << endl;
		salva_dati_CSV(runTimeMillisec_1, runTimeMillisec_2, runTimeMillisec_3);
		vector<int> tempi;
		tempi.push_back(runTimeMillisec_1);
		tempi.push_back(runTimeMillisec_2);
		tempi.push_back(runTimeMillisec_3);
		insert_in_table(tempi);
	}
	
	genera_immagine_grafico();
	chiudiHTML();
	
	return 0;
}

// VERSIONE 1 - CONTROLLA CARATTERE PER CARATTERE LE STRINGHE
bool checkPalindrome_v1 (const string& theString) {
	//cout << endl << "\tFunzione \"isPalindrome\":" << endl;
	int len = theString.length();
	//cout << "Lunghezza: " << len <<endl;
	bool palindroma = false;
	for (int i=0; i<len; i++) {
		if (theString[i]==theString[len-1-i]) {
			palindroma = true;
		} else {
			palindroma = false;
			return palindroma;
		}
		/* TEST
		cout<<" "<<i;
		cout<<" "<<len-1-i;
		cout<<" "<<palindroma;
		cout<<endl;
		*/
	}
	return palindroma;
}

// VERSIONE 2 - CONFRONTA LE STRINGHE COSTRUENDO LE STRINGHE INVERSE GRAZIE AGLI ITERATORI INVERSI
bool checkPalindrome_v2(const string& theString) {
	bool palindroma;
	//cout << endl << "\tIteratori:" << endl;
	if (theString == string(theString.rbegin(), theString.rend())) {
		palindroma=true;
	} else {
		palindroma=false;
	}
	return palindroma;
}

// VERSIONE 3 - METODO EQUAL
bool checkPalindrome_v3(const string& theString) {
	return equal(theString.begin(), theString.begin() + theString.size() / 2, theString.rbegin() );
}

/*bool checkPalindrome_exv3 (const string& theString) {
	bool palindroma;
	//cout << endl << "\tMetodo equals (STL):" << endl;
	if (equal(theString.begin(),theString.end(),theString.rbegin())) {
		cout<<"Palindroma"<<endl;
		palindroma=true;
	} else {
		cout<<"Non palindroma"<<endl;
		palindroma=false;
	}
	return palindroma;
}*/

// FUNZIONE BENCHMARK
int doTest(const vector<string>& toCheck, bool(*checkPalindromeFunz)(const string&)) {
	bool test = true;
	bool ritorno = false;
	int count = 0;
	clock_t t_start = clock();
	for(unsigned int i = 0; i < BENCH_ITERATIONS; i++) {
		for (unsigned int j = 0; j < toCheck.size(); j++) {
			ritorno = checkPalindromeFunz(toCheck[j]);
			if (ritorno == test) { // IL CICLO VIENE ESEGUITO
				count++;
			}
		}
	}
	clock_t t_stop = clock();
	int tempo = (((double)(t_stop - t_start))/CLOCKS_PER_SEC)*1000;
	cout<<"contatore di prova: "<<count<<endl; // CONTROLLIAMO CHE IL CICLO SIA STATO ESEGUITO
	count=0;
	return tempo;
}

void salva_dati_CSV(int t1, int t2, int t3) {
	cout << "Salvataggio tempi su un file CSV..." << endl;
	ofstream filecsv;
	filecsv.open("benchmark.csv",ios::app);
	if (!filecsv.is_open()) {
		cout << "Problemi con il file CSV!" << endl;
		return;
	}
	filecsv << BENCH_ITERATIONS << ";" << t1 << ";" << t2 << ";" << t3 <<"\n";
	filecsv.close();
	cout << "Dati salvati sul file CSV." << endl;
	return;
}

void generaHeadHTML() {
	cout << "Generazione prima parte pagina HTML e CSS..." << endl;
	ofstream pagina;
	pagina.open("benchmark.html"); 
	if (!pagina.is_open()) {
		cout << "Impossibile creare la pagina HTML!" << endl;
		return;
	}
	pagina << "<html>\n";
	pagina << "<head>\n";
	pagina << "\t<title>Benchmark</title>\n";
	pagina << "\t<link href=\"benchmark.css\" rel=\"stylesheet\" type=\"text/css\"></link>\n";
	pagina << "</head>\n";
	pagina << "<body>\n";
	pagina << "\t<h2>Benchmark</h2>\n";
	pagina << "\t<table>\n";
	pagina << "\t\t<tr>\n";
	pagina << "\t\t\t<th>Iterazioni</th>\n";
	pagina << "\t\t\t<th>T1</th>\n";
	pagina << "\t\t\t<th>T2</th>\n";
	pagina << "\t\t\t<th>T3</th>\n";
	pagina << "\t\t</tr>\n";
	pagina << "\t\t<tr>\n";
	pagina.close();
	cout << "Prima parte pagina HTML generata." << endl;
	
	ofstream stile;
	stile.open("benchmark.css");
	if (!stile.is_open()) {
		cout << "Impossibile creare il CSS!" << endl;
	}
	stile << "h2 {\n";
	stile << "\ttext-align:center\n";
	stile << "}\n";
	stile << "table {\n";
	stile << "\tborder-collapse: collapse;\n";
	stile << "\ttext-align:center;\n";
	stile << "\tmargin-left: auto;\n";
	stile << "\tmargin-right: auto;\n";
	stile << "}\n";
	stile << "table, th, td {\n";
	stile << "\tborder: 1px solid black;\n";
	stile << "}\n";
	stile << "th, td {\n";
	stile << "\tpadding: 15px;\n";
	stile << "}\n";
	stile << "img {\n";
	stile << "\tdisplay: block;\n";
	stile << "\tmargin: auto;\n";
	stile << "}\n";
	stile.close();
	cout << "Creato CSS." << endl;
	return;
}

void insert_in_table(vector<int> tempi) {
	cout << "Inserimento dati in tabella..." << endl;
	ofstream pagina;
	pagina.open("benchmark.html",ios::app);
	pagina << "\t\t<tr>\n";
	pagina << "\t\t\t<td>" << BENCH_ITERATIONS << "</td>\n";
	for (int i = 0; i < 3; i++) {
		pagina << "\t\t\t<td>" << tempi[i] << "</td>\n";
	}
	pagina << "\t\t</tr>\n";
	pagina.close();
	cout<<"Tabella aggiornata."<<endl;
	return;
}

void chiudiHTML() {
	cout << "Conclusione pagina HTML..." << endl;
	ofstream pagina;
	pagina.open("benchmark.html",ios::app);	
	pagina << "\t</table>\n";
	pagina << "\t<img src=\"grafico.png\" alt=\"gnuplot\">\n";
	pagina << "</body>\n";
	pagina << "</html>\n";
	pagina.close();
	cout << "Pagina HTML terminata." << endl;
	return;
}

void genera_immagine_grafico() {
	cout << "Generazione grafico..." << endl;
	ofstream comandi;
	comandi.open("comandi_gnuplot.txt");
	if (!comandi.is_open()) {
		cout << "Impossibile salvare i comandi di gnuplot!" << endl;
		return;
	}
	// Salvo i comandi da passare a Gnuplot in un file
	comandi << "set datafile separator \";\"\n";
	comandi << "set auto x\n";
	comandi << "set auto y\n";
	comandi << "set title \'Benchmark\'\n";
	comandi << "set ylabel \'Tempo esec. (millisec)\'\n";
	comandi << "set xlabel \'Iterazioni\'\n";
	comandi << "set key left\n";
	comandi << "color1 = \"#99ffff\"; color2 = \"#4671d5\"; color3 = \"#ff0000\";\n";
	comandi << "set style data histogram\n";
	comandi << "set style histogram cluster gap 1\n";
	comandi << "set style fill solid border -1\n";
	comandi << "set xtic scale 0\n";
	comandi << "set term png\n";
	comandi << "set output \'grafico.png\'\n";
	comandi << "plot \'benchmark.csv\' using 2:xtic(1) ti col fc rgb color1, \'\' u 3 ti col fc rgb color2, \'\' u 4 ti col fc rgb color3\n";
	comandi << "quit\n";
	comandi.close();
	system("gnuplot comandi_gnuplot.txt"); // Gnuplot legge i comandi da file creato prima e genera immagine
	cout << "Grafico completato. " << endl;
	return;
}
