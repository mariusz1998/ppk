#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void help()  //pomoc 
{
	cout << "Program pokazuje palindormy w danym przedziale. Mi\210ego dnia :-)" << endl;
	cout << "Program dzia\210a na lliczbach naturalnych wi\251kszych od zera." << endl;
	cout << "Prawid\210owe nazwy plik\242w to przedzia\210.txt i wypisywanie.txt ." << endl;
	cout << "Je\230li program ma z\210y przedzia\210 powinno si\251 uda\206 do pliku przedzia\210.txt i zmieni\206 go!" << endl;
}
int main(int argc, char* argv[])
{
	string znaczek = "-h", plik1 = "przedzia³.txt", plik2 = "wypisywanie.txt";
	if (!argv[1])  //sprawdzanie czy podano argument pierwszy 
	{
		cout << "Brak argumentu pierwszego!" << endl;
		help();
		system("pause");
		return 0;
	}
	if (!argv[2]) //sprawdzanie czy podano argument drugi a argumnet pierwszy nie jest prosb¹ o pomoc lub poprawn¹ nazw¹ pliku
	{
		if (argv[1] != znaczek) 
			if (argv[1] != plik1)
		{
			cout << "Brak argumentu drugiego i z\210y argument pierwszy!" << endl;
			help();
			system("pause");
			return 0;
		}
		else
		{
			cout << "Brak argumentu drugiego." << endl;
			help();
			system("pause");
			return 0;

		}
	}
	if (argv[1] == znaczek)  // sprawdzamy czy podano prosbe o pomoc 
	{
		help();
		system("pause");
		return 0;
	}	
	else
		if ((argv[1] == plik1) && (argv[2] == plik2)) // sprawdzamy czy nazwy plikow sa zgodne 
		{
			string p, r;
			int y, x;
			using namespace std;
			fstream p1(plik1, ios::in); //inicjacja pliku do odczytania przedzia³u 
			if (!p1)  //sprawdzamy czy plik z przedzia³em istnieje 
			{
				cout << "Brak pliku z podanym przedia\210em!" << endl;
				help();
				system("pause");
				return 0;
			} //pobieranie przedzialu ktory jest 
			getline(p1, p);
			y = atoi(p.c_str()); //zamiana tekstu na liczbe
			getline(p1, r);
			x = atoi(r.c_str());
			p1.close();
			if (y > x) //sprawdzinie czy przedzia³ jest zgodny 
			{
				help();
				system("pause");
				return 0;
			}
			fstream p2(argv[2], ios::out); // inicjacja pliku do zapisania palindromów
			int w, k, s, i, l, h, o, m, v,z;
			for (y; y <= x; y++) //wykonywanie od pocz¹tku a¿ do koñca przedzia³u
			{
				z = 0;  //wartosci te musz¹ byæ tzw. "zresetowane" dla ka¿dej sprawdzanej liczby 
				i = 0;
				h = 0;
				l = y;
				w = 0;
				v = 0;
				while (l >= 1) // sprawdzanie d³ugosæi "w" jest licznikiem
				{
					l = l / 10;
					w++;
				}
				o = w;
				m = y;
				if (w == 1) //jezeli liczba jest z zakresu <1,9> to ja wypisujemy
				{
					p2 << y << endl;
				}
				while (i < (w / 2)) // sprawdzamy odpowiednie liczby wykonuje a¿ dojdzie do po³owy liczby 
				{
					s = (y / pow(10, o - 1)) - v; //wyci¹ganie liczby z lewej 
					k = m % 10; //wyciaganie liczby z prawej
					h = s;
					v = 10 * h + v * 10;
					if (s == k) // jezeli zgodne to "z" jest równe 1  
					{

						z = 1;
					}
					else //jeœli nie to wychodzimy z petli
					{
						z = 0;
						break;
					}
					i++;
					o--;
					m = m / 10; 
				}
				if (z==1) //jesli zgodne to wpisujemy liczbe do pliku
				{
					p2 << y << endl;
				}
			}
			p2.close();
			cout << "liczby kt\242re s\245 palindormami: " << endl;
			int liczba, Liczba1=0;
			fstream p3(argv[2], ios::in);  //inicjacja pliku do odczytania palindrmów 
			while (!p3.eof()) //dopóki dojdzie do koñca plków
			{
				p3 >> liczba;
				if (Liczba1 == liczba) //pêtla while(!p3.eof) wypisuje ostatni¹ wartoœæ dwukrotnie wiêc staramy siê temu zapobiec  
					break;
				cout << liczba << endl;
				Liczba1 = liczba;
			}
			p3.close();
		}
		else // u¿ytkownik podaje z³e nazwy 
		{
			cout <<"Z\210e nazwy plik\242w" << endl; 
			help();
		}
	system("pause");
	return 0;
}