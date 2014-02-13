/*
 * ZAMIENIC INTERAKCJUJ NA SENSOWNA NAZWE
 * interakcjuj będzie odpowiedzialne za rózne interakcjie pomiedzy stworzeniami
 * */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "przedmioty.h"

#ifndef STWORZENIE_H
#define STWORZENIE_H

using namespace std;

class Poszukiwacz;
class Stworzenie;
class Inteligentne;
class Prymitywne;
class Pole;

int wylosuj(int a, int b);


class Stworzenie{

public:
	Stworzenie();
	virtual ~Stworzenie();

	int daj_zdrowie() const;
	int daj_sile() const;
	int daj_ruch() const;
	int daj_pole() const;
	float daj_bron() const;
	float daj_zbroje() const;

	bool zyje() const;
	void ustaw_pole(int x);
	void ustaw_ruch(int x);
	void ustaw_sile( int x );
	void ustaw_zdrowie(int x);
	void ustaw_bron(float x);
	void ustaw_zbroje(float x);
	void zabierz_ruch(int x);
	void zadaj_obrazenie(int x);
 	void uderz(Stworzenie&);
 	void umrzyj();
 	void ustaw_polozenie(Pole* pole);

  	virtual void wstaw_komunikat(string s, float x);
  	virtual void wstaw_komunikat_bez_liczby(string s) ;
	virtual void interakcjuj(Stworzenie &stworzenie);
	virtual void atakuj(Stworzenie &stworzenie);
	virtual char jakie_stworzenie() const = 0;
	virtual bool daj_prezent() const;
	virtual bool czy_atakowac(Stworzenie&) const;
	virtual void ustaw_prezent(bool x);
	virtual void dostawa();
	virtual bool czy_moze_kupic() const;
	virtual bool czy_wstawia() const;

	
	
protected:
	int zdrowie;
	int sila;
	int punkty_ruchu;
	int po;

	queue<string> komunikaty;
	Bron bron;
	Zbroja zbroja;
	Prezent prezent;
	Pole* polozenie;
};



class Inteligentne:public Stworzenie{

public:
	Inteligentne();
	virtual ~Inteligentne();

	virtual void interakcjuj(Poszukiwacz &stworzenie);
};


class Prymitywne:public Stworzenie{

public:	
	Prymitywne();
	virtual ~Prymitywne();

	virtual void interakcjuj(Stworzenie&);	//trololo
	virtual bool czy_atakowac(Stworzenie &stworzenie) const = 0;
	virtual void atakuj(Stworzenie &stworzenie);
};


class Poszukiwacz:public Inteligentne{
	
public:
	Poszukiwacz();
	virtual ~Poszukiwacz();

	float daj_zbroje() const;
	float daj_bron() const;
	void ustaw_prezent(bool x);
	
	virtual bool daj_prezent() const;
	virtual void kup(const vector <Przedmiot> przedmioty);
	virtual char jakie_stworzenie() const;
};

class Milosz: public Poszukiwacz{

public:
	Milosz();
	virtual ~Milosz();

	string daj_glowe() const;
	void usun_glowe();
	bool puste_komunikaty() const;

	virtual bool czy_wstawia() const;
	virtual void wstaw_komunikat(string s, float x);
	virtual void wstaw_komunikat_bez_liczby(string s);
	virtual bool czy_moze_kupic() const;
	virtual char jakie_stworzenie() const;
};


class Znachorka:public Inteligentne {

public:	
	Znachorka();
	virtual ~Znachorka();

	virtual char jakie_stworzenie() const;
	virtual void interakcjuj(Stworzenie &poszukiwacz);
};

class Sklepikarz:public Inteligentne{
	
public:
	Sklepikarz();
	virtual ~Sklepikarz();
	
	void dostawa();
	
	virtual void interakcjuj(Stworzenie &stworzenie);
	virtual char jakie_stworzenie() const;

private:
	vector<Bron> asortyment_broni;
	vector<Zbroja> asortyment_zbroi;
	int liczba_prezentow;

	
};


class Bard:public Inteligentne{

public:	
	Bard(int x);
	virtual ~Bard();
	
	void ustaw_skarb(int x);
	void pokaz();
	int daj_skarb() const;

	virtual void interakcjuj(Stworzenie &poszukiwacz);
	virtual char jakie_stworzenie() const;

private:
	int skarb;
	
};

class Wybredne:public Prymitywne{

public:
	Wybredne();
	virtual ~Wybredne();

	virtual bool czy_atakowac(Stworzenie &stworzenie) const;
	virtual void atakuj(Stworzenie &stworzenie);
	virtual char jakie_stworzenie() const;
};

class Tchorzliwy:public Prymitywne{

public:
	Tchorzliwy();
	virtual ~Tchorzliwy();

	virtual bool czy_atakowac(Stworzenie &stworzenie) const;
	virtual char jakie_stworzenie() const;

};


class Neutralny:public Prymitywne{

public:
	Neutralny();
	virtual ~Neutralny();

	virtual bool czy_atakowac(Stworzenie &stworzenie) const;
	virtual char jakie_stworzenie() const;

};

class Agresywny:public Prymitywne{

public:
	Agresywny();
	virtual ~Agresywny();
	
	virtual bool czy_atakowac(Stworzenie &stworzenie) const;
	virtual char jakie_stworzenie() const;

};
#endif
