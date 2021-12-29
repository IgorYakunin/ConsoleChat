#include "Chat.h"
#include "Menu.h"
#include "Form.h"

int main()
{
	std::shared_ptr<Chat> chat{ new Chat };

	Menu main_menu{ menu_construction(chat) };

	while (chat->is_open()) {
		main_menu.input_processing();
	}

	return 0;
}