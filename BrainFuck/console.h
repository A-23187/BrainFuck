#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H
#include <Windows.h>
#include <iostream>
enum concol {
	black,		// ��ɫ
	dblue,		// ���� 'd' means 'dark'
	dgreen,		// ����
	daqua,		// ����
	dred,		// ����
	dpurple,	// ����
	dyellow,	// ����
	dwhite,		// ����
	gray,		// ��
	blue,		// ��
	green,		// ��
	aqua,		// ��
	red,		// ��
	purple,		// ��
	yellow,		// ��
	white,		// ��
	dcyan = 3,  // ����
	cyan = 11,	// ��
	dpink = 5, dmagenta = 5, // ����
	pink = 13, magenta = 13,  // ��
};

struct colorflag {
	concol textcol;
	concol backcol;
	bool protect;
};


#define std_con_out GetStdHandle(STD_OUTPUT_HANDLE)

// returns current text color
inline concol textcolor()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(std_con_out, &csbi);
	WORD a = csbi.wAttributes;
	return concol(a & 0xf);
}

// returns current background color
inline concol backcolor()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(std_con_out, &csbi);
	WORD a = csbi.wAttributes;
	return concol((a >> 4) & 0xf);
}

inline WORD makecolors(concol textcol, concol backcol)
{
	return (backcol << 4) | textcol;
}

inline void setcolor(concol textcol, concol backcol, bool protect)
{
	if (protect && textcol == backcol) { // doesn't let textcolor be the same as background color if true
		textcol = concol((textcol + 1) & 0xf);
	}
	SetConsoleTextAttribute(std_con_out, makecolors(textcol, backcol));
}

inline void setcolor(const colorflag& flag)
{
	setcolor(flag.textcol, flag.backcol, flag.protect);
}

inline std::ostream& operator<<(std::ostream& out, colorflag flag)
{
	out.flush();
	setcolor(flag);
	return out;
}

inline void gotoxy(int x, int y)
{
	SetConsoleCursorPosition(std_con_out, { (short)x, (short)y });
}
#endif // !CONSOLE_H