#pragma once
#include "Chat.h"
#include "Form.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

struct Line
{//строка в меню
	char key;
	std::string description;
	std::shared_ptr<Form> form;
};

class Menu
{
public:
	Menu(const std::vector<Line>& operations) : operations_{ operations } {}
	void display() const;
	void input_processing();
protected:
	std::vector<Line> operations_;
};

class User_menu : public Menu
{
public:
	User_menu(const std::vector<Line>& operations, std::shared_ptr<User> user)
		: Menu{ operations }, user_{ user } {}
	bool is_user_actvie() const { return user_->is_active(); }
private:
	std::shared_ptr<User> user_;
};

std::vector<Line> menu_construction(std::shared_ptr<Chat> chat);
std::vector<Line> menu_construction(std::shared_ptr<Chat> chat, std::shared_ptr<User> user);