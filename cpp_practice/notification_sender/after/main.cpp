#include <iostream>
#include <string>

class NotificationSender {
public:
    virtual void Send(const std::string& recipient, const std::string& message) const {
        std::cout << "Notification to " << recipient << ": " << message << '\n';
    }
};

class EmailSender : public NotificationSender {
public:
    void Send(const std::string& recipient, const std::string& message) const override {
        std::cout << "Email to " << recipient << ": " << message << '\n';
    }
};

class SmsSender : public NotificationSender {
public:
    void Send(const std::string& recipient, const std::string& message) const override {
        std::cout << "SMS to " << recipient << ": " << message << '\n';
    }
};

void Notify(const NotificationSender& sender, const std::string& recipient, const std::string& message) {
    sender.Send(recipient, message);
}

int main() {
    EmailSender email;
    SmsSender sms;

    Notify(email, "alice@example.com", "Welcome!");
    Notify(sms, "+1234567890", "Your code: 1234");

    return 0;
}
