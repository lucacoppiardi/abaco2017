#include <iostream>
using namespace std;
#include <string>

bool isPalindrome(string str);

int main (int argc, char **argv) {
	
	string str;
	cout<<"Inserire stringa palindroma: ";
	cin>>str;
	cout<<"Stringa inserita: "<<str<<endl;
	isPalindrome(str);
	
	string input;
	cout << "Soluzione alternativa con iteratori:" << endl;
	cout << "Stringa: ";
	cin >> input;
	if (input == string(input.rbegin(), input.rend())) {
		cout << input << " e' palindroma";
	} else {
		cout << input << " non e' palindroma";
	}
	
	return 0;
}

bool isPalindrome (string str) {
	
	int len = str.length();
	cout<<"Lunghezza: "<<len<<endl;
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
		cout<<"Palindroma";
	} else {
		cout<<"Non palindroma";
	}
	return palindroma;
	
}