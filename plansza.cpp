#include "plansza.h"
#include "stworzenie.h"
/*
 * TROLOLOLO
 */
Plansza::Plansza()
{
	plansza = new Pole* [100];
}

Pole::Pole()
{
	
}

Pole::~Pole()
{
}

Dozwolone::Dozwolone()
: Pole()
{
}
Zakazane::Zakazane()
:Pole()
{
}

Zakazane::~Zakazane()
{
}


Dozwolone::~Dozwolone()
{
}

Trawa::Trawa()
: Dozwolone()
{
}

Trawa::~Trawa()
{
}

Rzeka::Rzeka()
:Dozwolone()
{
}

Rzeka::~Rzeka()
{
}

Jaskinia::Jaskinia()
:Dozwolone()
{
}

Jaskinia::~Jaskinia()
{
}

Bagna::Bagna()
:Dozwolone()
{
}

Bagna::~Bagna()
{
}

Bagna_lagodne::Bagna_lagodne()
:Bagna()
{
}

Bagna_lagodne::~Bagna_lagodne()
{
}

Bagna_smiertelne::Bagna_smiertelne()
:Bagna()
{
}

Bagna_smiertelne::~Bagna_smiertelne()
{
}

Droga::Droga()
{
}

Droga::~Droga()
{
}

Gory::Gory()
{
	
}

Gory::~Gory()
{
	
}

Skaly::Skaly()
:Zakazane()
{
}

Skaly::~Skaly()
{
}

void Plansza::wczytaj()
{
	int dl,sz;
	plansza = new Pole*[dl*sz + dl + sz +1];
	scanf("%d%d",&dl,&sz); //wczytuje wymiary planszy
	for(int i = 0; i < dl; ++i)
	{
		for(int j = 0; j < sz; ++j)
		{
			char tmp;
			scanf("%c",&tmp);	
			switch(tmp)
			{
			case '#':
				plansza[i+j] = new Skaly;
				break;
 			case '^':
 				plansza[ i + j ] = new Gory;
				break;
 			case '&':
				if( wylosuj(1,100)%7 )
				{
					plansza[ i + j ] = new Bagna_lagodne;
					break;
				}
				else
				{
					plansza[ i + j ] = new Bagna_smiertelne;
					break;
				}
 				
 			case '.':
 				plansza[ i + j ] = new Trawa;
 			case '=':
 				plansza[ i + j ] = new Droga;
 				break;
			case '~':
				plansza[ i + j ] = new Rzeka;
				break;
			case '$':
				plansza[ i + j ] = new Jaskinia;
				break;
			case '*':
				plansza[ i + j ] = new Jaskinia;
				break;
			}			
		}
	}
}

void Plansza::wypisz() const
{
	for(int i = 0; i < 5; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			if(*plansza[ i + j] == '&')
				printf("&");
		}
		printf("\n");
	}
	
}


bool Zakazane::czy_mozna_wejsc() const 
{
	return false;
}

bool Dozwolone::czy_mozna_wejsc() const 
{
	return true;
}

int Trawa::ruch() const
{
	return 2;
}

int Rzeka::ruch() const
{
	return 8;
}

int Jaskinia::ruch() const
{
	return 3;
}

int Bagna_lagodne::ruch() const
{
	return 7;
}

int Bagna_smiertelne::ruch() const
{
	return 1;
}

int Skaly::ruch() const
{
	return 12;
}

int Rzeka::obrazenie() const
{
	return 5;
}

int Bagna_lagodne::obrazenie() const
{
	return 8;
}

int Droga::ruch() const
{
	return 1;
}

int Gory::ruch() const
{
	return 18;
}

int Gory::obrazenie() const
{
	return 8;
}

int Pole::obrazenie() const
{
	return 0;
}

bool Pole::czy_smiertelne() const
{
	return false;
}

bool Bagna_smiertelne::czy_smiertelne() const
{
	return true;
}

int Pole::dzialaj(Stworzenie &stworzenie) 
{
	stworzenie.zabierz_ruch(ruch());
	stworzenie.zadaj_obrazenie(obrazenie());
	if(czy_smiertelne())
	{
		stworzenie.umrzyj();
	}
}