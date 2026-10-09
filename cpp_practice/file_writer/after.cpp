#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

class FileWriter {
public:
    explicit FileWriter(const std::string& path) {
        file_ = std::fopen(path.c_str(), "w");

        if (!file_) {
            throw std::runtime_error("Cannot open file");
        }
    }

    FileWriter(const FileWriter&) = delete;
    FileWriter& operator=(const FileWriter&) = delete;

    FileWriter(FileWriter&& other) noexcept
        : file_(std::exchange(other.file_, nullptr)) {}

    FileWriter& operator=(FileWriter&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        if (file_) {
            std::fclose(file_);
        }

        file_ = std::exchange(other.file_, nullptr);
        return *this;
    }

    ~FileWriter() {
        if (file_) {
            std::fclose(file_);
        }
    }

    void Write(const std::string& text) {
        if (!file_) {
            throw std::logic_error("File is not open");
        }

        if (std::fputs(text.c_str(), file_) == EOF) {
            throw std::runtime_error("Write failed");
        }
    }

private:
    std::FILE* file_ = nullptr;
};

void SaveReports(const std::vector<std::string>& reports) {
    FileWriter writer("reports.txt");

    for (const auto& report : reports) {
        writer.Write(report);
    }
}