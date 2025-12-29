#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <list>
using namespace std;
enum TipPersonaj { PROTAGONIST, ANTAGONIST, NPC, COMPANION };

//template - clasa care poate sa manipuleze orice tip de data
template <typename T>
class Colectie {
private:
	T v[20];
public:
	Colectie() {
		for (int i = 0; i < 20; i++) {
			v[i] = T();
		}
	}

	void set(int index, const T& valoare) {
		if (index >= 0 && index < 20) {
			v[index] = valoare;
		}
	}

	T maxim() {
		T max = v[0];
		for (int i = 1; i < 20; i++) {
			if (v[i] > max) {
				max = v[i];
			}
		}
		return max;
	}
};

class Om {
public:
	void saluta() {
		cout << "Salut! " << endl;
	}

	virtual void prezinta() = 0;
};

//metode abstracte - se afla intr-o clasa abstracta
//metode virtual pure - se pune =0, metode care nu au implementare, pot avea implementari diferite in clasele mostenite prin IS A

class Rucsac {
private:
	float greutateRucsac;
public:
	Rucsac(float greutateRucsac) {
		this->greutateRucsac = greutateRucsac;
	}

	Rucsac() {
		greutateRucsac = 0;
	}

	friend ostream& operator<<(ostream& out, const Rucsac& r) {
		out << "Greutate rucsac: " << r.greutateRucsac << endl;
		return out;
	}

	float getGreutateRucsac() const {
		return greutateRucsac;
	}
};

class Personaj :public Om {
private:
	string nume;
	TipPersonaj tipPersonaj;
	int nrBagaje;
	float* greutatiBagaje;
	Rucsac rucsac;

public:
	Personaj() :rucsac(0) {
		nume = "Necunoscut";
		tipPersonaj = PROTAGONIST;
		nrBagaje = 0;
		greutatiBagaje = nullptr;
	}

	Personaj(string nume, TipPersonaj tipPersonaj, int nrBagaje, float* greutatiBagaje, float greutateRucsac) :rucsac(greutateRucsac) {
		this->nume = nume;
		this->tipPersonaj = tipPersonaj;
		this->nrBagaje = nrBagaje;
		if (greutatiBagaje != nullptr) {
			this->greutatiBagaje = new float[nrBagaje];
			for (int i = 0; i < nrBagaje; i++) {
				this->greutatiBagaje[i] = greutatiBagaje[i];
			}
		}
		else {
			this->greutatiBagaje = nullptr;
		}
	}

	Personaj(const Personaj& p) :rucsac(p.rucsac) {
		this->nume = p.nume;
		this->tipPersonaj = p.tipPersonaj;
		this->nrBagaje = p.nrBagaje;
		if (p.greutatiBagaje != nullptr) {
			this->greutatiBagaje = new float[p.nrBagaje];
			for (int i = 0; i < p.nrBagaje; i++) {
				this->greutatiBagaje[i] = p.greutatiBagaje[i];
			}
		}
		else {
			this->greutatiBagaje = nullptr;
		}
	}

	~Personaj() {
		if (this->greutatiBagaje != nullptr) {
			delete[] this->greutatiBagaje;
		}
	}

	Personaj& operator=(const Personaj& p) {
		if (this != &p) {
			this->nume = p.nume;
			this->tipPersonaj = p.tipPersonaj;
			this->nrBagaje = p.nrBagaje;
			this->rucsac = p.rucsac;
			if (this->greutatiBagaje != nullptr) {
				delete[] this->greutatiBagaje;
			}
			if (p.greutatiBagaje != nullptr) {
				this->greutatiBagaje = new float[p.nrBagaje];
				for (int i = 0; i < p.nrBagaje; i++) {
					this->greutatiBagaje[i] = p.greutatiBagaje[i];
				}
			}
			else {
				this->greutatiBagaje = nullptr;
			}
		}

		return *this;
	}


