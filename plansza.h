#ifndef PLANSZA_H
#define PLANSZA_H
#include "stworzenie.h"


class Pole;
class Stworzenie;

class Plansza{

public:
	Plansza();
	virtual ~Plansza();

	void wczytaj(char** argv);
	void wypisz() const;
	void posprzataj();
	void rusz_milosza();
	void pokaz_skarb();
	void rusz_reszte();
	void rozegraj(char** argv);
	bool widac_skarb() const;
	bool daj_koniec_gry() const;
	void ustaw_koniec_gry(bool x);
	void miejsce_skarbu(int x);
	void gra(char** argv);
	int pol()const;

private:

	Pole** plansza;
	Milosz* milosz;
	std::vector<Stworzenie*> stwory;
	int dl;
	int sz;
	int polozenie_skarbu;
	bool widac;
	bool koniec_gry;
};

class Pole{
	
public:

	Pole(Plansza* x);
	virtual ~Pole();

	void dzialaj(Stworzenie &stworzenie) ;
	void postaw(Stworzenie&);
	void usun_z_pola();
	void usun();

	int daj_skarb() const;

	bool spr() const;
	bool widac() const;
	char oddaj() const;
	
	virtual bool czy_mozna_wejsc() const = 0;
	virtual bool czy_smiertelne() const;
	virtual char jakie_pole() const = 0;
	virtual int ruch() const = 0;
	virtual int obrazenie() const;

	Stworzenie* daj_stworzenie() const;
	Plansza* daj_plansze() const;
	
protected:

	int koszt_przejscia;
	Stworzenie* stworek;
	Plansza* plansza1;
};

class Dozwolone : public Pole {

public:	

	Dozwolone(Plansza* plansza);
	virtual ~Dozwolone();
	
	virtual	bool czy_mozna_wejsc() const;
	
};

class Zakazane : public Pole {

public:

	Zakazane(Plansza* plansza);
	virtual ~Zakazane();

	virtual bool czy_mozna_wejsc() const;
	
};

class Trawa : public Dozwolone{

public:
	Trawa(Plansza*);
	virtual ~Trawa();

	virtual int ruch() const;
	virtual char jakie_pole() const;
};

class Rzeka : public Dozwolone{

public:
	Rzeka(Plansza*);
	virtual ~Rzeka();

	virtual int ruch() const;
	virtual int obrazenie() const;
	virtual char jakie_pole() const;
};

class Jaskinia : public Dozwolone{

public:	
	Jaskinia(Plansza*);
	virtual ~Jaskinia();

	virtual int ruch() const;
	virtual char jakie_pole() const;
};

class Bagna : public Dozwolone{

public:
	Bagna(Plansza*);
	virtual ~Bagna();

	virtual char jakie_pole() const = 0;
	
};

class Bagna_lagodne : public Bagna{

public:	
	Bagna_lagodne(Plansza*);
	virtual ~Bagna_lagodne();

	virtual int ruch() const;
	virtual int obrazenie() const;
	virtual char jakie_pole() const;
};

class Bagna_smiertelne: public Bagna{

public:	
	Bagna_smiertelne(Plansza*);
	virtual ~Bagna_smiertelne();

	virtual bool czy_smiertelne() const;
	virtual int ruch() const;
	virtual char jakie_pole() const;
};

class Droga : public Dozwolone{

public:
	Droga(Plansza*);
	virtual ~Droga();

	virtual int ruch() const;
	virtual char jakie_pole() const;
};

class Gory : public  Dozwolone{

public:
	Gory(Plansza*);
	virtual ~Gory();

	virtual int ruch() const;
	virtual int obrazenie() const;
	virtual char jakie_pole() const;
};

class Skaly:public Zakazane{

public:	
	Skaly(Plansza*);
	virtual ~Skaly();

	virtual int ruch() const;
	virtual char jakie_pole() const;
};

#endif
