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

Plansza::~Plansza()
{
	posprzataj();
}

bool Plansza::widac_skarb() const
{
	return widac;
}

void Plansza::posprzataj()
{
	delete [] plansza;
	stwory.clear();
	delete milosz;
}

void Plansza::ustaw_koniec_gry(bool x)
{
	koniec_gry = x;
}

void Plansza::pokaz_skarb()
{
	widac = true;
}

bool Plansza::daj_koniec_gry() const
{
	return koniec_gry;
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

void Plansza::wczytaj(char** argv)
{
	FILE *plik;
	int licznik = 0;
	if(argv[1] == nullptr)
		cout<<"Nie podales planszy"<<endl;

	plik = fopen(argv[1],"r");
	fscanf(plik,"%d%d",&dl,&sz);
	plansza = new Pole*[dl*sz + dl*2 + sz*2 +4000];
	int i = 0;

	for( i = 0; i < sz + 2; i++)
	{
		plansza[ i ] = new Skaly(this);
	}

	for(; i < 2*dl + 2*sz + 4 + dl*sz -sz -1 ; i++)
	{

			if( licznik == 0 || licznik == sz + 1)
			{
				plansza[ i ] = new Skaly(this);
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
					miejsce_skarbu(i);
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
				stw = new Bard();
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
		i = 0;
}

void Plansza::miejsce_skarbu(int x)
{
	polozenie_skarbu = x;
}

int Plansza::pol() const
{
	return polozenie_skarbu;
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
				milosz->wstaw_komunikat_bez_liczby("Milosz zginal!");
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


Pole::Pole(Plansza* plansza)
{
	plansza1 = plansza;

}

Pole::~Pole()
{
	usun();
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

void Pole::usun_z_pola()
{
	stworek = nullptr;
}

Plansza* Pole::daj_plansze() const
{
	return plansza1;
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

Stworzenie*  Pole::daj_stworzenie() const
{
	return stworek;
}

bool Pole::czy_smiertelne() const
{
	return false;
}

int Pole::obrazenie() const
{
	return 0;
}

Dozwolone::Dozwolone(Plansza* plansza)
: Pole(plansza)
{

}

Dozwolone::~Dozwolone()
{

}

bool Dozwolone::czy_mozna_wejsc() const 
{
	return true;
}

Zakazane::Zakazane(Plansza* plansza)
:Pole(plansza)
{

}

Zakazane::~Zakazane()
{
}


bool Zakazane::czy_mozna_wejsc() const
{
	return false;
}

Trawa::Trawa(Plansza* plansza)
: Dozwolone(plansza)
{
}

Trawa::~Trawa()
{
}

int Trawa::ruch() const
{
	return 2;
}
char Trawa::jakie_pole() const
{
	return '.';
}


Rzeka::Rzeka(Plansza* plansza)
:Dozwolone(plansza)
{

}

Rzeka::~Rzeka()
{

}

int Rzeka::ruch() const
{
	return 8;
}

char Rzeka::jakie_pole() const
{
	return '~';
}

int Rzeka::obrazenie() const
{
	return 5;
}

Jaskinia::Jaskinia(Plansza* plansza)
:Dozwolone(plansza)
{

}

Jaskinia::~Jaskinia()
{

}

int Jaskinia::ruch() const
{
	return 3;
}

char Jaskinia::jakie_pole() const
{
	return '*';
}


Bagna::Bagna(Plansza* plansza)
:Dozwolone(plansza)
{

}

Bagna::~Bagna()
{

}

char Bagna::jakie_pole() const
{
	return 0; //?
}

Bagna_lagodne::Bagna_lagodne(Plansza* plansza)
:Bagna(plansza)
{

}

Bagna_lagodne::~Bagna_lagodne()
{

}

char Bagna_lagodne::jakie_pole() const
{
	return '&';
}

int Bagna_lagodne::obrazenie() const
{
	return 8;
}

int Bagna_lagodne::ruch() const
{
	return 5;
}

Bagna_smiertelne::Bagna_smiertelne(Plansza* plansza)
:Bagna(plansza)
{

}

Bagna_smiertelne::~Bagna_smiertelne()
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

bool Bagna_smiertelne::czy_smiertelne() const
{
	return true;
}

Droga::Droga(Plansza* plansza)
:Dozwolone(plansza)
{

}

Droga::~Droga()
{

}

int Droga::ruch() const
{
	return 1;
}

char Droga::jakie_pole() const
{
	return '=';
}

Gory::Gory(Plansza* plansza)
:Dozwolone(plansza)
{

}

Gory::~Gory()
{

}

int Gory::ruch() const
{
	return 8;
}

int Gory::obrazenie() const
{
	return 8;
}

char Gory::jakie_pole() const
{
	return '^';
}

Skaly::Skaly(Plansza* plansza)
:Zakazane(plansza)
{

}

Skaly::~Skaly()
{
}

int Skaly::ruch() const
{
	return 1000000;
}

char Skaly::jakie_pole() const
{
	return '#';
}

