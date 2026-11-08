#include <iostream>

class Counter {
public:
    Counter(int value) : value_{value} {};

    void Increment() {
        ++value_;
    }

    int Value() const {
        return value_;
    }

    void Reset(int newValue) {
        value_ = newValue;
    }

private:
    int value_;
};

int main() {
    Counter c{1};

    int saved = c.Value();
    c.Reset(2);

    std::cout << saved << "\n";
    std::cout << c.Value() << "\n";
    
    return 0;
}
