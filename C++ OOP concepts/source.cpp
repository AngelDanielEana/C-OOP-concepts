#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>
#include <set>
#include <list>
using namespace std;


//Tema proiectului: Depozit de alimente 
//(E - Eana, D - Daniel)

//Am ales aceasta tema, deoarece mi-as dori pe viitor sa am o afacere de genul.
//Spre exemplu, franciza de la MegaImage mi se pare profitabila, desi aceste depozite de alimente sunt la tot pasul.


//CLASA ABSTRACTA
class Sablon
{
public:
	//functii virtual pure
	virtual string returneazaClasaInCareMaAflu() = 0;
	virtual void resetareObiect() = 0;
};
//Clasa RaportAfisare are rolul de a permite generarea unui rapoarta care sa analizeze activitatea utilizatorilor.
class RaportAfisare
{
	int nrAfisari;

public:

	RaportAfisare() {
		this->nrAfisari = 0;
	}

	void crestereAfisari() {
		this->nrAfisari++;
	}

	void raportAfisari(ofstream& fout) {

		fout << "S-a folosit functia de afisare de " << this->nrAfisari << " ori " << endl;
	}

};

RaportAfisare dm;

class Angajat :public Sablon
{
public:
	char* nume;
	string functie;
	int varsta;
	float salariu;
	float oreLucratePeZi[7]; //(7 zile/saptamana)
	int nrPrime;
	float* valoarePrime;
	bool sporDeNoapte;
public:

	//constructor fara parametrii pentru clasa Angajat

	Angajat()
	{
		this->nume = new char[strlen("Necunoscut") + 1];
		strcpy(this->nume, "Necunoscut");
		this->functie = "Necunoscuta";
		this->varsta = 0;
		this->salariu = 0;
		for (int i = 0; i < 7; i++)
		{
			this->oreLucratePeZi[i] = 0;
		}
		this->nrPrime = 0;
		this->valoarePrime = NULL;
		this->sporDeNoapte = 0;
	}
	//constructor cu toti parametrii pentru clasa Angajat

	Angajat(const char* nume, string functie, int varsta, float salariu, float oreLucratePeZi[7], int nrPrime, float* valoarePrime, bool sporDeNoapte)
	{
		if (strlen(nume) >= 3)
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
		else
		{
			this->nume = new char[strlen("Necunoscut") + 1];
			strcpy(this->nume, "Necunoscut");
			cout << "Eroare introducere date! " << endl;
		}

		if (functie.length() >= 1)
		{
			this->functie = functie;
		}
		else
		{
			this->functie = "Necunoscuta";
		}

		if (varsta >= 18 && varsta <= 65)
		{
			this->varsta = varsta;
		}
		else
		{
			this->varsta = 0;
		}

		if (salariu >= 0)
		{
			this->salariu = salariu;
		}
		else
		{
			this->salariu = 0;
		}

		if (nrPrime > 0 && valoarePrime != NULL)
		{
			this->nrPrime = nrPrime;
			this->valoarePrime = new float[this->nrPrime];

			for (int i = 0; i < this->nrPrime; i++)
			{
				this->valoarePrime[i] = valoarePrime[i];
			}
		}
		else
		{
			this->nrPrime = 0;
			this->valoarePrime = NULL;
		}

		for (int i = 0; i < 7; i++)
		{
			this->oreLucratePeZi[i] = oreLucratePeZi[i];
		}

		if (sporDeNoapte == 1 || sporDeNoapte == 0)
		{
			this->sporDeNoapte = sporDeNoapte;
		}
		else
		{
			this->sporDeNoapte = 0;
		}

	}
	// destructor pentru clasa Angajat

	~Angajat()
	{
		if (this->nume != NULL)
		{
			delete[] this->nume;
		}


		if (this->valoarePrime != NULL)
		{
			delete[] this->valoarePrime;
		}

	}

	//GETTERI pentru clasa Angajat 

	char* getNume()
	{
		return this->nume;
	}

	string getFunctie()
	{
		return this->functie;
	}

	int getVarsta()
	{
		return this->varsta;
	}

	float getSalariu()
	{
		return this->salariu;
	}

	int getNrPrime()
	{
		return this->nrPrime;
	}

	float* getOreLucratePeZi()
	{
		return this->oreLucratePeZi;
	}

	float* getvaloarePrime()
	{
		return this->valoarePrime;
	}

	bool getSporDeNoapte()
	{
		return this->sporDeNoapte;
	}

	//SETTERI pentru clasa Angajat

	void setNume(const char* numeNew)
	{
		if (this->nume != NULL)
		{
			delete[] this->nume;
		}
		this->nume = new char[strlen(numeNew) + 1];
		strcpy(this->nume, numeNew);
	}

	void setFunctie(string functieNew)
	{
		this->functie = functieNew;
	}
	void setVarsta(int varstaNew)
	{
		this->varsta = varstaNew;
	}
	void setSalariu(float salariuNew)
	{
		this->salariu = salariuNew;
	}

	void setOreLucratePeZi(float oreLucratePeZiNew[7])
	{
		for (int i = 0; i < 7; i++)
		{
			this->oreLucratePeZi[i] = oreLucratePeZiNew[i];
		}
	}

	void setPrime(int nrPrimeNew, float* valoarePrimeNew)
	{
		if (this->valoarePrime != NULL)
		{
			delete[] this->valoarePrime;
		}
		this->nrPrime = nrPrimeNew;
		this->valoarePrime = new float[this->nrPrime];
		for (int i = 0; i < this->nrPrime; i++)
		{
			this->valoarePrime[i] = valoarePrimeNew[i];
		}
	}

	void setSporDeNoapte(bool sporDeNoapteNew)
	{
		this->sporDeNoapte = sporDeNoapteNew;
	}

	//Constructorul de copiere pentru clasa Angajat

	Angajat(const Angajat& obj)
	{
		if (strlen(obj.nume) >= 3)
		{
			this->nume = new char[strlen(obj.nume) + 1];
			strcpy(this->nume, obj.nume);
		}
		else
		{
			this->nume = new char[strlen("Necunoscut") + 1];
			strcpy(this->nume, "Necunoscut");
		}
		if (obj.functie.length() >= 1)
		{
			this->functie = obj.functie;
		}
		else
		{
			this->functie = "Necunoscuta";
		}
		if (obj.varsta >= 18)
		{
			this->varsta = obj.varsta;
		}
		else
		{
			this->varsta = 0;
		}
		if (obj.salariu >= 0)
		{
			this->salariu = obj.salariu;
		}
		else
		{
			this->salariu = 0;
		}

		if (obj.nrPrime > 0 && obj.valoarePrime != NULL)
		{
			this->nrPrime = obj.nrPrime;
			this->valoarePrime = new float[this->nrPrime];

			for (int i = 0; i < this->nrPrime; i++)
			{
				this->valoarePrime[i] = obj.valoarePrime[i];
			}
		}
		else
		{
			this->nrPrime = 0;
			this->valoarePrime = NULL;
		}
		for (int i = 0; i < 7; i++)
		{
			this->oreLucratePeZi[i] = obj.oreLucratePeZi[i];
		}
		if (obj.sporDeNoapte == 1 || obj.sporDeNoapte == 0)
		{
			this->sporDeNoapte = obj.sporDeNoapte;
		}
		else
		{
			this->sporDeNoapte = 0;
		}
	}

	//operator = (egal) pentru clasa Angajat

	Angajat& operator=(const Angajat& obj)
	{
		if (this != &obj) // conditie pentru evitarea autoasignarii.
		{
			if (this->nume != NULL)
			{
				delete[] this->nume;
			}

			if (this->valoarePrime != NULL)
			{
				delete[] this->valoarePrime;
			}

			if (strlen(obj.nume) >= 3)
			{
				this->nume = new char[strlen(obj.nume) + 1];
				strcpy(this->nume, obj.nume);
			}
			else
			{
				this->nume = new char[strlen("Necunoscut") + 1];
				strcpy(this->nume, "Necunoscut");
			}
			if (obj.functie.length() >= 1)
			{
				this->functie = obj.functie;
			}
			else
			{
				this->functie = "Necunoscuta";
			}
			if (obj.varsta >= 18)
			{
				this->varsta = obj.varsta;
			}
			else
			{
				this->varsta = 0;
			}
			if (obj.salariu >= 0)
			{
				this->salariu = obj.salariu;
			}
			else
			{
				this->salariu = 0;
			}

			if (obj.nrPrime > 0 && obj.valoarePrime != NULL)
			{
				this->nrPrime = obj.nrPrime;
				this->valoarePrime = new float[this->nrPrime];

				for (int i = 0; i < this->nrPrime; i++)
				{
					this->valoarePrime[i] = obj.valoarePrime[i];
				}
			}
			else
			{
				this->nrPrime = 0;
				this->valoarePrime = NULL;
			}
			for (int i = 0; i < 7; i++)
			{
				this->oreLucratePeZi[i] = obj.oreLucratePeZi[i];
			}
			if (obj.sporDeNoapte == 1 || obj.sporDeNoapte == 0)
			{
				this->sporDeNoapte = obj.sporDeNoapte;
			}
			else
			{
				this->sporDeNoapte = 0;
			}
		}
		return *this;
	}
	//operatorul << (afisare) pentru clasa Angajat.

	friend ostream& operator<<(ostream& out, const Angajat& obj)
	{
		out << "Nume angajat: " << obj.nume << endl;
		out << "Functie angajat: " << obj.functie << endl;
		out << "Varsta angajat: " << obj.varsta << endl;
		out << "Salariu angajat: " << obj.salariu << endl;
		for (int i = 0; i < 7; i++)
		{
			out << "Ore lucrate pe zi: " << obj.oreLucratePeZi[i] << endl;
		}
		out << "Spor de noapte: " << obj.sporDeNoapte << endl;
		out << "Numar prime: " << obj.nrPrime << endl;

		for (int i = 0; i < obj.nrPrime; i++)
		{
			out << "Valoare prime: " << obj.valoarePrime[i] << endl;

		}
		return out;
	}

	// Operatorul >> (citire) pentru clasa Angajat.

	friend istream& operator>>(istream& in, Angajat& obj)
	{
		if (obj.nume != NULL)
		{
			delete[] obj.nume;
		}


		if (obj.valoarePrime != NULL)
		{
			delete[] obj.valoarePrime;
		}

		cout << "Nume angajat: " << endl;
		char aux[100];
		in >> aux;
		obj.nume = new char[strlen(aux) + 1];
		strcpy(obj.nume, aux);
		cout << "Functie angajat: " << endl;
		in >> obj.functie;
		cout << "Varsta angajat: " << endl;
		in >> obj.varsta;
		cout << "Salariu angajat: " << endl;
		in >> obj.salariu;
		cout << "Spor de noapte: " << endl;
		in >> obj.sporDeNoapte;
		cout << "Numar prime: " << endl;
		in >> obj.nrPrime;
		obj.valoarePrime = new float[obj.nrPrime];
		for (int i = 0; i < obj.nrPrime; i++)
		{
			cout << "Valoare prime: " << endl;
			in >> obj.valoarePrime[i];

		}
		cout << "Ore lucrate pe zi: " << endl;
		for (int i = 0; i < 7; i++)
		{
			in >> obj.oreLucratePeZi[i];
		}
		return in;
	}

	//operator indexare[]. Returneaza elementul de pe pozitia dorita

	float operator[](int pozitieDorita)
	{
		if (pozitieDorita >= 0 && pozitieDorita < this->nrPrime)
		{
			return this->valoarePrime[pozitieDorita];
		}
		else
		{
			return -1;
		}

	}

	// operator ! (negatie). Transforma din 1(adevarat) in 0(fals)

	friend void operator!(Angajat& obj)
	{
		if (obj.sporDeNoapte == 0)
		{
			obj.sporDeNoapte = 1;
		}
		else
		{
			obj.sporDeNoapte = 0;
		}
	}

	// operator > Compara valorile primelor 

	bool operator>(float val)
	{
		float suma1 = 0;
		for (int i = 0; i < this->nrPrime; i++)
		{
			suma1 = suma1 + this->valoarePrime[i];
		}
		return suma1 > val;
	}
	// forma preincrementata a operatorului ++
	Angajat& operator++() {
		this->varsta += 10;
		return *this;
	}
	// forma postincrementata a operatorului ++
	Angajat  operator++(int) {
		Angajat c = (*this);
		this->varsta += 10;
		return c;
	}

	// operator  == Arata daca varsta a doi angajati este egala. In cazul in care se dovedeste adevarat, returneaza valoarea true, altfel false;
	bool operator ==(Angajat obj)
	{
		if (this->varsta == obj.varsta) {
			return true;
		}
		else
		{
			return false;
		}
	}
	//operator de cast. Acest operator arata care sunt primele angajatilor care depasesc 150. 
	operator int()
	{
		int contor = 0;
		for (int i = 0; i < this->nrPrime; i++)
		{
			if (this->valoarePrime[i] > 150)
			{
				contor++;
			}
		}
		return contor;
	}
	// Metoda care arata valoarea medie a primelor.
	float valoareMediePrima(/*this*/)
	{
		float suma = 0;
		for (int i = 0; i < this->nrPrime; i++)
		{
			suma = suma + this->valoarePrime[i];
		}
		float primeMedii = suma / this->nrPrime;
		return primeMedii;
	}
	// Metoda care arata valoarea maxima a primelor.
	float valoareMaximPrima()
	{
		float primeMax = this->valoarePrime[0];
		for (int i = 1; i < this->nrPrime; i++)
		{
			if (primeMax < this->valoarePrime[i])
			{
				primeMax = this->valoarePrime[i];
			}
		}
		return primeMax;
	}

	//Fisiere text pentru clasa Angajat

	friend ofstream& operator<<(ofstream& file, Angajat& obj)
	{
		file << obj.nume << endl;
		file << obj.functie << endl;
		file << obj.varsta << endl;
		file << obj.salariu << endl;
		for (int i = 0; i < 7; i++)
		{
			file << obj.oreLucratePeZi[i] << endl;
		}
		file << obj.sporDeNoapte << endl;
		file << obj.nrPrime << endl;

		for (int i = 0; i < obj.nrPrime; i++)
		{
			file << obj.valoarePrime[i] << endl;

		}

		return file;
	}
	// Citire fisier text clasa Angajat

	friend ifstream& operator>>(ifstream& file, Angajat& obj)
	{
		if (obj.nume != NULL)
		{
			delete[] obj.nume;
		}


		if (obj.valoarePrime != NULL)
		{
			delete[] obj.valoarePrime;
		}

		char aux[100];
		file >> aux;
		obj.nume = new char[strlen(aux) + 1];
		strcpy(obj.nume, aux);

		file >> obj.functie;
		file >> obj.varsta;
		file >> obj.salariu;

		for (int i = 0; i < 7; i++)
		{
			file >> obj.oreLucratePeZi[i];
		}

		file >> obj.sporDeNoapte;
		file >> obj.nrPrime;
		obj.valoarePrime = new float[obj.nrPrime];
		for (int i = 0; i < obj.nrPrime; i++)
		{
			file >> obj.valoarePrime[i];

		}

		return file;

	}
	//Scriere in fisier binar clasa Angajat
	void scriereBinarAngajat(fstream& file)
	{
		//char* nume
		int lungime1 = strlen(this->nume);
		file.write((char*)&lungime1, sizeof(int));
		for (int i = 0; i < lungime1; i++)
		{
			file.write((char*)&this->nume[i], sizeof(char));
		}
		// int varsta
		file.write((char*)&this->varsta, sizeof(int));

		//float salariu
		file.write((char*)&this->salariu, sizeof(float));

		//float oreLucratePeZi
		for (int i = 0; i < 7; i++)
		{
			file.write((char*)&this->oreLucratePeZi[i], sizeof(float));
		}

		//string functie
		int lungime2 = this->functie.size();
		file.write((char*)&lungime2, sizeof(int));
		file.write(this->functie.c_str(), lungime2);
		//int nrPrime
		file.write((char*)&this->nrPrime, sizeof(int));

		for (int i = 0; i < this->nrPrime; i++)
		{
			//valoare prime
			file.write((char*)&this->valoarePrime[i], sizeof(float));
		}
		// bool spor de noapte
		file.write((char*)&this->sporDeNoapte, sizeof(bool));
	}
	//Citire fisier binar clasa Angajat
	void CitireBinarAngajat(fstream& file)
	{
		//dezalocare memorie
		if (this->nume != NULL)
		{
			delete[] this->nume;
		}
		// char* nume
		if (this->valoarePrime != NULL)
		{
			delete[] this->valoarePrime;
		}
		int nrLitereNume;
		file.read((char*)&nrLitereNume, sizeof(int));
		this->nume = new char[nrLitereNume + 1];
		for (int i = 0; i < nrLitereNume; i++)
		{
			file.read((char*)&this->nume[i], sizeof(char));
		}
		this->nume[nrLitereNume] = '\0';
		//int varsta
		file.read((char*)&this->varsta, sizeof(int));
		//float salariu
		file.read((char*)&this->salariu, sizeof(float));
		//float ore lucrate pe zi
		for (int i = 0; i < 7; i++)
		{
			file.read((char*)&this->oreLucratePeZi[i], sizeof(float));
		}
		//string functie 
		int nrLitereFunctie;
		file.read((char*)&nrLitereFunctie, sizeof(int));
		string aux;
		aux.resize(nrLitereFunctie);
		file.read((char*)aux.c_str(), nrLitereFunctie);
		this->functie = aux;

		//int nrPrime 
		file.read((char*)&this->nrPrime, sizeof(int));
		this->valoarePrime = new float[this->nrPrime];
		for (int i = 0; i < this->nrPrime; i++)
		{
			//valoare prime
			file.read((char*)&this->valoarePrime[i], sizeof(float));
		}
		// bool spor de noapte
		file.read((char*)&this->sporDeNoapte, sizeof(bool));
	}

