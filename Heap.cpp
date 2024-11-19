#include <iostream>

using namespace std;
void heapify(int a[], int n, int i)
{
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && a[left] < a[smallest])
		smallest = left;

	if (right < n && a[right] < a[smallest])
		smallest = right;

	if (smallest != i)
	{
		swap(a[smallest], a[i]);
		heapify(a, n, smallest);
	}
}
void insert(int a[], int &n, int x)
{
	n++;
	int i = n - 1;
	a[n - 1] = x;
	while (i != 0 && a[i] < a[i / 2 - 1])
	{
		swap(a[i], a[i / 2 - 1]);
		i = i / 2 - 1;
	}
}
int main()
{
	int a[10] = { 15, 10, 5, 4, 3, 2 };
	int n = 6;
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(a, n, i);
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	
	cout << endl;
	insert(a, n, 1);
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	return 0;
}