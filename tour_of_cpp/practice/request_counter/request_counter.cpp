#include "request_counter.hpp"

metrics::RequestCounter::RequestCounter() 
    : successCount_(0), failureCount_(0) {}

void metrics::RequestCounter::Record(bool success) {
    if (success) {
        ++successCount_;
    } else {
        ++failureCount_;
    }
}

int metrics::RequestCounter::SuccessCount() const {
    return successCount_;
}

int metrics::RequestCounter::FailureCount() const {
    return failureCount_;
}

long long metrics::RequestCounter::Total() const {
    return static_cast<long long>(successCount_) + failureCount_;
}
