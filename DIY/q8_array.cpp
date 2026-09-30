#include <iostream>

class Counter {
private:
    int count;
public:
    Counter() : count(0) {}

    void increment() {
        count++;
    }

    void reset() {
        count = 0;
    }
    int get() const {
        return count;
    }
};
int main() {
    Counter counters[3];
    counters[0].increment();
    counters[1].increment();
    counters[1].increment();
    counters[2].increment();
    counters[2].increment();
    counters[2].reset(); 
    for (int i = 0; i < 3; i++) {
        std::cout << "Counter " << i << " value: " << counters[i].get() << "\n";
    }
    return 0;
}