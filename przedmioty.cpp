#include "przedmioty.h"


bool Prezent::sprawdz_prezent() const
{
	return czy_prezent;
}

void Prezent::ustaw_prezent(int x)
{
	czy_prezent = x;
}

float Bron::daj_klase_broni() const
{
	return klasa_broni;
}

void Bron::ustaw_klase_broni(float x)
{
	klasa_broni = x;
}

float Zbroja::daj_klase_zbroi() const
{
	return klasa_zbroi;
}

void Zbroja::ustaw_klase_zbroi(float x)
{
	klasa_zbroi = x;
}