	// Functie care scrie datele intr-un fisier text de tip CSV 
	void scriereAngajatCSV(ofstream& file)
	{
		file << this->nume << ", ";
		file << this->functie << ", ";
		file << this->varsta << ", ";
		file << this->salariu << ", ";
		for (int i = 0; i < 7; i++)
		{
			file << this->oreLucratePeZi[i] << ", ";
		}
		file << this->sporDeNoapte << ", ";
		file << this->nrPrime << ", ";

		for (int i = 0; i < this->nrPrime; i++)
		{
			file << this->valoarePrime[i] << ", ";

		}
	}
	//FUNCTII VIRTUALE
	//Functie virtuala care returneaza numele clasei in care te afli (baza sau derivata)
	virtual string returneazaClasaInCareMaAflu()
	{
		return "Sunt in clasa de baza (clasa Angajat)";
	}
	//Functie virtuala care reseteaza un obiect (da tuturor atributelor valoarea 0)
	virtual void  resetareObiect() {
		*this = Angajat();
	}
	//Operator + pentru clasa Angajat (adauga o valoare precizata la salariul angajatului) 
	Angajat operator + (float salariu) {
		Angajat s = *this;
		s.salariu += salariu;
		return s;
	}
};

// Aici incepe clasa Produs Alimentar

class ProdusAlimentar
{
	char* denumireProdus;
	int dataExpirare[3];
	float pretBucata;
	const int idProdus;
	string distribuitor;
	bool alergeni;
	static float TVA;
public:
	// Constructorul fara parametrii
	ProdusAlimentar() :idProdus(1)
	{

		this->denumireProdus = new char[strlen("Necunoscut") + 1];
		strcpy(this->denumireProdus, "Necunoscut");
		for (int i = 0; i < 3; i++)
		{
			this->dataExpirare[i] = 0;
		}
		this->pretBucata = 0;
		this->distribuitor = "Anonim";

		this->alergeni = 0;
	}
	//Constructorul cu toti parametrii
	ProdusAlimentar(const char* denumireProdus, int dataExpirare[3], float pretBucata, string distribuitor, bool alergeni, int idProdus) :idProdus(idProdus > 0 ? idProdus : 0)
		/*idProdus > 0 ? idProdus : 0*/ // am folosit un operator special pentru a face o validare a atributul constant 
	{
		if (strlen(denumireProdus) >= 3)
		{
			this->denumireProdus = new char[strlen(denumireProdus) + 1];
			strcpy(this->denumireProdus, denumireProdus);
		}
		else
		{
			this->denumireProdus = new char[strlen("Necunoscut") + 1];
			strcpy(this->denumireProdus, "Necunoscut");
		}

		for (int i = 0; i < 3; i++)
		{
			this->dataExpirare[i] = dataExpirare[i];
		}


		if (pretBucata > 0)
		{
			this->pretBucata = pretBucata;
		}
		else
		{
			this->pretBucata = 0;
		}

		if (distribuitor.length() > 1)
		{
			this->distribuitor = distribuitor;
		}
		else
		{
			this->distribuitor = "Anonim";
		}

		if (alergeni == 1 || alergeni == 0)
		{
			this->alergeni = alergeni;
		}
		else
		{
			this->alergeni = 0;
		}

	}

	//Destructuorul pentru clasa ProdusAlimentar.

	~ProdusAlimentar()
	{
		if (this->denumireProdus != NULL)
		{
			delete[] this->denumireProdus;
		}
	}

	//GETTERI pentru clasa ProdusAlimentar.
	char* getDenumireProdus()
	{
		return this->denumireProdus;
	}
	int* getDataExpirare()
	{
		return this->dataExpirare;
	}
	float getPretBaza()
	{
		return this->pretBucata;
	}
	string getDistribuitor()
	{
		return this->distribuitor;
	}
	bool getAlergeni()
	{
		return this->alergeni;
	}
	int getIdProdus()
	{
		return this->idProdus;
	}

	//SETTERI pentru clasa ProdusAlimentar

	void setAlergeni(bool alergeniNew)
	{
		this->alergeni = alergeniNew;
	}
	void setDistribuitor(string distribuitorNew)
	{
		this->distribuitor = distribuitorNew;
	}

	void setDenumireProdus(const char* denumireProdusNew)
	{
		if (this->denumireProdus != NULL)
		{
			delete[] this->denumireProdus;
		}
		this->denumireProdus = new char[strlen(denumireProdusNew) + 1];
		strcpy(this->denumireProdus, denumireProdusNew);
	}

	void setdataExpirare(int dataExpirareNew[3])
	{
		for (int i = 0; i < 3; i++)
		{
			this->dataExpirare[i] = dataExpirareNew[i];
		}
	}

	void setPretBucata(float pretBucataNew)
	{
		this->pretBucata = pretBucataNew;
	}

	//Constructorul de copiere pentru clasa ProdusAlimentar.

	ProdusAlimentar(const ProdusAlimentar& obj) :idProdus(obj.idProdus)
	{
		if (strlen(obj.denumireProdus) >= 3)
		{
			this->denumireProdus = new char[strlen(obj.denumireProdus) + 1];
			strcpy(this->denumireProdus, obj.denumireProdus);
		}
		else
		{
			this->denumireProdus = new char[strlen("Necunoscut") + 1];
			strcpy(this->denumireProdus, "Necunoscut");
		}

		for (int i = 0; i < 3; i++)
		{
			this->dataExpirare[i] = obj.dataExpirare[i];
		}

		if (obj.pretBucata > 0)
		{
			this->pretBucata = obj.pretBucata;
		}
		else
		{
			this->pretBucata = 0;
		}

		if (obj.distribuitor.length() > 1)
		{
			this->distribuitor = obj.distribuitor;
		}
		else
		{
			this->distribuitor = "Anonim";
		}
		if (obj.alergeni == 1 || obj.alergeni == 0)
		{
			this->alergeni = obj.alergeni;
		}
		else
		{
			this->alergeni = 0;
		}

	}
	//OPERATOR EGAL = pentru clasa ProdusAlimentar
	ProdusAlimentar& operator=(const ProdusAlimentar& obj)
	{
		if (this != &obj) // conditie evitarea autoasignarii
		{
			if (this->denumireProdus != NULL)
			{
				delete[] this->denumireProdus;
			}

			if (strlen(obj.denumireProdus) >= 3)
			{
				this->denumireProdus = new char[strlen(obj.denumireProdus) + 1];
				strcpy(this->denumireProdus, obj.denumireProdus);
			}
			else
			{
				this->denumireProdus = new char[strlen("Necunoscut") + 1];
				strcpy(this->denumireProdus, "Necunoscut");
			}

			for (int i = 0; i < 3; i++)
			{
				this->dataExpirare[i] = obj.dataExpirare[i];
			}

			if (obj.pretBucata > 0)
			{
				this->pretBucata = obj.pretBucata;
			}
			else
			{
				this->pretBucata = 0;
			}

			if (obj.distribuitor.length() > 1)
			{
				this->distribuitor = obj.distribuitor;
			}
			else
			{
				this->distribuitor = "Anonim";
			}
			if (obj.alergeni == 1 || obj.alergeni == 0)
			{
				this->alergeni = obj.alergeni;
			}
			else
			{
				this->alergeni = 0;
			}
		}

		return *this;
	}


	//OPERATOR AFISARE << pentru clasa ProdusAlimentar.
	friend ostream& operator<<(ostream& out, const ProdusAlimentar& obj)
	{
		out << "Denumire produs: " << obj.denumireProdus << endl;
		out << "Data expirare:";
		for (int i = 0; i < 3; i++)
		{
			out << obj.dataExpirare[i] << "/";
		}
		out << endl;
		out << "Pret bucata: " << obj.pretBucata << endl;
		out << "Distribuitor: " << obj.distribuitor << endl;
		out << "Alergeni: " << obj.alergeni << endl;
		out << "Id Produs: " << obj.idProdus << endl;

		return out;
	}
	// OPERATOR CITIRE >> pentru clasa ProdusAlimentar.
	friend istream& operator>>(istream& in, ProdusAlimentar& obj)
	{

		cout << "Denumire produs: ";
		char aux[100];
		in >> aux;
		if (obj.denumireProdus != NULL) {
			delete[]obj.denumireProdus;
		}
		obj.denumireProdus = new char[strlen(aux) + 1];
		strcpy(obj.denumireProdus, aux);
		for (int i = 0; i < 3; i++)
		{
			cout << "Data expirare(zi, luna, an): " << endl;
			in >> obj.dataExpirare[i];
		}
		cout << "Pret bucata: " << endl;
		in >> obj.pretBucata;
		cout << "Distribuitor: " << endl;
		in >> obj.distribuitor;
		cout << "Alergeni: " << endl;
		in >> obj.alergeni;

		return in;
	}
	//operator negatie ! pentru clasa ProdusAlimentar. Transforma din valoarea 1(true) in 0(false) si vice-versa.
	friend void operator!(ProdusAlimentar& obj)
	{
		if (obj.alergeni == 0)
		{
			obj.alergeni = 1;
		}
		else
		{
			obj.alergeni = 0;
		}
	}
	//operator >= (comparatie) pentru clasa ProdusAlimentar. Compara 2 obiecte din punct de vedere al pretului/bucata
	bool operator>=(ProdusAlimentar& obj)
	{
		if (this->pretBucata >= obj.pretBucata)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	// forma preincrementata a operatorului ++
	ProdusAlimentar& operator++() {
		this->pretBucata += 5;
		return *this;
	}


	// operator  == pentru clasa ProdusAlimentar. 
	bool operator ==(ProdusAlimentar& obj)
	{
		if (this->alergeni == obj.alergeni) {
			return true;
		}
		else
		{
			return false;
		}
	}

	//Operatorul index pentru clasa ProdusAlimentar.

	float operator[](int pozitieDorita)
	{
		if (pozitieDorita >= 0 && pozitieDorita < 3)
		{
			return this->dataExpirare[pozitieDorita];
		}
		else
		{
			return -1;
		}

	}
	//Operator de cast la string
	operator string()
	{
		return "Distribuitorul este: " + this->distribuitor;
	}

	ProdusAlimentar& operator--()
	{

		this->pretBucata--;
		return *this;
	}

	//Operator + (adauga o valoare la un obiect) 

	ProdusAlimentar operator + (float pretBucata) {
		ProdusAlimentar p = *this;
		p.pretBucata += pretBucata;
		return p;
	}

	//fisiere text clasa ProdusAlimentar
	friend ofstream& operator<<(ofstream& file, ProdusAlimentar& obj)
	{
		file << obj.denumireProdus << endl;
		for (int i = 0; i < 3; i++)
		{
			file << obj.dataExpirare[i] << endl;
		}
		file << obj.pretBucata << endl;
		file << obj.distribuitor << endl;
		file << obj.alergeni << endl;
		return file;
	}
	//citire fisier text clasa ProdusAlimentar
	friend ifstream& operator<<(ifstream& file, ProdusAlimentar& obj)
	{
		char aux[100];
		file >> aux;
		if (obj.denumireProdus != NULL) {
			delete[]obj.denumireProdus;
		}
		obj.denumireProdus = new char[strlen(aux) + 1];
		strcpy(obj.denumireProdus, aux);
		for (int i = 0; i < 3; i++)
		{
			file >> obj.dataExpirare[i];
		}
		file >> obj.pretBucata;
		file >> obj.distribuitor;
		file >> obj.alergeni;

		return file;
	}
	//Scriere fisier binar clasa ProdusAlimentar
	void scriereBinarProdusAlimentar(fstream& file)
	{
		//char* denumireProdus
		int lungimecuvant2 = strlen(this->denumireProdus);
		file.write((char*)&lungimecuvant2, sizeof(int));
		for (int i = 0; i < lungimecuvant2; i++)
		{
			file.write((char*)&this->denumireProdus[i], sizeof(char));
		}
		//float pretBucata
		file.write((char*)&this->pretBucata, sizeof(float));
		//float oreLucratePeZi
		for (int i = 0; i < 3; i++)
		{
			file.write((char*)&this->dataExpirare[i], sizeof(float));
		}

		//string distribuitor
		int lungimecuvant3 = this->distribuitor.size();
		file.write((char*)&lungimecuvant3, sizeof(int));
		file.write(this->distribuitor.c_str(), lungimecuvant3);

		// bool spor de noapte
		file.write((char*)&this->alergeni, sizeof(bool));
	}
	//Citire fisier fisier binar clasa ProdusAlimentar
	void CitireBinarProdusAlimentar(fstream& file)
	{
		//dezalocare memorie
		if (this->denumireProdus != NULL)
		{
			delete[] this->denumireProdus;
		}
		//char* denumireProdus
		int lengthDenumireProdus;
		file.read((char*)&lengthDenumireProdus, sizeof(int));
		this->denumireProdus = new char[lengthDenumireProdus + 1];
		for (int i = 0; i < lengthDenumireProdus; i++)
		{
			file.read((char*)&this->denumireProdus[i], sizeof(char));
		}
		this->denumireProdus[lengthDenumireProdus] = '\0';

		//float pretBucata
		file.read((char*)&this->pretBucata, sizeof(float));
		//float oreLucratePeZi
		for (int i = 0; i < 3; i++)
		{
			file.read((char*)&this->dataExpirare[i], sizeof(float));
		}
		//string distribuitor
		int lengthDistribuitor;
		file.read((char*)&lengthDistribuitor, sizeof(int));
		string aux;
		aux.resize(lengthDistribuitor);
		file.read((char*)aux.c_str(), lengthDistribuitor);
		this->distribuitor = aux;

		// bool spor de noapte
		file.read((char*)&this->alergeni, sizeof(bool));
	}

	//Functie care scrie datele intr-un fisier de tip CSV
	void scriereProdusAlimentarCSV(ofstream& file)
	{
		file << this->denumireProdus << ", ";
		for (int i = 0; i < 3; i++)
		{
			file << this->dataExpirare[i] << ", ";
		}
		file << this->pretBucata << ", ";
		file << this->distribuitor << ", ";
		file << this->alergeni << ", ";

	}
	//Functie care genereaza un raport intr-un fisier text referitor la pretul unui produs
	void raportProdusAlimentar(const char* file) {
		ofstream fout;
		fout.open(file, ofstream::out);
		fout << "Produsul " << denumireProdus << "are pretul de  " << pretBucata << " lei" << endl;
	}

};
// initializare atribut static
//double ProdusAlimentar:TVA = 0.19;

//Aici incepe clasa AsiguareDepozit.

class AsigurareDepozit
{
	char firmaAsiguratoare[30];
	int nrClauze;
	string* tipClauze;
	float valoare;
	bool reInnoireAnuala;
public:
	//Constructorul fara parametrii pentru clasa AsigurareDepozit
	AsigurareDepozit()
	{
		strcpy(this->firmaAsiguratoare, "Necunoscuta");
		this->nrClauze = 0;
		this->tipClauze = NULL;
		this->valoare = 0;
		this->reInnoireAnuala = 0;
	}
	//Constructorul cu toti parametrii pentru clasa AsigurareDepozit
	AsigurareDepozit(const char firmaAsiguratoare[30], int nrClauze, string* tipClauze, float valoare, bool reInnoireAnuala)
	{

		strcpy(this->firmaAsiguratoare, firmaAsiguratoare);

		if (nrClauze > 0 && tipClauze != NULL)
		{
			this->nrClauze = nrClauze;
			this->tipClauze = new string[this->nrClauze];

			for (int i = 0; i < this->nrClauze; i++)
			{
				this->tipClauze[i] = tipClauze[i];
			}
		}
		else
		{
			this->nrClauze = 0;
			this->tipClauze = NULL;
		}

		if (this->valoare > 0)
		{
			this->valoare = valoare;
		}
		else
		{
			this->valoare = 0;
		}


		if (reInnoireAnuala == 1 || reInnoireAnuala == 0)
		{
			this->reInnoireAnuala = reInnoireAnuala;
		}
		else
		{
			this->reInnoireAnuala = 0;
		}

	}
	// Destructorul pentru clasa AsigurareDepozit.
	~AsigurareDepozit()
	{
		if (this->tipClauze != NULL)
		{
			delete[] this->tipClauze;
		}
	}
	//GETTERI pentru clasa AsigurareDepozit.
	char* getFirmaAsiguratoare()
	{
		return this->firmaAsiguratoare;
	}
	int getNrClauze()
	{
		return this->nrClauze;
	}
	string* getTipClauze()
	{
		return this->tipClauze;
	}
	float getValoare()
	{
		return this->valoare;
	}
	bool getReInnoireAnuala()
	{
		return reInnoireAnuala;
	}
	//SETTERI pentru clasa AsigurareDepozit.

	void setFirmaAsiguratoare(const char firmaAsiguratoareNew[30])
	{
		strcpy(firmaAsiguratoare, firmaAsiguratoareNew);
	}

	void setClauze(int nrClauzeNew, string* tipClauzeNew)
	{
		if (this->tipClauze != NULL)
		{
			delete[] this->tipClauze;
		}
		this->nrClauze = nrClauzeNew;
		this->tipClauze = new string[this->nrClauze];
		for (int i = 0; i < this->nrClauze; i++)
		{
			this->tipClauze[i] = tipClauzeNew[i];
		}
	}

