#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct Data {  //dekralacja struktury 
	int dzien;
	int miesiac;
	int rok;
	Data(int dzien1, int miesiac1, int rok1) :dzien(dzien1), miesiac(miesiac1), rok(rok1) {};
};
struct utwor //dekralacja struktury 
{   string nazwa_utworu;
	utwor *nastepny;
	utwor(string nazwa) : nazwa_utworu(nazwa), nastepny(NULL) {};
};
struct album //dekralacja struktury 
{
	string nazwa;
	float cena;
	album * nastepny;
	utwor *wskaznik_utwory;
	Data data;
	album(string nazwa1, int cena1, int dzien1, int miesiac1, int rok1) :wskaznik_utwory(NULL),nastepny(NULL), nazwa(nazwa1), cena(cena1), data(Data(dzien1, miesiac1, rok1)) {};
};
struct wykonawca { //dekralacja struktury 
	string imie;
	string nazwisko;
	album * wydane_albumy;
	wykonawca * nastepny;
	wykonawca(string imie1, string nazwisko1) : imie(imie1),wydane_albumy(NULL),nastepny(NULL), nazwisko(nazwisko1) {};
};
void dodanie_albumu(album * &wskaznik, string nazwa,int cena,int dzien,int miesiac,int rok)  //dodanie albumu 
{
	if (wskaznik == NULL)    // dodanie dla przypadku gdy nie ma zadnego albumu 
	{	wskaznik = new album(nazwa,cena,dzien,miesiac,rok);
	    cout << "dodano album : " << nazwa << endl;
		return;
	}
	album* wskaznik1 = wskaznik;
	while (wskaznik1->nastepny != NULL) //dodanie do inncyh albumow 
	{
		wskaznik1 = wskaznik1->nastepny;
	}
	wskaznik1->nastepny = new album(nazwa, cena, dzien, miesiac, rok);
	cout << "dodano album : " << nazwa << endl;
}
void dodanie_utworu(utwor *& wskaznik, string nazwa)  //dodanie utworu 
{
	if (wskaznik == NULL) //opcja gdyby nie bylo autworow wczesniej 
	{
		wskaznik = new utwor(nazwa);
		cout << "dodano utwor : " << nazwa << endl;
		return;
	}
	utwor * wskaznik1 = wskaznik;
	while (wskaznik1->nastepny != NULL)  //opcja dodania utworu do istniejacych 
	{
		wskaznik1 = wskaznik1->nastepny;
	}
	wskaznik1->nastepny = new utwor(nazwa);
	cout << "dodano utwor : " << nazwa << endl;
} 
void nazwa_pliku(string &nazwa_pliku)  
{
	cout << "Podaj nazwe pliku " << endl;
	cin >> nazwa_pliku;
}
bool otwarcie_pliku(const string nazwa, ifstream &plik1)  
{
	plik1.open(nazwa);
	if (plik1.good() == true && plik1.is_open())
	{
		cout << "Udalo sie otworzyc plik" << endl;
		return true;
	}
	else
	{
		cout << "Otwieranie pliku sie nie powiodlo, podaj inna nazwe." << endl;
		return false;
	}
}
void dodaj_wykonawce(wykonawca * & lista, string imie, string nazwisko) {  
	if (lista == NULL) {     //opcja gdyby nie bylo wykonawcow 
		cout << "dodano wykonawce : "<< imie <<"  "<< nazwisko << endl;
		lista = new wykonawca(imie, nazwisko);
		return;
	}
	wykonawca* lista1 = lista;
	while (lista1->nastepny != NULL)   //dodanie wykonawcow do istniejacych 
	{
		lista1 = lista1->nastepny;
	}
		lista1->nastepny = new wykonawca(imie, nazwisko);
		cout << "dodano wykonawce : " << imie <<" "<< nazwisko << endl;
	}
