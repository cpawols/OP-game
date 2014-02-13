#include <cassert>
#include <random>
#include <iostream>
#include "stworzenie.h"
#include "plansza.h"


int wylosuj(int a, int b)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(a, b);
	
	return dis(gen);
}

float wylosuj_ekwipunek(int a, int b)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(a, b);
	return dis(gen)*0.01;
}


Stworzenie::Stworzenie()
{
	prezent.ustaw_prezent(0);
}

Stworzenie::~Stworzenie()
{
}

int Stworzenie::daj_zdrowie() const
{
	return zdrowie;
}

int Stworzenie::daj_sile() const
{
	return sila;
}

int Stworzenie::daj_ruch() const
{
	return punkty_ruchu;
}

int Stworzenie::daj_pole() const
{
		return po;
}

float Stworzenie::daj_bron() const
{
	return bron.daj_klase_broni();
}

float Stworzenie::daj_zbroje() const
{
	return zbroja.daj_klase_zbroi();
}

bool Stworzenie::zyje() const
{
	if(this->daj_zdrowie() <= 0)
	{
		return false;
	}
	return true;

}

bool Stworzenie::czy_wstawia() const
{
	return false;
}

bool Stworzenie::czy_atakowac(Stworzenie&) const
{
	return false;
}

bool Stworzenie::daj_prezent() const
{
	return false;
}

bool Stworzenie::czy_moze_kupic() const
{
	return false;
}

void Stworzenie::ustaw_bron(float x)
{
	bron.ustaw_klase_broni(x);
}

void Stworzenie::ustaw_zbroje(float x)
{
	zbroja.ustaw_klase_zbroi(x);
}

void Stworzenie::ustaw_pole(int x)
{
	po = x;
}

void Stworzenie::ustaw_polozenie(Pole* pole)
{
	polozenie = pole;
}

void Stworzenie::zabierz_ruch( int x )
{
	punkty_ruchu -= x;

// 	assert (punkty_ruchu > 0);
}

void Stworzenie::zadaj_obrazenie( int x )
{
	zdrowie -= x;
}



void Stworzenie::uderz( Stworzenie&  A)
{
	A.zadaj_obrazenie( int(A.daj_sile()* ( A.daj_zdrowie()*0.001 ) *(1.00 + A.daj_bron() ) *(1 - this->daj_zbroje())));
}


void Stworzenie::umrzyj()
{
	ustaw_zdrowie(0);
}

void Stworzenie::ustaw_ruch(int x)
{
	punkty_ruchu = x;
}

void Stworzenie::ustaw_prezent(bool x)
{
	prezent.ustaw_prezent(false);
}


void Stworzenie::ustaw_sile(int x)
{
	sila = x;
}

void Stworzenie::ustaw_zdrowie( int x)
{
	zdrowie = x;
}

void Stworzenie::interakcjuj(Stworzenie&)
{

}

void Stworzenie::atakuj(Stworzenie& stworzenie)
{
	this->uderz(stworzenie);
	if(stworzenie.daj_zdrowie() > 0)
		stworzenie.uderz(*this);
	
}

void Stworzenie::wstaw_komunikat(string s, float x)
{

}

void Stworzenie::wstaw_komunikat_bez_liczby(string s)
{

}

void Stworzenie::dostawa()
{

}


Inteligentne::Inteligentne()
:Stworzenie()
{
}

Inteligentne::~Inteligentne()
{
	
}

void Inteligentne::interakcjuj(Poszukiwacz& poszukiwacz)
{

}

Bard::Bard(int x)
:Inteligentne()
{
	skarb = x;
	ustaw_ruch(wylosuj(1,100));
	ustaw_zdrowie(wylosuj(1,100));
	ustaw_sile(wylosuj(1,100));
}

Bard::~Bard()
{
}




char Bard::jakie_stworzenie() const
{
	return 'B';
}

void Bard::ustaw_skarb(int x)
{
	skarb = x;
}


void Bard::interakcjuj(Stworzenie &poszukiwacz)
{

	if(poszukiwacz.daj_prezent())
	{
		poszukiwacz.ustaw_prezent( false );
		polozenie->daj_plansze()->pokaz_skarb();
		poszukiwacz.wstaw_komunikat_bez_liczby("Bard Pokazal skarb ");
	}
}

int Bard::daj_skarb() const
{
	return skarb;
}



