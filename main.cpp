
#include<bits/stdc++.h>
using namespace std;


string XOR(string a, string b)                                      //stowrzenie funkcji odpowiedzialnej za wykonanie operacji XOR
                                                                    //pobierającej 2 argumenty typu string
{
	string wynikowy = "";                                             //deklaracja pustej zmeinnej string do ktorej zapisywany bedzie
	int n = b.length();                                             //wynik opreacji XOR
	for(int i = 1; i < n; i++)                                      //inicjalizajca petli for() która realizuje operacja logiczna XOR
	{
		if (a[i] == b[i])                                           //porównanie wartości na i-tym indeksie stringów (jeśli są równe
			wynikowy += "0";                                        // dopisuje do stringa wynikowego na i-tym indeksie wartość 0
		else                                                        //jesli sa rozne zapisuje do stringa wynikowego na i-tym indeksie 1
            wynikowy += "1";
	}
	return wynikowy;                                                //zwraca stringa wynikowego z zapisany wynikiem operacji xor
}

string modulo(string dzielony, string dzielnik)                      //funkcja wykonujaca dzielenie danych przez wielomian
{

	int l_dzielnika = dzielnik.length();                            //pobranie dlugosci dzielnika
	string tmp = dzielony.substr(0, l_dzielnika);               //stworzenie zmiennej typu string i przypisanie jej wszystkich
	                                                                // elementow z danych  od 0 do dlugości dzielnika
	int n = dzielony.length();                                      //pobranie dlugosci  danych ktore dzielimy
	while (l_dzielnika < n)                                         //implementacja petli while w ktorej wykonamy opreacje XOR
	{                                                               //jesli dlogosc dzielnika bedzie mniejsza od dlugosci danych dzielonych
		if (tmp[0] == '1') {                                        //sprawdzenie czy 1 element jest rowny '1' jesli tak przypisanie do
                                                                    //tmp stringa wynikowego z funkcji XOR i dodaje kolejna element z dzielonego
                                                                    //ciagu do tmp
            tmp = XOR(dzielnik, tmp) + dzielony[l_dzielnika];                                                   //^
        }                                                                                                       //|
		else                                                                                                    //|
            tmp = XOR(string(l_dzielnika, '0'), tmp) + dzielony[l_dzielnika];  //jesli tmp zaczyna sie od 0 |


        l_dzielnika += 1;                                           //inkrementacja warunku petli
	}
	if (tmp[0] == '1')
		tmp = XOR(dzielnik, tmp);                                   //ostatnie wykonanie powyzszej petli jesli dlugosc dzielnika == dlugosci danych dzielonych
	else
		tmp = XOR(string(l_dzielnika, '0'), tmp);
	return tmp;                                                     //zwrocenie CRC
}
void Zakodowane(string data, string key,fstream &wynik)                            //funkcja wyswietlajaca wyniki,zapisujaca do pliku i inicjujaca kodowanie
{
	int l_key = key.length();                                       //dlugosc wielomianu generujacego

	string dana_z_zerami = (data + string(l_key - 1, '0'));    //dodanie k-1 '0' do danych do zakodowania gdzie k-dlugosc wielomianu generujacego
	cout << "dopisanie '0' do ciagu kodowanego:\t"<< dana_z_zerami << endl;
    cout<<"------------------------------"<<endl;
	string CRC = modulo(dana_z_zerami, key);                            //wywolanie funkcji liczacej CRC
	string dane_i_CRC = data + CRC;                                  //polaczenie  danych z CRC
	cout << "CRC :\t " << CRC << "\n";                               //wyswietlenie wynikow
	cout<<"------------------------------"<<endl;
	cout << "Dane + CRC :\t" << dane_i_CRC << "\n";                 //wyswietlenie wynikow
    cout<<"------------------------------"<<endl;
	cout << "sprawdzenie:\t" << modulo(dane_i_CRC, key) << endl;    //sprawdzenie czy nie wystapilo przeklamanie bitow
    cout<<"------------------------------"<<endl;
   //--------------ZAPIS WYNIKOW DO PLIKU------------------//
    wynik<<"Wyniki kodowania:"<<endl;
    wynik<<"Wyznaczone CRC dla podanego ciagu:"<<CRC<<endl;
    wynik<<"Dany ciag + CRC:"<<dane_i_CRC<<endl;
    wynik<<"Sprawdznie czy nie nastapilo przeklamanie:"<< modulo(dane_i_CRC, key)<<endl;
}

int main()
{
    fstream wielomian,dane,wynik;                             //implementacja zmiennych plikowych
    wielomian.open("wielomian_generujacy.txt",ios::in);              //otwarcie pliku z uprawnieniami do odczytu
    if (wielomian.good() == true)
        cout<<"plik wielomian_generujacy.txt otwarty"<<endl;
    else
        cout<<"error [1]"<<endl;
    dane.open("dane.txt",ios::in);                         //otwarcie pliku z uprawnieniami do odczytu
    if (dane.good() == true)
        cout<<"plik dane.txt otwarty"<<endl;
    else
        cout<<"error [2]"<<endl;
    wynik.open("wynik.txt",ios::out);                       //otwarcie pliku z uprawnieniami do zapisu
    if (dane.good() == true)
        cout<<"plik wynik.txt otwarty"<<endl;
    else
        cout<<"error [3]"<<endl;
    string wielomia_n;                                            //stworzenie zmiennej do ktorej przypiszemy nasz wielomian
    getline(wielomian, wielomia_n);                        //przypisanie wielomianu generujacego  z pliku do zmiennej
    string data,data1;
    while (!dane.eof()) {                                         //zapis danych do zakodowania z pliku
        getline(dane, data1);
        data+=data1;
    }//pobranie danych do zakodowania z pliku
    cout<<"------------------------------"<<endl;
    cout << "wielomian :\t" << wielomia_n << endl;                //wyswietlenie pobranego wielomianu generujacego
    cout<<"------------------------------"<<endl;
    cout<<"dane do zakodowania :\t"<<data<<endl;                  //wyswietlenie danych do zakodowania
    cout<<"------------------------------"<<endl;
    Zakodowane(data, wielomia_n,wynik);                               //wywoalnie funkcji inicjujacej kodowanie

    wielomian.close();                                          //zamkniecie plikow
    dane.close();                                               //zamkniecie plikow
	wynik.close();                                              //zamkniecie plikow
    return 0;
}

