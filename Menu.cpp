#include "Menu.h"
#include "Chat.h"
#include "Form.h"
#include <iostream>
#include <algorithm>

using std::cout; using std::cin; using std::endl; using std::cerr;

char get_choice()
{//вспомогательная утилита для чтения в меню с защитой от случайных ошибок ввода
	char ch;
	cin >> ch;

	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return ch;
}

void Menu::display() const
{//показ вариантов выбора
	cout << '\n';
	for (const auto& line : operations_) {
		cout << line.key << ": " << line.description << endl;
	}
	cout << "\nEnter your choice: ";
}

void Menu::input_processing()
{//обработка ввода в меню
	bool restart{ true };
	while (restart) {
		display();
		char choice{ get_choice() };
		auto iter = std::find_if(operations_.cbegin(), operations_.cend(),
			[choice](const Line& line) {return choice == line.key; });
		if (iter == operations_.cend()) {
			cout << "Oops! Something went wrong. Let's try again\n";
		}
		else {
			try {
				auto user = iter->form->input_processing();
				if (user == nullptr)
					restart = false;
			}
			catch (const std::runtime_error& err) {
				cerr << err.what();
			}
		}
	}
}

std::vector<Line> menu_construction(std::shared_ptr<Chat> chat)
{
	std::vector<Line> operations;

	operations.push_back(Line{ '0', "Exit chat", std::make_shared<Exit_form>(Exit_form{ chat }) });
	operations.push_back(Line{ '1', "Login", std::make_shared<Login_form>(Login_form{ chat }) });
	operations.push_back(Line{ '2', "Sign up", std::make_shared<Sign_up_form>(Sign_up_form{ chat }) });

	return operations;
}

std::vector<Line> menu_construction(std::shared_ptr<Chat> chat, std::shared_ptr<User> user)
{
	std::vector<Line> operations;

	operations.push_back(Line{ '0', "Logout", std::make_shared<Logout_form>(Logout_form{ chat, user }) });
	operations.push_back(Line{ '1', "View chat", std::make_shared<View_form>(View_form{ chat, user }) });
	operations.push_back(Line{ '2', "Send message", std::make_shared<Message_form>(Message_form{ chat, user }) });

	return operations;
}