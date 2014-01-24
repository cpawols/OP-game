#ifndef PRZEDMIOTY_H
#define PRZEDMIOTY_H

class Przedmiot{

};

class Zbroja : public Przedmiot{
public:	
	float daj_klase_zbroi() const;	

	float klasa_zbroi;
};

class Bron : public Przedmiot{
	
public:
	float daj_klase_broni() const;
	

	float klasa_broni;
};

class Prezent : public Przedmiot{
	
public:	
	bool sprawdz_prezent() const;
	

	bool czy_prezent;
};

#endif