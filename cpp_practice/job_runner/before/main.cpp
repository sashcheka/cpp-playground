#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

class Job {
public:
    ~Job() = default;

    virtual void Run() const = 0;
};

class MessageJob : public Job {
public:
    explicit MessageJob(std::string message)
        : message_(std::move(message)) {}

    void Run() const override {
        std::cout << message_ << '\n';
    }

private:
    std::string message_;
};

class SumJob : public Job {
public:
    explicit SumJob(std::vector<int> values)
        : values_(std::move(values)) {}

    void Run() const override {
        std::cout << "Sum: "
                  << std::accumulate(values_.begin(), values_.end(), 0)
                  << '\n';
    }

private:
    std::vector<int> values_;
};

class JobRunner {
public:
    ~JobRunner() {
        for (Job* job : jobs_) {
            delete job;
        }
    }

    void Add(Job* job) {
        jobs_.push_back(job);
    }

    void RunAll() const {
        for (const Job* job : jobs_) {
            job->Run();
        }
    }

private:
    std::vector<Job*> jobs_;
};

int main() {
    JobRunner runner;

    runner.Add(new MessageJob("Starting report"));
    runner.Add(new SumJob({10, 20, 30}));
    runner.Add(new MessageJob("Report complete"));

    JobRunner next = std::move(runner);

    next.RunAll();

    return 0;
}
