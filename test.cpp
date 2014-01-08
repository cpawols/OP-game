#include <iostream>
#include "plansza.h"
#include "stworzenie.h"

using namespace std;


int main()
{
	/*Trawa t;
	Rzeka R;
	Skaly S;
	Bagna_smiertelne B;
	Bagna_lagodne b;
	cout<<t.ruch()<<endl;
	cout<<t.obrazenie()<<endl;
	cout<<t.czy_mozna_wejsc()<<endl;
	cout<<b.czy_smiertelne()<<endl;
 	cout<<B.czy_smiertelne()<<endl;
	*/
	
	Znachorka Z;
	Milosz M;
	
	
	cout<<"Milosz zdrowie"<<M.daj_zdrowie()<<endl;
	Z.interakcjuj(M);
	cout<<"Milosz zdrowie"<<M.daj_zdrowie()<<endl;
	
	M.zadaj_obrazenie(100);
	
	cout<<"Milosz zdrowie"<<M.daj_zdrowie()<<endl;
	
	Z.interakcjuj(M);
	
	cout<<"Milosz zdrowie"<<M.daj_zdrowie()<<endl;
	
	
	
 	cout<<"Milosz ma prezent"<<M.daj_prezent()<<endl;
	
	M.ustaw_prezent(1);
	
	cout<<"Milosz ma prezent"<<M.daj_prezent()<<endl;
	
	Z.interakcjuj(M);
	
	cout<<"Milosz zdrowie"<<M.daj_zdrowie()<<endl;
	cout<<"Milosz ma prezent"<<M.daj_prezent()<<endl;
	
	M.ustaw_zdrowie(-99999990);
	
	cout<<"Milosz zdrowie"<<M.daj_zdrowie()<<endl;
	return 0;
}