// 基本模式 (命令行模式、脚本模式)

#include "pch.h"
#ifdef BASE
#include <iostream>
#include <fstream>
#include "Fucker.h"
#include "console.h"
using namespace std;

// 颜色控制
inline colorflag fuckcolor(concol textcol)
{
	static concol backcol = backcolor();
	return { textcol, backcol, true };
}

// 命令行交互模式
void cmd()
{
	colorflag oldflag{ textcolor(), backcolor(), false };

	Fucker fucker;
	cout << "Brian Fuck" << endl;
	while (true) {
		cout << fuckcolor(cyan) << "\nFuck:\n" << oldflag;
		cin >> fucker;
		cout << fuckcolor(blue) << "\nOut :\n" << oldflag;
		if (fucker.dead()) {
			cout << "Bye.";
			break;
		}
		if (fucker)
			fucker.fuck();
		else
			cerr << fuckcolor(red) << "Unclosed bracket.";
		cout << endl;
	}
}

// 脚本模式
void script(const char* file)
{
	ifstream fin(file);
	if (!fin) {
		cerr << fuckcolor(red) << "No such script file.\n";
		return;
	}
	Fucker fucker;
	fin >> fucker;
	if (fucker)
		fucker.fuck();
	else
		cerr << fuckcolor(red) << "Unclosed bracket.\n";
	fin.close();
}

int main(int argc, char** argv)
{
	if (argc == 1) { // 不带参数，则为命令行模式
		cmd();
	}
	else { // 脚本模式
		script(argv[1]);
	}
	return 0;
}
#endif // BASE