#include "request_counter.hpp"
#include "request_report.hpp"

#include <iostream>

int main() {
    const metrics::RequestCounter crc;

    std::cout << "Success count: " << crc.SuccessCount() << "\n";
    std::cout << "Failure count: " << crc.FailureCount() << "\n";
    std::cout << "Total count: " << crc.Total() << "\n";

    metrics::RequestCounter rc;

    rc.Record(true);
    rc.Record(false);
    rc.Record(true);

    std::cout << "Success count: " << rc.SuccessCount() << "\n";
    std::cout << "Failure count: " << rc.FailureCount() << "\n";
    std::cout << "Total count: " << rc.Total() << "\n";
    
    std::cout << "Report: " << metrics::FormatReport(rc) << "\n";

    return 0;
}
