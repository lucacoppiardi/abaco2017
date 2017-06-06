#include <iostream>
using namespace std;
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>

#define BENCH_ITERATIONS 1000000

bool checkPalindrome_v1(const string& theString); // ciclo for
bool checkPalindrome_v2(const string& theString); // stringa iteratori inversi
bool checkPalindrome_v3(const string& theString); // equal
//bool checkPalindrome_exv3 (const string& theString); // equal non ottimizzato
int doTest(const vector<string>& toCheck, bool(*checkPalindromeFunz)(const string&)); // benchmark

int main (int argc, char **argv) {
	
	/* // PROVA DI TUTTE LE FUNZIONI SU UNA SOLA STRINGA
	string str;
	cout << "Inserire stringa palindroma: ";
	cin >> str;
	cout << "Stringa inserita: " << str <<endl;
	checkPalindrome_v1(str);
	checkPalindrome_v2(str);
	checkPalindrome_equals(str);
	*/
	vector<string> v1;
	
	v1.push_back("ciao");
	v1.push_back("anna");
	v1.push_back("inipotinonavevanotopi");
	v1.push_back("itopinonavevanonipoti");
	
	/* // PROVA DI TUTTE LE FUNZIONI SU UN VECTOR DI STRING
	for (unsigned int i=0;i<v1.size(); i++) {
		cout<<v1[i]<<endl;
	}
	
	cout<<endl<<"v1"<<endl;
	for (unsigned int i=0;i<v1.size();i++) {
		checkPalindrome_v1(v1[i]);
	}
	
	cout<<endl<<"v2"<<endl;
	for (unsigned int i=0;i<v1.size();i++) {
		checkPalindrome_v2(v1[i]);
	}
	
	cout<<endl<<"v3"<<endl;
	for (unsigned int i=0;i<v1.size();i++) {
		if (checkPalindrome_v3(v1[i]) == true) {
			cout << v1[i] << " e' palindroma" << endl;
		} else {
			cout << v1[i] << " non e' palindroma" << endl;
		}
	}
	
	cout<<endl;
	
	// BENCHMARK
	cout<<"Premere invio per iniziare il benchmark...";
	cin.get();
	cout<<"BENCH_ITERATIONS = "<<BENCH_ITERATIONS<<endl;
	*/
	
	// BENCHMARK (SENZA FUNZIONE DoTest)
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
	int runTimeMillisec_1 = doTest(v1, checkPalindrome_v1);
	int runTimeMillisec_2 = doTest(v1, checkPalindrome_v2);
	int runTimeMillisec_3 = doTest(v1, checkPalindrome_v3);
	
	cout<<"T1: "<<runTimeMillisec_1<<endl;
	cout<<"T2: "<<runTimeMillisec_2<<endl;
	cout<<"T3: "<<runTimeMillisec_3<<endl;
		
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
		for (unsigned int j=0;j<toCheck.size();j++) {
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