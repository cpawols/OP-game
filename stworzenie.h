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
	int daj_zdrowie() const;				//zwraca zdrowie danego stworzenia
	int daj_sile() const;	//zwraca sile danego stworzenia
	int daj_ruch() const;
	void ustaw_pole(int x);
	int daj_pole() const;
	void ustaw_ruch(int x);
	void ustaw_sile( int x );				//ustawia sile danego stworzenia
	void ustaw_zdrowie(int x);				// ustawia zdrowie danego stworzenia
// /*NIE*/	void rusz();	//ZMIENIAM TYP
	void zabierz_ruch(int x);
	void zadaj_obrazenie(int x);
 	void uderz(Stworzenie&); 	//odpowiedzialna za zadawanie obrażeń.
/*NIE*/	void umrzyj();

	virtual void interakcjuj(Stworzenie &stworzenie);
	virtual void atakuj(Stworzenie &stworzenie);
	virtual char jakie_stworzenie() const;
// 	
	//virtual string komunikat(const Stworzenie &stworzenie);				//oddawaie komunikatow przez rozne stworzenia
	/* METODY TYLKO DO TESTOW
	 */
	
	float z() const;	//daje klase zbroi
	float b() const;
	bool p() const;
	
protected:							//konieczie protected bo prawie wszystko dziedziczy po tym
	int zdrowie;						//zdrowie stworzenia
	int sila;
	int punkty_ruchu;
	Bron bron;
	Zbroja zbroja;
	Prezent prezent;
	int po;
	Pole *polozenie;	//byc moze nie potrzebne wystarczy int
	queue <string> infrmacje;				//do dodawania komunikatw
};

// class Poszukiwacz;

class Inteligentne:public Stworzenie{

public:
	Inteligentne();
	virtual ~Inteligentne();
	virtual void interakcjuj(Stworzenie &stworzenie);	//zmienia mlosza
// 	virtual string komunikat(const Stworzenie &stworzenie);
	/*
	 * Do przedefiniowania w kilku miejscach
	 * */
};


class Prymitywne:public Stworzenie{

public:	
	Prymitywne();
	virtual ~Prymitywne();
	virtual bool czy_atakowac(Stworzenie &stworzenie) const;
	virtual void atakuj(Stworzenie &stworzenie);
	
// 	virtual string komunikat(const Stworzenie &stworzenie);
};


class Poszukiwacz:public Inteligentne{
	
public:
	Poszukiwacz();						//spladzamy poszukiwacza
	virtual ~Poszukiwacz();//zabijamy poszukiwacza
	Zbroja daj_zbroje() const;
	Bron daj_bron() const;			
	bool daj_prezent() const;
	void ustaw_prezent(bool x);		//zwracamy te trzy
	virtual void kup(const vector <Przedmiot> przedmioty);	//kupujemy od sklepikarza
	virtual char jakie_stworzenie() const;
	
	
protected:
	
	/*Zbroja zbroja;
	Bron bron;
	Prezent prezent;
	*/
};

class Milosz: public Poszukiwacz{				//chyba wszystko

public:
	Milosz();
	virtual ~Milosz();
	void kup(const vector <Przedmiot> przedmioty);		//przedefiniowac
	char jakie_stworzenie() const;
	
private:
	
	vector <Przedmiot> *ekwipunek;		//wskaznik na to z czym bedzie chodzil

};


class Znachorka:public Inteligentne {

public:	
	Znachorka();						//spladzamy znachorke
	virtual ~Znachorka();
	void interakcjuj(Poszukiwacz &poszukiwacz);
	char jakie_stworzenie() const;
// 	string komunikat(const Stworzenie &stworzenie);
};

class Sklepikarz:public Inteligentne{
	
public:
	Sklepikarz();
	virtual ~Sklepikarz();
	void interakcjuj(Stworzenie &stworzenie);		//przedefiniowac na sprzedawanie
	void dostawa();
	char jakie_stworzenie() const;
// 	string komunikat(const Stworzenie &stworzenie);
	
};

class  Bard:public Inteligentne{

public:	
	Bard();
	virtual ~Bard();
	void interakcjuj(Stworzenie &stworzenie);
	char jakie_stworzenie() const;
// 	string komunikat(const Stworzenie &stworzenie);
	/*
	 * Pozostaje problem jak rozwiazac to co Bard nam przekazuje, 
	 * zeby nie wiazac tego zbyt mocno z interfejsem
	 * */
private:
	//jak ma przechowywac skarb.
	
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