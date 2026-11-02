#include "inference.hpp"

#include <stdexcept>

std::vector<float> CsvParser::Parse(std::string_view) const {
    throw std::logic_error("CsvParser::Parse is not implemented");
}

float MaxModel::Predict(const std::vector<float>&) const {
    throw std::logic_error("MaxModel::Predict is not implemented");
}

Logger::Logger(std::ostream& output)
    : output_(output) {}

void Logger::Log(std::string_view) {
    throw std::logic_error("Logger::Log is not implemented");
}

InferenceServer::InferenceServer(
    const Model& model,
    const Parser& parser,
    Logger& logger
)
    : model_(model), parser_(parser), logger_(logger) {}

std::string InferenceServer::Predict(std::string_view) const {
    throw std::logic_error("InferenceServer::Predict is not implemented");
}
