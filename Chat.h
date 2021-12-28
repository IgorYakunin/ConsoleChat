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
	Chat() { users_.push_back(User{ "ALL", "ALL", "" }); }//добавл€ем фиктивного пользовател€ дл€ общей рассылки
	~Chat() = default;
	bool is_open() const noexcept { return open_; }
	void close() noexcept { open_ = false; }
	void add_user(const User& user) { users_.push_back(user); }
	void add_message(const Message& message) { messages_.push_back(message); }
	std::shared_ptr<User> find_user(const std::string&, ID) const;
	const std::vector<Message>& get_message() const noexcept { return messages_; }
private:
	bool open_{ true };//флаг состо€ни€ чата
	std::vector<User> users_;//контейнер дл€ хранени€ пользовательских данных (на территории –‘)
	std::vector<Message> messages_;//почтовый €щик
};