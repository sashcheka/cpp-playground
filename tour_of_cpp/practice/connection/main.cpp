#include <iostream>
#include <string_view>

enum class ConnectionState {
    Disconnected,
    Connecting,
    Connected
};

enum class ConnectionEvent {
    Start,
    Established,
    Reset
};

class Connection {
public:
    Connection() : state(ConnectionState::Disconnected) {}

    static std::string_view ToString(ConnectionState state) {
        switch (state) {
            case ConnectionState::Disconnected:
                return "Disconnected";
            case ConnectionState::Connecting:
                return "Connecting";
            case ConnectionState::Connected:
                return "Connected";
            default:
                return "Unknown";
        }
    }

    bool Start() {
        if (state == ConnectionState::Disconnected) {
            state = ConnectionState::Connecting;
            return true;
        }
        return false;
    }

    bool OnConnected() {
        if (state == ConnectionState::Connecting) {
            state = ConnectionState::Connected;
            return true;
        }
        return false;
    }

    void Reset() {
        state = ConnectionState::Disconnected;
    }

    ConnectionState State() const {
        return state;
    }

    bool Handle(ConnectionEvent event) {
        switch (event) {
            case (ConnectionEvent::Start):
                return Start();
            case (ConnectionEvent::Established):
                return OnConnected();
            case (ConnectionEvent::Reset):
                Reset();
                return true;
            default:
                return false;
        }
    }
private:
    ConnectionState state;
};

int main() {
    Connection c;

    std::cout << "Initial state: " << Connection::ToString(c.State()) << "\n";

    for (int i = 0; i < 2; i++) {
        if (c.Start()) {
            std::cout << "Start: " << Connection::ToString(c.State()) << "\n";
        } else {
            std::cout << "Couldn't start: " << Connection::ToString(c.State()) << "\n";
        }
    }

    for (int i = 0; i < 2; i++) {
        if (c.OnConnected()) {
            std::cout << "Connected: " << Connection::ToString(c.State()) << "\n";
        } else {
            std::cout << "Couldn't become connected: " << Connection::ToString(c.State()) << "\n";
        }
    }
    
    c.Reset();
    std::cout << "State after the reset: " << Connection::ToString(c.State()) << "\n";

    std::cout << "Test invalid connection state: " << Connection::ToString(static_cast<ConnectionState>(99)) << "\n";

    if (c.Handle(ConnectionEvent::Start)) {
        std::cout << "Handle: " << Connection::ToString(c.State()) << "\n";
    } else {
        std::cout << "Handle with invalid connection event: " << Connection::ToString(c.State()) << "\n";
    }

    if (c.Handle(ConnectionEvent::Established)) {
        std::cout << "Handle: " << Connection::ToString(c.State()) << "\n";
    } else {
        std::cout << "Handle with invalid connection event: " << Connection::ToString(c.State()) << "\n";
    }

    if (c.Handle(ConnectionEvent::Reset)) {
        std::cout << "Handle: " << Connection::ToString(c.State()) << "\n";
    } else {
        std::cout << "Handle with invalid connection event: " << Connection::ToString(c.State()) << "\n";
    }

    if (c.Handle(static_cast<ConnectionEvent>(99))) {
        std::cout << "Handle: " << Connection::ToString(c.State()) << "\n";
    } else {
        std::cout << "Handle with invalid connection event: " << "\n";
    }

    return 0;
}
