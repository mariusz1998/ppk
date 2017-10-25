# include <iostream>
# include <string>
using namespace std;
int main()
{
	string nazwisko;
	char znak;
	int tab[30], n = 0, i = 1;
	cout << "podaj nazwisko" << endl;
	cin >> nazwisko;
	do
	{
		cout << "podaj ocene" << endl;
		cin >> tab[i];
		n = n + tab[i];
		i++;
		cout << "chcesz jescze podaæ ocenê?" << endl;
		cin >> znak;
		cin.ignore(5000, '\n');
	} while (znak == 't');
	cout << "srdenia ocen " << n / (i - 1) << "  twoje nazwisko " << nazwisko << endl;
	cin.get();
	return 0;
}

