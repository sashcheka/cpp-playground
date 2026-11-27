#include <iostream>
#include <memory>
#include <vector>

class Job {
public:
    virtual void Run() const {
        std::cout << "JOB" << "\n";
    };
    virtual ~Job() = default;
};

class TextJob : public Job {
public:
    void Run() const override {
        std::cout << "Processing text" << "\n";
    }
};

class ImageJob : public Job {
public:
    void Run() const override {
        std::cout << "Processing image" << "\n";
    }
};

namespace crtp {

template <typename Derived>
class JobBase {
public:
    void Run() const {
        static_cast<const Derived&>(*this).RunImpl();
    }
};

class TextJob : public JobBase<TextJob> {
public:
    void RunImpl() const {
        std::cout << "Processing text\n";
    }
};

class ImageJob : public JobBase<ImageJob> {
public:
    void RunImpl() const {
        std::cout << "Processing image\n";
    }
};

class DefaultJob : public JobBase<DefaultJob> {
public:
    void RunImpl() const {
        std::cout << "JOB\n";
    }
};

}  // namespace crtp

int main() {
    std::vector<std::unique_ptr<Job>> jobs;

    jobs.emplace_back(std::make_unique<TextJob>());
    jobs.emplace_back(std::make_unique<ImageJob>());
    jobs.emplace_back(std::make_unique<Job>());

    std::cout << "Dynamic polymorphism\n";
    for (const std::unique_ptr<Job>& job : jobs) {
        job->Run();
    }

    std::cout << "\nStatic polymorphism (CRTP)\n";
    crtp::TextJob{}.Run();
    crtp::ImageJob{}.Run();
    crtp::DefaultJob{}.Run();

    return 0;
}
