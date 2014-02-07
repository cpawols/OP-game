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
{/*
	 * 
	 * */
}

void Pole::postaw(Stworzenie& A)
{
  	stworek = &A;
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
	int licznik = 0;
	
	plik = fopen("plansza_m.txt","r");
   	fscanf(plik,"%d%d",&sz,&dl);

 	plansza = new Pole*[dl*sz + dl*2 + sz*2 +4000];
	int i = 0;
	for( i = 0; i < sz + 2; i++)
	{
		plansza[ i ] = new Skaly;
	}
	for(; i < 2*dl + 2*sz + 4 + dl*sz -sz -1 ; i++)
	{
			
			if( licznik == 0 || licznik == sz + 1)
			{
				plansza[ i ] = new Skaly;
					if(licznik == sz + 1 )
						licznik = -1;
			}
			else
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
			licznik++;
     			plansza[ i ]->usun();
			
	}
	
 	for( i = (sz + 2)*(dl + 1)  ; i < 2*dl + 2*sz + 4 +dl*sz ; i++)
	{
 		plansza[ i ] = new Skaly;
 		plansza[ i ]->usun();
	}
	Stworzenie* stw;
	
	while(!feof(plik))
	{
		char temp1;
		int temp2,temp3;
		fscanf(plik,"%c%d%d",&temp1,&temp3,&temp2);
		
		switch(temp1)
		{
			case 'M':
 				milosz= new Milosz;
 				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*milosz);
 				milosz->ustaw_pole((sz + 2)*temp3 + temp2);
				break;
			case 'S':
				stw = new Sklepikarz;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stwory.push_back((sz + 2)*temp3 + temp2);
				break;
			case  'Z':
				stw = new Znachorka;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stwory.push_back((sz + 2)*temp3 + temp2);
				break;
			case 'B':
				stw = new Bard;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stwory.push_back((sz + 2)*temp3 + temp2);
				break;
			case 'P':
				stw = new Poszukiwacz;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stwory.push_back((sz + 2)*temp3 + temp2);
				break;
			case 'W':
				stw = new Wybredne;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stwory.push_back((sz + 2)*temp3 + temp2);
				break;
			case 'A':
				stw = new Agresywny;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stwory.push_back((sz + 2)*temp3 + temp2);
				break;
			case 'T':
				stw = new Tchorzliwy;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stwory.push_back((sz + 2)*temp3 + temp2);
				break;
			case 'N':
 				stw = new Neutralny;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stwory.push_back((sz + 2)*temp3 + temp2);
					break;
			
 			delete stw;
		}
	}
}

void Plansza::rusz_reszte()
{
		
}



char Pole::oddaj() const
{
	return stworek->jakie_stworzenie();	
}

void Pole::usun()
{
 	stworek = nullptr;
}

bool Pole::spr() const
{
	if(stworek == nullptr)
		return false;
	return true;
}

void Plansza::wypisz() const
{
	int licznik = 0; 
	for(int i = 0; i < (dl+2)*(sz+2); i++)
	{			
			if(plansza[i]->spr())
				cout<<plansza[i]->oddaj();
			else
				cout<<plansza[i]->jakie_pole(); 
			if(licznik == (sz+1))
			{	
				cout<<endl;
				licznik = -1;
			}
			licznik++;
	}	
}

void Plansza::rusz_milosza()
{
	cout<<milosz->daj_ruch()<<endl;
	
	char kierunek;
	cin>>kierunek;
	int x;
	
 	switch(kierunek)
 	{
 		case('p'):
				x = 1;
				break;
		case('l'):
				x = -1;
				break;
		case('g'):
				x = -dl-2;
				break;
		case('d'):
				x = dl+2;
				break;
 	}
 	
 	if(
		plansza[ milosz->daj_pole()+x]->czy_mozna_wejsc() == true 
		&& plansza[ milosz->daj_pole() + x ]->spr() == false
	)
	{
			plansza[milosz->daj_pole()+x]->dzialaj(*milosz);
			if(milosz->daj_zdrowie()==0)
			{
				milosz->umrzyj();
				cout<<"Koniec gry"<<endl;
			}
			milosz->ustaw_pole(milosz->daj_pole() + x);
			plansza[milosz->daj_pole()]->postaw(*milosz);
			plansza[milosz->daj_pole() - x ]->usun();
	}
	else
		if(plansza[ milosz->daj_pole() + x ]->spr() == true)
		{
			/*
			 * Dopisac co sie tu bedzie dzialo
			 * */
		}
 		cout<<milosz->daj_ruch()<<endl;
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
