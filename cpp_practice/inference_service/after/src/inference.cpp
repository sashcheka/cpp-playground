#include "inference.hpp"
#include "utils.hpp"

#include <stdexcept>
#include <cctype>
#include <limits>
#include <algorithm>
#include <cmath>
#include <cfloat>

std::vector<float> CsvParser::Parse(std::string_view input) const {
    std::size_t n = input.size();
    std::vector<float> features;
    std::string token;

    for (std::size_t i = 0; i <= n; ++i) {
        if (i == n || input[i] == ',') {
            if (token.empty()) {
                throw std::invalid_argument("Input has wrong format");
            }

            try {
                std::size_t processed_chars = 0;
                double feature_d = std::stod(token, &processed_chars);

                for (std::size_t j = processed_chars; j < token.size(); ++j) {
                    if (!std::isspace(static_cast<unsigned char>(token[j]))) {
                        throw std::invalid_argument("Input has wrong format");
                    }
                }

                if (std::isnan(feature_d) || std::isinf(feature_d)) {
                    throw std::invalid_argument("Input has wrong format");
                }

                if (!utils::is_in_range<float>(feature_d)) {
                    throw std::invalid_argument("Input has wrong format");
                }

                features.push_back(static_cast<float>(feature_d));
                token.clear();
            } catch (const std::invalid_argument&) {
                throw std::invalid_argument("Input has wrong format");
            } catch (const std::out_of_range&) {
                throw std::invalid_argument("Input has wrong format");
            }
        } else {
            token += input[i];
        }
    }

    if (features.empty()) {
        throw std::invalid_argument("Input has wrong format");
    }

    return features;
}

float MaxModel::Predict(const std::vector<float>& features) const {
    if (features.empty()) {
        throw std::invalid_argument("Input has wrong format");
    }

    float maxFeature = features[0];
    for (float f : features) {
        if (std::isnan(f) || std::isinf(f)) {
            throw std::invalid_argument("Input has wrong format");
        }
        maxFeature = std::max(maxFeature, f);
    }

    return maxFeature;
}

Logger::Logger(std::ostream& output)
    : output_(output) {}

void Logger::Log(std::string_view message) {
    output_ << message << "\n";
}

InferenceServer::InferenceServer(
    const Model& model,
    const Parser& parser,
    Logger& logger
)
    : model_(model), parser_(parser), logger_(logger) {}

std::string InferenceServer::Predict(std::string_view input) const {
    std::vector<float> features;
    try {
        features = parser_.Parse(input);
    } catch (std::invalid_argument& e) {
        logger_.Log(e.what());
        return "{\"error\":\"invalid input\"}";
    }

    float prediction;
    try {
        prediction = model_.Predict(features);
    } catch (std::invalid_argument& e) {
        logger_.Log(e.what());
        return "{\"error\":\"invalid input\"}";
    }
    
    logger_.Log("prediction succeeded");

    return "{\"prediction\":" + std::to_string(prediction) + "}";
}
