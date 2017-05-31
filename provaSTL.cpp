#include <iostream>
using namespace std;

/* Standard Template Library */
#include <string>
#include <vector>
#include <set>

/* 
 * http://www.bogotobogo.com/cplusplus/stl_vector_list.php 
 * http://www.cplusplus.com/reference/string/string/
*/

int main(int argc, char **argv)
{
	/* STL String */
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
	cout<<endl;
	
	/* STL Vector */
	vector<int> v1;
	v1.push_back(52);
	v1.push_back(34);
	v1.push_back(48);
	v1.push_back(30);
	v1.push_back(21);
	vector<int> v2 (v1.begin(),v1.end());
	cout<<"Vettore 1: ";
	for (int i=0;i<v1.size(); i++) {
		cout<<v1[i]<<" ";
	}
	cout<<endl;
	cout<<"Vettore 2: ";
	v2.pop_back();
	for (int i=0;i<v2.size(); i++) {
		cout<<v2[i]<<" ";
	}
	cout<<endl;
	
	/* STL Set */
	set<string> set1;
	set1.insert("mercurio");
	set1.insert("venere");
	set1.insert("terra");
	set1.insert("giove");
	cout<<endl;
	string pianeta;
	cout<<"Un altro pianeta da inserire: ";
	cin>>pianeta;
	set1.insert(pianeta);
	cout<<"Dimensione set: "<<set1.size()<<endl;
	set<string>::iterator it1;
	for (it1=set1.begin(); it1!=set1.end(); it1++) {
		cout<<*it1<<" ";
	}
	cout<<endl;
	set1.erase(set1.find(pianeta));
	cout<<"Il pianeta "<<pianeta<<" e' stato rimosso dal set:"<<endl;
	cout<<"Dimensione set: "<<set1.size()<<endl;
	for (it1=set1.begin(); it1!=set1.end(); it1++) {
		cout<<*it1<<" ";
	}
	cout<<endl;
	
	/* STL Map */
	
	
	return 0;
}
