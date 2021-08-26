#pragma once
#include "Exception.h"


template <class T>
class LinkedList
{
private:
    struct element
    {
        T value;
        element* next;
    };

public:
    LinkedList();
    LinkedList(T* items, int count);
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();

    void Free();

    T GetFirst();
    T GetLast();
    T Get(int index);
    LinkedList<T>* GetSubList(int startIndex, int endIndex);
    int GetLength();


    void Append(const T& item);
    void Prepend(const T& item);
    void Set(const T& item, int index);
    void InsertAt(const T& item, int index);
    void DeleteAt(int index);
    LinkedList<T>* Concat(LinkedList<T>* list);

private:
    element* first;
    element* last;
    int length;
};



template <class T>
LinkedList<T>::LinkedList()
{
    first = nullptr;
    last = nullptr;
    length = 0;
}

template <class T>
LinkedList<T>::LinkedList(T* items, int count)
{
    first = nullptr;
    last = nullptr;
    length = 0;

    for (int i = 0; i < count; i++)
    {
        Append(items[i]);
    }
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
    first = nullptr;
    last = nullptr;
    length = 0;

    element* current = list.first;
    while (current != nullptr)
    {
        Append(current->value);
        current = current->next;
    }
}

template <class T>
LinkedList<T>::~LinkedList()
{
    Free();
}

template <class T>
void LinkedList<T>::Free()
{
    element* elmt = first;
    while (elmt != nullptr)
    {
        element* previous = elmt;
        elmt = elmt->next;
        delete(previous);
    }
}


template <class T>
T LinkedList<T>::GetFirst()
{
    if (first == nullptr)
    {
        throw Exception("IndexOutOfRange"); //IndexOutOfRangeException();
    }

    return first->value;
}

template <class T>
T LinkedList<T>::GetLast()
{
    if (last == nullptr)
    {
        throw Exception("IndexOutOfRange");
    }

    return last->value;
}

template <class T>
int LinkedList<T>::GetLength()
{
    return length;
}

template <class T>
T LinkedList<T>::Get(int index)
{
    if (index < 0 || index >= length)
    {
        throw Exception("IndexOutOfRange"); //IndexOutOfRangeException();
    }

    element* current = first;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current->value;
}

template <class T>
LinkedList<T>* LinkedList<T>::GetSubList(int startIndex, int endIndex)
{
    if (startIndex < 0 || startIndex > length ||
        endIndex < 0 || endIndex >= length || startIndex > endIndex)
    {
        throw Exception("IndexOutOfRange"); //IndexOutOfRangeException();
    }

    LinkedList<T>* result = new LinkedList<T>();

    element* current = first;
    for (int i = 0; i <= endIndex; i++)
    {
        if (i >= startIndex)
        {
            result->Append(current->value);
        }
        current = current->next;
    }

    return result;
}

template <class T>
void LinkedList<T>::Prepend(const T& item)
{
    element* elmt = new element;
    elmt->next = first;
    elmt->value = item;

    first = elmt;

    if (last == nullptr)
    {
        last = elmt;
    }

    length++;
}

template <class T>
void LinkedList<T>::Append(const T& item)
{
    element* elmt = new element;
    elmt->next = nullptr;
    elmt->value = item;

    if (first == nullptr)
    {
        first = elmt;
    }

    if (last != nullptr)
    {
        last->next = elmt;
    }
    last = elmt;

    length++;
}

template <class T>
void LinkedList<T>::Set(const T& item, int index)
{
    if (index < 0 || index > length)
    {
        throw Exception("IndexOutOfRange");// IndexOutOfRangeException();
    }

    if (index == 0)
    {
        first->value = item;
    }
    else
    {
        element* previous = first;
        for (int i = 0; i < index; i++)
        {
            previous = previous->next;
        }
        previous->value = item;
    }
}

template <class T>
void LinkedList<T>::InsertAt(const T& item, int index)
{
    if (index < 0 || index > length)
    {
        throw Exception("IndexOutOfRange"); //IndexOutOfRangeException();
    }

    element* elmt = new element;
    elmt->value = item;

    if (index == 0)
    {
        elmt->next = first;
        first = elmt;
    }
    else
    {
        element* previous = first;
        for (int i = 0; i < (index - 1); i++)
        {
            previous = previous->next;
        }
        elmt->next = previous->next;
        previous->next = elmt;
    }
    length++;
}

template <class T>
void LinkedList<T>::DeleteAt(int index)
{
    if (index < 0 || index >= length)
    {
        throw Exception("IndexOutOfRange"); //IndexOutOfRangeException();
    }

    if (index == 0)
    {
        element* p = first->next;
        delete(first);
        first = p;
    }
    else
    {
        element* previous = first;
        for (int i = 0; i < (index - 1); i++)
        {
            previous = previous->next;
        }

        if (previous->next != last)
        {
            element* p = previous->next;
            previous->next = (previous->next)->next;
            delete(p);
        }
        else
        {
            delete(previous->next);
            last = previous;
        }
    }
    length--;
}

template <class T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T>* list)
{
    LinkedList<T>* result = new LinkedList<T>(*this);

    element* current = list->first;
    while (current != nullptr)
    {
        result->Append(current->value);
        current = current->next;
    }

    return result;
}
