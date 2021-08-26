	#pragma once

#include "LinkedList.h"
#include "Seq.h"

template <class T>
class LinkedListSequence : public Sequence<T>
{
private:
    LinkedList<T>* list;

public:
    LinkedListSequence()
    {
        this->list = new LinkedList<T>();
    }

    LinkedListSequence(T* array, int count)
    {
        this->list = new LinkedList<T>(array, count);
    }

    LinkedListSequence(const LinkedList<T>& list)
    {
        this->list = new LinkedList<T>(list);
    }

    LinkedListSequence(const LinkedListSequence<T>& sequence)
    {
        this->list = new LinkedList<T>(*sequence.list);
    }

    ~LinkedListSequence()
    {
        Free();
    }

    void Free()
    {
        if (this->list != nullptr)
        {
            delete(this->list);
            this->list = nullptr;
        }
    }

    T GetFirst()
    {
        return this->list->GetFirst();
    }

    T GetLast()
    {
        return this->list->GetLast();
    }

    T Get(int index)
    {
        return this->list->Get(index);
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex)
    {
        LinkedList<T>* plist = this->list->GetSubList(startIndex, endIndex);//TODO SMART POINTER
        LinkedListSequence<T>* result = new LinkedListSequence<T>(*plist);
        plist->~LinkedList();
        return result;
    }

    int GetLength()
    {
        return this->list->GetLength();
    }

    void Append(const T& item)
    {
        return this->list->Append(item);
    }

    void Prepend(const T& item)
    {
        return this->list->Prepend(item);
    }

    void Set(const T& item, int index)
    {
        this->list->Set(item, index);
    }

    void InsertAt(const T& item, int index)
    {
        this->list->InsertAt(item, index);
    }

    void RemoveAt(int index)
    {
        this->list->DeleteAt(index);
    }

    Sequence<T>* Concat(Sequence<T>* sequence)
    {
        LinkedList<T> lst(*(this->list));

        for (int i = 0; i < sequence->GetLength(); i++)
        {
            lst.Append(sequence->Get(i));
        }

        LinkedListSequence<T>* result = new LinkedListSequence<T>(lst);
        return result;
    }
};