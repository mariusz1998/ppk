#include <iostream>
#include <ctime>
using namespace std;
int main()
{
	int tab[20];
	for (int i = 0; i < 20; i++)
		tab[i] = rand() % 29 + 11;
	for (int i = 0; i < 20; i++)
	cout << tab[i] << endl;
system("pause");
	return 0;
}