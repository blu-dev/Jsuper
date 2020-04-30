#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <conio.h>
#include <windows.h>

struct pConsole;
class Console {
private:
	pConsole* mData;
public:
	Console(void);
	Console(const Console&) = delete;
	Console(Console&&) = delete;

	~Console(void);

	void setPosition(short x, short y);
	void getPosition(short& x, short& y);
};

#endif