	double sumaGreutati() const {
		double suma = 0;
		for (int i = 0; i < nrBagaje; i++) {
			suma += greutatiBagaje[i];
		}
		return suma;
	}

	bool operator>(double valoare) const {
		return sumaGreutati() > valoare;
	}

	bool operator>(const Personaj& p) const {
		return this->sumaGreutati() > p.sumaGreutati();
	}

	friend bool operator>(double valoare, const Personaj& p) {
		return valoare > p.sumaGreutati();
	}

	friend ostream& operator<<(ostream& out, const Personaj& p) {
		out << "Nume personaj: " << p.nume << endl;
		out << "Tip personaj: ";
		switch (p.tipPersonaj) {
		case PROTAGONIST:
			out << "Protagonist" << endl;
			break;
		case ANTAGONIST:
			out << "Antagonist" << endl;
			break;
		case NPC:
			out << "NPC" << endl;
			break;
		case COMPANION:
			out << "Companion" << endl;
			break;
		}
		out << "Numar de bagaje: " << p.nrBagaje << endl;
		if (p.greutatiBagaje != nullptr) {
			out << "Greutati bagaje: ";
			for (int i = 0; i < p.nrBagaje; i++) {
				out << p.greutatiBagaje[i] << "  ";
			}
			out << endl;
		}
		out << "Greutate rucsac: " << p.rucsac.getGreutateRucsac() << endl;
		return out;
	}

	TipPersonaj getTipPersonaj() const {
		return this->tipPersonaj;
	}

	void codRosu() {
		if (greutatiBagaje != nullptr) {
			float celMaiGreu = greutatiBagaje[0];
			for (int i = 0; i < nrBagaje; i++) {
				if (greutatiBagaje[i] > celMaiGreu) {
					celMaiGreu = greutatiBagaje[i];
				}
			}

			delete[] greutatiBagaje;

			nrBagaje = 1;
			greutatiBagaje = new float[1];
			greutatiBagaje[0] = celMaiGreu;
		}
		else {
			cout << "Personajul nu are bagaje" << endl;
		}
	}

	void prezinta() override {
		cout << "Eu sunt aventurierul " << nume << endl;
	}
};

int main() {
	float greutatiBagajeLink[] = { 10.2f, 4.7f };
	Personaj link("Link", PROTAGONIST, 2, greutatiBagajeLink, 6.8f);
	cout << link << endl;
	cout << "==================" << endl;

	Personaj zelda("Zelda", NPC, 0, nullptr, 0.0f);
	cout << zelda << endl;
	cout << "==================" << endl;

	Personaj link2(link);
	cout << link2 << endl;
	cout << "==================" << endl;

	float greutatiBagajeGanon[] = { 10.2f, 4.7f, 7.5f, 14.8f };

	/*link.codRosu();
	cout << link << endl;
	cout << "==================" << endl;*/

	/*zelda.codRosu();
	cout << zelda << endl;
	cout << "==================" << endl;*/

	cout << link.sumaGreutati() << endl;
	if (link > 14) {
		cout << "Suma greutatilor este mai mare decat 14" << endl;
	}
	else {
		cout << "Suma greutatilor este mai mica decat 14" << endl;
	}

	link.saluta();
	link.prezinta();

	Colectie <int> c1;
	c1.set(0, 10);
	c1.set(1, 5);
	c1.set(2, 7);

	cout << c1.maxim() << endl;

	Colectie <Personaj> c2;
	c2.set(0, link);
	c2.set(1, zelda);
	c2.set(2, Personaj("Ganon", ANTAGONIST, 4, greutatiBagajeGanon, 12.0f));

	cout << "================" << endl;
	cout << c2.maxim() << endl;

	list <Personaj*> listaPersonaje;
	listaPersonaje.push_back(&link);
	listaPersonaje.push_back(&zelda);
	double greutateTotala = 0;

	// enhanced for
	for (Personaj* personaj : listaPersonaje) {
		greutateTotala += personaj->sumaGreutati();
	}
	cout << greutateTotala << endl;

	return 0;
}