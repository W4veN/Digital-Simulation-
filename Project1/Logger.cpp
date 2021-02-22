#include "logger.h"
#include <iostream>
using namespace std;
Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Info(string message)
{
	cout << "[info]: " << message <<endl;
}

void Logger::Error(std::string message)
{
	cout << "[Error]: " << message << endl;
}

void Logger::Debug(std::string message)
{
	cout << "[Debug]: " << message << endl;
}