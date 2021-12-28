#include "Chat.h"
#include <algorithm>
#include <string>
#include <stdexcept>

std::shared_ptr<User> Chat::find_user(const std::string& str, ID id) const
{
	std::vector<User>::const_iterator iter;
	if (id == ID::Login) {
		iter = std::find_if(users_.cbegin(), users_.cend(),
			[str](const User& user) { return user.login() == str; });
	}
	else {
		iter = std::find_if(users_.cbegin(), users_.cend(),
			[str](const User& user) { return user.nickname() == str; });
	}
	return iter == users_.cend() ? nullptr : std::make_shared<User>(*iter);
}