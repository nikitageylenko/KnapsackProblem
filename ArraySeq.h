#pragma once
#include "DynArray.h"
#include "Seq.h"


using namespace std;

template <class T>
class ArraySequence : public Sequence<T>
{
private:
	DynamicArray<T>* items;

public:

	ArraySequence() { //пустой список 
		int size = 0;
		try {
			this->items = new DynamicArray<T>(size);
		}
		catch (Exception& exception) {
			cout << exception.getError();
		}
	}

	ArraySequence(T* items, int count) { //копировать эл-ты из переданного массива
		try {
			this->items = new DynamicArray<T>(items, count);
		}
		catch (Exception& exception) {
			cout << exception.getError();
		}
	}

	ArraySequence(const ArraySequence<T>& items) { // копирующий конструктор
		try {
			this->items = new DynamicArray<T>();
			for (int i = 0; i < items.GetLength(); i++) {
				this->Append(items.Get(i));
			}
		}
		catch (Exception& exception) {
			cout << exception.getError();
		}
	}

	virtual int GetLength() const override { //получить длину списка
		return this->items->GetLength();
	}

	virtual T GetFirst() const override { //получить 1ый эл-т
		try {
			return this->items->Get(0);
		}
		catch (Exception& exception) {
			cout << exception.getError();
		}
	}

	virtual T GetLast() const override { //получить 2ой эл-т
		try {
			return this->items->Get(this->items->GetLength() - 1);
		}
		catch (Exception& exception) {
			cout << exception.getError();
		}
	};

	virtual T Get(int index) const override { //получить эл-т по индексу
		return this->items->Get(index);
	};

	virtual void Set(int index, T value) override { //получить эл-т по индексу
		try {
			this->items->Set(index, value);
		}
		catch (Exception& exception) {
			cout << exception.getError();
		}
	};

	virtual void Append(T value) override {
		this->items->Resize(this->GetLength() + 1);
		this->items->Set(this->GetLength() - 1, value);
	}

	virtual void Prepend(T value) override {
		this->items->Resize(this->GetLength() + 1);
		for (int i = this->GetLength() - 1; i > 0; i--) {
			this->items->Set(i, this->items->Get(i - 1));
		}
		this->items->Set(0, value);
	}

	virtual void InsertAt(T value, const int index) override {
		try {
			this->items->InsertAt(value, index);
		}
		catch (Exception& exception) {
			cout << exception.getError();
		}
	}

	virtual void Resize(int newSize) override {
		try {
			this->items->Resize(newSize);
		}
		catch (Exception& exception) {
			cout << exception.getError();
		}
	}

	virtual void RemoveAt(int index) override {
		try {
			this->items->RemoveAt(index);
		}
		catch (Exception& exception) {
			cout << exception.getError();
		}
	}

	virtual ~ArraySequence() {
		delete this->items;
	}
};
