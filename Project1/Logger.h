#ifndef LOGGER_H
#define LOGGER_H
#include <string>
using namespace std;
class Logger
{
public:
	Logger();
	~Logger();
	void Info(string message);
	void Error(string message);
	void Debug(string message);
private:

};



#endif // !LOGGER_H
