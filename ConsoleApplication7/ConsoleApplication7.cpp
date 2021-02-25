#include <iostream>
#include <math.h>
#include <string>

using namespace std;


template <class typ>
class Node {
public:
	typ dane;
	Node* nastepny;
	Node(typ dane) {
		this->dane = dane;
		this->nastepny = NULL;
	}
};

template <class typ>
class Lista {
public:
	Node <typ>* head;
	Node <typ>* tail;
	void push(typ dane) {
		Node<typ>* nowy = new Node<typ>(dane);
		if (tail)
			this->tail->nastepny = nowy;
		else 
			this->head = nowy;
		this->tail = nowy;
	}
	void pop() {
		Node<typ>* tmp = this->head;
		this->head = this->head->nastepny;
		if (!head) tail = NULL;
		delete tmp;
	}
	Lista() {
		head = NULL;
		tail = NULL;
	}
	bool empty() {
		return !head;
	}
	typ* zwroc_dany_element(int n) {
		Node<typ>* obecny = this->head;
		for (int i = 0; i < n; i++) {
			if(obecny!=NULL)
				obecny = obecny->nastepny;
		}
		return &obecny->dane;
	}
	void clear() {
		while (this->head!=NULL) {
			this->pop();
		}
	}
	int ilosc_elementow() {
		int a = 0;
		Node<typ>* obecny = this->head;
		while (obecny != NULL) {
			a++;
			obecny = obecny->nastepny;
		}
		return a;
	}
};


class Ujscie {
public:
	int wartosc = 0;
};

class GrupaZadan {
public:
	Ujscie* ujscie;
	string nazwa;
	int ilosc_osoboH;
	int ilosc_zadan;
	int extraH = 0;
};

class Zadanie;

class Czas{
public:
	//lista zadan o danej godzinie
	int id;
	Zadanie* zadanie;
	Czas() {}
};

class Dzien {
public:
	//lista godzin w ktorych cos sie dzieje
	int id;
	Lista<Czas> lista_godzin;
};

class Zadanie{
public:
	Dzien dzien;
	Czas* czas;
	int min;
	int max;
	GrupaZadan* grupa;
	Ujscie* ujscie;
	Zadanie() {}
};

class Pracownik {
public:
	string imie;
	int wartosc;
	int godziny_ogolem;
	int godziny_dziennie;
	//lista wszystkich dni
	Lista<Dzien> lista_dni;
	Lista<Zadanie> lista_zadan;
	Pracownik() {}
};

class Katedra {
public:
	string nazwa;
	int ilosc_pracownikow;
	//lista pracownikow
	Lista<Pracownik> lista_pracownikow;
	//Katedra(){}
};

class Zrodlo{
	int wartosc = 0;
	Lista<Pracownik> lista_aktywnych_pracownikow;
};


struct Wynik {
	int wartosciowosc;
	int* tablica_kombinacji;
	Lista<Pracownik> lista_pracownikow;
};

struct do_sortowania {
	int wartosciowosc;
	int* kombinacja;
	bool zgodnosc;
};

int my_compare(const void* a, const void* b) {
	do_sortowania _a = *(do_sortowania*)a;
	do_sortowania _b = *(do_sortowania*)b;
	if (_a.wartosciowosc < _b.wartosciowosc)
		return -1;
	else return 1;
}

bool czy_jest(Lista<Dzien> lista_dni, int szukane) {
	Node<Dzien>* obecny = lista_dni.head;
	while (obecny != NULL) {
		if (obecny->dane.id == szukane)
			return true;
		else
			obecny = obecny->nastepny;
	}
	return false;
}

bool czy_jest(Lista<Czas> lista_godzin, int szukana) {
	Node<Czas>* obecny = lista_godzin.head;
	while (obecny != NULL) {
		if (obecny->dane.id == szukana)
			return true;
		obecny = obecny->nastepny;
	}
	return false;
}

Dzien* zwroc_po_id(Lista<Dzien> lista_dni, int szukane) {
	Node<Dzien>* obecny = lista_dni.head;
	while (obecny != NULL) {
		if (obecny->dane.id == szukane)
			return &obecny->dane;
		else
			obecny = obecny->nastepny;
	}
	return NULL;
}

Czas* zwroc_po_id(Lista<Czas> lista_godzin, int szukane) {
	Node<Czas>* obecny = lista_godzin.head;
	while (obecny != NULL) {
		if (obecny->dane.id == szukane)
			return &obecny->dane;
		else
			obecny = obecny->nastepny;
	}
	return NULL;
}

