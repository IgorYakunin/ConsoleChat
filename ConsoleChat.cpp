#include "Chat.h"
#include "Menu.h"

int main()
{
	std::shared_ptr<Chat> chat{ new Chat };

	Start_menu menu{ chat };

	while (chat->is_open()) {
		menu.process();
	}

	return 0;
}