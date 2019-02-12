#pragma once
#ifndef VBFUCK_H
#define VBFUCK_H
#include <iostream>
#include <string>
#include "BFuck.h"
#include "console.h"
using std::cout;
using std::endl;

constexpr size_t VBFUCK_CELLS_CAP = 16;
using BFFather = BFuck<VBFUCK_CELLS_CAP>;
class VBFuck :public BFFather {
	colorflag oldcolor;
	colorflag inversecolor;
	void showUI() const;

	static constexpr int x = 4;
	static constexpr int y = 2;
public:
	VBFuck();
	~VBFuck() = default;
	void prev();
	//void next();
	void clear();
};

inline VBFuck::VBFuck()
	:oldcolor({ textcolor(), backcolor(), false }),
	inversecolor({backcolor(), textcolor(), false})
{
	// 调节窗口大小
	char mode[20];
	sprintf_s(mode, "mode %d,36", 6 + VBFUCK_CELLS_CAP * 5);
	system(mode);

	// 打印界面
	showUI();

}

inline void VBFuck::prev()
{
	BFFather::prev();
	gotoxy(x + pos * 6, y);
	
}

inline void VBFuck::showUI() const
{
	cout << "\n  ┌";
	// first line
	for (int i = 1; i < VBFUCK_CELLS_CAP; i++)
		cout << "────┬";
	cout << "────┐ \n  │ ";
	// second line
	cout << inversecolor << "  0" << oldcolor;
	for (int i = 1; i < VBFUCK_CELLS_CAP; i++)
		cout << "│    ";
	cout << "│ \n  └";
	// third line
	for (int i = 1; i < VBFUCK_CELLS_CAP; i++)
		cout << "────┴";
	cout << "────┘ \n";
}

inline void VBFuck::clear()
{
	BFFather::clear();
	system("cls");
	showUI();
}
#endif // VBFUCK_H