#include <iostream>
using namespace std;
int main()
{
    int a = 10;
    int b = 20;

    cout << "Before swap: " << "a= " << a << " \nb= " << b << endl;
    swap(a, b);
    cout << "After swap: " << "a= " << a << " \nb= " << b << endl;
}
void swap(int x, int y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;
}
