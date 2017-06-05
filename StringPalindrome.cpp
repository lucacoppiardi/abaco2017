#include <iostream>
using namespace std;
#include <string>
#include <algorithm>

bool isPalindrome(string str);

int main (int argc, char **argv) {
	
	string str;
	cout << "Inserire stringa palindroma: ";
	cin >> str;
	cout << "Stringa inserita: " << str <<endl;
	cout << endl << "1: Funzione \"isPalindrome\":" << endl;
	isPalindrome(str);
	
	cout << endl << "2: Iteratori:" << endl;
	if (str == string(str.rbegin(), str.rend())) {
		cout << str << " e' palindroma" << endl;
	} else {
		cout << str << " non e' palindroma" << endl;
	}
	
	cout << endl << "3: Metodo equals (STL):" << endl;
	if (equal(str.begin(),str.end(),str.rbegin())) {
		cout<<"Palindroma"<<endl;
	} else {
		cout<<"Non palindroma"<<endl;
	}
	
	return 0;
}

bool isPalindrome (string str) {
	
	int len = str.length();
	cout << "Lunghezza: " << len <<endl;
	bool palindroma = false;
	for (int i=0; i<len; i++) {
		/*cout<<" "<<i;
		cout<<" "<<len-i;
		cout<<endl;*/
		if (str[i]==str[len-1-i]) {
			palindroma = true;
		} else {
			palindroma = false;
		}
	}
	if (palindroma==true) {
		cout << "Palindroma" << endl;
	} else {
		cout << "Non palindroma" << endl;
	}
	return palindroma;
	
}