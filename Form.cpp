#include "Form.h"
#include "User.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>

using std::cout; using std::cin; using std::endl;
using std::string;

string fill_in_field(const char* request)
{//улитита для заполнения поля в форме и защиты от ошибки при вводе
	cout << request;

	string field;
	cin >> field;

	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return field;
}

std::shared_ptr<User> Sign_up_form::input() const
{//ввод данных, проверка и регистрация нового пользователя
	cout << endl;

	auto nickname{ fill_in_field("Enter your nickname: ") };
	if (chat_->find_user(nickname, ID::Nickname)) {
		throw std::runtime_error("This nickname is already in use.\n");
	}
	auto login{ fill_in_field("Enter your login: ") };
	if (chat_->find_user(login, ID::Login)) {
		throw std::runtime_error("This login is already in use.\n");
	}
	auto password{ fill_in_field("Enter your password: ") };

	chat_->add_user(User{ nickname, login, password });

	return nullptr;
}
std::shared_ptr<User> Login_form::input() const
{//ввод и проверка данных пользователя
	cout << endl;

	auto login{ fill_in_field("Enter your login: ") };
	if (login == "ALL") {
	throw std::runtime_error("Think twice about it!\n");
	}
	auto user{ chat_->find_user(login, ID::Login) };
	if (user == nullptr) {
		throw std::runtime_error("Sorry! I don't know you, buddy!\n");
	}
	auto password{ fill_in_field("Enter your password: ") };
	if (user->password() != password) {
		throw std::runtime_error("Wrong password\n");
	}
	return user;
}
std::shared_ptr<User> Message_form::input() const
{//ввод и проверка данных адресата для отправки сообщения
	cout << "\nUse nickname ALL to inform every user.\n";

	auto nickname{ fill_in_field("To (nickname): ") };
	auto user{ chat_->find_user(nickname, ID::Nickname) };
	if (user == nullptr)
		throw std::runtime_error("There aren't user with such a nick.\n");

	return user;
}