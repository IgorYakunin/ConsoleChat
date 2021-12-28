#include "Menu.h"
#include "Chat.h"
#include "Form.h"
#include <iostream>
#include <algorithm>
#include <string>

using std::cout; using std::cin; using std::endl; using std::cerr;

void Menu::display() const
{//показ вариантов выбора
	cout << '\n';
	for (const auto& line : operations_) {
		cout << line.key << ": " << line.description << endl;
	}
	cout << "\nEnter your choice: ";
}
char get_choice()
{//вспомогательная утилита для чтения в меню с защитой от случайных ошибок ввода
	char ch;
	cin >> ch;

	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return ch;
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
Start_menu::Start_menu(std::shared_ptr<Chat> chat) : chat_{ chat }
{
	operations_.push_back(Line{ '0', "Exit chat" });
	operations_.push_back(Line{ '1', "Login" });
	operations_.push_back(Line{ '2', "Sign up" });
}
void Start_menu::process()
{//обработка ввода в стартовом меню
	bool restart = true;
	do {
		display();
		char choice{ get_choice() };
		switch (choice) {
		case '0':
			exit();
			restart = false;
			break;
		case '1':
			try {
				login();
			}
			catch (const std::runtime_error& e) {
				cerr << e.what();
			}
			break;
		case '2':
			try {
				sign_up();
				cout << "Registration was successful. Congratulations!\n";
			}
			catch (const std::runtime_error& e) {
				cerr << e.what();
			}
			break;
		default:
			cout << "Oops! Something went wrong. Let's try again\n";
		}
	} while (restart);
}
void Start_menu::exit()
{//выход
	chat_->close();
}
void Start_menu::login()
{//заолняем входную форму
	Login_form login_form{ chat_ };
	auto user{ login_form.input() };
//если все проходит успешно, вызываем пользовательское меню
	User_menu user_menu{ chat_, *user };
//читаем и пишем сообщения пока не надоест
	while (user_menu.is_open()) {
		user_menu.process();
	}
}
void Start_menu::sign_up()
{//вызов регистрационной формы для заполнения
	Sign_up_form sign_up_form{ chat_ };
	sign_up_form.input();
}
User_menu::User_menu(std::shared_ptr<Chat> chat, const User& user)
	: chat_{ chat }, user_{ std::make_unique<User>(user) }
{
	operations_.push_back(Line{ '0', "Logout" });
	operations_.push_back(Line{ '1', "View chat" });
	operations_.push_back(Line{ '2', "Send message" });
}
void User_menu::process()
{//обработка пользовательского выбора
	bool restart = true;
	do {
		display();
		char choice{ get_choice() };
		switch (choice) {
		case '0':
			logout();
			restart = false;
			break;
		case '1':
			view_chat();
			break;
		case '2':
			send_message();
			break;
		default:
			cout << "Oops! Something went wrong. Let's try again\n";
		}
	} while (restart);
}
void User_menu::logout()
{//выход из пользовательского меню
	user_.release();
}
void User_menu::view_chat()
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
}
void User_menu::send_message()
{//запись сообщения
	Message_form message_form{ chat_ };
	auto user{ message_form.input() };

	std::string text;
	write_text(text);

	Message message{ user->nickname(), user_->nickname(), text };
	chat_->add_message(message);
}