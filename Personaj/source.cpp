#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
enum TipPersonaj { PROTAGONIST, ANTAGONIST, NPC, COMPANION };

class Rucsac {
private:
	float greutateRucsac;
public:
	Rucsac(float greutateRucsac) {
		this->greutateRucsac = greutateRucsac;
	}

	friend ostream& operator<<(ostream& out, const Rucsac& r) {
		out << "Greutate rucsac: "  << r.greutateRucsac << endl;
		return out;
	}
};

class Personaj {
private:
	string nume;
	TipPersonaj tipPersonaj;
	int nrBagaje;
	float* greutatiBagaje;
	Rucsac rucsac;

public:

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
		return *this;
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
		out << (Rucsac&)p;
		return out;
	}

	TipPersonaj getTipPersonaj() {
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
};

void main() {
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

	link.codRosu();
	cout << link << endl;
	cout << "==================" << endl;

	zelda.codRosu();
	cout << zelda << endl;
	cout << "==================" << endl;
}