	void setReinnoireAnuala(bool reinnoireAnualanew)
	{
		this->reInnoireAnuala = reinnoireAnualanew;
	}
	void setValoare(float valoareNew)
	{
		this->valoare = valoareNew;
	}

	//OPERATORUL << (AFISARE) pentru clasa AsigurareDepozit.
	friend ostream& operator<<(ostream& ost, const AsigurareDepozit& sursa)
	{
		ost << "Firma asiguratoare: " << sursa.firmaAsiguratoare << endl;
		ost << "Valoare: " << sursa.valoare << endl;
		ost << "Numar clauze:  " << sursa.nrClauze << endl;
		for (int i = 0; i < sursa.nrClauze; i++)
		{
			ost << "Tip clauze:  " << sursa.tipClauze[i] << endl;

		}
		ost << "Reinnoire anuala:  " << sursa.reInnoireAnuala << endl;
		return ost;
	}
	//Constructorul de copiere pentru clasa AsigurareDepozit
	AsigurareDepozit(const AsigurareDepozit& sursa)
	{
		strcpy(this->firmaAsiguratoare, sursa.firmaAsiguratoare);

		if (sursa.nrClauze > 0 && sursa.tipClauze != NULL)
		{
			this->nrClauze = sursa.nrClauze;
			this->tipClauze = new string[this->nrClauze];

			for (int i = 0; i < this->nrClauze; i++)
			{
				this->tipClauze[i] = sursa.tipClauze[i];
			}
		}
		else
		{
			this->nrClauze = 0;
			this->tipClauze = NULL;
		}
		if (sursa.valoare > 0)
		{
			this->valoare = sursa.valoare;
		}
		else
		{
			this->valoare = 0;
		}

		if (sursa.reInnoireAnuala == 1 || sursa.reInnoireAnuala == 0)
		{
			this->reInnoireAnuala = sursa.reInnoireAnuala;
		}
		else
		{
			this->reInnoireAnuala = 0;
		}
	}
	//OPERATORUL = pentru clasa AsiguareDepozit. 

	AsigurareDepozit& operator=(const AsigurareDepozit& sursa)
	{
		if (this != &sursa)
		{
			if (this->tipClauze != NULL)
			{
				delete[] this->tipClauze;
			}
			strcpy(this->firmaAsiguratoare, sursa.firmaAsiguratoare);

			if (sursa.nrClauze > 0 && sursa.tipClauze != NULL)
			{
				this->nrClauze = sursa.nrClauze;
				this->tipClauze = new string[this->nrClauze];

				for (int i = 0; i < this->nrClauze; i++)
				{
					this->tipClauze[i] = sursa.tipClauze[i];
				}
			}
			else
			{
				this->nrClauze = 0;
				this->tipClauze = NULL;
			}
			if (sursa.valoare > 0)
			{
				this->valoare = sursa.valoare;
			}
			else
			{
				this->valoare = 0;
			}

			if (sursa.reInnoireAnuala == 1 || sursa.reInnoireAnuala == 0)
			{
				this->reInnoireAnuala = sursa.reInnoireAnuala;
			}
			else
			{
				this->reInnoireAnuala = 0;
			}
		}
		return *this;
	}
	// operator index []. Intoarce tipul clauzei de pe pozitia dorita
	string operator[](int pozitieDorita)
	{
		if (pozitieDorita >= 0 && pozitieDorita < this->nrClauze)
		{
			return this->tipClauze[pozitieDorita];
		}
		else
		{
			return "Nu exista aceasta pozitie in vector";
		}

	}
	// operator ! (negatie) pentru clasa AsigurareDepozit.

	friend void operator!(AsigurareDepozit& sursa)
	{
		if (sursa.reInnoireAnuala == 0)
		{
			sursa.reInnoireAnuala = 1;
		}
		else
		{
			sursa.reInnoireAnuala = 0;
		}
	}
	//operator > (comparatie) pentru clasa AsigurareDepozit. Compara 2 obiecte dupa valoare
	bool operator>(const AsigurareDepozit& sursa)
	{
		if (this->valoare > sursa.valoare)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// operator -- 
	AsigurareDepozit& operator--()
	{

		this->valoare--;
		return *this;
	}

	// Metoda care adauga o noua clauza in vector

	void adaugaClauzaNoua(string tipClauzeNou)
	{
		AsigurareDepozit copieObiect = *this;

		if (this->tipClauze != NULL)
		{
			delete[] this->tipClauze;
		}

		this->nrClauze++;

		this->tipClauze = new string[this->nrClauze];

		for (int i = 0; i < copieObiect.nrClauze; i++)
		{

			this->tipClauze[i] = copieObiect.tipClauze[i];
		}

		this->tipClauze[this->nrClauze - 1] = tipClauzeNou;
	}

	//OPERATORUL >> (AFISARE) pentru clasa AsigurareDepozit
	friend istream& operator>>(istream& ist, AsigurareDepozit& sursa)
	{
		if (sursa.tipClauze != NULL)
		{
			delete[] sursa.tipClauze;
		}

		cout << "Firma asiguratoare: " << endl;
		char aux[30];
		ist >> aux;
		strcpy(sursa.firmaAsiguratoare, aux);
		cout << "Valoare: " << endl;
		ist >> sursa.valoare;
		cout << "Numar clauze:  " << endl;
		ist >> sursa.nrClauze;
		sursa.tipClauze = new string[sursa.nrClauze];
		for (int i = 0; i < sursa.nrClauze; i++)
		{
			cout << "Tip clauze:  " << endl;
			ist >> sursa.tipClauze[i];

		}
		cout << "Reinnoire anuala:  " << endl;
		ist >> sursa.reInnoireAnuala;
		return ist;
	}

	//Operator comparatie pentru clasa AsigurareDepozit. Am folosit alt mod pentru aceasta clasa.
	bool operator<(const AsigurareDepozit& d)const
	{
		return this->nrClauze < d.nrClauze;
	}
	//Operatorul == pentru clasa AsiguareDepozit
	bool operator ==(AsigurareDepozit obj)
	{
		if (this->reInnoireAnuala == obj.reInnoireAnuala) {
			return true;
		}
		else
		{
			return false;
		}
	}
	//Operator + clasa AsigurareDepozit (adauga o valoare precizata la valoarea asigurarii) 
	AsigurareDepozit operator + (float valoare) {
		AsigurareDepozit v = *this;
		v.valoare += valoare;
		return v;
	}

	//Metoda care elimina o clauza din vector in functie de pozitia dorita spre a fi eliminata.

	void eliminaDupaPozitie(int pozitieDorita)
	{
		AsigurareDepozit copie = *this;
		if (this->tipClauze != NULL)
			delete[]this->tipClauze;
		this->nrClauze--;
		this->tipClauze = new string[this->nrClauze];
		for (int i = 0; i < pozitieDorita; i++)
			this->tipClauze[i] = copie.tipClauze[i];

		for (int i = pozitieDorita; i < this->nrClauze; i++)
			this->tipClauze[i] = copie.tipClauze[i + 1];

	}
	explicit operator int() {
		return this->nrClauze;
	}

	//FISIERE TEXT SI BINARE
	//Scriere fisier text pentru clasa AsigurareDepozit

	friend ofstream& operator<<(ofstream& file, AsigurareDepozit& sursa)
	{
		file << sursa.firmaAsiguratoare << endl;
		file << sursa.valoare << endl;
		file << sursa.nrClauze << endl;
		for (int i = 0; i < sursa.nrClauze; i++)
		{
			file << sursa.tipClauze[i] << endl;

		}
		file << sursa.reInnoireAnuala << endl;
		return file;

	}

	//Citire fisier text pentru clasa AsigurareDepozit
	friend ifstream& operator<<(ifstream& file, AsigurareDepozit& sursa)
	{
		if (sursa.tipClauze != NULL)
		{
			delete[] sursa.tipClauze;
		}

		char aux[30];
		file >> aux;
		strcpy(sursa.firmaAsiguratoare, aux);
		file >> sursa.valoare;
		file >> sursa.nrClauze;
		sursa.tipClauze = new string[sursa.nrClauze];
		for (int i = 0; i < sursa.nrClauze; i++)
		{
			file >> sursa.tipClauze[i];

		}
		file >> sursa.reInnoireAnuala;
		return file;
	}

	//Scriere fisier binar clasa AsigurareDepozit

	void scriereBinarAsigurareDepozit(fstream& file)
	{
		//char firmaAsiguratoare
		int length = strlen(this->firmaAsiguratoare);
		file.write((char*)&length, sizeof(int));
		for (int i = 0; i < length; i++)
		{
			file.write((char*)&this->firmaAsiguratoare[i], sizeof(char));
		}

		//int nrClauze
		file.write((char*)&this->nrClauze, sizeof(int));


		//string* tipClauze
		for (int i = 0; i < this->nrClauze; i++)
		{
			int length1 = this->tipClauze[i].size();
			file.write((char*)&length1, sizeof(int));
			file.write(this->tipClauze[i].c_str(), length1);
		}

		//float valoare 
		file.write((char*)&this->valoare, sizeof(float));

		// bool reInnoireAnuala
		file.write((char*)&this->reInnoireAnuala, sizeof(bool));
	}
	//Citire fisier binar clasa AsigurareDepozit
	void CitireBinarAsigurareDepozit(fstream& file)
	{

		if (this->tipClauze != NULL)
		{
			delete[] this->tipClauze;
		}
		//char firmaAsiguratoare[30];
		int lengthFirmaAsiguratoare;
		file.read((char*)&lengthFirmaAsiguratoare, sizeof(int));
		for (int i = 0; i < lengthFirmaAsiguratoare; i++)
		{
			file.read((char*)&this->firmaAsiguratoare[i], sizeof(char));
		}
		this->firmaAsiguratoare[lengthFirmaAsiguratoare] = '\0';

		//int nrClauze
		file.read((char*)&this->nrClauze, sizeof(int));
		//string* tipClauze
		this->tipClauze = new string[this->nrClauze];
		for (int i = 0; i < this->nrClauze; i++)
		{
			int lengthTipClauze;
			file.read((char*)&lengthTipClauze, sizeof(int));
			string aux1;
			aux1.resize(lengthTipClauze);
			file.read((char*)aux1.c_str(), lengthTipClauze);
			this->tipClauze[i] = aux1;
		}

		//float valoare
		file.read((char*)&this->valoare, sizeof(float));

		// bool reInnoireAnuala
		file.read((char*)&this->reInnoireAnuala, sizeof(bool));

	}

	//Functie care scrie in fisier CSV datele pentru clasa AsigurareDepozit
	void scriereAsigurareDepozitCSV(ofstream& file)
	{
		file << this->firmaAsiguratoare << ", ";
		file << this->valoare << ", ";
		file << this->nrClauze << ", ";
		for (int i = 0; i < this->nrClauze; i++)
		{
			file << this->tipClauze[i] << ", ";

		}
		file << this->reInnoireAnuala << ", ";

	}
	//Functie care genereaza un raport in fisier text despre numarul de clauze al firmei asiguratoare
	void raportAsigurareDepozit(const char* file)
	{
		ofstream fout;
		fout.open(file, ofstream::out);
		fout << "Firma asiguratoare  " << firmaAsiguratoare << " ofera un numar de " << nrClauze << " clauze." << endl;
	}
};

//Aici incepe clasa Comanda


class Comanda
{
	const int idComanda;
	int dataPlasareComanda[3];
	int nrProduseComandate;
	ProdusAlimentar* vectorProduseComandate;
	int* nrBucatiFiecareProdus;
	float valoareTransport;
	bool expediata;
public:

	//Constructorul fara parametrii pentru clasa Comanda.

	Comanda() :idComanda(1)
	{
		for (int i = 0; i < 3; i++)
		{
			this->dataPlasareComanda[i] = 0;
		}
		this->nrProduseComandate = 0;
		this->vectorProduseComandate = NULL;
		this->nrBucatiFiecareProdus = NULL;
		this->valoareTransport = 0;
		this->expediata = 0;
	}
	//Constructorul cu toti parametrii pentru clasa Comanda

	Comanda(int dataPlasareComanda[3], int nrProduseComandate, ProdusAlimentar* vectorProduseComandate, int* nrBucatiFiecareProdus, float valoareTransport, bool expediata, int idComanda) :idComanda(idComanda > 0 ? idComanda : 0)
		/*	idComanda > 0 ? idComanda : 0*/ // Am folosit un operator special pentru a face o validare pentru atributul constant
	{
		for (int i = 0; i < 3; i++)
		{
			this->dataPlasareComanda[i] = dataPlasareComanda[i];
		}
		if (valoareTransport > 0)
		{
			this->valoareTransport = valoareTransport;
		}
		else
		{
			this->valoareTransport = 0;
		}

		if (expediata == 1 || expediata == 0)
		{
			this->expediata = expediata;
		}
		else
		{
			this->expediata = 0;
		}

		this->nrProduseComandate = nrProduseComandate;
		this->vectorProduseComandate = new ProdusAlimentar[this->nrProduseComandate];
		this->nrBucatiFiecareProdus = new int[this->nrProduseComandate];
		for (int i = 0; i < this->nrProduseComandate; i++)
		{
			this->vectorProduseComandate[i] = vectorProduseComandate[i];
			this->nrBucatiFiecareProdus[i] = nrBucatiFiecareProdus[i];
		}
	}
	//Destructorul pentru clasa Comanda.
	~Comanda()
	{
		if (this->nrBucatiFiecareProdus != NULL)
		{
			delete[] this->nrBucatiFiecareProdus;
		}
		if (this->vectorProduseComandate != NULL)
		{
			delete[] this->vectorProduseComandate;
		}
	}
	//GETTERI pentru clasa Comanda.

	int* getDataPlasareComanda()
	{
		return this->dataPlasareComanda;
	}

	int getIdComanda()
	{
		return this->idComanda;
	}
	ProdusAlimentar* getVectorProduseComandate()
	{
		return this->vectorProduseComandate;
	}
	int* getNrBucatiFiecareProdus()
	{
		return this->nrBucatiFiecareProdus;
	}
	float getValoareTransport()
	{
		return this->valoareTransport;
	}
	bool getExpediata()
	{
		return this->expediata;
	}
	int getNrProduseComandate()
	{
		return this->nrProduseComandate;
	}

	//SETTERI pentru clasa Comanda.

	void setDataPlasareComanda(int dataPlasareComandaNew[3])
	{
		for (int i = 0; i < 3; i++)
		{
			this->dataPlasareComanda[i] = dataPlasareComandaNew[i];
		}
	}

	void setValoareTransport(float valoareTransportNew)
	{
		this->valoareTransport = valoareTransportNew;
	}

	void setExpediata(bool expediataNew)
	{
		this->expediata = expediataNew;
	}

	void setVectorProduseComandate(int nrProduseComandateNew, ProdusAlimentar* vectorProduseComandateNew, int* nrBucatiFiecareProdusNew)
	{
		if (this->nrBucatiFiecareProdus != NULL)
		{
			delete[] this->nrBucatiFiecareProdus;
		}
		if (this->vectorProduseComandate != NULL)
		{
			delete[] this->vectorProduseComandate;
		}
		this->nrProduseComandate = nrProduseComandateNew;
		this->vectorProduseComandate = new ProdusAlimentar[this->nrProduseComandate];
		this->nrBucatiFiecareProdus = new int[this->nrProduseComandate];
		for (int i = 0; i < this->nrProduseComandate; i++)
		{
			this->vectorProduseComandate[i] = vectorProduseComandateNew[i];
			this->nrBucatiFiecareProdus[i] = nrBucatiFiecareProdusNew[i];
		}
	}
	//Constructorul de copiere pentru clasa Comanda

	Comanda(const Comanda& obj) :idComanda(obj.idComanda)
	{
		for (int i = 0; i < 3; i++)
		{
			this->dataPlasareComanda[i] = obj.dataPlasareComanda[i];
		}
		if (obj.valoareTransport > 0)
		{
			this->valoareTransport = obj.valoareTransport;
		}
		else
		{
			this->valoareTransport = 0;
		}

		if (obj.expediata == 1 || obj.expediata == 0)
		{
			this->expediata = obj.expediata;
		}
		else
		{
			this->expediata = 0;
		}

		this->nrProduseComandate = obj.nrProduseComandate;
		this->vectorProduseComandate = new ProdusAlimentar[this->nrProduseComandate];
		this->nrBucatiFiecareProdus = new int[this->nrProduseComandate];
		for (int i = 0; i < this->nrProduseComandate; i++)
		{
			this->vectorProduseComandate[i] = obj.vectorProduseComandate[i];
			this->nrBucatiFiecareProdus[i] = obj.nrBucatiFiecareProdus[i];
		}

	}
	//Operator = pentru clasa Comanda

