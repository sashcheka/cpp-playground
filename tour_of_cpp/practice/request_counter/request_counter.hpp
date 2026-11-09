#pragma once

namespace metrics {

class RequestCounter {
    public:
        RequestCounter();
        void Record(bool);
        int SuccessCount() const;
        int FailureCount() const;
        long long Total() const;

    private:
        int successCount_;
        int failureCount_;
};

}  // namespace metrics
