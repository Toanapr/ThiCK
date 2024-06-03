#include <iostream>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int partition(int a[], int start, int end)
{
    int pivot = a[start];
    int cnt = 0;

    for (int i = start + 1; i <= end; i++)
        if (a[i] < pivot)
            cnt++;

    int pivotIndex = start + cnt;
    swap(a[start], a[pivotIndex]);

    int i = start;
    int j = end;

    while (i < pivotIndex && j > pivotIndex)
    {
        while (a[i] < a[pivotIndex] && i < pivotIndex)
            i++;
        while (a[j] > a[pivotIndex] && j > pivotIndex)
            j--;

        swap(a[i], a[j]);
    }

    return pivotIndex;
}

void quickSort(int a[], int start, int end)
{
    if (start >= end)
        return;

    int p = partition(a, start, end);
    quickSort(a, start, p - 1);
    quickSort(a, p + 1, end);
}

int binarySearch(int a[], int n, int val)
{
    int l = 0;
    int r = n - 1;
    int mid = (r + l) / 2;

    while (true)
    {
        if (l > r)
            return -1;
        mid = (r + l) / 2;
        if (a[mid] == val)
            return mid;
        else if (a[mid] < val)
            l = mid + 1;
        else
            r = mid - 1;
    }
}

int binarySearchByRecursion(int a[], int n, int val, int l, int r)
{
    int mid = (l + r) / 2;

    if (a[mid] == val)
        return mid;
    else if (a[mid] < val)
        return binarySearchByRecursion(a, n, val, mid + 1, r);
    else
        return binarySearchByRecursion(a, n, val, l, mid - 1);
}


int main()
{
    int a[] = {10, 90, 20, 40, 70, 15, 34};
    quickSort(a, 0, 6);
    for (int i = 0; i < 7; i++)
        cout << a[i] << " ";
    cout << endl;
    cout << binarySearchByRecursion(a, 7, 40, 0, 6);
    return 0;
}