	Comanda& operator=(const Comanda& obj)
	{
		if (this != &obj) // conditie evitarea autoasignarii
		{
			if (this->nrBucatiFiecareProdus != NULL)
			{
				delete[] this->nrBucatiFiecareProdus;
			}
			if (this->vectorProduseComandate != NULL)
			{
				delete[] this->vectorProduseComandate;
			}

			for (int i = 0; i < 3; i++)
			{
				this->dataPlasareComanda[i] = obj.dataPlasareComanda[i];
			}
			if (obj.valoareTransport > 0)
			{
				this->valoareTransport = obj.valoareTransport;
			}
			else
			{
				this->valoareTransport = 0;
			}

			if (obj.expediata == 1 || obj.expediata == 0)
			{
				this->expediata = obj.expediata;
			}
			else
			{
				this->expediata = 0;
			}

			this->nrProduseComandate = obj.nrProduseComandate;
			this->vectorProduseComandate = new ProdusAlimentar[this->nrProduseComandate];
			this->nrBucatiFiecareProdus = new int[this->nrProduseComandate];
			for (int i = 0; i < this->nrProduseComandate; i++)
			{
				this->vectorProduseComandate[i] = obj.vectorProduseComandate[i];
				this->nrBucatiFiecareProdus[i] = obj.nrBucatiFiecareProdus[i];
			}
		}
		return *this;
	}
	//OPERATOR << (AFISARE) pentru clasa Comanda.
	friend ostream& operator<<(ostream& out, const Comanda& obj)
	{
		for (int i = 0; i < 3; i++)
		{
			out << "Data plasare comanda: " << obj.dataPlasareComanda[i] << "/" << endl;
		}
		out << "Numar produse comanda: " << obj.nrProduseComandate << endl;
		for (int i = 0; i < obj.nrProduseComandate; i++)
		{
			out << "Produse comandate: " << obj.vectorProduseComandate[i] << endl;
			out << "Numar bucati Fiecare Produs: " << obj.nrBucatiFiecareProdus[i] << endl;

		}
		out << "Valoare transport: " << obj.valoareTransport << endl;
		out << "Status expediere comanda: " << obj.expediata << endl;
		out << "Id comanda: " << obj.idComanda << endl;
		return out;
	}
	//OPERATOR >> (CITIRE) pentru clasa Comanda.

	friend istream& operator>>(istream& in, Comanda& obj)
	{
		if (obj.nrBucatiFiecareProdus != NULL)
		{
			delete[] obj.nrBucatiFiecareProdus;
		}

		if (obj.vectorProduseComandate != NULL)
		{
			delete[] obj.vectorProduseComandate;
		}

		for (int i = 0; i < 3; i++)
		{
			cout << "Data plasare comanda: " << "/" << endl;;
			in >> obj.dataPlasareComanda[i];
		}
		cout << "Numar produse comanda: " << endl;
		in >> obj.nrProduseComandate;
		obj.vectorProduseComandate = new ProdusAlimentar[obj.nrProduseComandate];
		obj.nrBucatiFiecareProdus = new int[obj.nrProduseComandate];
		for (int i = 0; i < obj.nrProduseComandate; i++)
		{
			cout << "Produse comandate: " << endl;
			in >> obj.vectorProduseComandate[i];
			cout << "Numar bucati Fiecare Produs: " << endl;
			in >> obj.nrBucatiFiecareProdus[i];
		}

		cout << "Valoare transport: ";
		in >> obj.valoareTransport;
		cout << "Status expediere comanda: ";
		in >> obj.expediata;

		return in;
	}
	// operator ! (negatie) pentru clasa Comanda
	friend void operator!(Comanda& sursa)
	{
		if (sursa.expediata == 0)
		{
			sursa.expediata = 1;
		}
		else
		{
			sursa.expediata = 0;
		}
	}

	//operator == pentru clasa Comanda
	bool operator ==(Comanda& obj)
	{
		if (this->expediata == obj.expediata)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//Operator + clasa AsigurareDepozit (adauga o valoare precizata valorii transportului comenzii) 
	Comanda operator + (float valoareTransport) {
		Comanda vt = *this;
		vt.valoareTransport += valoareTransport;
		return vt;
	}

	//Scriere fisier text pentru clasa Comanda

	friend ofstream& operator<<(ofstream& file, Comanda& obj)
	{
		for (int i = 0; i < 3; i++)
		{
			file << obj.dataPlasareComanda[i] << endl;
		}
		file << obj.nrProduseComandate << endl;
		for (int i = 0; i < obj.nrProduseComandate; i++)
		{
			file << obj.vectorProduseComandate[i] << endl;
		}
		for (int i = 0; i < obj.nrProduseComandate; i++)
		{
			file << obj.nrBucatiFiecareProdus[i] << endl;
		}
		file << obj.valoareTransport << endl;
		file << obj.expediata << endl;
		return file;
	}

	//Citire fisier text clasa Comanda
	friend ifstream& operator<<(ifstream& file, Comanda& obj)
	{
		if (obj.nrBucatiFiecareProdus != NULL)
		{
			delete[] obj.nrBucatiFiecareProdus;
		}

		if (obj.vectorProduseComandate != NULL)
		{
			delete[] obj.vectorProduseComandate;
		}

		for (int i = 0; i < 3; i++)
		{
			file >> obj.dataPlasareComanda[i];
		}
		file >> obj.nrProduseComandate;
		obj.vectorProduseComandate = new ProdusAlimentar[obj.nrProduseComandate];
		obj.nrBucatiFiecareProdus = new int[obj.nrProduseComandate];
		for (int i = 0; i < obj.nrProduseComandate; i++)
		{
			file >> obj.vectorProduseComandate[i];
		}
		for (int i = 0; i < obj.nrProduseComandate; i++)
		{
			file >> obj.nrBucatiFiecareProdus[i];
		}

		file >> obj.valoareTransport;
		file >> obj.expediata;

		return file;
	}

	//Scriere in fisier binar pentru clasa Comanda

	void scriereBinarComanda(fstream& file)
	{

		//int dataPlasareComanda
		for (int i = 0; i < 3; i++)
		{
			file.write((char*)&this->dataPlasareComanda[i], sizeof(int));
		}

		//int nrProduseComandate
		file.write((char*)&this->nrProduseComandate, sizeof(int));


		for (int i = 0; i < this->nrProduseComandate; i++)
		{
			this->vectorProduseComandate[i].scriereBinarProdusAlimentar(file);
		}

		//int* nrBucatiFiecareProdus
		for (int i = 0; i < this->nrProduseComandate; i++)
		{
			file.write((char*)&this->nrBucatiFiecareProdus[i], sizeof(int));
		}

		//float valoareTransport
		file.write((char*)&this->valoareTransport, sizeof(float));

		// bool expediata
		file.write((char*)&this->expediata, sizeof(bool));
	}
	//Citire in binar pentru clasa Comanda

	void CitireBinarComanda(fstream& file)
	{
		if (this->nrBucatiFiecareProdus != NULL)
		{
			delete[] this->nrBucatiFiecareProdus;
		}
		if (this->vectorProduseComandate != NULL)
		{
			delete[] this->vectorProduseComandate;
		}
		//int dataPlasareComanda
		for (int i = 0; i < 3; i++)
		{
			file.read((char*)&this->dataPlasareComanda[i], sizeof(int));
		}
		//int nrProduseComandate
		file.read((char*)&this->nrProduseComandate, sizeof(int));

		//ProdusAlimentar* vectorProduseComandate;
		this->vectorProduseComandate = new ProdusAlimentar[this->nrProduseComandate];

		for (int i = 0; i < this->nrProduseComandate; i++)
		{
			this->vectorProduseComandate[i].CitireBinarProdusAlimentar(file);
		}

		//int* nrBucatiFiecareProdus
		this->nrBucatiFiecareProdus = new int[this->nrProduseComandate];
		for (int i = 0; i < this->nrProduseComandate; i++)
		{
			file.read((char*)&this->nrBucatiFiecareProdus[i], sizeof(int));
		}

		//float valoareTransport
		file.read((char*)&this->valoareTransport, sizeof(float));

		// bool expediata
		file.read((char*)&this->expediata, sizeof(bool));

	}

	//Functie care scrie in fisier CSV datele pentru clasa Comanda

	void scriereComandaCSV(ofstream& file)
	{
		for (int i = 0; i < 3; i++)
		{
			file << this->dataPlasareComanda[i] << ", ";
		}
		file << this->nrProduseComandate << ", ";
		for (int i = 0; i < this->nrProduseComandate; i++)
		{
			file << this->vectorProduseComandate[i] << ", ";
		}
		for (int i = 0; i < this->nrProduseComandate; i++)
		{
			file << this->nrBucatiFiecareProdus[i] << ", ";
		}
		file << this->valoareTransport << ", ";
		file << this->expediata << ", ";
	}
};

//Aici incepe clasa Depozit

class Depozit
{
	char numeDepozit[30];
	float suprafata;
	bool areEtaj;
	int nrAngajati;
	Angajat* vectorAngajati;
	int nrComenzi;
	Comanda** vectorComanda;
	AsigurareDepozit asigurare;
public:
	//Constructorul fara parametrii pentru clasa Depozit
	Depozit()
	{
		strcpy(this->numeDepozit, "Necunoscut");
		this->suprafata = 0;
		this->areEtaj = 0;
		this->vectorAngajati = NULL;
		this->nrComenzi = 0;
		this->vectorComanda = NULL;
	}
	//Constructorul cu toti parametrii pentru clasa Depozit

	Depozit(const char numeDepozit[30], float suprafata, bool areEtaj, int nrAngajati, Angajat* vectorAngajati, int nrComenzi, Comanda** vectorComanda, AsigurareDepozit asigurare)
	{
		strcpy(this->numeDepozit, numeDepozit);
		if (suprafata > 0)
		{
			this->suprafata = suprafata;
		}
		else
		{
			suprafata = 0;
		}
		if (areEtaj == 1 || areEtaj == 0)
		{
			this->areEtaj = areEtaj;
		}
		else
		{
			this->areEtaj = 0;
		}

		if (nrAngajati > 0 && vectorAngajati != NULL)
		{
			this->nrAngajati = nrAngajati;
			this->vectorAngajati = new Angajat[this->nrAngajati];

			for (int i = 0; i < this->nrAngajati; i++)
			{
				this->vectorAngajati[i] = vectorAngajati[i];
			}
		}
		else
		{
			this->nrAngajati = 0;
			this->vectorAngajati = NULL;
		}

		if (nrComenzi > 0 && vectorComanda != NULL)
		{
			this->nrComenzi = nrComenzi;
			this->vectorComanda = new Comanda * [this->nrComenzi];

			for (int i = 0; i < this->nrComenzi; i++)
			{
				this->vectorComanda[i] = new Comanda(*vectorComanda[i]);
			}
		}
		else
		{
			this->nrComenzi = 0;
			this->vectorComanda = NULL;
		}

		this->asigurare = asigurare;
	}

	//Destructor pentru clasa Depozit.
	~Depozit()
	{
		for (int i = 0; i < this->nrComenzi; i++)
		{
			delete this->vectorComanda[i];
		}
		delete[] this->vectorComanda;


		delete[] this->vectorAngajati;

	}

	//GETTERI pentru clasa Depozit.

	char* getNumeDepozit()
	{
		return this->numeDepozit;
	}
	float getSuprafata()
	{
		return this->suprafata;
	}
	bool getAreEtaj()
	{
		return this->areEtaj;
	}
	int getNrAngajati()
	{
		return this->nrAngajati;
	}
	Angajat* getVectorAngajati()
	{
		return this->vectorAngajati;
	}

	int getNrComenzi()
	{
		return this->nrComenzi;
	}
	Comanda** getVectorComanda()
	{
		return this->vectorComanda;
	}
	AsigurareDepozit getVectorAsigurari()
	{
		return this->asigurare;
	}

	// SETTERI pentru clasa Depozit.
	void setNumeDepozit(const char numeDepozitNew[30])
	{
		strcpy(numeDepozit, numeDepozitNew);
	}

	void setSuprafata(float suprafataNew)
	{
		this->suprafata = suprafataNew;
	}
	void setAreEtaj(bool areEtajNew)
	{
		this->areEtaj = areEtajNew;
	}

	void SetVectorAngajati(int nrAngajatiNew, Angajat* vectorAngajatiNew)
	{
		delete[] this->vectorAngajati;
		this->nrAngajati = nrAngajatiNew;
		this->vectorAngajati = new Angajat[this->nrAngajati];

		for (int i = 0; i < this->nrAngajati; i++)
		{
			this->vectorAngajati[i] = vectorAngajatiNew[i];
		}
	}

	void SetVectorComanda(int nrComenziNew, Comanda** vectorComandaNew)
	{
		for (int i = 0; i < this->nrComenzi; i++)
		{
			delete this->vectorComanda[i];
		}
		delete[] this->vectorComanda;

		this->nrComenzi = nrComenziNew;
		this->vectorComanda = new Comanda * [this->nrComenzi];

		for (int i = 0; i < this->nrComenzi; i++)
		{
			this->vectorComanda[i] = new Comanda(*vectorComandaNew[i]);
		}
	}

	void SetVectorAsigurare(AsigurareDepozit asigurareNew)
	{
		this->asigurare = asigurareNew;
	}
	//Constructorul de copiere pentru clasa  Depozit

	Depozit(const Depozit& obj)
	{
		strcpy(this->numeDepozit, obj.numeDepozit);
		if (obj.suprafata > 0)
		{
			this->suprafata = obj.suprafata;
		}
		else
		{
			this->suprafata = 0;
		}
		if (obj.areEtaj == 1 || obj.areEtaj == 0)
		{
			this->areEtaj = obj.areEtaj;
		}
		else
		{
			this->areEtaj = 0;
		}

		if (obj.nrAngajati > 0 && obj.vectorAngajati != NULL)
		{
			this->nrAngajati = obj.nrAngajati;
			this->vectorAngajati = new Angajat[this->nrAngajati];

			for (int i = 0; i < this->nrAngajati; i++)
			{
				this->vectorAngajati[i] = obj.vectorAngajati[i];
			}
		}
		else
		{
			this->nrAngajati = 0;
			this->vectorAngajati = NULL;
		}

		if (obj.nrComenzi > 0 && obj.vectorComanda != NULL)
		{
			this->nrComenzi = obj.nrComenzi;
			this->vectorComanda = new Comanda * [this->nrComenzi];

			for (int i = 0; i < this->nrComenzi; i++)
			{
				this->vectorComanda[i] = new Comanda(*obj.vectorComanda[i]);
			}
		}
		else
		{
			this->nrComenzi = 0;
			this->vectorComanda = NULL;
		}

		this->asigurare = obj.asigurare;
	}

	//OPERATOR = pentru clasa Depozit

	Depozit& operator=(const Depozit& obj)
	{
		if (this != &obj) // conditie evitare autoasignare
		{
			for (int i = 0; i < this->nrComenzi; i++)
			{
				delete this->vectorComanda[i];
			}
			delete[] this->vectorComanda;

			delete[] this->vectorAngajati;

			strcpy(this->numeDepozit, obj.numeDepozit);
			if (obj.suprafata > 0)
			{
				this->suprafata = obj.suprafata;
			}
			else
			{
				this->suprafata = 0;
			}
			if (obj.areEtaj == 1 || obj.areEtaj == 0)
			{
				this->areEtaj = obj.areEtaj;
			}
			else
			{
				this->areEtaj = 0;
			}

			if (obj.nrAngajati > 0 && obj.vectorAngajati != NULL)
			{
				this->nrAngajati = obj.nrAngajati;
				this->vectorAngajati = new Angajat[this->nrAngajati];

				for (int i = 0; i < this->nrAngajati; i++)
				{
					this->vectorAngajati[i] = obj.vectorAngajati[i];
				}
			}
			else
			{
				this->nrAngajati = 0;
				this->vectorAngajati = NULL;
			}

			if (obj.nrComenzi > 0 && obj.vectorComanda != NULL)
			{
				this->nrComenzi = obj.nrComenzi;
				this->vectorComanda = new Comanda * [this->nrComenzi];

				for (int i = 0; i < this->nrComenzi; i++)
				{
					this->vectorComanda[i] = new Comanda(*obj.vectorComanda[i]);
				}
			}
			else
			{
				this->nrComenzi = 0;
				this->vectorComanda = NULL;
			}

			this->asigurare = obj.asigurare;

		}
		return*this;
	}
	//OPERATOR << (AFISARE) pentru clasa Depozit
	friend ostream& operator<<(ostream& out, const Depozit& obj)
	{
		out << "Denumire depozit: " << obj.numeDepozit << endl;
		out << "Suprafata: " << obj.suprafata << endl;
		out << "Etaj: " << obj.areEtaj << endl;
		out << "Numar angajati: " << obj.nrAngajati << endl;
		for (int i = 0; i < obj.nrAngajati; i++)
		{
			out << "Angajati: " << obj.vectorAngajati[i] << endl;
		}
		out << "Numar comenzi: " << obj.nrComenzi << endl;
		for (int i = 0; i < obj.nrComenzi; i++)
		{
			out << "Produse comandate: " << *obj.vectorComanda[i] << endl;
		}
		out << "Asigurare: " << obj.asigurare << endl;

		return out;
	}
	//OPERATOR >> (CITIRE) pentru clasa Depozit
	friend istream& operator>>(istream& in, Depozit& obj)
	{
		for (int i = 0; i < obj.nrComenzi; i++)
		{
			delete obj.vectorComanda[i];
		}
		delete[] obj.vectorComanda;

		delete[] obj.vectorAngajati;


		cout << "Denumire depozit: ";
		char aux[30];
		in >> aux;
		strcpy(obj.numeDepozit, aux);

		cout << "Suprafata: " << endl;
		in >> obj.suprafata;
		cout << "Etaj: " << endl;
		in >> obj.areEtaj;
		cout << "Numar angajati: " << endl;
		in >> obj.nrAngajati;
		obj.vectorAngajati = new Angajat[obj.nrAngajati];
		cout << "Angajati: " << endl;
		for (int i = 0; i < obj.nrAngajati; i++)
		{
			in >> obj.vectorAngajati[i];
		}
		cout << "Nr comenzi: " << endl;
		in >> obj.nrComenzi;
		obj.vectorComanda = new Comanda * [obj.nrComenzi];
		cout << "Comenzi: " << endl;
		for (int i = 0; i < obj.nrComenzi; i++)
		{
			obj.vectorComanda[i] = new Comanda();
			in >> *obj.vectorComanda[i];
		}
		cout << "Asigurare depozit: " << endl;
		in >> obj.asigurare;

		return in;
	}
	// operator comparatie pentru clasa Depozit. Compara 2 obiecte din punct de vedere al suprafetei.
	bool operator<(const Depozit& d)const
	{
		return this->suprafata < d.suprafata;
	}
	//operator ! (negatie) pentru clasa Depozit
	friend void operator!(Depozit& sursa)
	{
		if (sursa.areEtaj == 0)
		{
			sursa.areEtaj = 1;
		}
		else
		{
			sursa.areEtaj = 0;
		}
	}
	//operator == pentru clasa Depozit
	bool operator ==(Depozit& obj)
	{
		if (this->areEtaj == obj.areEtaj) {
			return true;
		}
		else
		{
			return false;
		}
	}

