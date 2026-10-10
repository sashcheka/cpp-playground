#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include <stdexcept>

struct User {
    int id;
    std::string name;
    bool active;
};

class UserRegistry {
public:
    void AddUser(int id, const std::string& name) {
        auto it = std::find_if(
            users_.begin(),
            users_.end(),
            [&id](const User& user) {
                return user.id == id;
            }
        );

        if (it != users_.end()) {
            throw std::logic_error("User already exists.");
        }

        users_.push_back(User{id, name, true});
        // or for C++20 and later versions
        // users_.emplace_back(id, name, true);
    }

    std::optional<User> FindUser(int id) const {
        auto it = std::find_if(
            users_.begin(),
            users_.end(),
            [id](const User& user) {
                return user.id == id;
            }
        );

        if (it != users_.end()) {
            return *it;
        }

        return std::nullopt;
    }

    void RenameUser(int id, const std::string& new_name) {
        auto it = std::find_if(
            users_.begin(),
            users_.end(),
            [&id](const User& user) {
                return user.id == id;
            }
        );

        if (it != users_.end()) {
            it->name = new_name;
        }
    }

    void RemoveInactive() {
        users_.erase(
            std::remove_if(
                users_.begin(),
                users_.end(),
                [](const User& user) {
                    return !user.active;
                }
            ),
            users_.end()
        );
    }

    std::optional<User> GetFirstUser() const {
        if (users_.empty()) {
            return std::nullopt;
        }

        return users_.front();
    }

private:
    std::vector<User> users_;
};
