#ifndef PLANSZA_H
#define PLANSZA_H
#include "stworzenie.h"

/*
 * Interakcjuj ma byc odpowiedzialne glownie za "odbieranie" punktow sily za ruch po danym polu
 * */
class Pole;
class Stworzenie;

class Plansza{
	friend class Stworzenie;
public:
	Plansza();
	Pole** plansza;					//wskaznik na tablice jednowymiarwa
	void wczytaj();
	void wypisz() const;
	void rusz_milosza();
	void rusz_reszte();
private:
	Milosz* milosz;
	vector<int> stwory;
	int dl;
	int sz;
	
};

class Pole{
	friend class Stworzenie;
	
public:
	Pole();
	virtual ~Pole();
	int dzialaj(Stworzenie &stworzenie) ; //koszt przejscia po danym polu, obrażenie, zabicie
	virtual bool czy_mozna_wejsc() const = 0;
	virtual bool czy_smiertelne() const;
	virtual char jakie_pole() const = 0;
	virtual int ruch() const = 0; //zwraca liczbe punktow ruchu potrzebych do wejscia na to pole
	virtual int obrazenie() const;
// 	void rusz_milosz();
	void postaw(Stworzenie&);
	void usun();
	bool spr() const;
	char oddaj() const;
	
protected:
	int x;		
	int y;
	int koszt_przejscia;
	Stworzenie* stworek;	
	
};

class Dozwolone : public Pole {
public:	
	Dozwolone();
	virtual ~Dozwolone();
	virtual	bool czy_mozna_wejsc() const; 			//juz nic nie chce przedefiniowac bo wszystko wiem
	
};

class Zakazane : public Pole {
public:
	Zakazane();
	virtual ~Zakazane();
	virtual bool czy_mozna_wejsc() const; 		//juz nic nie chce przedefiniowac bo wszystko wiem
	
};

class Trawa : public Dozwolone{
public:
	Trawa();
	virtual ~Trawa();
	int ruch() const;
	char jakie_pole() const;
	
};

class Rzeka : public Dozwolone{
public:
	Rzeka();
	virtual ~Rzeka();
	int ruch() const;
	int obrazenie() const;
	char jakie_pole() const;
	
};

class Jaskinia : public Dozwolone{
public:	
	Jaskinia();
	virtual ~Jaskinia();
	int ruch() const;
	char jakie_pole() const;
	
};

class Bagna : public Dozwolone{
public:
	Bagna();
	virtual ~Bagna();
	virtual char jakie_pole() const;
	
};

class Bagna_lagodne : public Bagna{
public:	
	Bagna_lagodne();
	virtual ~Bagna_lagodne();
	int ruch() const;
	int obrazenie() const;
	char jakie_pole() const;
	
};

class Bagna_smiertelne: public Bagna{
public:	
	Bagna_smiertelne();
	virtual ~Bagna_smiertelne();
	bool czy_smiertelne() const;
	int ruch() const;
	char jakie_pole() const;
};

class Droga : public Dozwolone{
public:
	Droga();
	virtual ~Droga();
	int ruch() const;
	char jakie_pole() const;
};

class Gory : public  Dozwolone{
public:
	Gory();
	virtual ~Gory();
	int ruch() const;
	int obrazenie() const;
	char jakie_pole() const;

};

class Skaly:public Zakazane{
public:	
	Skaly();
	virtual ~Skaly();
	int ruch() const;
	char jakie_pole() const;
};

#endif
