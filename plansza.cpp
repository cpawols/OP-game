#include "plansza.h"
#include "stworzenie.h"
/*
 * TROLOLOLO
 */
Plansza::Plansza()
{
	koniec_gry = false;
	plansza = new Pole* [100000];
}

Pole::Pole(Plansza* plansza)
{
	plansza1 = plansza;

}

Pole::~Pole()
{

}

/*void Pole::ustaw_x(int pion)
{
	x = pion;
}*/

/*void Pole::ustaw_y(int poziom)
{
	y = poziom;
}*/

void Plansza::ustaw_koniec_gry(bool x)
{
	koniec_gry = x;
}

bool Plansza::daj_koniec_gry() const
{
	return koniec_gry;
}

void Pole::postaw(Stworzenie& A)
{
  	stworek = &A;
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

/*int Pole::daj_x() const
{
	return x;
}*/

void Pole::usun_z_pola()
{
	stworek = nullptr;
}

Stworzenie*  Pole::daj_stworzenie() const
{
	return stworek;
}

Dozwolone::Dozwolone(Plansza* plansza)
: Pole(plansza)
{
}
Dozwolone::~Dozwolone()
{
}

Zakazane::Zakazane(Plansza* plansza)
:Pole(plansza)
{
}

Zakazane::~Zakazane()
{
}


Trawa::Trawa(Plansza* plansza)
: Dozwolone(plansza)
{
}

Trawa::~Trawa()
{
}

Rzeka::Rzeka(Plansza* plansza)
:Dozwolone(plansza)
{
}

Rzeka::~Rzeka()
{
}

Jaskinia::Jaskinia(Plansza* plansza)
:Dozwolone(plansza)
{
}

Jaskinia::~Jaskinia()
{
}

Bagna::Bagna(Plansza* plansza)
:Dozwolone(plansza)
{
}

Bagna::~Bagna()
{
}

Bagna_lagodne::Bagna_lagodne(Plansza* plansza)
:Bagna(plansza)
{
}

Bagna_lagodne::~Bagna_lagodne()
{
}

Bagna_smiertelne::Bagna_smiertelne(Plansza* plansza)
:Bagna(plansza)
{
}

Bagna_smiertelne::~Bagna_smiertelne()
{
}

Droga::Droga(Plansza* plansza)
:Dozwolone(plansza)
{
}

Droga::~Droga()
{
}

Gory::Gory(Plansza* plansza)
:Dozwolone(plansza)
{
	
}

Gory::~Gory()
{
	
}

Skaly::Skaly(Plansza* plansza)
:Zakazane(plansza)
{
}

Skaly::~Skaly()
{
}

void Plansza::pokaz_skarb()
{
	widac = true;
}

void Plansza::u(int x)
{
	polozenie_skarbu = x;
}

void Plansza::wczytaj(char** argv)
{
	FILE *plik;
	int licznik = 0;
	int x = 0;
	if(argv[1]	 == nullptr)
	        cout<<"jestes debilem"<<endl;
	plik = fopen(argv[1],"r");
   	fscanf(plik,"%d%d",&dl,&sz);

 	plansza = new Pole*[dl*sz + dl*2 + sz*2 +4000];

	int i = 0;
	int pionowa = 0;
	int pozioma = 0;

	for( i = 0; i < sz + 2; i++)
	{
		plansza[ i ] = new Skaly(this);
	}

	for(; i < 2*dl + 2*sz + 4 + dl*sz -sz -1 ; i++)
	{
			pionowa = 0;
			if( licznik == 0 || licznik == sz + 1)
			{
				plansza[ i ] = new Skaly(this);
					if(licznik == sz + 1 )
						licznik = -1;
					pozioma++;
					pionowa++;
			}
			else
			{
				char tmp;
				fscanf(plik," %c",&tmp);

				switch(tmp)
				{
				case '#':
					plansza[ i ] = new Skaly(this);
					break;
				case '^':
					plansza[ i ] = new Gory(this);
					break;
				case '&':
					if( wylosuj(1,100)%7 )
					{
						plansza[ i ] = new Bagna_lagodne(this);
						break;
					}
					else
					{
						plansza[ i ] = new Bagna_smiertelne(this);
						break;
					}
					
				case '.':
					plansza[ i ] = new Trawa(this);
					break;
				case '=':
					plansza[ i ] = new Droga(this);
					break;
				case '~':
					plansza[ i ] = new Rzeka(this);
					break;
				case '$':
					plansza[ i ] = new Jaskinia(this);

					u(i);
					break;
				case '*':
					plansza[ i ] = new Jaskinia(this);
					break;
				}
			}
			licznik++;
     		plansza[ i ]->usun();
			
	}
	
 	for( i = (sz + 2)*(dl + 1)  ; i < 2*dl + 2*sz + 4 +dl*sz ; i++)
	{
 		plansza[ i ] = new Skaly(this);
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
 				milosz->ustaw_polozenie(plansza[ (sz + 2)*temp3 + temp2 ]);
				break;
			case 'S':
				stw = new Sklepikarz;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stw->ustaw_polozenie(plansza[ (sz + 2)*temp3 + temp2 ]);
				stwory.push_back(stw);
				break;
			case  'Z':
				stw = new Znachorka;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stw->ustaw_polozenie(plansza[ (sz + 2)*temp3 + temp2 ]);
				stwory.push_back(stw);
				break;
			case 'B':
				stw = new Bard(x);
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stw->ustaw_polozenie(plansza[ (sz + 2)*temp3 + temp2 ]);
				stwory.push_back(stw);
				break;
			case 'P':
				stw = new Poszukiwacz;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stw->ustaw_polozenie(plansza[ (sz + 2)*temp3 + temp2 ]);
				stwory.push_back(stw);
				break;
			case 'W':
				stw = new Wybredne;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stw->ustaw_polozenie(plansza[ (sz + 2)*temp3 + temp2 ]);
				stwory.push_back(stw);
				break;
			case 'A':
				stw = new Agresywny;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stw->ustaw_polozenie(plansza[ (sz + 2)*temp3 + temp2 ]);
				stwory.push_back(stw);
				break;
			case 'T':
				stw = new Tchorzliwy;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stw->ustaw_polozenie(plansza[ (sz + 2)*temp3 + temp2 ]);
				stwory.push_back(stw);
				break;
			case 'N':
 				stw = new Neutralny;
				plansza[ (sz + 2)*temp3 + temp2 ]->postaw(*stw);
				stw->ustaw_pole((sz + 2)*temp3 + temp2);
				stw->ustaw_polozenie(plansza[ (sz + 2)*temp3 + temp2 ]);
				stwory.push_back(stw);
					break;
			
 			delete stw;

		}
	}
	fclose(plik);
}

