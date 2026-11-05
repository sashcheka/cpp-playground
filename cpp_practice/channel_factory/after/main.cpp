#include <iostream>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <vector>

class Channel {
public:
    // virtual void Send(std::string_view message) const noexcept = 0;
    virtual void Send(std::string_view message) const noexcept {
        std::cout << "Base: " << message << "\n";
    }

    virtual ~Channel() = default;
};

class EmailChannel : public Channel {
public:
    void Send(std::string_view message) const noexcept override {
        std::cout << "Email: " << message << "\n";
    }
};

class SmsChannel : public Channel {
public:
    void Send(std::string_view message) const noexcept override {
        std::cout << "Sms: " << message << "\n";
    }
};

enum class ChannelType {
    Channel,
    EmailChannel,
    SmsChannel
};

std::unique_ptr<Channel> CreateUniqueChannel(ChannelType type) {
    if (type == ChannelType::EmailChannel) {
        return std::make_unique<EmailChannel>();
    } else if (type == ChannelType::SmsChannel) {
        return std::make_unique<SmsChannel>();
    } else {
        return std::make_unique<Channel>();
    }
    throw std::invalid_argument("Current ChannelType doesn't exist");
}

std::shared_ptr<Channel> CreateSharedChannel(ChannelType type) {
    if (type == ChannelType::EmailChannel) {
        return std::make_shared<EmailChannel>();
    } else if (type == ChannelType::SmsChannel) {
        return std::make_shared<SmsChannel>();
    } else {
        return std::make_shared<Channel>();
    }
    throw std::invalid_argument("Current ChannelType doesn't exist");
}

int main() {
    // std::unique_ptr<Channel> baseChannel = CreateUniqueChannel(ChannelType::Channel);
    // std::unique_ptr<Channel> emailChannel1 = CreateUniqueChannel(ChannelType::EmailChannel);
    // std::unique_ptr<Channel> smsChannel = CreateUniqueChannel(ChannelType::SmsChannel);
    // std::unique_ptr<Channel> emailChannel2 = CreateUniqueChannel(ChannelType::EmailChannel);

    // std::vector<std::unique_ptr<Channel>> channels;
    // channels.push_back(std::move(baseChannel));
    // channels.push_back(std::move(emailChannel1));
    // channels.push_back(std::move(smsChannel));
    // channels.push_back(std::move(emailChannel2));

    // for (const std::unique_ptr<Channel>& channel : channels) {
    //     channel->Send("Hello");
    // }

    std::shared_ptr<Channel> baseChannel = CreateSharedChannel(ChannelType::Channel);
    std::shared_ptr<Channel> emailChannel1 = CreateSharedChannel(ChannelType::EmailChannel);
    std::shared_ptr<Channel> smsChannel = CreateSharedChannel(ChannelType::SmsChannel);
    std::shared_ptr<Channel> emailChannel2 = CreateSharedChannel(ChannelType::EmailChannel);
    
    // std::vector<std::shared_ptr<Channel>> channels = {
    //     std::move(baseChannel), 
    //     std::move(emailChannel1), 
    //     std::move(smsChannel), 
    //     std::move(emailChannel2)
    // };

    std::vector<std::shared_ptr<Channel>> channels = {
        baseChannel, 
        emailChannel1, 
        smsChannel, 
        emailChannel2
    };

    for (const std::shared_ptr<Channel>& channel : channels) {
        channel->Send("Hello");
    }

    return 0;
}
