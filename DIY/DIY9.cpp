#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    void setData(double r, double i) {
        real = r;
        imag = i;
    }
    void display() const {
        std::cout << real << " + " << imag << "i" << "\n";
    }
};

int main() {
    Complex numArr[3];
    numArr[0].setData(2.5, 4.0);
    numArr[1].setData(-1.0, 7.5);
    numArr[2].setData(0.0, 3.2);
    std::cout << "Complex Numbers List:\n";
    for (int i = 0; i < 3; i++) {
        std::cout << "Number " << i + 1 << ": ";
        numArr[i].display();
    }
    return 0;
}