void Plansza::wypisz() const
{
	while(!milosz->puste_komunikaty())
	{
		cout<<milosz->daj_glowe()<<endl;
		milosz->usun_glowe();
	}

	int licznik = 0; 
	for(int i = 0; i < (dl+2)*(sz+2); i++)
	{			
			if(plansza[i]->spr())
				cout<<plansza[i]->oddaj();
			else
				if( widac_skarb() && i == pol())
					cout<<"$";
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

void Plansza::posprzataj()
{
	for(int i = 0; i < (dl+2)*(sz+2); i++)
	{
		delete plansza[i];
	}
	stwory.clear();
}


bool Plansza::widac_skarb() const
{
	return widac;
}

int Plansza::pol() const
{
	return polozenie_skarbu;
}

Plansza* Pole::daj_plansze() const
{
	return plansza1;
}

void Plansza::rusz_milosza()
{
	char kierunek;
	cin>>kierunek;
	int x = 0;
	
	if(milosz->daj_zdrowie() > 0 && milosz->daj_ruch() > 0)
	{
		switch(kierunek)
		{
			case('p'):
					x = 1;
					break;
			case('l'):
					x = -1;
					break;
			case('g'):
					x = -sz-2;
					break;
			case('d'):
					x = sz+2;
					break;
		}
	}

 	if(	plansza[ milosz->daj_pole()+x]->czy_mozna_wejsc() &&
		!plansza[ milosz->daj_pole() + x ]->spr() )
	{
			plansza[milosz->daj_pole()+x]->dzialaj(*milosz);
			if(milosz->daj_zdrowie() <= 0 ||  milosz->daj_ruch() <= 0)

			{
				ustaw_koniec_gry(true);
				milosz->wstaw_komunikat("Milosz zginal", 0);
			}

			milosz->ustaw_pole(milosz->daj_pole() + x);
			plansza[milosz->daj_pole()]->postaw(*milosz);
			milosz->ustaw_polozenie(plansza[milosz->daj_pole()]);
			plansza[milosz->daj_pole() - x ]->usun();

			if(milosz->daj_pole()   == pol() )
			{
				milosz->wstaw_komunikat_bez_liczby("MILOSZ ZNALAZL SKARB, KONIEC GRY");
				ustaw_koniec_gry(true);
			}
	}
	else
		if(plansza[ milosz->daj_pole() + x ]->spr())
		{
			plansza[ milosz->daj_pole() +x ]->daj_stworzenie()->interakcjuj(*milosz);
			if(!plansza[milosz->daj_pole() +x]->daj_stworzenie()->zyje())
			{
				milosz->ustaw_pole(milosz->daj_pole() + x);
				plansza[milosz->daj_pole()]->postaw(*milosz);
				milosz->ustaw_polozenie(plansza[milosz->daj_pole()]);
				plansza[milosz->daj_pole() - x ]->usun();
			}
		}
 	milosz->wstaw_komunikat("Milosz ma zdrowie ",milosz->daj_zdrowie());
 	milosz->wstaw_komunikat("Milosz ma sile ",milosz->daj_sile());
 	milosz->wstaw_komunikat("Milosz ma punkty ruchu ",milosz->daj_ruch());
 	milosz->wstaw_komunikat("Milosz ma zbroje ",milosz->daj_zbroje());
 	milosz->wstaw_komunikat("Milosz ma bron ",milosz->daj_bron());
 	if(milosz->daj_prezent())
 		milosz->wstaw_komunikat_bez_liczby("Milosz posiada prezent");
 	else
 		milosz->wstaw_komunikat_bez_liczby("Milosz nie posiada prezentu");


}


void Plansza::rusz_reszte()
{
	int x;
	for(auto stw:stwory)
	{
		int kierunek = wylosuj(1,4);

		switch(kierunek)
		{
			case(1):
					x = 1;
					break;
			case(2):
					x = -1;
					break;
			case(3):
					x = -sz - 2;
					break;
			case(4):
					x = sz + 2;
					break;
		}

		if(stw->jakie_stworzenie() == 'S')
			stw->dostawa();

		if(		plansza[stw->daj_pole() + x]->czy_mozna_wejsc() &&
				!plansza[stw->daj_pole()+x]->spr()
		)
		{
			plansza[stw->daj_pole() +x ]->dzialaj(*stw);
			stw->ustaw_pole(stw->daj_pole() + x);
			plansza[stw->daj_pole()]->postaw(*stw);
			stw->ustaw_polozenie(plansza[stw->daj_pole()]);
			plansza[stw->daj_pole() - x ]->usun();

			if(stw->daj_pole() == pol() && stw->jakie_stworzenie() == 'P')
			{
					stw->wstaw_komunikat("Poszukiwacz znalazl skarb", 0);
					ustaw_koniec_gry(true);
			}

			if(plansza[stw->daj_pole()]->daj_stworzenie()->daj_zdrowie() <= 0 ||
				plansza[stw->daj_pole()]->daj_stworzenie()->daj_ruch() <= 0)
			{
				int temp = 0;
				for(auto s : stwory)
				{

					if(s == plansza[stw->daj_pole()]->daj_stworzenie())
					{
						stwory.erase(stwory.begin()+temp);
					}
					temp++;
				}
				plansza[stw->daj_pole()]->usun_z_pola();
			}


		}
		else
			if(plansza[stw->daj_pole() + x ]->spr())
			{
				if(stw->czy_atakowac(*plansza[stw->daj_pole()+x]->daj_stworzenie()))
				{
					stw->interakcjuj(*plansza[stw->daj_pole()+x]->daj_stworzenie());
				}
			}
	}
}





/*int Pole::daj_y() const
{
	return y;
}*/


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
	return 0; //?
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

void Pole::dzialaj(Stworzenie &stworzenie)
{
	stworzenie.zabierz_ruch(ruch());
	stworzenie.zadaj_obrazenie(obrazenie());
	if(czy_smiertelne())
	{
		stworzenie.umrzyj();
	}
}
