#include <iostream>
using namespace std;
int area(int side)
{
    return side * side;
}
int area(int length, int breadth)
{
    return length * breadth;
}
float area(float base, float height)
{
    return 0.5 * base * height;
}
int main()
{
    int side, length, breadth;
    float base, height;
    cout << "Enter the side of the square: ";
    cin >> side;
    cout << "Area of square: " << area(side) << endl;
    cout << "Enter the length and breadth of rectangle: ";
    cin >> length >> breadth;
    cout << "Area of rectangle: " << area(length, breadth) << endl;
    cout << "Enter the base and height of triangle: ";
    cin >> base >> height;
    cout << "Area of triangle: " << area(base, height) << endl;
    return 0;
}