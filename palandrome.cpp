#include <iostream>
#include <string>
using namespace std;
int main()
{
    string str;
    cout << "Enter the word: ";
    cin >> str;
    cout << "Length of the string: " << str.length() << endl;
    for (char c : str)
    {
        cout << (char)toupper(c);
    }
    cout << endl;
    bool pal;
    size_t i = 0;
    size_t j = str.length() - 1;
    for (i = 0, j = str.length() - 1; i < j; i++, j--)
    {
        if (str[i] != str[j])
        {
            pal = false;
            break;
        }
    }
    if (pal)
    {
        cout << "The word is a palindrome." << endl;
    }
    else
    {
        cout << "The word is not a palindrome." << endl;
    }
    size_t size_pos = str.find("a");
    if (size_pos == 1)
    {
        cout << "Substring 'a' is found in the given string." << endl;
    }
    else
    {
        cout << "Substring 'a' is not found in the given string." << endl;
    }
}