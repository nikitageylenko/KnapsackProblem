#pragma once
#include <cmath>
#include <algorithm>
#include "ArraySeq.h"

using namespace std;

template <class T>
class SortedSequence
{
private:
	Sequence<T>* items;

	void QuickSort(int first, int last) {
		int f = first;
		int l = last;
		T middle = this->Get(round((f + l) / 2));
		while (f <= l)
		{
			while (this->Get(f) < middle) {
				f++;
			}
			while (this->Get(l) > middle) {
				l--;
			}
			if (f <= l) {
				T value = this->Get(f);
				this->Set(f, this->Get(l));
				this->Set(l, value);
				f++;
				l--;
			}
		}

		if (l > first) {
			QuickSort(first, l);
		}
		if (l < last) {
			QuickSort(f, last);
		}
	}

public:

	SortedSequence() {
		this->items = new ArraySequence<T>(); // пустое мн-во
	}

	SortedSequence(T* arr, int size) {
		QuickSort(0, size - 1);
		this->items = new ArraySequence<T>(arr, size); //копирует эл-ты из переданного массива
	}

	bool has(T value) {
		for (int i = 0; i < this->items->GetLength() - 1; i++) {
			if (value == this->items->Get(i))
				return true;
		}
	}

	T Get(int index) const
	{
		return this->items->Get(index);
	}

	int GetLength() const
	{
		return this->items->GetLength();
	}

	//void Append(T value)
	//{
	//	//проверка на аналогичный айтм
	//	this->items->Append(value);
	//}

	void Add(T value)
	{
		this->items->Append(value);
		QuickSort(0, items->GetLength() - 1);
	}

	void Set(int index, T value) {
		this->items->Set(index, value);
	}

	//void InsertAt(T value, const int index) { //вставляет эл-т в заданную позицию
	//	try {
	//		this->items->InsertAt(value, index);
	//	}
	//	catch (Exception& exception) {
	//		cout << exception.getError();
	//	}
	//}

	void RemoveAt(int index) {
		this->items->RemoveAt(index);
	}

	~SortedSequence() {
		delete this->items;
	}
};
