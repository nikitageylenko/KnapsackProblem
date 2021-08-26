#pragma once
#include <string>
#include "Exception.h"
#include <iostream>


template <class T>
class DynamicArray
{
private:
	T* items;
	bool* itemsCheck; // для проверки на мусор
	int size;
	int ArraySize; // для копир конструктора

public:

	DynamicArray(int size)
	{
		if (size < 0)
			throw Exception("IndexOutOfRage");
		this->ArraySize = size;
		this->items = new T[size]; //выделение памяти под массив
		this->itemsCheck = new bool[size];
		for (int i = 0; i < size; i++)
			this->itemsCheck[i] = false;
		this->size = size;
	}

	DynamicArray(T* items, int size) { //копировать эл-ты из переданного массива
		if (size < 0)
			throw Exception("");
		this->ArraySize = size;
		this->size = size;
		this->items = new T[size]; //выделение памяти
		this->itemsCheck = new bool[size];
		for (int i = 0; i < size; i++) {
			this->itemsCheck[i] = true;
			this->items[i] = items[i]; //передача значений в новый массив 
		}
	}

	DynamicArray(const DynamicArray<T>& array) {
		this->ArraySize = array.ArraySize;
		this->size = new int[array.ArraySize];
		this->items = new T[this->size];
		this->itemsCheck = new bool[this->size];
		for (int i = 0; i < array.ArraySize; i++) {
			if (array.GetitemsCheck(i)) {
				this->items[i] = array.items[i];
				this->itemsCheck[i] = true;
			}
			else
				this->itemsCheck[i] = false;
		}
	}

	T Get(int index) const {
		if (index < 0 || index >= this->size)//|| !this->itemsCheck[index] || !this->itemsCheck[index]
			throw  Exception("");
		return this->items[index];
	}

	int GetLength() { //получить размер массива
		return this->size;
	}

	void Set(int index, T value) //задать эл-т по индексу
	{
		if (index < 0 || index >= this->size)
			throw  Exception("IndexOutOfRange");
		this->items[index] = value;
		this->itemsCheck[index] = true;
	}

	void Resize(int newSize) { //изм размер массива поменять так, чтобы только последние сохранялись
		if (newSize < this->size) { //уменьшается
			this->size = newSize;
			T* temp1 = new T[newSize];
			bool* newitemsCheck1 = new bool[newSize];
			for (int i = 0; i < newSize; i++) {
				if (this->itemsCheck[i]) {
					temp1[i] = this->items[i];
					newitemsCheck1[i] = true;
				}
				else {
					newitemsCheck1[i] = false;
				}
			}
			delete[] this->items;
			delete[] this->itemsCheck;
			this->items = temp1;
			this->itemsCheck = newitemsCheck1;
			delete[] temp1;
			delete[] newitemsCheck1;
		}
		else if (newSize > this->size) {
			this->size = newSize;
			T* temp = new T[newSize];
			bool* newitemsCheck = new bool[newSize];
			for (int i = 0; i < this->size; i++) {
				if (this->itemsCheck[i]) {
					temp[i] = this->items[i];
					newitemsCheck[i] = true;
				}
				else {
					newitemsCheck[i] = false;
				}
			}
			for (int i = this->size; i < newSize; i++) {
				newitemsCheck[i] = false; // здесь мусор
			}
			delete[] this->items;
			delete[] this->itemsCheck;
			this->items = temp;
			this->itemsCheck = newitemsCheck;
		}
	}

	void InsertAt(T value, int index) { //вставить в
		if (index < 0 || index > this->size - 1)
			throw  Exception("IndexOutOfRange");
		T* temp = new T[this->size + 1];
		bool* newitemsCheck = new bool[this->size + 1];
		for (int i = 0; i < index; i++) {
			temp[i] = this->items[i];
			newitemsCheck[i] = this->itemsCheck[i];
		}
		temp[index] = value;
		for (int i = index + 1; i < this->size + 1; i++) {
			temp[i] = this->items[i - 1];
			newitemsCheck[i] = this->itemsCheck[i];
		}
		delete[] this->items;
		delete[] this->itemsCheck;
		this->items = temp;
		this->itemsCheck = newitemsCheck;
		delete[] temp;
		delete[] newitemsCheck;
	}

	void RemoveAt(const int index) {
		if (index < 0 || index > this->size - 1)
			throw  Exception("IndexOutOfRangre");
		T* newItems = new T[size - 1];
		bool* newItemsCheck = new bool[size - 1];
		for (int i = 0; i < index; i++) {
			newItems[i] = this->Get(i);
			newItemsCheck[i] = this->itemsCheck[i];
		}
		for (int i = index + 1; i < size; i++) {
			newItems[i - 1] = this->Get(i);
			newItemsCheck[i - 1] = this->itemsCheck[i];
		}
		this->size = this->size - 1;
		delete[] this->items;
		delete[] this->itemsCheck;
		this->items = newItems;
		this->itemsCheck = newItemsCheck;
		this->size--;
		delete[] newItems;
		delete[]  newItemsCheck;
	}

	bool GetitemsCheck(int index) { //получить itemsCheck
		return this->itemsCheck[index];
	}

	~DynamicArray() {
		delete[] this->items;
		delete[] this->itemsCheck;
	}
};
