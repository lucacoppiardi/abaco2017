#include <iostream>
using namespace std;

/* Standard Template Library */
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <deque>
#include <stack>

/* 
 * http://www.bogotobogo.com/cplusplus/stl_vector_list.php 
 * http://www.cplusplus.com/reference/string/string/
*/

int main(int argc, char **argv)
{
	/* STL String */
	string s1 = "Stringa di prova STL";
	cout << s1 << endl;
	string s2("Altra stringa");
	cout<<s2<<endl;
	string s3;
	cout<<"s3: ";
	cin>>s3;
	cout<<"s3: "<<s3<<endl;
	string s4;
	cout<<"Lunghezza s3: "<<s3.size()<<endl;
	s4=s1+s2;
	cout<<"Concatenazione s1+s2: "<<s4<<endl;
	s4.erase (5,3); 
	cout<<"cancello qualche carattere: "<<s4<<endl;
	cout<<endl;
	
	/* STL Vector */
	vector<int> v1;
	v1.push_back(52);
	v1.push_back(34);
	v1.push_back(48);
	v1.push_back(30);
	v1.push_back(21);
	vector<int> v2 (v1.begin(),v1.end()); // copia v1
	cout<<"Vettore 1: ";
	for (unsigned int i=0;i<v1.size(); i++) {
		cout<<v1[i]<<" ";
	}
	cout<<endl;
	cout<<"Vettore 2 (pop): ";
	v2.pop_back(); // estraggo ultimo elemento
	for (unsigned int i=0;i<v2.size(); i++) {
		cout<<v2[i]<<" ";
	}
	cout<<endl<<"primo elemento: "<<v2.front()<<endl;
	cout<<"ultimo elemento: "<<v2.back()<<endl;
	
	/* STL Set */
	set<string> set1;
	set1.insert("mercurio");
	set1.insert("venere");
	set1.insert("terra");
	set1.insert("giove");
	cout<<endl;
	string pianeta;
	cout<<"Nome di un pianeta: ";
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
	cout<<endl<<endl;
	
	/* STL Map */
	map<int, string> impiegati;
	impiegati[100]="Luca";
	impiegati[101]="Matteo";
	impiegati[432]="Giorgio";
	impiegati[535]="Lorenzo";
	impiegati[72]="Alessandro";
	cout << "Map size: " << impiegati.size() << endl;
	cout << "impiegati:" << endl;
	for( map<int,string>::iterator ii=impiegati.begin(); ii!=impiegati.end(); ii++)
	{
		cout << (*ii).first << ": " << (*ii).second << endl;
	}
	cout<<endl;
	
	/* STL List */
	list<int> list1;
	list1.push_back(1);
	list1.push_back(6);
	list1.push_back(8);
	list1.push_back(2);
	list1.push_back(4);
	cout<<"Contenuto lista: ";
	for(list<int>::iterator list_iter = list1.begin(); list_iter != list1.end(); list_iter++) {
		cout<<*list_iter<<" ";
	}
	cout<<endl;
	cout<<"Contenuto lista ordinata: ";
	list1.sort();
	for(list<int>::iterator list_iter = list1.begin(); list_iter != list1.end(); list_iter++) {
		cout<<*list_iter<<" ";
	}
	cout<<endl;
	list1.remove(8);
	cout<<"Rimosso 8: ";
	for(list<int>::iterator list_iter = list1.begin(); list_iter != list1.end(); list_iter++) {
		cout<<*list_iter<<" ";
	}
	cout<<endl<<endl;
	
	/* STL Deque */
	deque<int> deque1;
	deque1.push_front(13);
	deque1.push_front(52);
	deque1.push_front(73);
	deque1.push_back(25);
	deque1.push_back(12);
	cout<<"deque1: ";
	for(deque<int>::iterator iter = deque1.begin(); iter != deque1.end(); iter++) {
		cout << *iter << " ";
	}
	cout<<endl<<"Posizione 3: "<<deque1.at(3)<<endl;
	cout<<"Elimino primo elemento: ";
	deque1.pop_front();
	for(deque<int>::iterator iter = deque1.begin(); iter != deque1.end(); iter++) {
		cout << *iter << " ";
	}
	cout<<endl<<endl;
	
	/* STL Stack */
	cout<<"Stack: ";
	stack<int> stack1;  
	for (int i=0; i<5; ++i) {
		stack1.push(i*2);
		cout<<stack1.top()<<" ";
	}
	cout<<endl;
	cout << "Svuoto lo stack con pop: ";
	while (!stack1.empty()) {
		cout << ' ' << stack1.top();
		stack1.pop();
	}
	cout << endl;
	
	return 0;
}
