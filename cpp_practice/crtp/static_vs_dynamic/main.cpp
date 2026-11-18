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

int main() {
    std::vector<std::unique_ptr<Job>> jobs;

    jobs.emplace_back(std::make_unique<TextJob>());
    jobs.emplace_back(std::make_unique<ImageJob>());
    jobs.emplace_back(std::make_unique<Job>());

    for (const std::unique_ptr<Job>& job : jobs) {
        job->Run();
    }

    return 0;
}
