#include <iostream>
#include <time.h>
#define SIZE1 10
#define SIZE 12
using namespace std;
int main()
{
	srand(time(NULL));
	int tab[SIZE1][SIZE];
	for (int i = 0; i < SIZE1; i++)
	{
		for (int j = 0; i < SIZE; j++)
		{
			tab[i][j] = 0;
		}
	}
	for (int i = 0; i < SIZE1; i++)
	{
		for (int j = 0; i < SIZE; j++)

			cout << tab[i][j] << endl;
	}
	system("pause");
return 0;

}