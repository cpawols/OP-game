#include <cassert>
#include <random>
#include "stworzenie.h"
#include "plansza.h"


int wylosuj(int a, int b) 
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(a, b);
	
	return dis(gen);
}



Stworzenie::Stworzenie()
{
	prezent.ustaw_prezent(0);
}

Stworzenie::~Stworzenie()
{
}

int Stworzenie::daj_bron() const
{
	return bron.daj_klase_broni();
}

int Stworzenie::daj_zbroje() const
{
	return zbroja.daj_klase_zbroi();
}

void Stworzenie::ustaw_bron(int x)
{
	bron.ustaw_klase_broni(x);
}

void Stworzenie::ustaw_zbroje(int x)
{
	zbroja.ustaw_klase_zbroi(x);
}

void Stworzenie::ustaw_pole(int x)
{
	po = x;
}

char Stworzenie::jakie_stworzenie() const
{

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
	/*
	 * this bije A
	 */
	/*
	cout<<"bron "<<bron.daj_klase_broni()<<endl;
	cout<<"zbroja "<<zbroja.daj_klase_zbroi()<<endl;
	cout<<"sila "<<sila<<endl;
	cout<<"zdrowie "<<zdrowie<<endl;
	
	cout<<(sila * (zdrowie / 100) * 
	(1 + bron.daj_klase_broni())+(1-A.zbroja.daj_klase_zbroi()))<<endl;
	*/
// 	cout<<"Z "<<zdrowie<<endl;
	int k = 30;
	
	cout<< float(k/4) <<endl;
// 	cout<<"Dupa"<< float(zdrowie/100) <<endl;
	A.zadaj_obrazenie( int(sila * float((zdrowie / 100)) * 
	(1 + bron.daj_klase_broni())*(1-A.zbroja.daj_klase_zbroi())) );
}


int Stworzenie::daj_pole() const
{
		return po;
}

void Stworzenie::umrzyj()
{
	ustaw_zdrowie(0);
	//to nie koniec
}

void Stworzenie::ustaw_ruch(int x)
{
	punkty_ruchu = x;
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

bool Stworzenie::daj_prezent() const
{
	return false;
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
	cout<<"TROLE"<<endl;

}

void Stworzenie::atakuj(Stworzenie&)
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
	cout<<"TROLE"<<endl;
}



Bard::Bard(int x)
:Inteligentne()
{
	skarb = x;
}

Bard::~Bard()
{
}

void Bard::ustaw_skarb(int x)
{
	skarb = x;
}

int Bard::daj_skarb() const
{
	return skarb;
}

void Bard::interakcjuj(Poszukiwacz &poszukiwacz)
{
	if(poszukiwacz.daj_prezent() )
	{
		poszukiwacz.ustaw_prezent( false );
		//dalej nie dokonczone
	}
}

char Bard::jakie_stworzenie() const
{
	return 'B';
}

Sklepikarz::Sklepikarz()
:Inteligentne()
{
	ustaw_zdrowie(100);
	ustaw_sile(10);
	ustaw_ruch(100);
	zbroja.ustaw_klase_zbroi(0);
	bron.ustaw_klase_broni(0);
	
}

Sklepikarz::~Sklepikarz()
{
}

void Stworzenie::dostawa()
{

}

void Sklepikarz::dostawa()
{
	Zbroja  z;
	Bron b;
	int random_x = wylosuj(1,100);
	if( random_x % 2  ==  0)
	{
		z.ustaw_klase_zbroi(wylosuj(1,100));
		asortyment_zbroi.push_back(z);
	}
	random_x = wylosuj(1,100);
	if(random_x % 5 == 0)
	{
		b.ustaw_klase_broni(wylosuj(1,100));
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
	cout<<"Stworzeni zmienia bron "<<endl;
	cout<<"Aktualna bron "<<stworzenie.daj_bron()<<endl;


	if(stworzenie.jakie_stworzenie() == 'P' || stworzenie.jakie_stworzenie() == 'M')
	{
		if(!asortyment_broni.empty())
		{
			stworzenie.ustaw_bron(asortyment_broni.back().daj_klase_broni());
			asortyment_broni.pop_back();
		}
		if(!asortyment_zbroi.empty())
		{
			stworzenie.ustaw_zbroje(asortyment_zbroi.back().daj_klase_zbroi());
			asortyment_zbroi.pop_back();
		}
		if(liczba_prezentow > 0)
		{
			stworzenie.ustaw_prezent(true);
			liczba_prezentow--;
		}

	}
	cout<<"NOWA bron "<<stworzenie.daj_bron()<<endl;

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
		poszukiwacz.ustaw_zdrowie(100);
		poszukiwacz.ustaw_prezent(false);
	}
}

char Znachorka::jakie_stworzenie() const
{
	return 'Z';
}


Milosz::Milosz()
:Poszukiwacz()
{
	
	ustaw_zdrowie(30);
	ustaw_sile(100);
	ustaw_ruch(100);
	zbroja.ustaw_klase_zbroi(wylosuj(1,100));
	bron.ustaw_klase_broni(wylosuj(1,100));
	prezent.ustaw_prezent(true);

	cout<<"Bron "<<bron.daj_klase_broni()<<endl;
}

Milosz::~Milosz()
{
}

void Milosz::kup(const vector <Przedmiot>)
{
	
}

char Milosz::jakie_stworzenie() const
{
	return 'M';
}


Poszukiwacz::Poszukiwacz()
:Inteligentne()
{
	zbroja.ustaw_klase_zbroi(wylosuj(0,100));
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

bool Prymitywne::czy_atakowac(Stworzenie&) const
{
	
}

void Prymitywne::atakuj(Stworzenie&)
{
}



Wybredne::Wybredne()
:Prymitywne()
{
}

Wybredne::~Wybredne()
{
}

bool Wybredne::czy_atakowac(Stworzenie&) const
{
	
}

void Wybredne::atakuj(Stworzenie&)
{
	
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

bool Tchorzliwy::czy_atakowac(Stworzenie&) const
{
	
}

char Tchorzliwy::jakie_stworzenie() const
{
	return 'T';
}

Agresywny::Agresywny()
:Prymitywne()
{
	ustaw_zdrowie(55);
 	ustaw_sile(88);
	ustaw_ruch(55);
}

Agresywny::~Agresywny()
{
	
}

bool Agresywny::czy_atakowac(Stworzenie&) const
{
	
}

char Agresywny::jakie_stworzenie() const
{
	return 'A';
}


char Neutralny::jakie_stworzenie() const
{
	return 'N';
}

bool Neutralny::czy_atakowac(Stworzenie&) const
{
	
}

Neutralny::Neutralny()
{
	
}

Neutralny::~Neutralny()
{
	
}


