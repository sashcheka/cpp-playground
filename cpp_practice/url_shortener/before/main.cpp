#include <cstddef>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class CodeGenerator {
public:
    explicit CodeGenerator(std::vector<std::string> candidates)
        : candidates_(std::move(candidates)) {
        if (candidates_.empty()) {
            throw std::invalid_argument("No code candidates");
        }
    }

    std::string Next() {
        std::string code = candidates_[position_];
        position_ = (position_ + 1) % candidates_.size();
        return code;
    }

private:
    std::vector<std::string> candidates_;
    std::size_t position_ = 0;
};

class UrlShortener {
public:
    explicit UrlShortener(
        std::vector<std::string> candidates,
        std::size_t max_attempts = 3
    )
        : urls_(new std::unordered_map<std::string, std::string>),
          generator_(new CodeGenerator(std::move(candidates))),
          max_attempts_(max_attempts) {
        if (max_attempts_ == 0) {
            throw std::invalid_argument("Attempt limit must be positive");
        }
    }

    ~UrlShortener() {
        delete generator_;
        delete urls_;
    }

    std::string Shorten(std::string url) {
        if (url.empty()) {
            throw std::invalid_argument("Empty URL");
        }

        std::string code = generator_->Next();
        (*urls_)[code] = std::move(url);
        return code;
    }

    std::optional<std::string> Resolve(const std::string& code) const {
        const auto it = urls_->find(code);
        if (it == urls_->end()) {
            return std::nullopt;
        }

        return it->second;
    }

    std::size_t Size() const {
        return urls_->size();
    }

private:
    std::unordered_map<std::string, std::string>* urls_;
    CodeGenerator* generator_;
    std::size_t max_attempts_;
};

int main() {
    UrlShortener shortener({"ab12", "ab12", "cd34"}, 3);

    const auto first = shortener.Shorten("https://example.com/users/alice");
    const auto second = shortener.Shorten("https://example.com/users/bob");

    std::cout << "https://sho.rt/" << first << " -> "
              << shortener.Resolve(first).value_or("missing") << '\n';
    std::cout << "https://sho.rt/" << second << " -> "
              << shortener.Resolve(second).value_or("missing") << '\n';
    std::cout << "Stored: " << shortener.Size() << '\n';
}