void przypisz_liste_dni(Lista<Dzien> lista_dni, Lista<Pracownik> lista_pracownikow) {
	Node<Pracownik>* obecny= lista_pracownikow.head;
	while (obecny != NULL) {
		obecny->dane.lista_dni = lista_dni;
		obecny = obecny->nastepny;
	}
}

void przypisz_liste_godzin(Lista<Czas> lista_godzin, Lista<Dzien> lista_dni) {
	Node<Dzien>* obecny = lista_dni.head;
	while (obecny != NULL) {
		obecny->dane.lista_godzin = lista_godzin;
		obecny = obecny->nastepny;
	}
}


int* zmien_liczba(int liczba, int podstawa, int ilosc_bitow) {
	int* wynik = new int[ilosc_bitow];
	for (int j = 0; j < ilosc_bitow; j++) wynik[j] = 0;
	int i = ilosc_bitow-1;
	while (liczba > 0) {
		wynik[i] = liczba % podstawa;
		liczba /= podstawa;
		i--;
	}
	return wynik;
}

void dodaj_pierwszych_na_liste(Lista<Pracownik>& lista, Lista<Pracownik> katedra, int ilu) {
	Node<Pracownik>* obecny = katedra.head;
	for (int i = 0; i < ilu; i++) {
		lista.push(obecny->dane);
		obecny = obecny->nastepny;
	}
}

int suma_wartosci(Lista<Pracownik> lista_pracownikow) {
	int wartosc = 0;
	Node<Pracownik>* obecny = lista_pracownikow.head;
	while (obecny != NULL) {
		wartosc += obecny->dane.wartosc;
		obecny = obecny->nastepny;
	}
	return wartosc;
}


