#include "Menu.h"
#include "Chat.h"
#include "Form.h"
#include <iostream>
#include <algorithm>
#include <string>

using std::cout; using std::cin; using std::endl; using std::cerr;

void Menu::display() const
{
	cout << '\n';
	for (const auto& line : operations_) {
		cout << line.key << ": " << line.description << endl;
	}
	cout << "\nEnter your choice: ";
}
char get_choice(std::istream& is)
{
	char ch;
	is >> ch;
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return ch;
}
void write_text(std::string& text)
{
	cout << "Type you message: ";
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
{
	bool restart = true;
	do {
		display();
		char choice{ get_choice(cin) };
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
{
	chat_->close();
}
void Start_menu::login()
{
	Login_form login_form{ chat_ };
	auto user{ login_form.input() };

	User_menu user_menu{ chat_, *user };

	while (user_menu.is_open()) {
		user_menu.process();
	}
}
void Start_menu::sign_up()
{
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
{
	bool restart = true;
	do {
		display();
		char choice{ get_choice(cin) };
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
{
	user_.release();
}
void User_menu::view_chat()
{
	cout << "\nAll messages for you up to now:\n";
	for (const auto& message : chat_->get_message()) {
		if (message.to() == user_->nickname() or message.to() == "ALL")
			cout << "from: " << message.from() << " ~ " << message.text() << '\n';
	}
}
void User_menu::send_message()
{
	Message_form message_form{ chat_ };
	auto user{ message_form.input() };

	std::string text;
	write_text(text);

	Message message{ user->nickname(), user_->nickname(), text };
	chat_->add_message(message);
}