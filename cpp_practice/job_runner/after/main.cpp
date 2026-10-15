#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
#include <memory>

class Job {
public:
    virtual ~Job() = default;

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
    void Add(std::unique_ptr<Job> job) {
        jobs_.push_back(std::move(job));
    }

    void RunAll() const {
        for (const std::unique_ptr<Job>& job : jobs_) {
            job.get()->Run();
        }
    }

    JobRunner() = default;

    JobRunner(JobRunner&& other) : jobs_(std::move(other.jobs_)) {
        other.jobs_.clear();
    }

private:
    std::vector<std::unique_ptr<Job>> jobs_;
};

int main() {
    JobRunner runner;

    runner.Add(std::make_unique<MessageJob>("Starting report"));
    runner.Add(std::make_unique<SumJob>(std::vector<int>{10, 20, 30}));
    runner.Add(std::make_unique<MessageJob>("Report complete"));

    JobRunner next = std::move(runner);

    next.RunAll();

    return 0;
}
