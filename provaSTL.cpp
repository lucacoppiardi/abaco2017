#include <iostream>
using namespace std;
#include <string> //STL

int main(int argc, char **argv)
{
	string s1 = "Stringa di prova STL";
	cout<<s1<<endl;
	string s2("Altra stringa");
	cout<<s2<<endl;
	string s3;
	cout<<"s3: ";
	cin>>s3;
	cout<<"s3: "<<s3<<endl;
	cout<<"Lunghezza s3: "<<s3.size()<<endl;
	cout<<"Concatenazione s1,2: "<<s1+s2<<endl;
	/* http://www.cplusplus.com/reference/string/string/ */
	return 0;
}
