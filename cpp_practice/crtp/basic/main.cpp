#include <iostream>

template<typename Derived>
class Base {
public:
    void Run() const {
        const Derived& d = static_cast<const Derived&>(*this);
        d.RunImpl();
    }

};

class TextJob : public Base<TextJob> {
public:
    void RunImpl() const {
        std::cout << "Processing text" << "\n";
    }
};

class ImageJob : public Base<ImageJob> {
public:
    void RunImpl() const {
        std::cout << "Processing image" << "\n";
    }
};

int main() {
    TextJob tj;
    ImageJob ij;

    tj.Run();
    ij.Run();

    return 0;
}
