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



public:

	SortedSequence() {
		this->items = new ArraySequence<T>(); // пустое мн-во
	}

	SortedSequence(T* arr, int size) {
		sort(arr, arr + size);
		this->items = new ArraySequence<T>(arr, size); //копирует эл-ты из переданного массива
	}

	T Get(int index) const
	{
		return this->items->Get(index);
	}

	int GetLength() const
	{
		return this->items->GetLength();
	}

	void Add(T value)
	{
		this->items->Append(value);
		sort(items, items + size); //можно просто проверить сначала и если нет, добавить в нужное место
	}

	void RemoveAt(int index) {
		this->items->RemoveAt(index);
	}

	~SortedSequence() {
		delete this->items;
	}
};
