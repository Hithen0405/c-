#include <iostream>
using namespace std;
double volume(double side)
{
    return side * side * side;
}
double volume(double length, double breadth, double height)
{
    return length * breadth * height;
}
double volume(double radius, double height)
{
    return 3.14159 * radius * radius * height;
}

int main()
{
    cout << "Volume of cube = " << volume(5) << endl;
    cout << "Volume of cuboid = " << volume(4, 5, 6) << endl;
    cout << "Volume of cylinder = " << volume(3, 7) << endl;
    return 0;
}