	//Operator + clasa Depozit (adauga o valoare precizata suprafetei depozitului)
	Depozit operator + (float suprafata) {
		Depozit sf = *this;
		sf.suprafata += suprafata;
		return sf;
	}

	//Operator de cast la string


	//FISIERE TEXT SI BINARE
	// Scriere fisier text clasa Depozit

	friend ofstream& operator <<(ofstream& file, Depozit& obj)
	{
		file << obj.numeDepozit << endl;
		file << obj.suprafata << endl;
		file << obj.areEtaj << endl;
		file << obj.nrAngajati << endl;
		for (int i = 0; i < obj.nrAngajati; i++)
		{
			file << obj.vectorAngajati[i] << endl;
		}
		file << obj.nrComenzi << endl;
		for (int i = 0; i < obj.nrComenzi; i++)
		{
			file << *obj.vectorComanda[i] << endl;
		}
		file << obj.asigurare << endl;

		return file;
	}

	// Citire fisier text clasa Depozit
	friend ifstream& operator<<(ifstream& file, Depozit& obj)
	{
		for (int i = 0; i < obj.nrComenzi; i++)
		{
			delete obj.vectorComanda[i];
		}
		delete[] obj.vectorComanda;

		delete[] obj.vectorAngajati;


		char aux[30];
		file >> aux;
		strcpy(obj.numeDepozit, aux);

		file >> obj.suprafata;
		file >> obj.areEtaj;
		file >> obj.nrAngajati;
		obj.vectorAngajati = new Angajat[obj.nrAngajati];
		for (int i = 0; i < obj.nrAngajati; i++)
		{
			file >> obj.vectorAngajati[i];
		}
		file >> obj.nrComenzi;
		obj.vectorComanda = new Comanda * [obj.nrComenzi];
		for (int i = 0; i < obj.nrComenzi; i++)
		{
			obj.vectorComanda[i] = new Comanda();
			file >> *obj.vectorComanda[i];
		}
		file >> obj.asigurare;

		return file;
	}


	void scriereBinarDepozit(fstream& file)
	{
		//char* numeDepozit[30];
		int lengthDepozit = strlen(this->numeDepozit);
		file.write((char*)&lengthDepozit, sizeof(int));
		for (int i = 0; i < lengthDepozit; i++)
		{
			file.write((char*)&this->numeDepozit[i], sizeof(char));
		}

		//float suprafata
		file.write((char*)&this->suprafata, sizeof(float));

		// bool are etaj
		file.write((char*)&this->areEtaj, sizeof(bool));

		//int nrAngajati;
		file.write((char*)&this->nrAngajati, sizeof(int));

		//Angajat* vectorAngajati;

		for (int i = 0; i < this->nrAngajati; i++)
		{
			this->vectorAngajati[i].scriereBinarAngajat(file);
		}
		//int nrComenzi;
		file.write((char*)&this->nrComenzi, sizeof(int));

		//Comanda**vectorComanda

		for (int i = 0; i < this->nrComenzi; i++)
		{
			(*this->vectorComanda[i]).scriereBinarComanda(file);
		}
		//AsigurareDepozit asigurare 

		this->asigurare.scriereBinarAsigurareDepozit(file);
	}

	void CitireBinarDepozit(fstream& file)
	{
		for (int i = 0; i < this->nrComenzi; i++)
		{
			delete this->vectorComanda[i];
		}
		delete[] this->vectorComanda;


		delete[] this->vectorAngajati;

		/**char numeDepozit[30]*/
		int lungimeDepozit;
		file.read((char*)&lungimeDepozit, sizeof(int));
		for (int i = 0; i < lungimeDepozit; i++)
		{
			file.read((char*)&this->numeDepozit[i], sizeof(char));
		}
		this->numeDepozit[lungimeDepozit] = '\0';

		//float suprafata
		file.read((char*)&this->suprafata, sizeof(float));

		// bool are etaj
		file.read((char*)&this->areEtaj, sizeof(bool));

		//int nrAngajati;
		file.read((char*)&this->nrAngajati, sizeof(int));

		this->vectorAngajati = new Angajat[this->nrAngajati];

		//Angajat* vectorAngajati;

		for (int i = 0; i < this->nrAngajati; i++)
		{
			this->vectorAngajati[i].CitireBinarAngajat(file);
		}

		//int nrComenzi;
		file.read((char*)&this->nrComenzi, sizeof(int));


		this->vectorComanda = new Comanda * [this->nrComenzi];
		//Comanda**vectorComanda

		for (int i = 0; i < this->nrComenzi; i++)
		{
			this->vectorComanda[i] = new Comanda();
			(*this->vectorComanda[i]).CitireBinarComanda(file);
		}
		//AsigurareDepozit asigurare 

		this->asigurare.CitireBinarAsigurareDepozit(file);

	}
	//Scriere in fisier CSV pentru clasa Depozit
	void scriereDepozitCSV(ofstream& file)
	{
		file << this->numeDepozit << ", ";
		file << this->suprafata << ", ";
		file << this->areEtaj << ", ";
		file << this->nrAngajati << ", ";
		for (int i = 0; i < this->nrAngajati; i++)
		{
			file << this->vectorAngajati[i] << ", ";
		}
		file << this->nrComenzi << ", ";
		for (int i = 0; i < this->nrComenzi; i++)
		{
			file << *this->vectorComanda[i] << ", ";
		}
		file << this->asigurare << ", ";
	}

	//Functie care genereaza un raport in legatura cu suprafata depozitului
	void raportDepozit(const char* file)
	{
		ofstream fout;
		fout.open(file, ofstream::out);
		fout << "Depozitul  " << numeDepozit << " are o suprafata de  " << suprafata << " m^2" << endl;
	}

};
//Clasa Menu: permite navigarea prin aplicatie. Poate afisa si citi clasele Angajat, ProdusAlimentar, AsigurareDepozit, Comanda, Depozit.
class Menu {
public:
	static void afisareMeniuPrincipal() {
		cout << "1)Afiseaza Angajat" << endl;
		cout << "2)Afiseaza Produs Alimentar" << endl;
		cout << "3)Afiseaza Asigurare Depozit" << endl;
		cout << "4)Afiseaza Comanda " << endl;
		cout << "5)Afisare Depozit" << endl;

		cout << "6)Citire Angajat" << endl;
		cout << "7)Citire ProdusAlimentar" << endl;
		cout << "8)Citire Asigurare Depozit" << endl;
		cout << "9)Citire Comanda" << endl;
		cout << "10)Citire Depozit" << endl;

		cout << "0)Iesire" << endl << endl;
		cout << "Alege optiunea:" << endl;
	}
};

//Aici incepe clasa Sofer care este in relatie de is a cu clasa Angajat.

class Sofer :public Angajat {
	float kmParcursi;
	int nrDestinatii;
	string* numeDestinatie;
	bool cursaDeNoapte;
public:
	//Constructor fara parametrii pentru clasa Angajat
	Sofer() :Angajat()
	{
		this->kmParcursi = 0;
		this->nrDestinatii = 0;
		this->numeDestinatie = NULL;
		this->cursaDeNoapte = 0;

	}
	//Constructor cu parametrii pentru clasa Angajat
	Sofer(float kmParcursi, int nrDestinatii, string* numeDestinatie, bool cursaDeNoapte, const char* nume, string functie, int varsta, float salariu, float oreLucratePeZi[7], int nrPrime, float* valoarePrime, bool sporDeNoapte) :Angajat(nume, functie, varsta, salariu, oreLucratePeZi, nrPrime, valoarePrime, sporDeNoapte)
	{
		this->kmParcursi = kmParcursi;
		if (nrDestinatii > 0 && numeDestinatie != NULL)
		{
			this->nrDestinatii = nrDestinatii;
			this->numeDestinatie = new string[this->nrDestinatii];

			for (int i = 0; i < this->nrDestinatii; i++)
			{
				this->numeDestinatie[i] = numeDestinatie[i];
			}
		}
		else
		{
			this->nrDestinatii = 0;
			this->numeDestinatie = NULL;
		}

		if (cursaDeNoapte == 1 || cursaDeNoapte == 0)
		{
			this->cursaDeNoapte = cursaDeNoapte;
		}
		else
		{
			this->cursaDeNoapte = 0;
		}
	}
	//Destructor pentru clasa Sofer

	~Sofer()
	{
		if (this->numeDestinatie != NULL)
		{
			delete[] this->numeDestinatie;
		}
	}
	//UPCASTING
	//Constructor de copiere pentru clasa Sofer
	Sofer(const Sofer& s) :Angajat(s)
	{
		this->kmParcursi = s.kmParcursi;
		if (nrDestinatii > 0 && numeDestinatie != NULL)
		{
			this->nrDestinatii = s.nrDestinatii;
			this->numeDestinatie = new string[this->nrDestinatii];

			for (int i = 0; i < this->nrDestinatii; i++)
			{
				this->numeDestinatie[i] = s.numeDestinatie[i];
			}
		}
		else
		{
			this->nrDestinatii = 0;
			this->numeDestinatie = NULL;
		}

		if (cursaDeNoapte == 1 || cursaDeNoapte == 0)
		{
			this->cursaDeNoapte = s.cursaDeNoapte;
		}
		else
		{
			this->cursaDeNoapte = 0;
		}
	}

	//Operator = pentru clasa Sofer
	Sofer& operator=(const Sofer& s)
	{
		if (this != &s)
		{
			if (this->numeDestinatie != NULL)
			{
				delete[] this->numeDestinatie;
			}

			this->kmParcursi = s.kmParcursi;
			if (nrDestinatii > 0 && numeDestinatie != NULL)
			{
				this->nrDestinatii = s.nrDestinatii;
				this->numeDestinatie = new string[this->nrDestinatii];

				for (int i = 0; i < this->nrDestinatii; i++)
				{
					this->numeDestinatie[i] = s.numeDestinatie[i];
				}
			}
			else
			{
				this->nrDestinatii = 0;
				this->numeDestinatie = NULL;
			}

			if (cursaDeNoapte == 1 || cursaDeNoapte == 0)
			{
				this->cursaDeNoapte = s.cursaDeNoapte;
			}
			else
			{
				this->cursaDeNoapte = 0;
			}

		}
		return *this;
	}
	//Getteri pentru clasa Sofer

	float getNrKmParcursi()
	{
		return this->kmParcursi;
	}
	int getNrDestinatie()
	{
		return this->nrDestinatii;
	}
	string* getNumeDestinatie()
	{
		return this->numeDestinatie;
	}
	bool getCursaDeNoapte()
	{
		return this->cursaDeNoapte;
	}

	//Setteri pentru clasa Sofer
	void setKmParcursi(int kmParcursiNew)
	{
		this->kmParcursi = kmParcursiNew;
	}

	void setDestinatie(int nrDestinatiiNew, string numeDestinatieNew)
	{
		if (this->numeDestinatie != NULL)
		{
			delete[] this->numeDestinatie;
		}
		this->nrDestinatii = nrDestinatiiNew;
		this->numeDestinatie = new string[this->nrDestinatii];
		for (int i = 0; i < this->nrDestinatii; i++)
		{
			this->numeDestinatie[i] = numeDestinatieNew[i];
		}
	}

	void setCursaDeNoapte(bool cursaDeNoapteNew)
	{
		this->cursaDeNoapte = cursaDeNoapteNew;
	}
	//Operator << (afisare) pentru clasa Sofer
	friend ostream& operator <<(ostream& out, Sofer& s)
	{
		out << "Numarul de kilometrii parcursi: " << s.kmParcursi << endl;
		out << "Numar de destinatii: " << s.nrDestinatii << endl;
		for (int i = 0; i < s.nrDestinatii; i++)
		{
			out << "Nume destinatii: " << s.numeDestinatie[i] << endl;
		}
		out << "Cursa de noapte: " << s.cursaDeNoapte << endl;
		out << (Angajat&)s;
		return out;
	}
	//Operator >> (citire) pentru clasa Sofer

	friend istream& operator >>(istream& in, Sofer& s)
	{
		if (s.numeDestinatie != NULL)
		{
			delete[] s.numeDestinatie;
		}

		cout << "Introduceti numarul de kilometrii: " << endl;
		in >> s.kmParcursi;
		cout << "Introduceti numarul de destinatii: " << endl;
		in >> s.nrDestinatii;
		s.numeDestinatie = new string[s.nrDestinatii];
		for (int i = 0; i < s.nrDestinatii; i++)
		{
			cout << "Introduceti numele destinatiilor: " << endl;
			in >> s.numeDestinatie[i];
		}
		cout << "Introduceti daca este cursa de noapte (1=da;0=nu): " << endl;
		in >> (Angajat&)s;
		return in;
	}
	//Metode virtuale 
	//Metoda care returneaza clasa in care te afli (baza sau derivata)
	string returneazaClasaInCareMaAflu()
	{
		return "Sunt in clasa derivata (clasa Sofer)";
	}
	//Metoda virtuala care reseteaza un obiect (da tuturor atributelor valoarea 0)
	void  resetareObiect() {
		*this = Sofer();
	}

};

// Aici incepe clasa ProdusAlimentarPromotie care este in relatie de is a cu clasa ProdusAlimentar

class ProdusAlimentarPromotie :public ProdusAlimentar
{
	int valabilitatePromotie; // numarul de zile in care este valabila promotia 
	float valoareDiscount;
public:
	//Constructor fara parametrii pentru clasa ProdusAlimentarPromotie
	ProdusAlimentarPromotie() :ProdusAlimentar()
	{
		this->valabilitatePromotie = 0;
		this->valoareDiscount = 0;
	}
	//Constructor cu toti parametrii pentru clasa ProdusAlimentarPromotie

	ProdusAlimentarPromotie(int valabilitatePromotie, float valoareDiscount, const char* denumireProdus, int dataExpirare[3], float pretBucata, string distribuitor, bool alergeni, int idProdus) :ProdusAlimentar(denumireProdus, dataExpirare, pretBucata, distribuitor, alergeni, idProdus)
	{
		this->valabilitatePromotie = valabilitatePromotie;
		this->valoareDiscount = valoareDiscount;
	}
	//Destructor pentru clasa ProdusAlimentarPromotie
	~ProdusAlimentarPromotie()
	{

	}
	// UPCASTING (constructor de copiere)
	ProdusAlimentarPromotie(const ProdusAlimentarPromotie& pap) :ProdusAlimentar(pap)
	{
		this->valabilitatePromotie = pap.valabilitatePromotie;
		this->valoareDiscount = pap.valoareDiscount;
	}

	//DOWNCASTING (constructor de copiere)
	ProdusAlimentarPromotie(const ProdusAlimentar& pap) :ProdusAlimentar(pap)
	{
		this->valabilitatePromotie = 7;
		this->valoareDiscount = 2.6;
	}
	//Getteri pentru clasa ProdusAlimetarPromotie
	int getValabilitatePromotie()
	{
		return this->valabilitatePromotie;
	}
	float getValoareDiscount()
	{
		return this->valoareDiscount;
	}
	//Setteri pentru clasa ProdusAlimentarPromotie
	void setValabilitatePromotie(int setValabilitatePromotieNew)
	{
		this->valabilitatePromotie = setValabilitatePromotieNew;
	}

	void setValoareDiscount(float valoareDiscountNew)
	{
		this->valoareDiscount = valoareDiscountNew;
	}

	//Operatorul = pentru clasa ProdusAlimentarPromotie
	ProdusAlimentarPromotie& operator=(const ProdusAlimentarPromotie& pap)
	{
		if (this != &pap)
		{
			ProdusAlimentar::operator=(pap);
			this->valabilitatePromotie = pap.valabilitatePromotie;
			this->valoareDiscount = pap.valoareDiscount;
		}
		return *this;
	}
	//Operatorul << (afisare) pentru clasa ProdusAlimentarPromotie
	friend ostream& operator<<(ostream& out, ProdusAlimentarPromotie& pap)
	{
		out << "Valabilitate Promotie: " << pap.valabilitatePromotie << endl;
		out << "Valoare discount: " << pap.valoareDiscount << endl;
		out << (ProdusAlimentar&)pap;
		return out;
	}
	//Operatorul >> (citire) pentru clasa ProdusAlimentarPromotie
	friend istream& operator>>(istream& in, ProdusAlimentarPromotie& pap)
	{
		cout << "Introduceti valabilitatea produsului: " << endl;
		in >> pap.valabilitatePromotie;
		cout << "Introduceti valoarea discountului: " << endl;
		in >> pap.valoareDiscount;
		in >> (ProdusAlimentar&)pap;
		return in;
	}
};

//Clasa template Gestiune

template <typename tipDataElementeGestiune>
class Gestiune
{
	int nrElemente;
	tipDataElementeGestiune* vectorElementeGestiune;
public:
	//Constructor fara parametrii pentru clasa Gestiune
	Gestiune()
	{
		this->nrElemente = 0;
		this->vectorElementeGestiune = NULL;
	}
	//Constructor cu toti parametrii pentru clasa Gestiune
	Gestiune(int nrElemente, tipDataElementeGestiune* vectorElementeGestiune)
	{
		this->nrElemente = nrElemente;
		this->vectorElementeGestiune = new tipDataElementeGestiune[this->nrElemente];
		{
			for (int i = 0; i < this->nrElemente; i++)
			{
				this->vectorElementeGestiune[i] = vectorElementeGestiune[i];
			}
		}
	}
	//Destructor pentru clasa template Gestiune
	~Gestiune()
	{
		if (this->vectorElementeGestiune != NULL)
		{
			delete[] this->vectorElementeGestiune;
		}
	}
	//Getteri pentru clasa template Gestiune
	int getNrElemente()
	{
		return this->nrElemente;
	}
	tipDataElementeGestiune* getVectorElementeGestiune()
	{
		return this->vectorElementeGestiune;
	}

