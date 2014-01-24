#include <cassert>
#include <random>
#include "stworzenie.h"



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


void Stworzenie::zabierz_ruch( int x )
{
	punkty_ruchu -= x;
 	assert (punkty_ruchu > 0);
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
	
	
	A.zdrowie -= int(this->sila * (this->zdrowie / 100) * 
	(1 + bron.daj_klase_broni())+(1-A.zbroja.daj_klase_zbroi()));
}

void Stworzenie::umrzyj()
{
	ustaw_zdrowie(0);
	/*
	 * 
	 * */
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

void Inteligentne::interakcjuj(Stworzenie&)
{
	
}

Bard::Bard()
:Inteligentne()
{
	
}

Bard::~Bard()
{
}

void Bard::interakcjuj(Stworzenie&)
{
	
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

void Sklepikarz::dostawa()
{
	cout<<zbroja.daj_klase_zbroi()<<endl;
	cout<<prezent.sprawdz_prezent()<<endl;
	
	zbroja.ustaw_klase_zbroi(wylosuj(0,100));
	bron.ustaw_klase_broni(wylosuj(0,100));
	prezent.ustaw_prezent(wylosuj(0,1));
	
	cout<<zbroja.daj_klase_zbroi()<<endl;
	cout<<prezent.sprawdz_prezent()<<endl;
}

void Sklepikarz::interakcjuj(Stworzenie&)
{
	
}

/*
 * ZNACHORKA
 * */


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

void Znachorka::interakcjuj(Poszukiwacz &poszukiwacz)
{
 	if(poszukiwacz.daj_prezent())
	{
		poszukiwacz.ustaw_zdrowie(100);
		poszukiwacz.ustaw_prezent(false);
	}
}



Milosz::Milosz()
:Poszukiwacz()
{
	
	ustaw_zdrowie(100);
	ustaw_sile(100);
	ustaw_ruch(430);
	zbroja.ustaw_klase_zbroi(wylosuj(0,100));
	bron.ustaw_klase_broni(wylosuj(0,100));
	
}

Milosz::~Milosz()
{
}

void Milosz::kup(const vector <Przedmiot>)
{
	
}



Poszukiwacz::Poszukiwacz()
:Inteligentne()
{
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

/*
 * METODY DO TESTOWANIA
 * */

float Stworzenie::z() const
{
	return zbroja.daj_klase_zbroi();
}

float Stworzenie::b() const
{
	return bron.daj_klase_broni();
}
bool Stworzenie::p() const
{
	return prezent.sprawdz_prezent();
}
