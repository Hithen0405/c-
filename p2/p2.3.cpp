#include <iostream>
using namespace std;
void minMax(int a[], int n, int &min, int &max)
{
    min = a[0];
    max = a[0];
    for (int i = 1; i < n; i++)
    {
        if (a[i] < min)
        {
            min = a[i];
        }
        else if (a[i] > max)
        {
            max = a[i];
        }
    }
}
int main()
{
    int data[] = {5, 2, 9, 1, 7};
    int min, max;
    minMax(data, 5, min, max);
    cout << "Minimum element: " << min << endl;
    cout << "Maximum element: " << max << endl;
    return 0;
}