#include <iostream>
using namespace std;

template <typename T>
void print_mas(T*, int);

int main()
{
	int mas_int[] = { 1, 2254, 3, 56,13, 35, 356 };
	double mas_double[] = { 1.3, 32.525, 13.35, 13.536, 35.315, 6.434 };
	print_mas(mas_int, sizeof(mas_int) / sizeof(mas_int[0]));
	cout << "\n";
	print_mas(mas_double, sizeof(mas_double) / sizeof(mas_double[0]));
	return 0;
}

template <typename T>
void print_mas(T* mas, int size)
{
	cout << mas[0];
	for (int i = 1; i < size; i++)
	{
		cout << ", " << mas[i];
	}
}