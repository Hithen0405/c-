#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str;
    cout << "Enter a string: ";
    cin >> str;
    cout << "You entered: "<< str << endl;
    cout << "Length of the string: " << str.length() << endl;
    cout << "Upper: ";
    for(char c : str)
    {
        cout << (char)toupper(c);
    }
    cout << endl;
    return 0;
}