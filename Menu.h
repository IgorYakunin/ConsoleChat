#pragma once
#include "Chat.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

struct Line
{
	char key;
	std::string description;
};

class Menu
{
public:
	virtual ~Menu() = default;
	virtual void process() = 0;
	virtual void display() const;
protected:
	std::vector<Line> operations_;
};

class Start_menu : public Menu
{
public:
	Start_menu(std::shared_ptr<Chat> chat);
	void process() override;
private:
	std::shared_ptr<Chat> chat_;
	void exit();
	void login();
	void sign_up();
};

class User_menu : public Menu
{
public:
	User_menu(std::shared_ptr<Chat> chat, const User& user);
	void process() override;
	bool is_open() const { return user_.get(); }
private:
	std::shared_ptr<Chat> chat_;
	std::unique_ptr<User> user_;
	void logout();
	void view_chat();
	void send_message();
};