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
	virtual std::shared_ptr<User> input_processing() const { return nullptr; }
protected:
	std::shared_ptr<Chat> chat_{ nullptr };
};

class Sign_up_form : public Form
{
public:
	Sign_up_form(std::shared_ptr<Chat> chat) : Form(chat) {}
	std::shared_ptr<User> input_processing() const override;
};

class Login_form: public Form
{
public:
	Login_form(std::shared_ptr<Chat> chat) : Form(chat) {}
	std::shared_ptr<User> input_processing() const override;
};

class Exit_form : public Form
{
public:
	Exit_form(std::shared_ptr<Chat> chat) : Form(chat) {}
	std::shared_ptr<User> input_processing() const override;
};

class Logout_form : public Form
{
public:
	Logout_form(std::shared_ptr<Chat> chat, std::shared_ptr<User> user) : Form(chat), user_{ user } {}
	std::shared_ptr<User> input_processing() const override;
private:
	std::shared_ptr<User> user_;
};

class View_form : public Form
{
public:
	View_form(std::shared_ptr<Chat> chat, std::shared_ptr<User> user) : Form(chat), user_{ user } {}
	std::shared_ptr<User> input_processing() const override;
private:
	std::shared_ptr<User> user_;
};

class Message_form : public Form
{
public:
	Message_form(std::shared_ptr<Chat> chat, std::shared_ptr<User> user) : Form(chat), user_{ user } {}
	std::shared_ptr<User> input_processing() const override;
private:
	std::shared_ptr<User> user_;
};