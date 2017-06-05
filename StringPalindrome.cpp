#include <iostream>
using namespace std;
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#define BENCH_ITERATIONS 50000

bool checkPalindrome_v1(const string& theString); // ciclo for
bool checkPalindrome_v2(const string& theString); // stringa iteratori inversi
bool checkPalindrome_v3(const string& theString); // equal
bool checkPalindrome_exv3 (const string& theString); // equal non ottimizzato

int main (int argc, char **argv) {
	
	/*
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
	
	/*
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
	*/
	
	cout<<"Premi invio per iniziare...";
	cin.get();
	
	clock_t t1_start = clock();
	cout<<endl<<"v1"<<endl;
	for(unsigned int i = 0; i < BENCH_ITERATIONS; i++)
	{
		for (unsigned int j=0;j<v1.size();j++) {
			checkPalindrome_v1(v1[j]);
		}
	}
	clock_t t1_stop = clock();
	
	cout<<endl<<"v2"<<endl;
	clock_t t2_start = clock();
	for(unsigned int i = 0; i < BENCH_ITERATIONS; i++)
	{
		for (unsigned int j=0;j<v1.size();j++) {
			checkPalindrome_v2(v1[j]);
		}
	}
	clock_t t2_stop = clock();

	cout<<endl<<"v3"<<endl;
	clock_t t3_start = clock();
	for(unsigned int i = 0; i < BENCH_ITERATIONS; i++)
	{
		for (unsigned int j=0;j<v1.size();j++) {
			if (checkPalindrome_v3(v1[j]) == true) {
				cout << v1[j] << " e' palindroma" << endl;
			} else {
				cout << v1[j] << " non e' palindroma" << endl;
			}
		}
	}
	clock_t t3_stop = clock();

	double runTimeMillisec_1 = t1_stop - t1_start;
	double runTimeMillisec_2 = t2_stop - t2_start;
	double runTimeMillisec_3 = t3_stop - t3_start;
	
	cout<<"T1: "<<runTimeMillisec_1/CLOCKS_PER_SEC<<endl;
	cout<<"T2: "<<runTimeMillisec_2/CLOCKS_PER_SEC<<endl;
	cout<<"T3: "<<runTimeMillisec_3/CLOCKS_PER_SEC<<endl;
	
	return 0;
}

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
			break;
		}
		/* TEST
		cout<<" "<<i;
		cout<<" "<<len-1-i;
		cout<<" "<<palindroma;
		cout<<endl;
		*/
	}
	if (palindroma==true) {
		cout << theString << " e' palindroma" << endl;
	} else {
		cout << theString << " non e' palindroma" << endl;
	}
	return palindroma;
	
}

bool checkPalindrome_v2(const string& theString) {
	bool palindroma;
	//cout << endl << "\tIteratori:" << endl;
	if (theString == string(theString.rbegin(), theString.rend())) {
		cout << theString << " e' palindroma" << endl;
		palindroma=true;
	} else {
		cout << theString << " non e' palindroma" << endl;
		palindroma=false;
	}
	return palindroma;
}

bool checkPalindrome_v3(const string& theString) {
	return equal(theString.begin(), theString.begin() + theString.size() / 2, theString.rbegin() );
}


bool checkPalindrome_exv3 (const string& theString) {
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
}