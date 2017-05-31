#include <cmath>
#include <cstdio>
#include <iostream>
#include <../meanDynamic/meanDynamic.h>

using namespace std;

/*double mean(double a, double b) {
  return (a+b) / 2;
}*/

int main(int argc, char **argv)
{
	float a,b,c,ris1,ris2;
	cout<<"A: ";
	cin>>a;
	cout<<"B: ";
	cin>>b;
	cout<<"C: ";
	cin>>c;
	ris1=((-1*b)+sqrtf((b*b)-(4*a*c)))/(2*a);
	ris2=((-1*b)-sqrtf((b*b)-(4*a*c)))/(2*a);
	cout<<"Soluzione 1 (+): "<<ris1<<endl;
	cout<<"Soluzione 2 (-): "<<ris2<<endl;
	
	double a1, b1;
	cout<<"Media"<<endl;
	cout<<"A1: ";
	cin>>a1;
	cout<<"B1: ";
	cin>>b1;
	double c1 = mean(a1,b1);
	cout << "media: " << c1 << endl;
	
	return 0;
}
