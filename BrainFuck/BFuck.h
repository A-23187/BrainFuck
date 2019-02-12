#pragma once
#ifndef BFUCK_H
#define BFUCK_H
#include <vector>
#include<iostream>

template <size_t cap> class BFuck;
template <size_t cap>
std::ostream& operator<<(std::ostream&, const BFuck<cap>&);
template <size_t cap>
std::istream& operator>>(std::istream&, BFuck<cap>&);

template <size_t cap = 30000>
class BFuck {
	uint8_t get() const;
	void set(uint8_t v);

protected:
	std::vector<uint8_t> cells;
	int pos = 0;

public:
	BFuck();
	~BFuck() = default;
	void prev();
	void next();
	BFuck& operator++();	// 前置++ 无论前置还是后置，都是返回 ++/-- 后的结果
	BFuck& operator--();	// 前置--
	BFuck& operator++(int);	// 后置++
	BFuck& operator--(int);	// 后置--
	operator bool() const;
	void clear();
	friend std::ostream& operator<< <>(std::ostream& out, const BFuck<cap>& bf);
	friend std::istream& operator>> <>(std::istream& in, BFuck<cap>& bf);
};


template <size_t cap>
inline BFuck<cap>::BFuck()
{
	cells.push_back(0);
}

template <size_t cap>
inline uint8_t BFuck<cap>::get() const
{
	return cells[pos];
}

template <size_t cap>
inline void BFuck<cap>::set(uint8_t v)
{
	cells[pos] = v;
}

template <size_t cap>
inline void BFuck<cap>::prev()
{
	if (!pos)
		pos = cells.size();
	pos--;
}

template <size_t cap>
inline void BFuck<cap>::next()
{
	pos++;
	if (pos == cells.size()) {
		if (pos < cap) {
			cells.push_back(0);
		}
		else {
			pos = 0;
		}
	}
}

template <size_t cap>
inline BFuck<cap>& BFuck<cap>::operator++()
{
	cells[pos]++;
	return *this;
}

template <size_t cap>
inline BFuck<cap>& BFuck<cap>::operator--()
{
	cells[pos]--;
	return *this;
}

template <size_t cap>
inline BFuck<cap>& BFuck<cap>::operator++(int)
{
	cells[pos]++;
	return *this;
}

template <size_t cap>
inline BFuck<cap>& BFuck<cap>::operator--(int)
{
	cells[pos]--;
	return *this;
}

template<size_t cap>
inline BFuck<cap>::operator bool() const
{
	return cells[pos];
}

template<size_t cap>
inline void BFuck<cap>::clear()
{
	for (uint8_t& cell : cells) {
		cell = 0;
	}
	pos = 0;
}

template<size_t cap>
inline std::ostream& operator<<(std::ostream& out, const BFuck<cap>& bf)
{
	out << bf.get();
	return out;
}

template <size_t cap>
inline std::istream& operator>>(std::istream& in, BFuck<cap>& bf)
{
	uint8_t v = (uint8_t)in.get();
	bf.set(v);
	return in;
}
#endif // !BFUCK_H