#include <algorithm>
#include <cstddef>
#include <exception>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>

class ByteBuffer {
public:
    static constexpr std::size_t kMaxCapacity = 1024;

    explicit ByteBuffer(std::size_t initial_capacity = 8) {
        if (initial_capacity > kMaxCapacity) {
            throw std::length_error("Buffer capacity limit exceeded");
        }

        if (initial_capacity != 0) {
            data_ = new char[initial_capacity];
        }

        capacity_ = initial_capacity;
    }

    ~ByteBuffer() {
        delete[] data_;
    }

    void Reserve(std::size_t requested_capacity) {
        if (requested_capacity > kMaxCapacity) {
            throw std::length_error("Buffer capacity limit exceeded");
        }

        if (requested_capacity <= capacity_) {
            return;
        }

        char* replacement = new char[requested_capacity];

        delete[] data_;
        data_ = replacement;
        capacity_ = requested_capacity;
    }

    void Append(std::string_view chunk) {
        if (chunk.empty()) {
            return;
        }

        if (chunk.size() > kMaxCapacity - size_) {
            throw std::length_error("Buffer capacity limit exceeded");
        }

        Reserve(size_ + chunk.size());
        std::copy(chunk.begin(), chunk.end(), data_ + size_);
        size_ += chunk.size();
    }

    void Consume(std::size_t) {
        throw std::logic_error("Operation not implemented");
    }

    std::optional<std::string> TryReadLine() {
        throw std::logic_error("Operation not implemented");
    }

    void Clear() {
        size_ = 0;
    }

    const char* Data() const {
        return data_;
    }

    std::size_t Size() const {
        return size_;
    }

    std::size_t Capacity() const {
        return capacity_;
    }

private:
    char* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
};

int main() {
    try {
        ByteBuffer input(4);
        const std::string_view chunks[] = {
            "HE",
            "LLO\nPI",
            "NG\nTAIL"
        };

        for (std::string_view chunk : chunks) {
            input.Append(chunk);

            while (auto message = input.TryReadLine()) {
                std::cout << "Message: " << *message << '\n';
            }
        }

        std::cout << "Remaining: "
                  << std::string(input.Data(), input.Size()) << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