Sklepikarz::Sklepikarz()
:Inteligentne()
{
	ustaw_zdrowie(100);
	ustaw_sile(10);
	ustaw_ruch(100);
	zbroja.ustaw_klase_zbroi(0);
	bron.ustaw_klase_broni(0);
	liczba_prezentow = 0;
	
}

Sklepikarz::~Sklepikarz()
{
}



void Sklepikarz::dostawa()
{

	Zbroja  z;
	Bron b;
	int random_x = wylosuj(1,100);
	if( random_x % 2  ==  0)
	{
		z.ustaw_klase_zbroi(wylosuj_ekwipunek(1,100));
		asortyment_zbroi.push_back(z);
	}

	random_x = wylosuj(1,100);

	if(random_x % 5 == 0)
	{
		b.ustaw_klase_broni(wylosuj_ekwipunek(1,100));
		asortyment_broni.push_back(b);
	}

	random_x = wylosuj(1,17);

	if(random_x % 3)
	{
		liczba_prezentow++;
	}
}

void Sklepikarz::interakcjuj(Stworzenie& stworzenie)
{

	if(stworzenie.czy_moze_kupic())
	{
		if(!asortyment_broni.empty())
		{

			if(stworzenie.czy_wstawia())
			{
				string s = "Milosz ma nowa bron ";
				stworzenie.wstaw_komunikat(s,asortyment_broni.back().daj_klase_broni());
				//cout<<komunikaty.front()<<endl;
			}

			stworzenie.ustaw_bron(asortyment_broni.back().daj_klase_broni());
			asortyment_broni.pop_back();
		}
		if(!asortyment_zbroi.empty())
		{

			if(stworzenie.czy_wstawia())
			{
				string s = "Milosz ma nowa zbroje ";
				stworzenie.wstaw_komunikat(s,asortyment_zbroi.back().daj_klase_zbroi());
			}

			stworzenie.ustaw_zbroje(asortyment_zbroi.back().daj_klase_zbroi());
			asortyment_zbroi.pop_back();
		}
		if(liczba_prezentow > 0)
		{
			if(stworzenie.czy_wstawia())
			{
				stworzenie.wstaw_komunikat_bez_liczby("Milosz dostal prezent");
			}
			stworzenie.ustaw_prezent(true);
			liczba_prezentow--;
		}

	}
	//cout<<"DUPA"<<endl;
	while(!komunikaty.empty())
	{
		cout<<komunikaty.front()<<endl;
		komunikaty.pop();
	}

}

char Sklepikarz::jakie_stworzenie() const
{
	return 'S';
}


Znachorka::Znachorka()
:Inteligentne()
{
	ustaw_zdrowie(82);
	ustaw_sile(10);
	ustaw_ruch(43);
}

Znachorka::~Znachorka()
{
	
}

void Znachorka::interakcjuj(Stworzenie &poszukiwacz)
{

 	if(poszukiwacz.daj_prezent())
	{
 		if(poszukiwacz.czy_wstawia())
 		{

 			poszukiwacz.wstaw_komunikat_bez_liczby("Znachorka Uleczyla Milosza");

 		}
		poszukiwacz.ustaw_zdrowie(100);
		poszukiwacz.ustaw_prezent(false);

	}
}

char Znachorka::jakie_stworzenie() const
{
	return 'Z';
}

float Poszukiwacz::daj_bron() const
{
	return bron.daj_klase_broni();
}

float Poszukiwacz::daj_zbroje() const
{
	return zbroja.daj_klase_zbroi();
}


Milosz::Milosz()
:Poszukiwacz()
{
	
	ustaw_zdrowie(50);
	ustaw_sile(50);
	ustaw_ruch(100);
	zbroja.ustaw_klase_zbroi(wylosuj_ekwipunek(1,100));
	bron.ustaw_klase_broni(wylosuj_ekwipunek(1,100));
	prezent.ustaw_prezent(true);
}

Milosz::~Milosz()
{
}

bool Milosz::czy_moze_kupic() const
{
	return true;
}


bool Milosz::czy_wstawia() const
{
	return true;
}


bool Milosz::puste_komunikaty() const
{
	return komunikaty.empty();
}


string Milosz::daj_glowe() const
{
	return komunikaty.front();
}

void Milosz::usun_glowe()
{
	komunikaty.pop();
}

void Milosz::wstaw_komunikat(string s, float x)
{
		char Cstr[5];
		gcvt(x , 6, Cstr);
		string w = Cstr;
		komunikaty.push(s+w);
}



