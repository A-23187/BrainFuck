// ���ӻ�ģʽ

#include "pch.h"
#ifdef VISUALIZER
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "console.h"
#include "Fucker.h"
using namespace std;

// ��ɫ����
inline colorflag fuckcolor(concol textcol)
{
	static concol backcol = backcolor();
	return { textcol, backcol, true };
}

// ������ ���� ���� �ȩ� �� ��
int main()
{
	// ���ô��ڱ���
	system("title Brain Fuck Visualizer");
	
	colorflag oldcol{ textcolor(), backcolor(), false };
	VFucker fucker;
	while (true) {
		cout << fuckcolor(cyan) << "\n  Fuck:\n  " << oldcol;
		cin >> fucker;
		cout << fuckcolor(blue) << "\n  Out :\n  " << oldcol;
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
	return 0;
}
#endif // VISUALIZER