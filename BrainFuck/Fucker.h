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

// ִ��һ��������Ȼ��αָ��whichָ����һ�������Ŀ�ʼ�ַ�
template <typename F>
inline void FuckerTemplate<F>::action()
{
	char c = stmt[which];
	switch (c) {
	case '>': // ��һ��
		bfuck.next();
		break;
	case '<': // ��һ��
		bfuck.prev();
		break;
	case '+': // ��ǰԪ������
		++bfuck;
		break;
	case '-': // ��ǰԪ���Լ�
		--bfuck;
		break;
	case '.': // ���
		std::cout << bfuck;
		break;
	case ',': // ����
		std::cin >> bfuck;
		break;
	case '[': // ѭ���忪ʼ
		loop();
		break;
	case ']': // ѭ�������
		break;
	default: // ע��
		break;
	}
	which++;
}

// ѭ������
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

	// �����ҵ���Ӧƥ���']'
	unsigned int tag = 1;
	while (tag) {
		if (stmt[which] == '[')
			tag++;
		else if (stmt[which] == ']')
			tag--;
		which++;
	}
	which--; // ����ѭ��������whichָ���Ӧ��']'����һ���ַ����ʽ�which--
}

// �������
template <typename F>
inline void FuckerTemplate<F>::fuck()
{
	which = 0;
	while (which < stmt.size()) {
		action();
	}
	// ��ԭbfuck
	bfuck.clear();
}

// �����������н���ģʽ���˳�����
template <typename F>
inline bool FuckerTemplate<F>::dead() const
{
	return stmt == "exit" || stmt == "quit" || stmt == "bye";
}

// ��� [��] �Ƿ�ƥ��
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

// �ӱ�׼�����ȡ����
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

// ���ļ���ȡ����
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