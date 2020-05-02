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

	static void showDefault(void);

	void show(void);
	void unfocus(void);
	
	void setCursor(short x, short y);
	bool getFocus(void);
	void getCursor(short* x, short* y);
	void getSize(short* x, short* y);
	void getStart(short* x, short* y);
};

#endif