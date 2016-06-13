#include "Exception.h"
#include <fstream>
#include<ctime>
#include <string>

GF::Core::Exception::Exception(std::string message, int code) :std::exception(message.c_str(), code) {
	code_ = code;
	message_ = message;
}

GF::Core::Exception::~Exception()
{
	std::ofstream file;
	file.open("ErrorLogs.log", std::ios::out|std::ios::app);
	if(!file.good())
		file.open("ErrorLogs.log", std::ios::out);
	//TODO
	if (file.good()) {
		time_t now = time(0);
		tm time = *localtime(&now);
		file << "\n[" << time.tm_year + 1900 << "-"<< (time.tm_mon<10?"0":"")<< time.tm_mon << "-" << (time.tm_mday<10 ? "0" : "") << time.tm_mday << " " << (time.tm_hour<10 ? "0" : "") << time.tm_hour <<
			":" << (time.tm_min<10 ? "0" : "") << time.tm_min << ":" << (time.tm_sec<10 ? "0" : "") << time.tm_sec << "] " << message_ << " Code: " << code_;
		file.close();
	}
}

std::string GF::Core::Exception::getMessage()
{
	return message_;
}

int GF::Core::Exception::getCode()
{
	return code_;
}
