#pragma once
#ifndef FUCKER_H
#define FUCKER_H
#include <iostream>
#include <fstream>
#include <string>
#include "BFuck.h"
#include "VBFuck.h"

template <typename F> class FuckerTemplate;
template <typename F>
std::istream& operator>>(std::istream& in, FuckerTemplate<F>& fucker);
template <typename F>
std::ifstream& operator>>(std::ifstream& in, FuckerTemplate<F>& fucker);

template <typename F = BFuck<>>
class FuckerTemplate {
	std::string stmt;
	F bfuck;
	size_t which = 0;

	void action();
	void loop();
public:
	FuckerTemplate() = default;
	~FuckerTemplate() = default;
	void fuck();
	bool dead() const;
	operator bool() const;
	friend std::istream& operator>> <>(std::istream& in, FuckerTemplate<F>& fucker);
	friend std::ifstream& operator>> <>(std::ifstream& in, FuckerTemplate<F>& fucker);
};

// 执行一个动作，然后将伪指针which指向下一个动作的开始字符
template <typename F>
inline void FuckerTemplate<F>::action()
{
	char c = stmt[which];
	switch (c) {
	case '>': // 下一个
		bfuck.next();
		break;
	case '<': // 上一个
		bfuck.prev();
		break;
	case '+': // 当前元素自增
		++bfuck;
		break;
	case '-': // 当前元素自减
		--bfuck;
		break;
	case '.': // 输出
		std::cout << bfuck;
		break;
	case ',': // 输入
		std::cin >> bfuck;
		break;
	case '[': // 循环体开始
		loop();
		break;
	case ']': // 循环体结束
		break;
	default: // 注释
		break;
	}
	which++;
}

// 循环动作
template <typename F>
inline void FuckerTemplate<F>::loop()
{
	int t = ++which;
	while (bfuck) {
		while (stmt[which] != ']') {
			action();
		}
		which = t;
	}

	// 往下找到对应匹配的']'
	unsigned int tag = 1;
	while (tag) {
		if (stmt[which] == '[')
			tag++;
		else if (stmt[which] == ']')
			tag--;
		which++;
	}
	which--; // 上面循环结束后，which指向对应的']'的下一个字符，故将which--
}

// 解析入口
template <typename F>
inline void FuckerTemplate<F>::fuck()
{
	which = 0;
	while (which < stmt.size()) {
		action();
	}
	// 还原bfuck
	bfuck.clear();
}

// 用于在命令行交互模式中退出程序
template <typename F>
inline bool FuckerTemplate<F>::dead() const
{
	return stmt == "exit" || stmt == "quit" || stmt == "bye";
}

// 检查 [、] 是否匹配
template <typename F>
inline FuckerTemplate<F>::operator bool() const
{
	unsigned int tag = 0;
	for (char c : stmt) {
		if (c == '[') {
			tag++;
		}
		else if (c == ']') {
			if (!tag)
				return false;
			tag--;
		}
	}
	return !tag;
}

// 从标准输入读取代码
template <typename F>
inline std::istream& operator>>(std::istream& in, FuckerTemplate<F>& fucker)
{
	//in.clear();
	fucker.stmt.clear();

	std::string t;
	while (true) {
		std::getline(in, t);
		if (t.empty())
			continue;
		fucker.stmt += t;
		if (t.back() == '\\') //  line-continuation character
			fucker.stmt.pop_back();
		else
			break;
	}

	return in;
}

// 从文件读取代码
template <typename F>
inline std::ifstream& operator>>(std::ifstream& in, FuckerTemplate<F>& fucker)
{
	std::istreambuf_iterator<char> beg(in), end;
	fucker.stmt.assign(beg, end);
	return in;
}

// 
using Fucker = FuckerTemplate<>;
using VFucker = FuckerTemplate<VBFuck>;
#endif// !FUCKER_H