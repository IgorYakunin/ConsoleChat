#include "Form.h"
#include "User.h"
#include "Menu.h"
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

void write_text(std::string& text)
{//вспомогательная утилита для чтения многострочного сообщения
	cout << "Type your message (Enter and Ctrl+Z to send): ";
	std::string line;
	while (cin) {
		getline(cin, line, '\n');
		text += line;
	}
	cin.clear();
}

std::shared_ptr<User> Sign_up_form::input_processing() const
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

std::shared_ptr<User> Login_form::input_processing() const
{//ввод и проверка данных пользователя
	cout << endl;

	auto login{ fill_in_field("Enter your login: ") };
	if (login == "ALL") {
		throw std::runtime_error("\nThink twice about it!\n");
	}

	auto user{ chat_->find_user(login, ID::Login) };
	if (user == nullptr) {
		throw std::runtime_error("\nSorry! I don't know you, buddy!\n");
	}

	auto password{ fill_in_field("Enter your password: ") };
	if (user->password() != password) {
		throw std::runtime_error("\nWrong password\n");
	}

	user->activate();

	User_menu user_menu{ menu_construction(chat_, user), user };
	//читаем и пишем сообщения пока не надоест
	while (user_menu.is_user_actvie()) {
		user_menu.input_processing();
	}
	return user;
}

std::shared_ptr<User> Message_form::input_processing() const
{//ввод и проверка данных адресата для отправки сообщения
	cout << "\nUse nickname ALL to inform every user.\n";

	auto nickname{ fill_in_field("To (nickname): ") };
	auto user{ chat_->find_user(nickname, ID::Nickname) };
	if (user == nullptr)
		throw std::runtime_error("\nThere aren't user with such a nick.\n");

	std::string text;
	write_text(text);

	Message message{ user->nickname(), user_->nickname(), text };
	chat_->add_message(message);

	return user_;
}

std::shared_ptr<User> View_form::input_processing() const
{//просмотр полученных сообщений
	cout << "\nHere are messages for you up to now:\n";
	for (const auto& message : chat_->get_message()) {
		if (message.to() == user_->nickname()
			or (message.to() == "ALL" and message.from() != user_->nickname())) {
			cout << "from: " << message.from() << " ~ " << message.text() << '\n';
		}
		else if (message.from() == user_->nickname()) {
			cout << "\tto: " << message.to() << " ~ " << message.text() << '\n';
		}
	}
	return user_;
}

std::shared_ptr<User> Exit_form::input_processing() const
{
	chat_->close();
	return nullptr;
}

std::shared_ptr<User> Logout_form::input_processing() const
{
	user_->quit();
	return nullptr;
}