	//Setteri pentru clasa template Gestiune
	void setElementeGestiune(int nrElementeNew, tipDataElementeGestiune* vectorElementeGestiuneNew)
	{
		if (this->vectorElementeGestiune != NULL)
		{
			delete[] this->vectorElementeGestiune;
		}
		this->nrElemente = nrElementeNew;
		this->vectorElementeGestiune = new tipDataElementeGestiune[this->nrElemente];
		for (int i = 0; i < this->nrElemente; i++)
		{
			this->vectorElementeGestiune[i] = vectorElementeGestiuneNew;
		}
	}

	//Constructor de copiere pentru clasa template Gestiune
	Gestiune(const Gestiune& g)
	{
		this->nrElemente = g.nrElemente;
		this->vectorElementeGestiune = new tipDataElementeGestiune[this->nrElemente];
		{
			for (int i = 0; i < this->nrElemente; i++)
			{
				this->vectorElementeGestiune[i] = g.vectorElementeGestiune[i];
			}
		}
	}
	//Operator = pentru clasa template Gestiune
	Gestiune& operator=(const Gestiune& g)
	{
		if (this != &g)
		{
			if (this->vectorElementeGestiune != NULL)
			{
				delete[] this->vectorElementeGestiune;
			}
			this->nrElemente = g.nrElemente;
			this->vectorElementeGestiune = new tipDataElementeGestiune[this->nrElemente];
			{
				for (int i = 0; i < this->nrElemente; i++)
				{
					this->vectorElementeGestiune[i] = g.vectorElementeGestiune[i];
				}
			}
		}
		return *this;
	}
	// Operator << (afisare) pentru clasa template Gestiune
	friend ostream& operator<<(ostream& out, Gestiune& g)
	{
		out << "Numar elemente: " << g.nrElemente << endl;
		out << "Elementele: " << endl;
		for (int i = 0; i < g.nrElemente; i++)
		{
			out << g.vectorElementeGestiune[i] << endl;
		}
		return out;
	}
	//Operator >> (citire) pentru clasa template Gestiune
	friend istream& operator>>(istream& in, Gestiune& g)
	{
		if (g.vectorElementeGestiune != NULL)
		{
			delete[] g.vectorElementeGestiune;
		}
		cout << "Introduceti numarul de elemente: " << endl;
		in >> g.nrElemente;
		g.vectorElementeGestiune = new tipDataElementeGestiune[g.nrElemente];
		cout << "Introduceti elementele: " << endl;
		for (int i = 0; i < g.nrElemente; i++)
		{
			in >> g.vectorElementeGestiune[i];
		}
		return in;
	}

};


//AICI INCEPE MAIN-UL 

int main()
{

	//AICI INCEPE APELAREA CLASEI ANGAJAT


	cout << endl;
	cout << "////////////////////////////////////// CLASA Angajat //////////////////////////" << endl;
	Angajat a1;
	cout << "------------------------------------GETTERI ------------------------------" << endl;
	cout << "Functie: " << a1.getFunctie() << endl;
	cout << "Varsta: " << a1.getVarsta() << endl;
	cout << "Nume: " << a1.getNume() << endl;
	cout << "Salariu: " << a1.getSalariu() << endl;
	cout << "Varsta: " << a1.getVarsta() << endl;
	cout << "Ore lucrate pe zi: " << a1.getOreLucratePeZi() << endl;

	cout << "Spor de noapte: " << endl;
	cout << "Numar prime: " << a1.getNrPrime() << endl;
	for (int i = 0; i < a1.getNrPrime(); i++) {
		cout << "Valoare prime: " << a1.getvaloarePrime()[i] << endl;
	}
	int oreLucratePeZi[7]{ 8,8,8,8,8,0,0 };
	float valoarePrimeAngajat[2]{ 150,180 };
	cout << "-----------------------------------SETTERI si GETTERI---------------------------------" << endl;
	a1.setFunctie("Casier");
	a1.setVarsta(42);
	a1.setNume("Alisa");
	float ore[7] = { 8,8,8,8,8,0,0 };
	a1.setOreLucratePeZi(ore);
	a1.setSporDeNoapte(1);
	float valoarePrime[3]{ 300,400,500 };
	a1.setPrime(3, valoarePrime);
	a1.setSalariu(3000);

	cout << "Nume: " << a1.getNume() << endl;
	cout << "Salariu: " << a1.getSalariu() << endl;
	cout << "Varsta: " << a1.getVarsta() << endl;

	for (int i = 0; i < 6; i++)
	{
		cout << "Ore lucrate pe zi: " << a1.getOreLucratePeZi()[i] << endl;
	}
	cout << "Spor de noapte: " << a1.getSporDeNoapte() << endl;
	cout << "Numar prime: " << a1.getNrPrime() << endl;
	for (int i = 0; i < a1.getNrPrime(); i++) {
		cout << "Valoare prime: " << a1.getvaloarePrime()[i] << endl;
	}

	cout << endl;

	cout << "-------------------------- Operator << (afisare) ------------------------------" << endl << endl;
	cout << "************************ Afisare obiectul a1 ***********************************" << endl;
	cout << a1;
	float vectorValoriPrime[3]{ 100.5,200.88,300.66 };
	float ore1[7] = { 8,8,8,8,4,4,0 };
	Angajat a2("Cristian", "Sofer", 25, 4000, ore1, 3, vectorValoriPrime, 0);
	float vectorValoriPrime10[3]{ 120,140,150.5 };
	float ore10[7] = { 6,6,6,6,6,6,0 };
	Angajat a10("Andreea", "femeie de serviciu", 54, 2000, ore10, 3, vectorValoriPrime10, 1);

	float vectorValoriPrime20[3]{ 200,230,260 };
	float ore20[7] = { 6,6,6,6,6,6,0 };
	Angajat a20("Valentin", "dispecer", 31, 3100, ore20, 3, vectorValoriPrime20, 1);

	cout << "************************ Afisare obiectul a2 ***********************************" << endl;
	cout << a2 << endl << endl;

	cout << "------------------------- Constructor de copiere --------------------------------" << endl;
	Angajat a3(a2);
	cout << a3;

	cout << "--------------------------- Operatorul = -----------------------------------------" << endl << endl;
	cout << "***************************** Obiectul inainte de modificare ************************" << endl;
	float vectorValoriPrime1[4]{ 100,150,200,250 };
	float ore2[7] = { 8,8,8,8,8,0,0 };
	Angajat a4("Sebastian", "Paznic", 25, 2200, ore2, 3, vectorValoriPrime1, 0);
	cout << a10;
	cout << "***************************** Obiectul dupa modificare ************************" << endl;
	a4 = a10;
	cout << a4;

	cout << "---------------------------- operatorul index [] -------------------------------------" << endl << endl;
	cout << "Indexare operator: " << a4[2] << endl;

	cout << "------------------------------ operatorul ! (negatie) ---------------------------------" << endl << endl;
	cout << "***************************** Obiectul inainte de modificare ************************" << endl;
	cout << a20;
	cout << "***************************** Obiectul dupa modificare ******************************" << endl;
	!a20;
	cout << a20;

	cout << "------------------------------- Operator == --------------------------------------" << endl;
	cout << "Cei doi angajati au aceeasi varsta?" << endl << "Raspuns (1=da;0=nu): " << (a2 == a4) << endl;
	cout << endl << endl;
	cout << "-----------------------------------Operator ++ (postincrementare) -----------------------------" << endl;
	cout << "Varsta inainte de modificare: " << a2.getVarsta() << endl;
	a2++;
	cout << "Varsta dupa modificare: " << a2.getVarsta() << endl;
	cout << endl << endl;
	cout << "----------------------------------- Operator ++ (preincrementare) -----------------------------" << endl;
	cout << "Varsta inainte de modificare: " << a2.getVarsta() << endl;
	++a2;
	cout << "Varsta dupa modificare: " << a2.getVarsta() << endl;
	cout << endl << endl;
	cout << "----------------------------- Operatorul < (comparatie) ---------------------------" << endl;
	cout << "Rezultat comparatie:  " << (a4 < a2) << endl;

	cout << "--------------------------- Operator >> (citire) ------------------------------" << endl;
	/*cin >> a2;*/
	cout << "------------------------------ Operator + ------------------------------" << endl << endl;
	cout << "----------------------------- Obiectul a10 inainte ----------------------" << endl << endl;
	cout << a10;
	cout << "----------------------------- Obiectul a10 dupa ----------------------" << endl << endl;
	cout << a10.operator+(200) << endl;




	cout << "------------------------------------- Metode prelucrare ------------------------------" << endl;
	cout << "Cea mai mare valoare a primelor: " << " " << a2.valoareMaximPrima() << endl;
	cout << "Valoarea medie a primelor: " << " " << a2.valoareMediePrima() << endl;


	cout << endl << endl << "-------------------------- operator de cast la int --------------------------" << endl << endl;
	cout << "Angajatii din depozit au " << (int)a4 << " prime mai mari de 150 lei. " << endl << endl;

	cout << "------------------------------------- Fisiere text clasa Angajat --------------------------------------------" << endl << endl;


	//Apelare fisiere CSV clasa Angajat
	ofstream fisierCSV1("AngajatiCSV.csv", ios::out);
	a2.scriereAngajatCSV(fisierCSV1);
	//Scriere fisier text Angajat
	ofstream f1("ScriereAngajatFisier.txt", ios::out);

	f1 << a2;

	f1.close();

	cout << "Obiectul a2 inainte de citirea din fisier text:" << endl << a2 << endl << endl;

	ifstream file("CitireAngajatFisier.txt", ios::in);
	cout << endl;
	file >> a2;

	file.close();

	cout << "Obiectul a2 dupa citirea din fisier text: " << endl << a2 << endl;

	cout << endl << endl << "------------------------ Fisier binar ----------------------" << endl << endl;
	//Scriere in fisier binar
	fstream fisBin1("AngajatBinar.bin", ios::out | ios::binary);
	a2.scriereBinarAngajat(fisBin1);
	fisBin1.close();

	//Citire din fisier binar
	Angajat a5;
	fstream fisBin2("AngajatBinar.bin", ios::in | ios::binary);
	a5.CitireBinarAngajat(fisBin2);
	fisBin2.close();

	cout << a5 << endl << endl;



	//AICI INCEPE APELAREA PENTRU CLASA ASIGURAREDEPOZIT






	cout << endl << endl << endl;
	cout << "//////////////////////////////// CLASA AsigurareDepozit //////////////////////////////" << endl << endl;
	AsigurareDepozit ad1;
	cout << "------------------------------------ GETTERI ------------------------------" << endl;
	cout << "Firma asiguratoare:  " << ad1.getFirmaAsiguratoare() << endl;
	cout << "Reinnoire anuala:  " << ad1.getReInnoireAnuala() << endl;

	cout << "Numar clauze: " << ad1.getNrClauze() << endl;
	for (int i = 0; i < ad1.getNrClauze(); i++) {
		cout << "Tip clauze " << ad1.getTipClauze()[i] << endl;
	}
	cout << "Valoare: " << ad1.getValoare() << endl;

	cout << "----------------------------------- SETTERI si GETTERI ---------------------------------" << endl;
	ad1.setFirmaAsiguratoare("Astra");
	ad1.setReinnoireAnuala(1);
	cout << "Firma asiguratoare:  " << ad1.getFirmaAsiguratoare() << endl;
	cout << "Reinnoire anuala:  " << ad1.getReInnoireAnuala() << endl;
	string numeClauze[3]{ "protectiaMediului", "igiena", "dezastreNaturale" };
	ad1.setClauze(3, numeClauze);
	ad1.setValoare(5000);
	cout << "Numar clauze: " << ad1.getNrClauze() << endl;
	for (int i = 0; i < ad1.getNrClauze(); i++) {
		cout << "Tip clauze: " << ad1.getTipClauze()[i] << endl;
	}
	cout << "Valoare: " << ad1.getValoare() << endl;

	cout << "-------------------------- Operator << (afisare) ------------------------------" << endl << endl;
	cout << "************************ Afisare obiectul ad1 ***********************************" << endl;
	cout << ad1;
	cout << "************************ Afisare obiectul ad2 ***********************************" << endl;
	float vectorValoareClauze[3]{ 2000,4000,6000 };
	string vectorTipClauze[3] = { "sanatate", "calamitati", "abuzive" };
	AsigurareDepozit ad2("EuroINS", 3, vectorTipClauze, 10000.9, 0);
	cout << ad2 << endl << endl;



	cout << "------------------------- Constructor de copiere --------------------------------" << endl;
	AsigurareDepozit ad3(ad2);
	cout << ad3;

	cout << "--------------------------- Operatorul = -----------------------------------------" << endl << endl;
	cout << "***************************** Obiectul inainte de modificare ************************" << endl;
	float vectorValoareClauze1[3]{ 1000,3000,5000 };
	char vectorNumeAsigurare1[30] = "Allianz";
	string vectorTipClauze1[3] = { "cutremur", "inundatii", "incendiu" };
	AsigurareDepozit ad4(vectorNumeAsigurare1, 3, vectorTipClauze1, 5000, 1);
	cout << ad4;
	cout << "***************************** Obiectul dupa modificare ************************" << endl;
	ad4 = ad2;
	cout << ad2;

	cout << "---------------------------- Operatorul index [] -------------------------------------" << endl << endl;
	cout << "Indexare operator: " << ad4[1] << endl;

	cout << "------------------------------ Operatorul ! (negatie) ---------------------------------" << endl << endl;
	cout << "***************************** Obiectul inainte de modificare ************************" << endl;
	cout << ad4;
	cout << "***************************** Obiectul dupa modificare ************************" << endl;
	!ad4;
	cout << ad4;


	cout << "----------------------------- Operatorul > (comparatie) ---------------------------" << endl;
	cout << "Comparatie: " << (ad1 > ad2) << endl;
	cout << "--------------------------- Operator >> (citire) ------------------------------" << endl;    ////merge forta
	/*cin >> ad2;*/

	cout << "------------------------------------- Metode prelucrare ------------------------------" << endl;
	cout << endl << endl;
	cout << "******* Metoda care adauga o noua clauza si o noua valoare in vector **********" << endl;
	cout << endl;
	ad4.adaugaClauzaNoua("accidente");
	cout << ad4 << endl << endl;
	cout << "*******Metoda care elimina dupa pozitie in vector o noua clauza si o noua valoare in vector**********" << endl;
	cout << "Clauza  ad2 inainte de eliminare (ad2(2)): " << endl << ad2 << endl;
	ad2.eliminaDupaPozitie(2);
	cout << "Clauza  ad2 dupa eliminare (ad2(2)): " << endl << ad2 << endl;

	cout << "------------------------------- Operator == --------------------------------------" << endl;
	cout << "Cele doua tipuri de asigurari sunt la fel din punct de vedere al reinnoirii anuale?  " << endl << "Raspuns (1=da;0=nu): " << (ad2 == ad4) << endl;
	cout << endl << endl;
	cout << "--------------------------------- Operator de cast -----------------------------------" << endl;
	int nrClauze = (int)ad2;
	cout << "Numar clauze:  " << nrClauze << endl;
	cout << "--------------------------- Operator + ------------------------------" << endl << endl;
	cout << "----------------------------- Obiectul ad4 inainte ----------------------" << endl << endl;
	cout << ad4;
	cout << "----------------------------- Obiectul ad4 dupa ----------------------" << endl << endl;
	cout << ad4.operator+(500) << endl;


	cout << "------------------------------------- Fisiere text clasa AsigurareDepozit --------------------------------------------" << endl << endl;

	ofstream f2("ScriereAsigurareDepozitFisier.txt", ios::out);

	//2.SCRIEREA UNUI OBIECT IN FISIER
	f2 << ad2;

	//3.INCHIDEREA FISIERULUI TEXT
	f2.close();

	cout << "Obiectul ad2 inainte de citirea din fisier text:" << endl << ad2 << endl << endl;

	ifstream file1("CitireAsigurareDepozitFisier.txt", ios::in);
	cout << endl;
	file1 >> ad2;

	file1.close();

	cout << "Obiectul ad2 dupa citirea din fisier text: " << endl << ad2 << endl;

	cout << endl << endl << "------------------------ Fisier binar ----------------------" << endl << endl;
	//Scriere in fisier binar
	fstream fisBin3("AsigurareDepozit.bin", ios::out | ios::binary);
	ad2.scriereBinarAsigurareDepozit(fisBin3);
	fisBin3.close();


	//Citire din fisier binar
	AsigurareDepozit ad5;
	fstream fisBinarAsigurareDepozit("AsigurareDepozit.bin", ios::in | ios::binary);
	ad5.CitireBinarAsigurareDepozit(fisBinarAsigurareDepozit);
	fisBinarAsigurareDepozit.close();

	cout << ad5 << endl << endl;

	//Raport clasa AsigurareDepozit
	float vectorValoareRaport[3]{ 1000,3000,5000 };
	char vectorNumeRaport1[30] = "Allianz";
	string vectorTipRaport[4] = { "cutremur", "inundatii", "incendiu", "sanatate" };

	AsigurareDepozit adraport(vectorNumeRaport1, 4, vectorTipRaport, 8000, 1);
	adraport.raportAsigurareDepozit("RaportAsigurareDepozit.txt");



	//AICI INCEPE APELAREA PENTRU CLASA PRODUS ALIMENTAR





	cout << endl << endl << endl;
	cout << "////////////////////////////// CLASA ProdusAlimentar /////////////////////////////////" << endl;
	ProdusAlimentar p1;
	cout << "------------------------------------ GETTERI ------------------------------" << endl;
	cout << "Distribuitor: " << p1.getDistribuitor() << endl;
	cout << "Id Produs:  " << p1.getIdProdus() << endl;
	cout << "Alergeni: " << p1.getAlergeni() << endl;
	cout << "Denumire produs: " << p1.getDenumireProdus() << endl;
	cout << "Pret de baza: " << p1.getPretBaza() << endl;
	cout << "Data expirare: ";
	for (int i = 0; i < 3; i++)
	{
		cout << p1.getDataExpirare()[i] << "/" << endl;
	}


	cout << "----------------------------------- SETTERI si GETTERI ---------------------------------" << endl;
	p1.setDistribuitor("Danone");
	p1.setDenumireProdus("iaurt");
	p1.setAlergeni(1);
	p1.setPretBucata(12);
	p1.setDenumireProdus("Iaurt");
	int dataExpirareprodus[3]{ 20,12,2022 };
	p1.setdataExpirare(dataExpirareprodus);

	cout << "Distribuitor: " << p1.getDistribuitor() << endl;
	cout << "Id Produs:  " << p1.getIdProdus() << endl;
	cout << "Alergeni: " << p1.getAlergeni() << endl;
	cout << "Denumire produs: " << p1.getDenumireProdus() << endl;
	cout << "Pret de baza: " << p1.getPretBaza() << endl;
	cout << "Data expirare: ";
	for (int i = 0; i < 3; i++)
	{
		cout << p1.getDataExpirare()[i] << "/" << endl;
	}

	cout << "-------------------------- Operator << (afisare) ------------------------------" << endl << endl;
	cout << "************************ Afisare obiectul a1 ***********************************" << endl;
	cout << p1;
	int dataexpirare[3] = { 20, 01, 2023 };
	ProdusAlimentar p2("Lapte batut", dataexpirare, 20, "Covalact", 0, 12);
	int dataExpirare2[3]{ 31,12,2024 };
	ProdusAlimentar p7("suc", dataExpirare2, 6, "Coca Cola", 1, 546);
	int dataExpirare3[3]{ 15,04, 2023 };
	ProdusAlimentar p10("Muschi file", dataExpirare3, 12, "Sissi", 0, 374);
	cout << "************************ Afisare obiectul a2 ***********************************" << endl;
	cout << p2 << endl << endl;

	cout << "------------------------- Constructor de copiere ----------------------------------------" << endl;
	ProdusAlimentar p3(p2);
	cout << p3;

	cout << "--------------------------- Operatorul = -------------------------------------------------" << endl << endl;
	cout << "*****************************Obiectul inainte de modificare************************" << endl;
	int dataexpirare1[3] = { 25, 07, 2024 };
	ProdusAlimentar p4("Pateu", dataexpirare1, 3, "Bucegi", 0, 34);


	cout << p4;
	cout << "***************************** Obiectul dupa modificare ************************" << endl;
	p4 = p2;
	cout << p2;
	cout << "------------------------------- Operator == --------------------------------------" << endl;
	cout << "Cele doua produse sunt la fel din punct de vedere al alergenilor " << endl << "Raspuns (1=da;0=nu): " << (p2 == p4) << endl;
	cout << endl << endl;


	cout << "--------------------------- Operator >> (citire) ------------------------------" << endl;
	/*cin >> p2;*/

	cout << "----------------------------- Operatorul >= (comparatie) ---------------------------" << endl;
	cout << endl;
	cout << "Comparatie intre preturi: " << (p2 >= p4) << endl;

	cout << endl << "------------------------- Operatorul cast la string --------------------------" << endl << endl;
	cout << string(p4) << endl;
	cout << "--------------------------- Operator predecrementare (--) ---------------------" << endl << endl;
	cout << "***************************** Obiectul inainte de modificare ************************" << endl;
	cout << p2;
	cout << "***************************** Obiectul dupa modificare ************************" << endl;
	p4 = --p2;
	cout << p4;

	cout << "----------------------------operatorul index []-------------------------------------" << endl << endl;
	cout << "Indexare operator: " << p2[2] << endl << endl;

	cout << "---------------------------Operator + ------------------------------" << endl << endl;
	cout << "------------------------------ Obiectul p7 inainte -------------------" << endl << endl;
	cout << p7;
	cout << "------------------------------ Obiectul p7 dupa -------------------" << endl << endl;
	cout << p7.operator+(40) << endl;


	cout << "------------------------------------- Fisiere text ProdusAlimentar --------------------------------------------" << endl;
	ofstream f3("ScriereProdusAlimentarFisier.txt", ios::out);

	//2.SCRIEREA UNUI OBIECT IN FISIER
	f3 << p2;

	//3.INCHIDEREA FISIERULUI TEXT
	f3.close();


	//CITIRE DIN FISIER TEXT
	cout << "Obiectul p2 inainte de citirea din fisier text:" << endl << p2 << endl << endl;

	ifstream file2("CitireProdusAlimentarFisier.txt", ios::in);

	//2.CITIREA UNUI OBIECT DIN FISERUL TEXT
	file2 >> p2;

	//3.INCHIDEREA FISIERULUI TEXT
	file2.close();

	cout << "Obiectul p2 dupa citirea din fisier text:" << endl << p2 << endl << endl;


	//Apelare fisier CSV clasa AsigurareDepozit
	ofstream fisierCSV3("AsigurareDepozitCSV.csv", ios::out);
	ad4.scriereAsigurareDepozitCSV(fisierCSV3);



	cout << endl << endl << "---------------------------- Fisier binar -------------------------" << endl << endl;
	//Scriere in fisier binar
	fstream fisBinProdus("ProdusAlimentarBinar.bin", ios::out | ios::binary);
	p2.scriereBinarProdusAlimentar(fisBinProdus);
	fisBinProdus.close();

	//Citire fisier binar
	ProdusAlimentar p5;
	fstream fisBinProdusAlimentar("ProdusAlimentarBinar.bin", ios::in | ios::binary);
	p5.CitireBinarProdusAlimentar(fisBinProdusAlimentar);
	fisBinProdusAlimentar.close();

	//Fisier CSV clasa Produs Alimentar
	ofstream fisierCSV2("ProdusAlimentarCSV.csv", ios::out);
	p2.scriereProdusAlimentarCSV(fisierCSV2);

	cout << p5 << endl << endl;

	int dataExpirareRaport[3] = { 12, 5, 2023 };

	//Raport clasa ProdusAlimentar
	ProdusAlimentar praport("Biscuiti", dataExpirareRaport, 7, "Biskreem", 0, 17);
	praport.raportProdusAlimentar("RaportProdusAlimentar.txt");







	//AICI INCEPE APELAREA PENTRU CLASA COMANDA


	cout << endl << endl << endl;
	cout << "///////////////////////////////////// CLASA Comanda ////////////////////////////////////" << endl << endl;
	Comanda c1;
	cout << "------------------------------------ GETTERI ------------------------------" << endl;
	int dataPlasareComanda[3] = { 16, 05, 2023 };
	int nrBucati[3]{ 345,543,876 };
	ProdusAlimentar vectorprodusAlimentar[] = { p2, p4 };
	Comanda c4(dataPlasareComanda, 2, vectorprodusAlimentar, nrBucati, 300, 1, 19);
	cout << "Data plasare comanda: ";
	for (int i = 0; i < 3; i++)
	{
		cout << c4.getDataPlasareComanda()[i] << "/" << endl;
	}
	cout << "Numar produse comandate: " << c4.getNrProduseComandate() << endl;


	for (int i = 0; i < c4.getNrProduseComandate(); i++)
	{
		cout << "Produse comandate: " << c4.getVectorProduseComandate()[i] << endl;
		cout << "Numar bucati fiecare produs: " << c4.getNrBucatiFiecareProdus()[i] << endl;

	}

	cout << "Valoare comanda:  " << c4.getValoareTransport() << endl;
	cout << "Status expediere: " << c4.getExpediata() << endl;

	int dataPlasareComanda2[3] = { 20, 8, 2023 };
	int nrBucati2[3]{ 214,327,374 };
	ProdusAlimentar vectorprodusAlimentar2[] = { p4, p7 };
	Comanda c5(dataPlasareComanda2, 2, vectorprodusAlimentar2, nrBucati2, 300, 1, 19);

	int dataPlasareComanda3[3] = { 27, 11, 2023 };
	int nrBucati3[3]{ 346,834,452 };
	ProdusAlimentar vectorprodusAlimentar3[] = { p2, p10 };
	Comanda c10(dataPlasareComanda3, 2, vectorprodusAlimentar3, nrBucati3, 40, 1, 475);


	int dataPlasareComanda4[3] = { 27, 11, 2023 };
	int nrBucati4[3]{ 346,834,452 };
	ProdusAlimentar vectorprodusAlimentar4[] = { p4, p10 };
	Comanda c20(dataPlasareComanda4, 2, vectorprodusAlimentar4, nrBucati4, 34, 1, 87);

	cout << "----------------------------------- SETTERI si GETTERI ---------------------------------" << endl;

	int dataPlasareComanda1[3] = { 25, 02, 2023 };
	int nrBucati1[2]{ 633,320 };
	ProdusAlimentar vectorprodusAlimentar1[] = { p7, p10 };
	c1.setValoareTransport(50);
	c1.setExpediata(1);
	c1.setDataPlasareComanda(dataPlasareComanda1);
	c1.setVectorProduseComandate(2, vectorprodusAlimentar1, nrBucati1);

	cout << "Data plasare comanda: ";
	for (int i = 0; i < 3; i++)
	{
		cout << c1.getDataPlasareComanda()[i] << "/" << endl;
	}
	cout << "Numar produse comandate: " << c1.getNrProduseComandate() << endl;


	for (int i = 0; i < c1.getNrProduseComandate(); i++)
	{
		cout << "Produse comandate: " << c1.getVectorProduseComandate()[i] << endl;
		cout << "Numar bucati fiecare produs: " << c1.getNrBucatiFiecareProdus()[i] << endl;

	}

	cout << "Valoare comanda:  " << c1.getValoareTransport() << endl;
	cout << "Status expediere: " << c1.getExpediata() << endl;




	cout << "-------------------------- Operator << (afisare) ------------------------------" << endl << endl;
	cout << "************************ Afisare obiectul c20 ***********************************" << endl;
	cout << c20;



	cout << "------------------------- Constructor de copiere ----------------------------------------" << endl;
	Comanda c30(c10);
	cout << c30;

	cout << "--------------------------- Operatorul = -----------------------------------------" << endl << endl;
	cout << "***************************** Obiectul inainte de modificare ************************" << endl;
	cout << c4;
	cout << "***************************** Obiectul dupa modificare ************************" << endl;
	c4 = c10;
	cout << c4;

	cout << "------------------------------ operatorul ! (negatie) ---------------------------------" << endl << endl;
	cout << "***************************** Obiectul inainte de modificare ************************" << endl;
	cout << c5;
	cout << "***************************** Obiectul dupa modificare ************************" << endl;
	!c5;
	cout << c5;

	cout << "------------------------------- Operator == --------------------------------------" << endl;
	cout << "Comenziile au acelasi status de expediere?  " << endl << "Raspuns (1=da;0=nu): " << (c20 == c4) << endl;
	cout << endl << endl;

	cout << endl << endl << endl;

	cout << "--------------------------- Operator + ------------------------------" << endl << endl;
	cout << "------------------------------ Obiectul c20 inainte -------------------" << endl << endl;
	cout << c20;
	cout << "------------------------------ Obiectul c20 dupa -------------------" << endl << endl;
	cout << c20.operator+(100) << endl;

	cout << "-------------------------- Operator >> (citire)------------------------------" << endl << endl;
	cout << "************************ Citire c3 ***********************************" << endl;
	/*cin>> c3;*/

	cout << endl << endl;

	cout << "----------------------------------- Fisier text clasa Comanda ------------------------------" << endl << endl;

	ofstream file4("ScriereComandaFisier.txt", ios::out);

	//2.SCRIEREA UNUI OBIECT IN FISIER
	file4 << c5;

	//3.INCHIDEREA FISIERULUI TEXT
	file4.close();
	cout << endl << endl;

	//CITIRE DIN FISIER TEXT

	cout << "Obiectul c20 inainte de citirea din fisier text:" << endl << c20 << endl << endl;
	cout << endl << endl;

	ifstream file5("CitireComandaFisier.txt", ios::in);

	//2.CITIREA UNUI OBIECT DIN FISERUL TEXT
	file5 >> c4;

	//3.INCHIDEREA FISIERULUI TEXT
	file5.close();
	cout << endl << endl;
	cout << "Obiectul c20 dupa citirea din fisier text:" << endl << c20 << endl << endl;


	cout << endl << endl << "--------------------------- Fisier binar -------------------------" << endl << endl;
	//Scriere in fisier binar
	fstream fisBin4("Comanda.bin", ios::out | ios::binary);
	c5.scriereBinarComanda(fisBin4);
	fisBin4.close();


	//Citire din fisier binar
	Comanda c6;
	fstream fisBinarComanda("Comanda.bin", ios::in | ios::binary);
	c6.CitireBinarComanda(fisBinarComanda);
	fisBinarComanda.close();

	cout << c6 << endl << endl;


	//Fisier CSV clasa Comanda
	ofstream fisierCSV4("ComandaCSV.csv", ios::out);
	c5.scriereComandaCSV(fisierCSV4);


	cout << endl << endl;


	//AICI INCEPE APELAREA PENTRU  CLASA DEPOZIT







	cout << "////////////////////////////////// CLASA Depozit /////////////////////////////////////" << endl << endl;
	Depozit d1;
	cout << "------------------------------------ GETTERI ------------------------------" << endl;
	cout << "Nume Depozit: " << d1.getNumeDepozit() << endl;
	cout << "Suprafata Magazin: " << d1.getSuprafata() << endl;
	cout << "Are etaj? (1=da;0=nu):  " << d1.getAreEtaj() << endl;
	cout << "Numar angajati:  " << d1.getNrAngajati() << endl;
	cout << "Numar comenzi: " << d1.getNrComenzi() << endl;
	cout << endl << endl << endl;

	Angajat vectorAngajati1[2] = { a10,a20 };
	Comanda** vectorPointeriComanda;
	vectorPointeriComanda = new Comanda * [2];
	vectorPointeriComanda[0] = new Comanda(c20);
	vectorPointeriComanda[1] = new Comanda(c10);



	Depozit d5("Emag", 2500.5, 1, 2, vectorAngajati1, 2, vectorPointeriComanda, ad1);
	cout << d5 << endl << endl;


	cout << "----------------------------------- GETTERI si SETTERI ---------------------------------" << endl;
	d1.setNumeDepozit("BricoStore");
	d1.setSuprafata(300.25);
	d1.setAreEtaj(1);
	cout << "Nume Depozit: " << d1.getNumeDepozit() << endl;
	cout << "Suprafata Magazin: " << d1.getSuprafata() << endl;
	cout << "Are etaj? (1=da;0=nu):  " << d1.getAreEtaj() << endl;


	cout << "------------------------- Constructor de copiere ----------------------------------------" << endl;
	Depozit d2(d1);
	cout << d2;

	cout << "--------------------------- Operatorul = -------------------------------------------------" << endl << endl;
	Depozit d3 = d1;
	cout << d3;


	cout << "----------------------------- Operatorul < (comparatie)---------------------------" << endl;
	cout << "Rezultat comparatie: " << (d1 < d2) << endl;

	cout << "------------------------------Operatorul ! (negatie) ---------------------------------" << endl << endl;
	cout << "***************************** Obiectul inainte de modificare ************************" << endl;
	cout << d1;
	cout << "***************************** Obiectul dupa modificare ************************" << endl;
	!d1;
	cout << d1;
	cout << "------------------------------- Operator == --------------------------------------" << endl;
	cout << "Cele doua depozite sunt la fel din punct de vedere al prezentei/lipsei etajului?   " << endl << "Raspuns (1=da;0=nu): " << (d1 == d1) << endl;
	cout << endl << endl;

	cout << "--------------------------- Operator + ------------------------------" << endl << endl;
	cout << "------------------------------ Obiectul d1 inainte -------------------" << endl << endl;
	cout << d1;
	cout << "------------------------------ Obiectul d1 dupa -------------------" << endl << endl;
	cout << d1.operator+(340) << endl;

	cout << "-------------------------- Operator >> (citire) ------------------------------" << endl << endl;
	cout << "*********************************citire d3***********************************" << endl;


	Angajat vectorAngajati2[2] = { a2,a4 };
	Comanda** vectorPointeriComanda1;
	vectorPointeriComanda1 = new Comanda * [3];
	vectorPointeriComanda1[0] = new Comanda(c10);
	vectorPointeriComanda1[1] = new Comanda(c5);
	vectorPointeriComanda1[2] = new Comanda(c20);

	Depozit depozitRaport("Flanco", 2500.5, 1, 2, vectorAngajati2, 3, vectorPointeriComanda1, ad1);
	depozitRaport.raportDepozit("RaportDepozit.txt");


	ofstream f5("ScriereDepozitFisier.txt", ios::out);

	//2.SCRIEREA UNUI OBIECT IN FISIER
	f5 << d5;

	//3.INCHIDEREA FISIERULUI TEXT
	f5.close();



	cout << endl << endl;
	cout << "Obiectul d5 dupa citirea din fisier text: " << endl << d5 << endl << endl;


	cout << "********************************* Scriere binare ***********************************" << endl;

	cout << d5 << endl << endl;
	fstream fisBin6("Depozit.bin", ios::out | ios::binary);
	d5.scriereBinarDepozit(fisBin6);
	fisBin6.close();

	cout << "********************************* Citire binare ***********************************" << endl;

	Depozit d6;
	fstream fisBinDepozit("Depozit.bin", ios::in | ios::binary);
	d6.CitireBinarDepozit(fisBinDepozit);
	fisBinDepozit.close();

	cout << d6 << endl << endl;

	//Fisiere CSV clasa Depozit
	ofstream fisierCSV5("DepozitCSV.csv", ios::out);
	d5.scriereDepozitCSV(fisierCSV5);






	cout << "///////////////////////////////// CLASA Sofer /////////////////////////////////////" << endl << endl;
	cout << "-------------------------------- GETTERI ---------------------------------------" << endl << endl;
	string vectorDestinatii[3]{ "Craiova", "Arges", "Valcea" };
	int oreLucrateSofer[7]{ 12,12,0,12,12,0,12 };
	int primeSofer[3]{ 100, 180, 220 };
	Sofer s1;
	//Sofer s2(430, 3, vectorDestinatii, 1, "Lucian", "sofer", 43, 3100, oreLucrateSofer, 3, primeSofer, 1);
	int oreLucrateSofer1[7]{ 8,8,8,8,8,0,0 };
	int primeSofer1[3]{ 100, 200, 250 };
	string vectorDestinatii1[3]{ "Pitesti", "Arges", "Bucuresti" };
	//Sofer s3(432, 3, vectorDestinatii1, 0, "Marius", "sofer", 43, 3200, oreLucrateSofer1, 3, primeSofer1, 0);

	cout << "Numar km parcursi: " << s1.getNrKmParcursi() << endl;
	cout << "Numar de destinatii: " << s1.getNrDestinatie() << endl;
	for (int i = 0; i < s1.getNrDestinatie(); i++) {
		cout << "Nume destinatii: " << s1.getNumeDestinatie()[i] << endl;
	}
	cout << "Cursa de noapte: " << s1.getCursaDeNoapte() << endl;

	cout << "------------------------------------- SETTERI -----------------------------------" << endl << endl;
	s1.setKmParcursi(562);
	s1.setCursaDeNoapte(1);
	s1.setDestinatie(1, "Bucuresti");

	cout << "Numar km parcursi: " << s1.getNrKmParcursi() << endl;
	cout << "Numar de destinatii: " << s1.getNrDestinatie() << endl;
	for (int i = 0; i < s1.getNrDestinatie(); i++) {
		cout << "Nume destinatii: " << s1.getNumeDestinatie()[i] << endl;
	}
	cout << "Cursa de noapte: " << s1.getCursaDeNoapte() << endl;

	cout << "--------------------- OPERATOR << CLASA SOFER ---------------------------" << endl;
	cout << s1;

	cout << "--------------------- OPERATOR >> CLASA SOFER ---------------------------" << endl;
	cin >> s1;
	cout << s1;
	cout << endl << endl;

	cout << "//////////////////////////////// FUNCTII VIRTUALE //////////////////////////////////" << endl;
	cout << "********************Functia virtuala care returneaza clasa in care te afli***********" << endl;
	cout << a4.returneazaClasaInCareMaAflu() << endl << endl;
	cout << s1.returneazaClasaInCareMaAflu() << endl << endl;
	cout << "********************* Functia virtuala care reseteaza un obiect ***********" << endl;
	cout << "----------------------- Obiectul a10 inainte de resetare -----------------------" << endl;
	cout << a10;
	cout << "----------------------- Obiectul a10 dupa resetare -----------------------" << endl;

	a10.resetareObiect();
	cout << a10 << endl;
	cout << "----------------------- Obiectul s1 inainte de resetare -----------------------" << endl;

	//Aici incepe apelarea clasei derivate ProdusAlimentarPromotie din clasa ProdusAlimentar



	cout << "////////////////////////////////// CLASA ProdusAlimentarPromotie /////////////////////////////////" << endl << endl;
	cout << "----------------------------------- GETTERI -----------------------------------" << endl;
	ProdusAlimentarPromotie pap1;
	cout << "Valabilitate promotie: " << pap1.getValabilitatePromotie() << endl;
	cout << "Valoare discount: " << pap1.getValoareDiscount() << endl;
	cout << "------------------------------------ SETTERI ----------------------------------" << endl;
	pap1.setValabilitatePromotie(15);
	pap1.setValoareDiscount(10);
	cout << "Valabilitate promotie: " << pap1.getValabilitatePromotie() << endl;
	cout << "Valoare discount: " << pap1.getValoareDiscount() << endl;


	cout << "-------------------------- Constructor de copiere ----------------------------" << endl;
	int dataExpirarePromotie[3]{ 23,01,2023 };
	ProdusAlimentarPromotie pap2(15, 2, "Conserve", dataExpirarePromotie, 5, "Mandy", 1, 556);
	int dataExpirarePromotie1[3]{ 15,02,2023 };
	ProdusAlimentarPromotie pap5(30, 0.9, "Ciocolata", dataExpirarePromotie1, 4.5, "Milka", 1, 325);


	cout << "----------------------------- UPCASTING -----------------------------" << endl;
	cout << "Valabilitate promotie: " << pap2.getValabilitatePromotie() << endl;
	cout << "Valoare discount: " << pap2.getValoareDiscount() << endl;
	ProdusAlimentar p8 = pap2;
	cout << p8;
	cout << "----------------------------- DOWNCASTING -----------------------------" << endl;
	ProdusAlimentarPromotie pap6 = p4;
	cout << pap6;
	cout << "----------------------- OPERATOR << CLASA PRODUS ALIMENTAR PROMOTIE ---------------------------" << endl;
	cout << pap2;

	cout << "----------------------- OPERATOR >> CLASA PRODUS ALIMENTAR PROMOTIE ---------------------------" << endl << endl;
	cin >> pap2;
	cout << pap2;


	cout << "-------------------------------- Operator = --------------------------------------" << endl << endl;
	cout << "****************Obiectul pap2 inainte de a fi modificat pe baza obiectului pap5******************" << endl;
	cout << pap2;
	pap2 = pap5;
	cout << endl << endl;
	cout << "*****************Obiectul pap2 dupa ce a fost  modificat pe baza obiectului pap5**************" << endl;
	cout << pap5;
	cout << endl << endl;



	//CLASE TEMPLATE
	cout << "/////////////////////////////// CLASA TEMPLATE GESTIUNE /////////////////////////" << endl << endl;
	cout << "--------------------------------- GETTERI CLASA TEMPLATE -------------------------------------" << endl;
	Angajat vectorElementeAngajat[] = { a10 };
	Gestiune<Angajat>g1(1, vectorElementeAngajat);
	cout << "Numar elemente g1:" << g1.getNrElemente() << endl;
	cout << "Elementele g1:" << endl;
	for (int i = 0; i < g1.getNrElemente(); i++)
	{
		cout << g1.getVectorElementeGestiune()[i] << endl << endl;
	}
	cout << endl << endl;
	ProdusAlimentar vectorElementeProdusAlimentar[]{ p2, p7 };
	Gestiune <ProdusAlimentar>g2(2, vectorElementeProdusAlimentar);
	cout << "Numar elemente g2:" << g2.getNrElemente() << endl;
	cout << "Elementele g2:" << endl;
	for (int i = 0; i < g2.getNrElemente(); i++)
	{
		cout << g2.getVectorElementeGestiune()[i] << endl << endl;
	}

	cout << endl << endl;
	ProdusAlimentar vectorElementeProdusAlimentar1[]{ p2, p10 };
	Gestiune <ProdusAlimentar>g4(2, vectorElementeProdusAlimentar1);
	cout << "Numar elemente g4:" << g4.getNrElemente() << endl;
	cout << "Elementele g4:" << endl;
	for (int i = 0; i < g4.getNrElemente(); i++)
	{
		cout << g4.getVectorElementeGestiune()[i] << endl << endl;
	}

	cout << "--------------------------- CONSTRUCTORUL DE COPIERE -----------------------" << endl << endl;
	Gestiune<ProdusAlimentar> g3 = g2;
	cout << "Numar elemente g3:" << g3.getNrElemente() << endl;
	cout << "Elemente g3:" << endl;
	cout << endl << endl;
	for (int i = 0; i < g3.getNrElemente(); i++)
	{
		cout << g3.getVectorElementeGestiune()[i] << endl << endl;
	}
	cout << endl << endl;

	cout << "--------------------------- OPERATORUL =-----------------------" << endl << endl;
	cout << "Obiectul macheta g4: " << endl << endl;
	cout << "Numar elemente g4: " << g4.getNrElemente() << endl;
	cout << "Elemente g4:" << endl;
	for (int i = 0; i < g4.getNrElemente(); i++)
	{
		cout << g4.getVectorElementeGestiune()[i] << endl << endl;
	}
	cout << endl << endl;

	g4 = g2;

	cout << "Obiectul g4 dupa ce a fost modificat pe baza lui g2:" << endl << endl;
	cout << "Numar elemente g4:" << g4.getNrElemente() << endl;
	cout << "Elemente g4:" << endl;
	for (int i = 0; i < g4.getNrElemente(); i++)
	{
		cout << g4.getVectorElementeGestiune()[i] << endl << endl;
	}
	cout << endl << endl;

	cout << "---------------------------OPERATORUL << si >> -----------------------" << endl << endl;
	cout << "***************************** Afisare g2 ********************************" << endl;
	cout << g2;
	//cin >> g1;

	cout << endl << endl;
	//cout << g1 << endl << endl;



	//Apelare clasa RaportAfisare in main 

	ofstream fout;
	fout.open("raportAfisare.txt", ofstream::out);
	dm.raportAfisari(fout);
	fout.close();


	//STL - STANDARD TEMPLATE LIBRARY = BIBLIOTECA
	cout << "--------------------------------- STANDARD TEMPLATE LIBRARY (STL)  -----------------------------" << endl << endl;

	cout << "------------------------------------CLASELE DE TIP CONTAINER ------------------------------------" << endl << endl;

	cout << "------------------------------------ VECTOR DE TIP STL --------------------------------------------" << endl << endl;

	//Construirea unui obiect de tipul clasei template vector
	vector<int> vectorSTL;
	//Populare cu elemente 
	vectorSTL.push_back(100);
	vectorSTL.push_back(200);
	vectorSTL.push_back(500);
	vectorSTL.push_back(1000);
	vectorSTL.push_back(2000);
	vectorSTL.push_back(5000);

	cout << "Numarul de elemente din vectorul de tip STL este: " << vectorSTL.size() << endl;

	//Afisarea elementelor din vectorul STL
	cout << "Elementele din vectorSTL sunt: " << endl;
	for (int i = 0; i < vectorSTL.size(); i++)
	{
		cout << vectorSTL[i] << endl;
	}

	//Eliminarea elementelor din vectorul de tip STL
	vectorSTL.pop_back();
	vectorSTL.pop_back();
	vectorSTL.pop_back();

	//Determinarea numarului de elemente dintr-un vector STL 
	cout << "Numarul de elemente din vectorul de tip STL este: " << vectorSTL.size() << endl;

	//Afisarea elementelor dintr-un vector STL
	cout << "Elementele din vectorSTL sunt: " << endl;
	for (int i = 0; i < vectorSTL.size(); i++)
	{
		cout << vectorSTL[i] << endl;
	}

	cout << endl << endl;

	vector<Angajat> vectorSTL1;
	//Eliminarea elementelor din vectorul STL cu metoda push_back 
	vectorSTL1.push_back(a10);
	vectorSTL1.push_back(a4);

	cout << "Numarul de elemente din vectorul de tip STL este: " << vectorSTL1.size() << endl;
	cout << "Elementele din vectorSTL1 sunt: " << endl;
	for (int i = 0; i < vectorSTL1.size(); i++)
	{
		cout << vectorSTL1[i] << endl;
	}
	// Metoda care elimina ultimul element din vectorul STL

	vectorSTL1.pop_back();
	vectorSTL1.pop_back();


	cout << "Numarul de elemente din vectorul de tip STL este: " << vectorSTL1.size() << endl;
	cout << "Elementele din vectorSTL1 sunt: " << endl;
	for (int i = 0; i < vectorSTL1.size(); i++)
	{
		cout << vectorSTL1[i] << endl;
	}

	cout << "------------------------------------- LISTA DE TIP STL ---------------------------------" << endl << endl;
	//Construirea unui obiect de tipul clasei template

	list<Angajat> listaSTL;
	//Popularea cu elemente a listei STL

	listaSTL.push_back(a4);
	listaSTL.push_back(a2);

	//Determinarea numarului de elemente dintr-o lista STL 
	cout << "Numarul de elemente din listaSTL este:" << listaSTL.size() << endl;
	//Metoda care elimina ultimul element din lista STL
	listaSTL.pop_back();


	cout << "------------------------------- CLASELE DE TIP ITERATOR --------------------------" << endl << endl;

	//Declararea unui element de tip iterator STL
	//Construirea unui obiect de tipul clasei template iterator

	list<Angajat>::iterator it1;
	//Parcurgerea elementelor dintr-un container de tip list
	for (it1 = listaSTL.begin(); it1 != listaSTL.end(); it1++)
	{
		cout << *it1 << endl << endl;
	}

	cout << "------------------------------- CONTAINER-UL SET DE TIP STL -----------------------------" << endl << endl;
	//Construirea unui obiect de tipul clasei template SET
	set<int> setSTL;
	//Introducerea elementelor 
	setSTL.insert(100);
	setSTL.insert(150);
	setSTL.insert(720);
	setSTL.insert(910);
	setSTL.insert(400);

	cout << "Numarul de elemente din setSTL1 este: " << setSTL.size() << endl;

	//Afisarea elementelor cu ajutorul unui iterator
	set<int>::iterator it2;
	//Determinarea numarului de elemente 
	for (it2 = setSTL.begin(); it2 != setSTL.end(); it2++)
	{
		cout << *it2 << endl << endl;
	}


	cout << "------------------------------ CONTAINER-UL SET DE TIP MAP -------------------------------" << endl << endl;

	map<int, int > mapSTL;//s-a apelat constructorul clasei template map
	//Introducerea elementelor 

	mapSTL.insert(pair<int, int>(150, 200));
	mapSTL.insert(pair<int, int>(200, 250));
	mapSTL.insert(pair<int, int>(300, 567));
	mapSTL.insert(pair<int, int>(3, 5464));
	mapSTL.insert(pair<int, int>(75, 8));
	//Determinarea numarului de elemente 

	cout << "Numarul de elemente din mapSTL este: " << mapSTL.size() << endl;

	map<int, int>::iterator it3;
	//Parcurgerea elementelor dintr-un container de tip map cu ajutorul unui iterator
	for (it3 = mapSTL.begin(); it3 != mapSTL.end(); it3++)
	{
		cout << "Cheia de identificare este: " << it3->first << endl;
		cout << "Valoarea este: " << it3->second << endl;
	}

	cout << endl << endl;

	//Aici incepe meniul aplicatiei 
	//Meniu
	cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\t\t     Meniu     \t\t\t\t\t" << endl;
	cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;

	bool startMenu = true;
	while (startMenu) {
		int optiune;
		Menu::afisareMeniuPrincipal();
		cin >> optiune;
		switch (optiune) {
		case 0: {
			startMenu = false;
			system("cls");
			cout << "Meniul se inchide" << endl;
			break;
		}

			  //Afisare obiecte in meniu 

		case 1: {
			system("cls");
			cout << a4;

			break;
		}
		case 2: {
			system("cls");
			cout << p4;

			break;
		}
		case 3:
			system("cls");
			cout << ad4;

			break;
		case 4:
			system("cls");
			cout << c20;
			break;
		case 5:
			system("cls");
			cout << d5;
			break;

			//Citire obiecte in meniu 

		case 6: {
			system("cls");
			cin >> a10;
			cout << endl;
			break;
		}
		case 7: {
			system("cls");
			cin >> p2;
			cout << endl;
			break;
		}
		case 8: {
			system("cls");
			cin >> ad4;
			cout << endl;
			break;
		}
		case 9: {
			system("cls");
			cin >> c10;
			cout << endl;
			break;
		}
		case 10: {
			system("cls");
			cin >> d5;
			cout << endl;
			break;
		}


		default: {
			system("cls");
			cout << "Optiune nepermisa" << endl << endl;
			break;
		}

		}
		cout << endl << endl;
	}

	return 0;

}
