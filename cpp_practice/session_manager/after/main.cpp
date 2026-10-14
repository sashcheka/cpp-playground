#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <stdexcept>

class SessionManager;

struct Session {
    std::string id;
    std::weak_ptr<SessionManager> manager;

    void Ping() const {
        std::cout << "Session: " << id << '\n';
    }

    ~Session() {
        std::cout << "Session destroyed: " << id << '\n';
    }
};

class SessionManager : public std::enable_shared_from_this<SessionManager> {
public:
    void AddSession(const std::string& id) {
        if (sessions_.find(id) != sessions_.end()) {
            throw std::logic_error("Session already exists.");
        }

        auto session = std::make_shared<Session>();

        session->id = id;
        session->manager = shared_from_this();

        sessions_[id] = std::move(session);
    }

    std::shared_ptr<const Session> FindSession(const std::string& id) const {
        auto it = sessions_.find(id);

        if (it == sessions_.end()) {
            return nullptr;
        }

        return it->second;
    }

    void RemoveSession(const std::string& id) {
        std::shared_ptr<const Session> session = FindSession(id);

        sessions_.erase(id);

        if (session) {
            session->Ping();
        }
    }

    std::size_t GetSessionCount() const {
        return sessions_.size();
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Session>> sessions_;
};

int main() {
    std::shared_ptr<SessionManager> manager = std::make_shared<SessionManager>();

    manager->AddSession("abc123");
    manager->AddSession("xyz456");

    std::shared_ptr<const Session> session = manager->FindSession("abc123");

    if (session) {
        session->Ping();
    }

    manager->RemoveSession("abc123");

    std::cout << manager->GetSessionCount() << '\n';

    return 0;
}