void dodaj_album_do_wykonawcy(wykonawca *&wskaznik, string imie, string nazwisko, string nazwa1, int cena, int dzien, int miesiac, int rok)
{   
	if (wskaznik == NULL)     // jesli nie ma wykonawcy to nie ma komu przypisac albumu wiec wracamy 
	{
		return;
	}
	if (wskaznik->imie == imie && wskaznik->nazwisko == nazwisko)  //jesli odnajudjemy odpowiedniego wykonawce dodajemy do niego album
	{
		dodanie_albumu(wskaznik->wydane_albumy, nazwa1, cena, dzien, miesiac, rok); //wykorzystanie funkcji ktora umozliwi dodanie albumu 
		return;
	}
	wykonawca *wskaznik1 = wskaznik;
	while (wskaznik1->nastepny != NULL)   //szukanie posrod wykonawcow wlasciwego
	{
		if (wskaznik1->nastepny->imie == imie && wskaznik1->nastepny->nazwisko == nazwisko) {
			dodanie_albumu(wskaznik1->nastepny->wydane_albumy, nazwa1, cena, dzien, miesiac, rok);
			return;
		}
		else
			wskaznik1 = wskaznik1->nastepny; 
	}
}
void dodaj_utwor_do_albumu(string nazwa_utworu, wykonawca *wskaznik_wykonawca,string imie, string nazwisko, string nazwa1)
{   
	if (wskaznik_wykonawca == NULL)    
		//dodawanie do pierwszego wykonawcy 
		//jesli nie ma wykonawcy to i nie ma albumu wiec wracamy 
	{
		return;
	}
	if (wskaznik_wykonawca->imie == imie && wskaznik_wykonawca->nazwisko == nazwisko) 
	{ 
		if (wskaznik_wykonawca->wydane_albumy == NULL)  //jesli odnajdziemy wykonawce ale nie ma albumu to wracamy 
		{
			return;
		}
		if (wskaznik_wykonawca->wydane_albumy->nazwa == nazwa1) //dodanie albumu jesli pierwszy album jest zgodny
		{
			dodanie_utworu(wskaznik_wykonawca->wydane_albumy->wskaznik_utwory, nazwa_utworu); 
			return;
		}
		while (wskaznik_wykonawca->wydane_albumy->nastepny != NULL)  //szukanie albumu wykonawcy ktory podal uzytkownik 
		{
			if (wskaznik_wykonawca->wydane_albumy->nastepny->nazwa == nazwa1)
			{
				dodanie_utworu(wskaznik_wykonawca->wydane_albumy->nastepny->wskaznik_utwory, nazwa_utworu);
				return;
			}
			else
				wskaznik_wykonawca->wydane_albumy = wskaznik_wykonawca->wydane_albumy->nastepny;
		}
		return;
	}
	wykonawca *wskaznik1 = wskaznik_wykonawca;
	while (wskaznik1->nastepny != NULL)  //szukanie odpowiedniego wykonawcy w pozostalych mozliwosciach i albumu wykonawcy   
	{
		if (wskaznik1->nastepny->imie == imie && wskaznik1->nastepny->nazwisko == nazwisko) {
			if (wskaznik1->wydane_albumy == NULL)
			{
				return;
			}
			if (wskaznik1->nastepny->wydane_albumy->nazwa == nazwa1)
			{
				dodanie_utworu(wskaznik1->nastepny->wydane_albumy->wskaznik_utwory, nazwa_utworu);
				return;
			}
			while (wskaznik1->nastepny->wydane_albumy->nastepny != NULL)
			{
				if (wskaznik1->nastepny->wydane_albumy->nastepny->nazwa == nazwa1)
				{
					dodanie_utworu(wskaznik1->nastepny->wydane_albumy->nastepny->wskaznik_utwory, nazwa_utworu);
					return;
				}
				else
					wskaznik1->nastepny->wydane_albumy = wskaznik1->nastepny->wydane_albumy->nastepny;
			}
		}
			else
				wskaznik1 = wskaznik1->nastepny;
			}
}
void czytaj_z_pliku(wykonawca * & wykonawca1, ifstream & plik)  //wczytanie z pliku
{   wykonawca *wskaznik1 = wykonawca1;
	string s這wo, nazwa1, nazwisko, imie, utwor1;
	int cena, dzien, miesiac, rok; 
	while (plik) {
		s這wo = " ";
		plik >> s這wo; // pobieramy slowo ktore oznajmia co jest dalej w lini w pliku odczytu 
		if (s這wo == "Koniec") 
		{
			return;
		}
		else if (s這wo == "Wykonawca") {
			plik >> imie;
				plik >> nazwisko;
			dodaj_wykonawce(wykonawca1, imie, nazwisko);  
		}
		else if (s這wo == "Album") {
			plik >> nazwa1;
			plik >> cena;
			plik >> dzien;
			plik >> miesiac;
			plik >> rok;
			dodaj_album_do_wykonawcy(wykonawca1, imie, nazwisko, nazwa1, cena, dzien, miesiac, rok);
		}
		else if (s這wo == "Utwor")
			{
				plik >> utwor1;
				dodaj_utwor_do_albumu(utwor1,wykonawca1,imie,nazwisko,nazwa1);
			}
		}
	}
