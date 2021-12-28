#pragma once
#include "Chat.h"
#include "User.h"
#include <memory>
#include <string>

class Form
{
public:
	Form(std::shared_ptr<Chat> chat) : chat_{ chat } {}
	virtual ~Form() = default;
	virtual std::shared_ptr<User> input() const = 0;
protected:
	std::shared_ptr<Chat> chat_;
};

class Sign_up_form : public Form
{
public:
	Sign_up_form(std::shared_ptr<Chat> chat) : Form(chat) {}
	std::shared_ptr<User> input() const override;
};

class Login_form: public Form
{
public:
	Login_form(std::shared_ptr<Chat> chat) : Form(chat) {}
	std::shared_ptr<User> input() const override;
};

class Message_form : public Form
{
public:
	Message_form(std::shared_ptr<Chat> chat) : Form(chat) {}
	std::shared_ptr<User> input() const override;
};