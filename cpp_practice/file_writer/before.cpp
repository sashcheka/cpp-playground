#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>

class FileWriter {
public:
    explicit FileWriter(const std::string& path) {
        file_ = std::fopen(path.c_str(), "w");

        if (!file_) {
            throw std::runtime_error("Cannot open file");
        }
    }

    ~FileWriter() {
        std::fclose(file_);
    }

    void Write(const std::string& text) {
        if (std::fputs(text.c_str(), file_) == EOF) {
            throw std::runtime_error("Write failed");
        }
    }

private:
    std::FILE* file_ = nullptr;
};

void SaveReports(const std::vector<std::string>& reports) {
    auto writer = new FileWriter("reports.txt");

    for (const auto& report : reports) {
        writer->Write(report);
    }

    delete writer;
}