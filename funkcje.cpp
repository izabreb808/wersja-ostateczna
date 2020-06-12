#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "funkcje.h"

using namespace std;

string wczytajposilek() {
	string posilek;
	cout << "Podaj nazwe posilku/produktu: " << endl;
	getline(cin, posilek);
	return posilek;
}

double iloscpobierz(double il) {
	ifstream f;
	f.open("Ile.txt");
	f >> il;
	f.close();
	return il;
}

void ilosczamien(double il) {
	ofstream f;
	f.open("Ile.txt");
	f << il;
	f.close();
}

void podsumujkalorie(double il) {
	il = iloscpobierz(il);
	ofstream plik;
	plik.open("Dziennik.txt", ios::app);
	if (il > 0) {
		plik << endl << "Ilosc kalorii spozytych tego dnia wynosi " << il << endl << endl;
		plik << "********** ";
		SYSTEMTIME st;
		GetSystemTime(&st);
		plik << st.wDay;
		switch (st.wMonth)
		{
		case 1: plik << " styczen "; break;
		case 2: plik << " luty "; break;
		case 3: plik << " marzec "; break;
		case 4: plik << " kwiecien "; break;
		case 5: plik << " maj "; break;
		case 6: plik << " czerwiec "; break;
		case 7: plik << " lipiec "; break;
		case 8: plik << " sierpien "; break;
		case 9: plik << " wrzesien "; break;
		case 10: plik << " pazdziernik "; break;
		case 11: plik << " listopad "; break;
		case 12: plik << " grudzien "; break;
		}
		plik << st.wYear << " **********" << endl << endl;


	}
	ilosczamien(0);

	//plik << DZISIEJSZA DATA

	plik.close();
}

void czynowydzien(double il) {
	string k;
	cout << "Czy to twoj pierwszy posilek dzisiaj? Tak-T, Nie-N  " << endl;
	HANDLE kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "Po zaznaczeniu opcji tak w dzienniku pojawi sie podsumowanie kalorii spozytych poprzedniego dnia ";
	cout << "oraz dzisiejsza data pod ktora beda wpisywane kolejne posilki. " << endl;

	cin >> k;
	while (cin.fail() || (k != "t" && k != "T" && k != "n" && k != "N"))
	{
		cout << "Wprowadzono niepoprawna wartosc!" << endl;
		cout << "\nPodaj poprawna wartosc: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> k;
	}
	/*if (k != 'T' && k != 'N' && k != 't' && k != 'n') {
		do {
			cout << "Nie ma takiej opcji. Wpisz T jesli to twoj pierwszy dzisiejszy posilek. W  przeciwnym wypadku wpisz N. " << endl;
			cin >> k;

		} while (k != 'T' && k != 'N' && k != 't' && k != 'n');

	}

	switch (k)
	{
	case 'T': case 't':
		podsumujkalorie(il);
		break;
	case 'N': case 'n':
		break;
	}*/

	if (k == "t" || k == "T")
	{
		podsumujkalorie(il);

	}
	if (k == "n" || k == "N")
	{
		return;
	}

}

double wczytajkalorie(double il) {
	double kcal{}, waga{};

	czynowydzien(il);

	cout << endl << "Podaj ilosc kalorii w 100g produktu : " << endl;
	HANDLE kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "(Jesli nie wiesz ile wynosi jego kalorycznosc, ";
	cout << "mozesz znalezc informacje na przyklad na stronie: http://www.ilewazy.pl)" << endl;

	cin >> kcal;
	while (cin.fail() || kcal <= 0)
	{
		cout << "Wprowadzono niepoprawna wartosc!" << endl;
		cout << "\nPodaj poprawna wartosc: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> kcal;
	}
	/*ile (kcal <= 0)
	{
		cout << "Podana wartosc jest nieprawidlowa, wpisz ja jeszcze raz!" << endl;
		cout << "Podaj ilość kalorii w 100g produktu : ";
		cin >> kcal;
	}*/
	cout << endl << "Podaj wage posilku (wyrazona w gramach): " << endl;
	cin >> waga;

	while (cin.fail() || waga <= 0)
	{
		cout << "Wprowadzono niepoprawna wartosc!" << endl;
		cout << "\nPodaj poprawna wartosc: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> waga;
	}

	kcal = (kcal * waga) / 100;
	cout << endl << "Ilosc kalorii w podanej porcji: " << kcal << endl;
	HANDLE kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "Posilek dopisano do dziennika. Mozesz sprawdzic efekt w pliku 'Dziennik.txt'" << endl;
	il = iloscpobierz(il) + kcal;
	ilosczamien(il);
	return kcal;
}

void wpiszdopliku(string posilek, double kcal) {
	ofstream plik;
	plik.open("Dziennik.txt", ios::app);
	plik << posilek << " " << kcal << endl;
	plik.close();
}

void dziennik() {
	string temp;
	ifstream plik;
	plik.open("Dziennik.txt");
	if (plik)
	{
		while (getline(plik, temp))
		{
			cout << temp << endl;
		}
		plik.close();
	}	else {
		cout << "plik nie otwiera się" << endl;
	}
	plik.close();

}
