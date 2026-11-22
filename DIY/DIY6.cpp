#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    string s;
    cout << "Enter a sentence: ";
    getline(cin, s);

    stringstream ss(s);
    string word;
    vector<string> words;
    while (ss >> word) {
        words.push_back(word);
    }
    cout << "Reversed word order: ";
    for (int i = words.size() - 1; i >= 0; i--) {
        cout << words[i] << (i == 0 ? "" : " ");
    }
    cout << endl;

    return 0;
}