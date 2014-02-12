#include <iostream>
#include <cstdio>
#include "plansza.h"
#include "przedmioty.h"
#include "stworzenie.h"

using namespace std;


int main(int argc, char** argv)
{

	Plansza p;
	bool gramy = true;

	while(gramy)
	{
		p.wczytaj(argv);
		p.wypisz();

		while(!p.daj_koniec_gry())
		{
			p.rusz_milosza();
			p.rusz_reszte();
			p.wypisz();
		}
		char c;
		cin>>c;
		if(c=='N')
		{
			p.ustaw_koniec_gry(false);
			gramy = true;
		}
		else
			gramy = false;
	}
	return 0;
}
