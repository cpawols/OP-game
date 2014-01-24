#ifndef PRZEDMIOTY_H
#define PRZEDMIOTY_H

class Przedmiot{
	
};

class Zbroja : public Przedmiot{
  
public:	
	float daj_klase_zbroi() const;	
	void ustaw_klase_zbroi(float);
	
private:
	float klasa_zbroi;
};

class Bron : public Przedmiot{
	
public:
	float daj_klase_broni() const;
	void ustaw_klase_broni(float);
private:
	float klasa_broni;
};

class Prezent : public Przedmiot{
	
public:	
	bool sprawdz_prezent() const;
	void ustaw_prezent(int);

private:
	bool czy_prezent;
};

#endif