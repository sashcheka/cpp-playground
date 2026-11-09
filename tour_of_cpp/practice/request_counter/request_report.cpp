#include "request_counter.hpp"
#include "request_report.hpp"

std::string metrics::FormatReport(const RequestCounter& counter) {
    return "Success: " + std::to_string(counter.SuccessCount()) +
            ", Failure: " + std::to_string(counter.FailureCount()) +
            ", Total: " + std::to_string(counter.Total());
}
