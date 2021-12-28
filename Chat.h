#pragma once
#include "User.h"
#include "Message.h"
#include <vector>
#include <string>
#include <memory>

enum class ID{Login, Nickname};

class Chat
{
public:
	Chat() { users_.push_back(User{ "ALL", "ALL", "" }); }
	~Chat() = default;
	bool is_open() const { return open_; }
	void close() { open_ = false; }
	void add_user(const User& user) { users_.push_back(user); }
	void add_message(const Message& message) { messages_.push_back(message); }
	std::shared_ptr<User> find_user(const std::string&, ID) const;
	const std::vector<Message>& get_message() const noexcept { return messages_; }
private:
	bool open_{ true };
	std::vector<User> users_;
	std::vector<Message> messages_;
};