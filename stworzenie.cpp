#include <cassert>
#include "stworzenie.h"

Stworzenie::Stworzenie()
{
}

Stworzenie::~Stworzenie()
{
}

Inteligentne::Inteligentne()
:Stworzenie()
{
}

Inteligentne::~Inteligentne()
{
}

Bard::Bard()
:Inteligentne()
{
	
}

Bard::~Bard()
{
}

Sklepikarz::Sklepikarz()
:Inteligentne()
{
	
}

Sklepikarz::~Sklepikarz()
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
	this->zdrowie = 10;
	this->sila = 88;
	this-> punkty_ruchu = 100;	
	
}

Milosz::~Milosz()
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



Prymitywne::Prymitywne()
:Stworzenie()
{
}

Prymitywne::~Prymitywne()
{
}

Wybredne::Wybredne()
:Prymitywne()
{
}

Wybredne::~Wybredne()
{
}

Tchorzliwy::Tchorzliwy()
:Prymitywne()
{
}

Tchorzliwy::~Tchorzliwy()
{
}

Agresywny::Agresywny()
:Prymitywne()
{
}

Agresywny::~Agresywny()
{
	
}

//STWORZENIE

void Stworzenie::zabierz_ruch( int x )
{
	this->punkty_ruchu -= x;
	assert (punkty_ruchu < 0);
}

void Stworzenie::zadaj_obrazenie( int x )
{
	this->zdrowie -= x;
}

void Stworzenie::umrzyj()
{
	this->zdrowie = 0;
}

int Stworzenie::daj_zdrowie() const
{
	return zdrowie;
}

int Stworzenie::daj_sile() const
{
	return sila;
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



void Inteligentne::interakcjuj(Stworzenie&)
{
	
}

void Milosz::kup(const vector <Przedmiot>)
{
	
}


void Bard::interakcjuj(Stworzenie&)
{
	
}

void Sklepikarz::interakcjuj(Stworzenie&)
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

void Stworzenie::atakuj(Stworzenie&)
{
	
}

//PRYMITYWNE

bool Prymitywne::czy_atakowac(Stworzenie&) const
{
	
}

void Prymitywne::atakuj(Stworzenie&)
{
}

//AGRESYWNE

bool Agresywny::czy_atakowac(Stworzenie&) const
{
	
}

//TCHORZLIWY

bool Tchorzliwy::czy_atakowac(Stworzenie&) const
{
	
}


//WYBREDNE

bool Wybredne::czy_atakowac(Stworzenie&) const
{
	
}

void Wybredne::atakuj(Stworzenie&)
{
	
}