void wyswietl_utwory(wykonawca *& wskaznik) 
{  wykonawca * wskaznik1 = wskaznik;
	while (wskaznik1 != NULL)  //sprawdzanie czy istnieje wykonawca
	{
		album *wskaznik2 = wskaznik1->wydane_albumy;
		while (wskaznik2!= NULL)  //sprawdzanie czy istnieje  album 
		{
			utwor *wskaznik3 = wskaznik2->wskaznik_utwory;
			while (wskaznik3!= NULL) //sprawdzanie czy istnieje  utwor 
			{
				cout << wskaznik3->nazwa_utworu << endl; 
				wskaznik3 = wskaznik3->nastepny; //przejscie po utworach w albumie
			}
			wskaznik2= wskaznik2->nastepny; //przejscie po albumach wykonawcy 
		}
		wskaznik1 = wskaznik1->nastepny; //przejscie po wykonawcach
	}
}
void wyswietl_albumy(wykonawca *& wskaznik)
{	wykonawca * wskaznik1 = wskaznik;
	while (wskaznik1 != NULL)  //sprawdzanie czy istnieje wykonawca
	{
		album *wskaznik2 = wskaznik1->wydane_albumy;  
		while (wskaznik2 != NULL) //sprawdzanie czy istnieje album
		{
			cout << wskaznik2->nazwa << endl;
			wskaznik2 = wskaznik2->nastepny; //przejscie po albumach wykonawcy 
		}
		wskaznik1 = wskaznik1->nastepny; //przejscie po wykonawcach
	}
}
void wyswietl_wykonawcy(wykonawca *& wskaznik)
{
	wykonawca * wskaznik1 = wskaznik; 
	while (wskaznik1 != NULL) //sprawdzanie czy istnieje  wykonawca
	{
		cout << wskaznik1->imie << " " << wskaznik1->nazwisko << endl;
		wskaznik1 = wskaznik1->nastepny; //przejscie po wykonawcach
	}
}
void wyswietl_date_podanego_albumu(wykonawca *& wskaznik, string nazwa_albumu)
{
	wykonawca * wskaznik1 = wskaznik;
	while (wskaznik1 != NULL) //sprawdzanie czy istnieje wykonawca
	{
		album * wskaznik2 = wskaznik1->wydane_albumy;
		while (wskaznik2 != NULL) //sprawdzanie czy istnieje album
		{ 
			if (wskaznik2->nazwa == nazwa_albumu)
			{
				cout << "Data wydania " << wskaznik2->nazwa << " to " << wskaznik2->data.dzien << "-" << wskaznik2->data.miesiac << "-" << wskaznik2->data.rok << endl;
				return;
			}
			wskaznik2 = wskaznik2->nastepny; //przejscie po albumach wykonawcy 
		}
		wskaznik1 = wskaznik1->nastepny;  //przejscie po wykonawcach
	}
	cout << "Nie ma takiego albumu." << endl;
}
void wyswietl_cene_podanego_albumu(wykonawca*&wskaznik,string nazwa_albumu)
{
	wykonawca * wskaznik1 = wskaznik; 
	while (wskaznik1 != NULL) //sprawdzanie czy istnieje wykonawca 
	{
		album * wskaznik2 = wskaznik1->wydane_albumy;
		while (wskaznik2 != NULL) //sprawdzenie czy istnieje album 
		{
			if (wskaznik2->nazwa == nazwa_albumu)
			{
				cout << "Cena albumu " << wskaznik2->nazwa << " wynosi " << wskaznik2->cena<< endl;
				return;
			}
			wskaznik2 = wskaznik2->nastepny;  //przejscie po albumach wykonawcy 
		}

		wskaznik1 = wskaznik1->nastepny; //przejscie po wykonawcach
	}
	cout << "Nie ma takiego albumu." << endl;
}
bool szukanie1(wykonawca*&wskaznik, string nazwa_albumu)  //funkcja ta pomaga w odnalezienu albumu przy wpisyawniu przez uzytkownika gdy chce dodac utwor do albumu
{  wykonawca* wskaznik1 = wskaznik;
	while (wskaznik1 != NULL)
	{
		while (wskaznik1->wydane_albumy != NULL)
		{
			if (wskaznik1->wydane_albumy->nazwa == nazwa_albumu)
			{
				return true;
			}
			else
			{
				wskaznik1->wydane_albumy = wskaznik1->wydane_albumy->nastepny;
			}
		}
		wskaznik1 = wskaznik1->nastepny;
	}
	return false;
}
string szukanie_imienia(wykonawca*&wskaznik, string nazwa_albumu) //funkcja wykorzystana w odnalezieniu imieina wykonawcy (czy ten wykonawca istnieje) gdy uzytkowni chce dodac utwor do albumu 
{
	string imie1;
	wykonawca* wskaznik1 = wskaznik;
	while (wskaznik1 != NULL)
	{
		while (wskaznik1->wydane_albumy != NULL)
		{
			if (wskaznik1->wydane_albumy->nazwa == nazwa_albumu)
			{
				imie1 = wskaznik1->imie;
				return imie1;
			}
			else
			{
				wskaznik1->wydane_albumy = wskaznik1->wydane_albumy->nastepny;
			}
		}
		wskaznik1 = wskaznik1->nastepny;
	}
	return "nie ma takiego imienia";
}
string szukanie_nazwiska(wykonawca*&wskaznik, string nazwa_albumu) //funkcja wykorzystana w odnalezieniu nazwiska wykonawcy (czy ten wykonawca istnieje) gdy uzytkowni chce dodac utwor do albumu 
{
	string nazwisko1;
	wykonawca* wskaznik1 = wskaznik;
	while (wskaznik1 != NULL)
	{
		while (wskaznik1->wydane_albumy != NULL)
		{
			if (wskaznik1->wydane_albumy->nazwa == nazwa_albumu)
			{
				nazwisko1 = wskaznik1->nazwisko;
				return nazwisko1;
			}
			else
			{
				wskaznik1->wydane_albumy = wskaznik1->wydane_albumy->nastepny;
			}
		}
		wskaznik1 = wskaznik1->nastepny;
	}
	return "nie ma takiego nazwiska";
}
bool szukanie3(wykonawca*&wskaznik, string nazwisko1,string imie1) //sprawdza czy podany album mozna przypisac wykonnawcy wpiasnemu przez uzytkowanika (czy istnieje wykonawca)
{
	string nazwisko, imie;
	wykonawca*wskaznik1 = wskaznik;
	while (wskaznik1 != NULL)
	{
		if (wskaznik1->nazwisko == nazwisko1 && wskaznik1->imie == imie1 )
		{
			return true;
		}
		else
		{
			wskaznik1 = wskaznik1->nastepny;
		}
	}
	return false;
}
void usuwanie_wykonawcy(wykonawca *& wskaznik, string imie1,string nazwisko1)  
{
	wykonawca * wskaznik1 = wskaznik;
	if (wskaznik1 != NULL)  //sprawdzenie czy wykonawcy wogole sa w bazie dancyh 
	{
		if (wskaznik1->imie == imie1 && wskaznik1->nazwisko == nazwisko1)
		{
			wskaznik = wskaznik1->nastepny;
			delete wskaznik1;
			cout << "usunieto wykonawce o imieniu " << imie1 <<"i nazwisku "<<nazwisko1 <<endl;
			return;
		}
		wykonawca *wskaznik2 = wskaznik1->nastepny;
			while (wskaznik1 != NULL)  //przejscie po kolejnych wykonawcach 
			{
				if (wskaznik2->nazwisko == nazwisko1 && wskaznik2->imie == imie1)
				{
					wskaznik2 = wskaznik2->nastepny;
					delete wskaznik1->nastepny;
					wskaznik1->nastepny = wskaznik2;
					cout << "usunieto wykonawce o imieniu"<<imie1<<"i nazwisku"<<nazwisko1<< endl;
					return;
				}
	
				wskaznik2 = wskaznik2->nastepny; 
			   wskaznik1 = wskaznik1->nastepny;
			}	
	}
	cout << "nie ma takiego wykonawcy" << endl;
}
void wyswietl_wykonawce_podanego_utworu(wykonawca *& wskaznik, string nazwa_utworu)
{
	wykonawca * wskaznik1 = wskaznik;
	while (wskaznik1 != NULL)  //sprawdzenie czy wykonawca istnieje 
	{
		album*wskaznik2 = wskaznik1->wydane_albumy;
		while (wskaznik2 != NULL) //program musi sprawdzic tez album 
		{
			utwor*wskaznik3 = wskaznik2->wskaznik_utwory;
			while (wskaznik3 != NULL)  //przejscie po kolejnych utworach albumu 
			{
				if (wskaznik3->nazwa_utworu == nazwa_utworu) 
				{
					cout << "Wykonawca tego utworu jest " << wskaznik1->imie << " " << wskaznik1->nazwisko << endl;
					return;
				}
				wskaznik3 = wskaznik3->nastepny;
			}
			wskaznik2 = wskaznik2->nastepny;
		}
		wskaznik1 = wskaznik1->nastepny;
	}
	cout << "Nie ma takiego utworu." << endl;
}
void zapis_do_pliku(wykonawca *& wskaznik, ofstream &plik)
{
	wykonawca * wskaznik1=wskaznik;
	while (wskaznik1 != NULL)  
	{
		plik << "Wykonawca " << wskaznik1->imie << " " << wskaznik1->nazwisko << endl;
		while (wskaznik1->wydane_albumy != NULL)
		{
			plik << "Album " << wskaznik1->wydane_albumy->nazwa << " " << wskaznik1->wydane_albumy->cena << " " << wskaznik1->wydane_albumy->data.dzien << " " << wskaznik1->wydane_albumy->data.miesiac << " " << wskaznik1->wydane_albumy->data.rok << endl;
			while (wskaznik1->wydane_albumy->wskaznik_utwory != NULL)
			{
				plik << "Utwor " << wskaznik1->wydane_albumy->wskaznik_utwory->nazwa_utworu << endl;
				wskaznik1->wydane_albumy->wskaznik_utwory = wskaznik1->wydane_albumy->wskaznik_utwory->nastepny; //przejscie po kolejnych utworach 
			}
			wskaznik1->wydane_albumy = wskaznik1->wydane_albumy->nastepny; //przejscie po albumach 

		}
		wskaznik1 = wskaznik1->nastepny; //przejscie po wykonawcach 
	}
}
void zapis_do_pliku2(wykonawca *wskaznik) //tworzenie pliku do zapisu 
{
	string nazwa_pliku;
	cout << "podaj nazwe pliku do ktorego chcesz zapisac dane po ukonczeniu pracy" << endl;
	cin >> nazwa_pliku;
	ofstream plik_do_zapisu(nazwa_pliku, ios::out);
	if (plik_do_zapisu.is_open())
	{
		cout << "Udalo sie utworzyc plik!" << endl;
		zapis_do_pliku(wskaznik, plik_do_zapisu); //wykonanie zapisu 
	}
	else
	{
		cout << "Nie udalo sie utworzyc pliku, sprobuj jeszcze raz!" << endl;
	}
	
}
char menu() 
{
	char znak;
	cout << "Podaj cyfre:" << endl;
	cout << "1.Wyswietl wykonawcow." << endl;
	cout << "2.Wyswietl albumy." << endl;
	cout << "3.Wyswietl utwory." << endl;
	cout << "4.Dodaj utwor do albumu." << endl;
	cout << "5.Dodaj album do wykonawcy." << endl;
	cout << "6.Dodaj wykonawce."<<endl; 
	cout << "7.Usuwanie wykonawcow." << endl;
	cout << "8.Wyswietl date podanego albumu." << endl;
	cout << "9.Wyswietl cene podanego albumu." << endl;
	cout << "a.Wyswietl wykonawce podanego utworu" << endl;
	cout << "Wybor literki 'k' oznacza koniec mozliwosci wyboru opcji." << endl;
	cin >> znak;
	return znak;
}
int main()
{
	ifstream plik_do_odczytu;
	ofstream nazwa_pliku_do_zapisu;
	string cos, nazwa_utworu, nazwa_albumu, imie, nazwisko;  //dane ktore wpisuje uzytkownik 
	char znak1;
	int cena, dzien, miesiac, rok;
	wykonawca * wykonawca1 = NULL;
	nazwa_pliku(cos);
	bool otwarcie_pliku1;
	otwarcie_pliku1 = otwarcie_pliku(cos, plik_do_odczytu);  //sprawdznie czy plik z danymi istnieje i sie  otworzyl
	if (otwarcie_pliku1)
	{
		czytaj_z_pliku(wykonawca1, plik_do_odczytu);
	}
	else
	{
		system("pause");
		return 0;
	}
	char znak = menu();
	while (znak != 'k')
	{
		switch (znak) //realizacja wybranej opcji 
		{
		case'1':
			cout << "Wykonawcy: " << endl;
			wyswietl_wykonawcy(wykonawca1);
			break;

		case'2': cout << "Albumy:" << endl;
			wyswietl_albumy(wykonawca1);
			break;

		case'3':
		{ cout << "Utwory" << endl;
		wyswietl_utwory(wykonawca1);
		break; }

		case'4':
			cout << "Podaj nazwe utworu" << endl;
			cin >> nazwa_utworu;
			cout << "Podaj nazwe albumu" << endl;
			cin >> nazwa_albumu;
			imie = szukanie_imienia(wykonawca1, nazwa_albumu);
			nazwisko = szukanie_nazwiska(wykonawca1, nazwa_albumu);
			if (imie == "nie ma takeigo imienia" || nazwisko == "nie ma takiego nazwiska")
			{
				cout << "Nie ma takiego albumu!" << endl;
				break;
			}
			if (szukanie1(wykonawca1, nazwa_albumu) == false)
			{
				cout << "W spisie nie ma takeigo albumu!" << endl;
				break;
			}
			else
				dodaj_utwor_do_albumu(nazwa_utworu, wykonawca1, imie, nazwisko, nazwa_albumu);
			break;

		case'5':
			cout << "Podaj nazwe albumu." << endl;
			cin >> nazwa_albumu;
			cout << "Podaj imie wykonawcy ktoremu chcesz dodac album." << endl;
			cin >> imie;
			cout << "Podaj nazwisko wykonawcy." << endl;
			cin >> nazwisko;
			cout << "Podaj cene dodanego albumu" << endl;
			cin >> cena;
			while (!cin && cena > 0)
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Podaj jescze raz" << endl;
				cin >> cena;
			}
			cout << "Podaj dzien wydania dodanego albumu" << endl;
			cin >> dzien;
			while (!cin && cena > 0 && cena < 32)
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Podaj jescze raz" << endl;
				cin >> dzien;
			}
			cout << "Podaj miesiac wydania dodanego albumu" << endl;
			cin >> miesiac;
			while (!cin && miesiac > 0 && miesiac < 13)
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Podaj jescze raz" << endl;
				cin >> miesiac;
			}
			cout << "Podaj rok wydania dodanego albumu" << endl;
			cin >> rok;
			while (!cin && rok > 0)
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Podaj jescze raz" << endl;
				cin >> rok;
			}
			if (szukanie3(wykonawca1, nazwisko, imie) == false)
				cout << "W spisie nie ma takeigo wykonawcy!" << endl;
			else
				dodaj_album_do_wykonawcy(wykonawca1, imie, nazwisko, nazwa_albumu, cena, dzien, miesiac, rok);
			break;
		case'6':
			cout << "Podaj imie  wykonawcy" << endl;
			cin >> imie;
			cout << "Podaj nazwisko wykonawcy" << endl;
			cin >> nazwisko;
			dodaj_wykonawce(wykonawca1, imie, nazwisko);
			break;
		case'7':
			cout << "Podaj imie wykonawcy ktorego chcesz usunac" << endl;
			cin >> imie;
			cout << "Podaj nazwisko wykonawcy ktorego chcesz usunac" << endl;
			cin >> nazwisko;
			usuwanie_wykonawcy(wykonawca1, imie, nazwisko);
			break;
		case '8':
			cout << "Podaj album ktorego date chcesz sprwadzic" << endl;
			cin >> nazwa_albumu;
			wyswietl_date_podanego_albumu(wykonawca1, nazwa_albumu);
			break;
		case '9':
			cout << "Podaj album kt鏎ego cene chcesz sprawdzic" << endl;
			cin >> nazwa_albumu;
			wyswietl_cene_podanego_albumu(wykonawca1, nazwa_albumu);
			break;
		case 'a':
			cout << "Podaj utwor ktorego wykonawce chcesz sprwadzic" << endl;
			cin >> nazwa_utworu;
			wyswietl_wykonawce_podanego_utworu(wykonawca1, nazwa_utworu);
			break;
		default:
			cout << "zly znak" << endl;
			break;
		}
		char znaczek;
		cout << "Twoj wybor zostal zrealizowany. Chcesz cos jesscze wykonac ('T') ?" << endl;
		cin >> znaczek;
		if (znaczek == 'T')
			znak = menu();
		else
		{
			zapis_do_pliku2(wykonawca1); //zapsianie do pliku
			system("pause");
			return 0;
		}
	}
}
