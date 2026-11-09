#pragma once

#include "request_counter.hpp"

#include <string>

namespace metrics {

std::string FormatReport(const RequestCounter&);

}  // namespace metrics
