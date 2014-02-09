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
	int daj_bron() const;
	int daj_zbroje() const;


	void ustaw_pole(int x);
	void ustaw_ruch(int x);
	void ustaw_sile( int x );
	void ustaw_zdrowie(int x);
	void ustaw_bron(int x);
	void ustaw_zbroje(int x);
	void zabierz_ruch(int x);
	void zadaj_obrazenie(int x);
 	void uderz(Stworzenie&);
 	void umrzyj();

	virtual void interakcjuj(Stworzenie &stworzenie);
	virtual void atakuj(Stworzenie &stworzenie);
	virtual char jakie_stworzenie() const;
	virtual bool daj_prezent() const;
	virtual void ustaw_prezent(bool x);
	virtual void dostawa();
	//virtual string komunikat(const Stworzenie &stworzenie);				//oddawaie komunikatow przez rozne stworzenia
	
	
protected:
	int zdrowie;
	int sila;
	int punkty_ruchu;
	int po;
	Bron bron;
	Zbroja zbroja;
	Prezent prezent;
	Pole *polozenie;
	queue <string> infrmacje;
};



class Inteligentne:public Stworzenie{

public:
	Inteligentne();
	virtual ~Inteligentne();

	virtual void interakcjuj(Poszukiwacz &stworzenie);
 	//virtual string komunikat(const Stworzenie &stworzenie);
};


class Prymitywne:public Stworzenie{

public:	
	Prymitywne();
	virtual ~Prymitywne();

	virtual bool czy_atakowac(Stworzenie &stworzenie) const;
	virtual void atakuj(Stworzenie &stworzenie);
 	//virtual string komunikat(const Stworzenie &stworzenie);
};


class Poszukiwacz:public Inteligentne{
	
public:
	Poszukiwacz();
	virtual ~Poszukiwacz();

	Zbroja daj_zbroje() const;
	Bron daj_bron() const;
	void ustaw_prezent(bool x);
	virtual bool daj_prezent() const;
	virtual void kup(const vector <Przedmiot> przedmioty);
	virtual char jakie_stworzenie() const;

};

class Milosz: public Poszukiwacz{

public:
	Milosz();
	virtual ~Milosz();

	char jakie_stworzenie() const;
	void kup(const vector <Przedmiot> przedmioty);



private:
	
	vector <Przedmiot> *ekwipunek;

};


class Znachorka:public Inteligentne {

public:	
	Znachorka();
	virtual ~Znachorka();

	char jakie_stworzenie() const;

	virtual void interakcjuj(Stworzenie &poszukiwacz);

 	//string komunikat(const Stworzenie &);
};

class Sklepikarz:public Inteligentne{
	
public:
	Sklepikarz();
	virtual ~Sklepikarz();

	void interakcjuj(Stworzenie &stworzenie);
	void dostawa();

	char jakie_stworzenie() const;
 //	string komunikat(const Stworzenie &stworzenie);
private:
	vector<Bron> asortyment_broni;
	vector<Zbroja> asortyment_zbroi;
	int liczba_prezentow;

	
};

class Bard:public Inteligentne{

public:	
	Bard(int x);
	virtual ~Bard();

	void interakcjuj(Poszukiwacz &poszukiwacz);
	void ustaw_skarb(int x);

	char jakie_stworzenie() const;

	int daj_skarb() const;
// 	string komunikat(const Stworzenie &stworzenie);

private:

	int skarb;
	
};

class Wybredne:public Prymitywne{

public:
	Wybredne();
	virtual ~Wybredne();

	bool czy_atakowac(Stworzenie &stworzenie) const;
// 	string komunikat(const Stworzenie &stworzenie);
	void atakuj(Stworzenie &stworzenie);

	char jakie_stworzenie() const;

};

class Tchorzliwy:public Prymitywne{

public:
	Tchorzliwy();
	virtual ~Tchorzliwy();

	bool czy_atakowac(Stworzenie &stworzenie) const;
	char jakie_stworzenie() const;
// 	string komunikat(const Stworzenie &stworzenie);
};


class Neutralny:public Prymitywne{

public:
	Neutralny();
	virtual ~Neutralny();

	bool czy_atakowac(Stworzenie &stworzenie) const;
	char jakie_stworzenie() const;
// 	string komunikat(const Stworzenie &stworzenie);
};

class Agresywny:public Prymitywne{

public:
	Agresywny();
	virtual ~Agresywny();

	bool czy_atakowac(Stworzenie &stworzenie) const;
	char jakie_stworzenie() const;
// 	string komunikat(const Stworzenie &stworzenie);
};
#endif

