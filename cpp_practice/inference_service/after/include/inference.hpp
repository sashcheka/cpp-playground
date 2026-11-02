#pragma once

#include <ostream>
#include <string>
#include <string_view>
#include <vector>

class Parser {
public:
    virtual ~Parser() = default;
    virtual std::vector<float> Parse(std::string_view input) const = 0;
};

class Model {
public:
    virtual ~Model() = default;
    virtual float Predict(const std::vector<float>& features) const = 0;
};

class CsvParser : public Parser {
public:
    std::vector<float> Parse(std::string_view input) const override;
};

class MaxModel : public Model {
public:
    float Predict(const std::vector<float>& features) const override;
};

class Logger {
public:
    explicit Logger(std::ostream& output);
    void Log(std::string_view message);

private:
    std::ostream& output_;
};

class InferenceServer {
public:
    InferenceServer(const Model& model, const Parser& parser, Logger& logger);
    std::string Predict(std::string_view request) const;

private:
    const Model& model_;
    const Parser& parser_;
    Logger& logger_;
};
