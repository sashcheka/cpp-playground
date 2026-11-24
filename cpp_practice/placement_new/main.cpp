#include <cstddef>
#include <iostream>
#include <new>
#include <memory>

template<class T>
class WidgetSlot {
public:
    WidgetSlot() = default;
    WidgetSlot(const WidgetSlot&) = delete;
    WidgetSlot(WidgetSlot&&) = delete;

    void Emplace(int id) {
        Reset();
        T* ptr = reinterpret_cast<T*>(buffer);
        widget_ = std::construct_at(ptr, id);
    }

    void Reset() {
        if (widget_) {
            std::destroy_at(widget_);
            widget_ = nullptr;
        }
    }

    ~WidgetSlot() {
        Reset();
    }

private:
    alignas(T) std::byte buffer[sizeof(T)];
    T* widget_ = nullptr;
};

class Widget {
public:
    explicit Widget(int id) : id_(id) {
        std::cout << "Construct " << id_ << '\n';
    }

    ~Widget() {
        std::cout << "Destroy " << id_ << '\n';
    }

    int Id() const {
        return id_;
    }

private:
    int id_;
};

int main() {
    WidgetSlot<Widget> slot;

    slot.Emplace(7);
    slot.Emplace(42);

    return 0;
}
