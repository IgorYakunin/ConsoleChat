#pragma once
#include <string>

class User
{
public:
	explicit User(const std::string& nickname, const std::string& login, const std::string& password)
		:nickname_{ nickname }, login_{ login }, password_{ password } {}
	User(const User&) = default;
	User& operator=(const User&) = delete;
	~User() = default;
	const std::string& nickname() const noexcept { return nickname_; }
	const std::string& login() const noexcept { return login_; }
	const std::string& password() const noexcept { return password_; }
private:
	std::string nickname_;
	std::string login_;
	std::string password_;
};