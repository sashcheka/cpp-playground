#include <concepts>
#include <iostream>

class TextJob {
public:
    void Run() const {
        std::cout << "TextJob RUN" << "\n";
    }
};

class ImageJob {
public:
    void Run() const {
        std::cout << "ImageJob RUN" << "\n";
    }
};

class WrongJob {
public:
    int Run() const {
        std::cout << "WrongJob RUN" << "\n";
        return 69;
    }
};

template<typename T>
concept Runnable = requires(const T& job) {
    { job.Run() } -> std::same_as<void>;
};

template<typename T>
requires Runnable<T>
void RunJob(const T& job) {
    job.Run();
}

template<typename T>
concept HasRunImpl = requires(const T& job) {
    { job.RunImpl() } -> std::same_as<void>;
};

template<class Derived>
class JobBase {
public:
    void Run() const requires HasRunImpl<Derived> {
        static_cast<const Derived&>(*this).RunImpl();
    }
};

namespace crtp {

class TextJob : public JobBase<TextJob> {
public:
    void RunImpl() const {
        std::cout << "CRPT TextJob runImpl()" << "\n";
    }
};

class ImageJob : public JobBase<ImageJob> {
public:
    void RunImpl() const {
        std::cout << "CRTP ImageJob runImpl()" << "\n";
    }
};

}  // crtp

int main() {
    TextJob tj;
    ImageJob ij;

    RunJob(tj);
    RunJob(ij);
    static_assert(!Runnable<WrongJob>);

    crtp::TextJob crtpTJ;
    crtpTJ.Run();
    crtp::ImageJob crtpIJ;
    crtpIJ.Run();

    return 0;
}