int main(){
	int tryb_szeregowania = 0;
	cin >> tryb_szeregowania;
	int opcje_wyjscia;
	cin >> opcje_wyjscia;
	int ilosc_katedr;
	int max_pracownikow = 0;
	cin >> ilosc_katedr;
	Katedra* katedry = new Katedra[ilosc_katedr];
	for (int i = 0; i < ilosc_katedr; i++) {
		cin >> katedry[i].nazwa;
		cin >> katedry[i].ilosc_pracownikow;
		if (katedry[i].ilosc_pracownikow > max_pracownikow) max_pracownikow = katedry[i].ilosc_pracownikow;
		for (int j = 0; j < katedry[i].ilosc_pracownikow; j++) {
			Pracownik* pracownik = new Pracownik;
			cin >> pracownik->imie;
			cin >> pracownik->wartosc;
			cin >> pracownik->godziny_ogolem;
			cin >> pracownik->godziny_dziennie;
			katedry[i].lista_pracownikow.push(*pracownik);
		}
	}
	int ilosc_grup;
	cin >> ilosc_grup;
	Ujscie ujscie;
	GrupaZadan* grupy = new GrupaZadan[ilosc_grup];
	Lista<Dzien> lista_dni;
	Lista<Czas> lista_godzin;
	Lista<Zadanie> lista_zadan;
	int ilosc_dni=0;
	int ile_godzin = 0;
	for (int i = 0; i < ilosc_grup; i++) {
		cin >> grupy[i].nazwa;
		cin >> grupy[i].ilosc_zadan;
		cin >> grupy[i].ilosc_osoboH;
		int godz = 0;
		for (int j = 0; j < grupy[i].ilosc_zadan; j++) {
			Zadanie* zadanie = new Zadanie;
			Czas* czas_zadania = new Czas;
			cin >> zadanie->dzien.id;
			if (!czy_jest(lista_dni, zadanie->dzien.id)) {
				lista_dni.push(zadanie->dzien);
				ilosc_dni++;
			}
			cin >> czas_zadania->id;
			if (!czy_jest(lista_godzin, czas_zadania->id)) {
				lista_godzin.push(*czas_zadania);
				ile_godzin++;
				zadanie->czas = czas_zadania;
				czas_zadania->zadanie = zadanie;
			}
			else {
				zadanie->czas = zwroc_po_id(lista_godzin, czas_zadania->id);
				zwroc_po_id(lista_godzin, czas_zadania->id)->zadanie = zadanie;
			}
			cin>>zadanie->min;
			cin>>zadanie->max;
			godz += zadanie->min;
			zadanie->grupa = &grupy[i];
			zadanie->ujscie = &ujscie;
			lista_zadan.push(*zadanie);
		}
		grupy[i].ujscie = &ujscie;
		grupy[i].extraH = grupy[i].ilosc_osoboH - godz;
	}
	przypisz_liste_godzin(lista_godzin, lista_dni);
	int ilosc_zadan = 0;
	//cout << pow(max_pracownikow + 1, ilosc_katedr);
	for (int r = 0; r < ilosc_grup; r++) ilosc_zadan += grupy[r].ilosc_zadan;
	bool czy_znaleziono=false;

	do_sortowania* sortowanie = new do_sortowania[(int)pow(max_pracownikow + 1, ilosc_katedr)-1];

	for (int i = 1; i < pow(max_pracownikow + 1, ilosc_katedr); i++) {
		int* kombinacja = zmien_liczba(i, max_pracownikow + 1, ilosc_katedr);
		sortowanie[i-1].kombinacja = kombinacja;
		bool czy_zgodne = true;
		Lista<Pracownik> pracownicy;
		bool cz_zgodne = true;
		for (int j = 0; j < ilosc_katedr; j++) {
			if (kombinacja[j] > katedry[j].ilosc_pracownikow) {
				czy_zgodne = false;
				break;
			}
		}
		sortowanie[i-1].zgodnosc = czy_zgodne;
		if (czy_zgodne) {
			for (int j = 0; j < ilosc_katedr; j++)
				dodaj_pierwszych_na_liste(pracownicy, katedry[j].lista_pracownikow, kombinacja[j]);
			sortowanie[i - 1].wartosciowosc = suma_wartosci(pracownicy);
		}
	}
	qsort(sortowanie, (int)pow(max_pracownikow + 1, ilosc_katedr)-1, sizeof(do_sortowania), my_compare);


	for (int i = 1; i < pow(max_pracownikow+1, ilosc_katedr); i++) {
		if (!sortowanie[i - 1].zgodnosc)
			continue;
		int* kombinacja = sortowanie[i - 1].kombinacja;
		int ilosc_wybranych_pracownikow = 0;
		for (int j = 0; j < ilosc_katedr; j++) {
			ilosc_wybranych_pracownikow += kombinacja[j];
		}
		int ilosc_wezlow = 1 + ilosc_wybranych_pracownikow + ilosc_wybranych_pracownikow * ilosc_dni+ile_godzin*ilosc_dni*ilosc_wybranych_pracownikow+ilosc_zadan+ilosc_grup+1;
		//int ilosc_krawedzi = ilosc_wybranych_pracownikow + ilosc_wybranych_pracownikow * ilosc_dni + ile_godzin * ilosc_dni * ilosc_wybranych_pracownikow + ile_godzin * ilosc_dni * ilosc_wybranych_pracownikow + ilosc_zadan + ilosc_zadan + ilosc_grup;
		Lista<Pracownik> lista_aktywnych_pracownikow;
		for (int j = 0; j < ilosc_katedr; j++)
			dodaj_pierwszych_na_liste(lista_aktywnych_pracownikow, katedry[j].lista_pracownikow, kombinacja[j]);


		//FORD-FULKERSON
		int** macierz_przepustowosci = new int* [ilosc_wezlow];
		int** macierz_przeplywow_netto = new int* [ilosc_wezlow];
		for (int k = 0; k < ilosc_wezlow; k++) {
			macierz_przepustowosci[k] = new int[ilosc_wezlow];
			macierz_przeplywow_netto[k] = new int[ilosc_wezlow];
		}
		int* tablica_poprzednikow = new int[ilosc_wezlow];
		int* tablica_przepustowosci_rezydualnych = new int [ilosc_wezlow];
		for (int k = 0; k < ilosc_wezlow; k++)
			for (int l = 0; l < ilosc_wezlow; l++)
				macierz_przepustowosci[k][l] = macierz_przeplywow_netto[k][l] = 0;





		Node<Pracownik>* obecny_pracownik = lista_aktywnych_pracownikow.head;
		for (int k = 0; k < ilosc_wybranych_pracownikow; k++) {
			macierz_przepustowosci[0][k + 1] = obecny_pracownik->dane.godziny_ogolem;
			obecny_pracownik = obecny_pracownik->nastepny;
		}
		obecny_pracownik = lista_aktywnych_pracownikow.head;
		for (int k = 0; k < ilosc_wybranych_pracownikow; k++) {
			for (int l = 0; l <  ilosc_dni; l++) {
				macierz_przepustowosci[k+1][k*ilosc_dni+l+ilosc_wybranych_pracownikow+1] = obecny_pracownik->dane.godziny_dziennie;
			}
			obecny_pracownik = obecny_pracownik->nastepny;
		}

		Node<Dzien>* obecny_dzien = lista_dni.head;
		for (int k = 0; k < ilosc_dni * ilosc_wybranych_pracownikow; k++) {
			for (int l = 0; l < ile_godzin; l++) {
				macierz_przepustowosci[k+1+ilosc_wybranych_pracownikow][l + k * ile_godzin+1+ilosc_wybranych_pracownikow+ilosc_dni*ilosc_wybranych_pracownikow]=1;
			}
		}


		Node<Zadanie>* obecne_zadanie = lista_zadan.head;
		Node<Czas>* obecny_czas = lista_godzin.head;
		int ktore = 0;
		for (int a = 0; a < ilosc_wybranych_pracownikow; a++) {
			obecny_dzien = lista_dni.head;
			for (int b = 0; b < ilosc_dni; b++) {
				obecny_czas = lista_godzin.head;
				for (int c = 0; c < ile_godzin; c++) {
					obecne_zadanie = lista_zadan.head;
					for (int d = 0; d < ilosc_zadan; d++) {
						if (obecne_zadanie->dane.dzien.id == obecny_dzien->dane.id && obecne_zadanie->dane.czas->id == obecny_czas->dane.id)
							macierz_przepustowosci[ktore+1+ilosc_wybranych_pracownikow+ilosc_wybranych_pracownikow*ilosc_dni][d+1+ilosc_wybranych_pracownikow+ilosc_wybranych_pracownikow*ilosc_dni+ilosc_wybranych_pracownikow*ilosc_dni*ile_godzin] = 1;
						obecne_zadanie = obecne_zadanie->nastepny;
					}
					ktore++;
					obecny_czas = obecny_czas->nastepny;
				}
				obecny_dzien = obecny_dzien->nastepny;
			}
		}
		
		obecne_zadanie = lista_zadan.head;
		for (int k = 0; k < ilosc_zadan; k++) {
			macierz_przepustowosci[k + 1 + ilosc_wybranych_pracownikow + ilosc_dni*ilosc_wybranych_pracownikow + ile_godzin*ilosc_wybranych_pracownikow*ilosc_dni][ilosc_wezlow-1] = obecne_zadanie->dane.min;
			for (int l = 0; l < ilosc_grup; l++) {
				if (&grupy[l] == obecne_zadanie->dane.grupa) {
					macierz_przepustowosci[k + 1 + ilosc_wybranych_pracownikow + ilosc_dni * ilosc_wybranych_pracownikow + ile_godzin * ilosc_wybranych_pracownikow*ilosc_dni][l + 1 + ilosc_wybranych_pracownikow + ilosc_dni*ilosc_wybranych_pracownikow + ile_godzin*ilosc_wybranych_pracownikow*ilosc_dni+ilosc_zadan] = obecne_zadanie->dane.max - obecne_zadanie->dane.min;
					break;
				}
			}
			obecne_zadanie = obecne_zadanie->nastepny;
			if (obecne_zadanie == NULL) obecne_zadanie = lista_zadan.head;
		}
		for (int k = 0; k < ilosc_grup; k++) {
			macierz_przepustowosci[k + 1 + ilosc_wybranych_pracownikow + ilosc_dni * ilosc_wybranych_pracownikow + ile_godzin * ilosc_dni * ilosc_wybranych_pracownikow + ilosc_zadan][ilosc_wezlow - 1] = grupy[k].extraH;
		}		

		int n, m, s, t, fmax, cp, x, y, a, b;

		//EDMOND=KARP?
		fmax = 0;
		while (true) {
			for (a = 0; a < ilosc_wezlow; a++) {
				tablica_poprzednikow[a] = -1;
			}
			tablica_poprzednikow[0] = -2;
			tablica_przepustowosci_rezydualnych[0] = 999;
			Lista<int> lista_x;
			lista_x.push(0);
			bool esc = false;

			while (!lista_x.empty()) {
				x = lista_x.head->dane;
				lista_x.pop();
				for (int y = 0; y < ilosc_wezlow; y++) {
					cp = macierz_przepustowosci[x][y] - macierz_przeplywow_netto[x][y];
					if (cp && (tablica_poprzednikow[y] == -1)) {
						tablica_poprzednikow[y] = x;
						tablica_przepustowosci_rezydualnych[y] = tablica_przepustowosci_rezydualnych[x] > cp ? cp : tablica_przepustowosci_rezydualnych[x];
						if (y == ilosc_wezlow - 1) {
							Pracownik* wskazany_pracownik=NULL;
							Zadanie* wskazane_zadanie=NULL;
							fmax += tablica_przepustowosci_rezydualnych[y];
							b = y;
							while (b != 0) {
								x = tablica_poprzednikow[b];
								//cout << x << '\t';
								macierz_przeplywow_netto[x][b] += tablica_przepustowosci_rezydualnych[y];
								macierz_przeplywow_netto[b][x] -= tablica_przepustowosci_rezydualnych[y];
								b = x;
								if (x > 0 && x <= ilosc_wybranych_pracownikow) {
									wskazany_pracownik = lista_aktywnych_pracownikow.zwroc_dany_element(x - 1);
									if (wskazane_zadanie != NULL) {
										wskazany_pracownik->lista_zadan.push(*wskazane_zadanie);
									}
								}
								else if (x > ilosc_wybranych_pracownikow + ilosc_wybranych_pracownikow * ilosc_dni + ilosc_wybranych_pracownikow * ilosc_dni * ile_godzin && x <= ilosc_wybranych_pracownikow + ilosc_wybranych_pracownikow * ilosc_dni + ilosc_wybranych_pracownikow * ilosc_dni * ile_godzin + ilosc_zadan) {
									wskazane_zadanie = lista_zadan.zwroc_dany_element(x - (ilosc_wybranych_pracownikow + ilosc_wybranych_pracownikow * ilosc_dni + ilosc_wybranych_pracownikow * ilosc_dni * ile_godzin) - 1);
								}
								else
									continue;

							}
							esc = true;
							break;
						}
						lista_x.push(y);
					}
				}
				if (esc) break;
			}
			if (!esc) break;
		}
		int wymagany_przeplyw = 0;
		for (int n = 0; n < ilosc_wezlow; n++) {
			wymagany_przeplyw += macierz_przepustowosci[n][ilosc_wezlow - 1];
		}
		if (fmax == wymagany_przeplyw) {
			if (opcje_wyjscia == 1) {
				cout << suma_wartosci(lista_aktywnych_pracownikow)<<'\t';
				for (int j = 0; j < ilosc_katedr; j++) {
					if(kombinacja[j]>0)
						cout << katedry[j].nazwa << '\t' << kombinacja[j] << endl;
				}
			}
			else {
				cout << suma_wartosci(lista_aktywnych_pracownikow)<<'\t';
				for (int j = 0; j < ilosc_katedr; j++) {
					if(kombinacja[j]>0)
						cout << katedry[j].nazwa << '\t' << kombinacja[j] << endl;
					obecny_pracownik = lista_aktywnych_pracownikow.head;
					for (int n = 0; n < kombinacja[j]; n++) {
						cout << obecny_pracownik->dane.imie <<" "<<obecny_pracownik->dane.lista_zadan.ilosc_elementow()<< endl;
						obecne_zadanie = obecny_pracownik->dane.lista_zadan.head;
						while (obecne_zadanie != NULL) {
							cout <<obecne_zadanie->dane.grupa->nazwa<<'\t'<< obecne_zadanie->dane.dzien.id << '\t' << obecne_zadanie->dane.czas->id<<endl;
							obecne_zadanie = obecne_zadanie->nastepny;
						}
						obecny_pracownik = obecny_pracownik->nastepny;
						cout << endl;
					}
				}
			}
			czy_znaleziono = true;
			break;
		}
		else {
			obecny_pracownik = lista_aktywnych_pracownikow.head;
			while (obecny_pracownik != NULL) {
				obecny_pracownik->dane.lista_zadan.clear();
				obecny_pracownik = obecny_pracownik->nastepny;
			}
			continue;
		}
		delete[] kombinacja;
		for (int n = 0; n < ilosc_wezlow; n++) {
			delete[] macierz_przepustowosci[n];
			delete[] macierz_przeplywow_netto[n];
		}
		delete[] kombinacja;
		delete[] macierz_przeplywow_netto;
		delete[] macierz_przepustowosci;
		delete[] tablica_poprzednikow;
		delete[] tablica_przepustowosci_rezydualnych;

	}
	if (!czy_znaleziono) cout << "NO";

	delete[] katedry;
	delete[] sortowanie;

}
