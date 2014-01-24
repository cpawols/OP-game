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
	this->prezent.czy_prezent = 0;
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
	this->zdrowie -= x;
}

void Stworzenie::uderz( Stworzenie&  A)
{
	/*
	 * this bije A
	 */
	
	
	A.zdrowie -= int(this->sila * (this->zdrowie / 100) * 
	(1 + this->bron.klasa_broni)+(1-A.zbroja.klasa_zbroi));
}

void Stworzenie::umrzyj()
{
	this->zdrowie = 0;
	/*
	 * 
	 * */
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
	this->sila = x;
}

void Stworzenie::ustaw_zdrowie( int x)
{
	this->zdrowie = x;
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
	this->zdrowie = 100;
	this->sila = 10;
	this -> punkty_ruchu = 100;
	this->zbroja.klasa_zbroi = 0;
	this->bron.klasa_broni =0;
	
}

Sklepikarz::~Sklepikarz()
{
}

void Sklepikarz::dostawa()
{
	cout<<this->zbroja.klasa_zbroi<<endl;
	cout<<this->prezent.czy_prezent<<endl;
	
	this->zbroja.klasa_zbroi = wylosuj(0,100);
	this->bron.klasa_broni = wylosuj(0,100);
	this->prezent.czy_prezent = wylosuj(0,1);
	
	cout<<this->zbroja.klasa_zbroi<<endl;
	cout<<this->prezent.czy_prezent<<endl;
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
	this->zdrowie = 100;
	this->sila = 10;
	this -> punkty_ruchu = 100;
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
	
	this->zdrowie = 100;
 	this->sila = 100;
	this-> punkty_ruchu = 100;	
	this->zbroja.klasa_zbroi = wylosuj(0,100);
	this->bron.klasa_broni  = wylosuj(0,100);
	
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
	this->prezent.czy_prezent = false; //ustawia wszystkim poszukiwaczom brak prezentu.
}

Poszukiwacz::~Poszukiwacz()
{
}

void Poszukiwacz::kup(const vector <Przedmiot> przedmioty)
{
	
}

void Poszukiwacz::ustaw_prezent(bool x)
{
	this->prezent.czy_prezent = x;
}

bool Poszukiwacz::daj_prezent() const
{
	return this->prezent.czy_prezent;
}






Prymitywne::Prymitywne()
:Stworzenie()
{
	this->zbroja.klasa_zbroi = 0;
	this->bron.klasa_broni = 0;
	this->prezent.czy_prezent = false;
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
	this->zdrowie = 55;
 	this->sila = 88;
	this-> punkty_ruchu = 100;	
}

Agresywny::~Agresywny()
{
	
}

bool Agresywny::czy_atakowac(Stworzenie&) const
{
	
}
