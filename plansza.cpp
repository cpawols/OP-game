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
 	FILE *plik;
 	plik = fopen("plansz_m.txt","r");
 	int dl,sz;
  	fscanf(plik," %d%d",&dl,&sz);
	
	
 	plansza = new Pole*[dl*sz + dl + sz +1];
	for(int i = 0; i < dl * sz; ++i)
	{
			char tmp;
			fscanf(plik," %c",&tmp);	
			switch(tmp)
			{
			case '#':
				plansza[ i ] = new Skaly;
				break;
 			case '^':
 				plansza[ i ] = new Gory;
				break;
 			case '&':
				if( wylosuj(1,100)%7 )
				{
					plansza[ i ] = new Bagna_lagodne;
					break;
				}
				else
				{
					plansza[ i ] = new Bagna_smiertelne;
					break;
				}
 				
 			case '.':
 				plansza[ i ] = new Trawa;
				break;
 			case '=':
 				plansza[ i ] = new Droga;
 				break;
			case '~':
				plansza[ i ] = new Rzeka;
				break;
			case '$':
				plansza[ i ] = new Jaskinia;
				break;
			case '*':
				plansza[ i ] = new Jaskinia;
				break;
			}			
	}
	while(!feof(plik))
	{
		char temp1;
		int temp2,temp3;
		fscanf(plik," %c %d %d",&temp1,&temp2,&temp3); 
	}
	
}


void Plansza::wypisz() const
{
	for(int i = 0; i < 25; ++i)
	{
		
			cout<<plansza[i]->jakie_pole(); 
			if((i+6)%5 == 0)
			 cout<<endl;
// 			cout<<*plansza[i+j]<<endl;
// 			if(*pole[ i + j] == '.')
// 				printf("&");

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
char Trawa::jakie_pole() const
{
	return '.';
}


int Rzeka::ruch() const
{
	return 8;
}

char Rzeka::jakie_pole() const
{
	return '~';
}

int Jaskinia::ruch() const
{
	return 3;
}

char Jaskinia::jakie_pole() const
{
	return '*';
}


int Bagna_lagodne::ruch() const
{
	return 7;
}

char Bagna::jakie_pole() const
{
	
}

int Bagna_smiertelne::ruch() const
{
	return 1;
}

char Bagna_smiertelne::jakie_pole() const
{
	return '&';
}

int Skaly::ruch() const
{
	return 12;
}

char Skaly::jakie_pole() const
{
	return '#';
}

int Rzeka::obrazenie() const
{
	return 5;
}

int Bagna_lagodne::obrazenie() const
{
	return 8;
}

char Bagna_lagodne::jakie_pole() const
{
	return '&';
}

int Droga::ruch() const
{
	return 1;
}

char Droga::jakie_pole() const
{
	return '=';
}

int Gory::ruch() const
{
	return 18;
}

int Gory::obrazenie() const
{
	return 8;
}

char Gory::jakie_pole() const
{
	return '^';
}

/*char Pole::jakie_pole() const
{
	
}*/

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