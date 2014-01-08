class Przedmiot{

};

class Zbroja : public Przedmiot{
	
	float daj_klase_zbroi() const;
	
private:
	float klasa_zbroi;
};

class Bron : public Przedmiot{
	
public:
	float daj_klase_broni() const;
	
private:
	float klasa_broni;
};

class Prezent : public Przedmiot{
	
public:	
	bool sprawdz_prezent() const;
	
public:
	bool czy_prezent;
};