#include <string>
#include <vector>
#include <optional>
#include <algorithm>

struct User {
    int id;
    std::string name;
    bool active;
};

class UserRegistry {
public:
    void AddUser(int id, const std::string& name) {
        User user{id, name, true};
        users_.push_back(user);
    }

    const User& FindUser(int id) const {
        for (const auto& user : users_) {
            if (user.id == id) {
                return user;
            }
        }

        return User{-1, "Unknown", false};
    }

    void RenameUser(int id, const std::string& new_name) {
        auto it = std::find_if(
            users_.begin(),
            users_.end(),
            [id](const User& user) {
                return user.id == id;
            }
        );

        if (it != users_.end()) {
            User user = *it;
            user.name = new_name;
        }
    }

    void RemoveInactive() {
        for (auto it = users_.begin(); it != users_.end(); ++it) {
            if (!it->active) {
                users_.erase(it);
            }
        }
    }

    const User* GetFirstUser() const {
        if (users_.empty()) {
            return nullptr;
        }

        return &users_.front();
    }

private:
    std::vector<User> users_;
};