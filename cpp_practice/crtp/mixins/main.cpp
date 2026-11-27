#include <iostream>

template<class Derived>
class WithPriority {
public:
    Derived& SetPriority(int priority) {
        priority_ = priority;
        return static_cast<Derived&>(*this);
    }

    int GetPriority() const {
        return priority_;
    }

private:
    int priority_ = 0;
};

class ImageJob : public WithPriority<ImageJob> {
public:
    ImageJob& SetWidth(int width) {
        width_ = width;
        return *this;
    }

    int GetWidth() const {
        return width_;
    }

private:
    int width_ = 0;
};

int main() {
    ImageJob job;
    job.SetPriority(3).SetWidth(128);

    std::cout << job.GetPriority() << "\n";
    std::cout << job.GetWidth() << "\n";


    return 0;
}
