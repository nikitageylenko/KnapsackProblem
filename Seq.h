#pragma once
template <class T>
class Sequence
{
public:
	virtual int GetLength() const = 0;
	virtual T GetFirst() const = 0;
	virtual T GetLast() const = 0;
	virtual void Append(T value) = 0;
	virtual void Prepend(T value) = 0;
	virtual void InsertAt(T value, const int index) = 0;// при данном методе абстракт не работает разобраться
	virtual void RemoveAt(const int index) = 0;
	virtual T Get(const int i) const = 0;
	virtual void Set(int index, T val) = 0;
	virtual void Resize(int newSize) = 0;
	virtual ~Sequence() {}
}; 