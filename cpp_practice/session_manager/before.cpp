#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

class SessionManager;

struct Session {
    std::string id;
    std::shared_ptr<SessionManager> manager;

    void Ping() const {
        std::cout << "Session: " << id << '\n';
    }

    ~Session() {
        std::cout << "Session destroyed: " << id << '\n';
    }
};

class SessionManager
    : public std::enable_shared_from_this<SessionManager> {

public:
    void AddSession(const std::string& id) {
        auto session = std::make_shared<Session>();

        session->id = id;
        session->manager = shared_from_this();

        sessions_[id] = std::move(session);
    }

    const Session* FindSession(const std::string& id) const {
        auto it = sessions_.find(id);

        if (it == sessions_.end()) {
            return nullptr;
        }

        return it->second.get();
    }

    void RemoveSession(const std::string& id) {
        const Session* session = FindSession(id);

        sessions_.erase(id);

        if (session) {
            session->Ping();
        }
    }

    std::size_t GetSessionCount() const {
        return sessions_.size();
    }

private:
    std::unordered_map<
        std::string,
        std::shared_ptr<Session>
    > sessions_;
};