void Milosz::wstaw_komunikat_bez_liczby(string s)
{
	komunikaty.push(s);
}

char Milosz::jakie_stworzenie() const
{
	return 'M';
}

Poszukiwacz::Poszukiwacz()
:Inteligentne()
{
	ustaw_zdrowie(wylosuj(1,100));
	ustaw_ruch(wylosuj(1,100));
	ustaw_sile(wylosuj(1,100));
	zbroja.ustaw_klase_zbroi(wylosuj_ekwipunek(0,100));
	prezent.ustaw_prezent(0); //ustawia wszystkim poszukiwaczom brak prezentu.
}

Poszukiwacz::~Poszukiwacz()
{
}

void Poszukiwacz::kup(const vector <Przedmiot> przedmioty)
{
	
}

void Poszukiwacz::ustaw_prezent(bool x)
{
	prezent.ustaw_prezent(x);
}

bool Poszukiwacz::daj_prezent() const
{
	return prezent.sprawdz_prezent();
}

char Poszukiwacz::jakie_stworzenie() const
{
	return 'P';
}


Prymitywne::Prymitywne()
:Stworzenie()
{
	zbroja.ustaw_klase_zbroi(0);
	bron.ustaw_klase_broni(0);
	prezent.ustaw_prezent(0);
}

Prymitywne::~Prymitywne()
{
}

/*bool Prymitywne::czy_atakowac(Stworzenie&) const
{
	
}*/

void Prymitywne::interakcjuj(Stworzenie &stworzenie)
{

	//TU COS ROBILEM + interakcuj dla prymitywnych i cos jeszcze ale nie pamietam co
	stworzenie.atakuj(*this);
	if(stworzenie.czy_wstawia())
	{
		stworzenie.wstaw_komunikat("Milosz zostal zaatakowany jego zdrowie to ", (float)stworzenie.daj_zdrowie());
		stworzenie.wstaw_komunikat("Zdrowie przeciwnika to ", (float)this->daj_zdrowie());
	}
}

void Prymitywne::atakuj(Stworzenie& stworzenie)
{
	stworzenie.uderz(*this);
	if(this->daj_zdrowie() > 0)
	{
		cout<<"wlazl"<<endl;
		this->uderz(stworzenie);
	}
}

Wybredne::Wybredne()
:Prymitywne()
{
}

Wybredne::~Wybredne()
{
}
//
bool Wybredne::czy_atakowac(Stworzenie& stworzenie) const
{
	if( stworzenie.jakie_stworzenie() == 'B' ||
		stworzenie.jakie_stworzenie() == 'M' ||
		stworzenie.jakie_stworzenie() == 'P' ||
		stworzenie.jakie_stworzenie() == 'Z')
		return true;
	return false;
}

void Wybredne::atakuj(Stworzenie& stworzenie)
{
	this->uderz(stworzenie);
	if(stworzenie.daj_zdrowie() > 0)
		stworzenie.uderz(*this);
}

char Wybredne::jakie_stworzenie() const
{
	return 'W';
}

Tchorzliwy::Tchorzliwy()
:Prymitywne()
{
}

Tchorzliwy::~Tchorzliwy()
{
}

bool Tchorzliwy::czy_atakowac(Stworzenie& stworzenie) const
{
	if(stworzenie.daj_zdrowie() < 50)
		return true;
	return false;
}

char Tchorzliwy::jakie_stworzenie() const
{
	return 'T';
}

Agresywny::Agresywny()
:Prymitywne()
{
	ustaw_zdrowie(wylosuj(1,100));
 	ustaw_sile(wylosuj(1,100));
	ustaw_ruch(wylosuj(1,100));
}

Agresywny::~Agresywny()
{
	
}

bool Agresywny::czy_atakowac(Stworzenie& stworzenie) const
{
	return true;
}

char Agresywny::jakie_stworzenie() const
{
	return 'A';
}

char Neutralny::jakie_stworzenie() const
{
	return 'N';
}

bool Neutralny::czy_atakowac(Stworzenie& stworzenie) const
{
	return false;
}

Neutralny::Neutralny()
{
	ustaw_zdrowie(wylosuj(1,100));
	ustaw_sile(wylosuj(1,100));
	ustaw_ruch(wylosuj(1,100));
}

Neutralny::~Neutralny()
{
	
}

