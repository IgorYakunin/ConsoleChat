#pragma once
#include <string>

class Message
{
public:
	Message(const std::string& to, const std::string& from, const std::string& text)
		: to_{ to }, from_{ from }, text_{ text } {}
	const std::string& to()   const noexcept { return to_; }
	const std::string& from() const noexcept { return from_; }
	const std::string& text() const noexcept { return text_; }
private:
	const std::string to_;
	const std::string from_;
	const std::string text_;
};