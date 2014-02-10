#include <iostream>
#include <cstdio>
#include "plansza.h"
#include "przedmioty.h"
#include "stworzenie.h"

using namespace std;


int main()
{
	Plansza p;
 	p.wczytaj();
	p.wypisz();
	while(1)
	{	
		p.rusz_milosza();
		p.rusz_reszte();
		p.wypisz();

	}

	return 0;
}
