#pragma once

#include "Seq.h"
#include "LinkedListSequence.h"

template <class T>
class Queue
{
private:
    Sequence<T>* sequence;

public:
    Queue()
    {
        sequence = new LinkedListSequence<T>();
    }

    Queue(Sequence<T>& sequence)
    {
        this->sequence = &sequence;
    }

    ~Queue()
    {
        Free();
    }

    void Free()
    {
        if (sequence != nullptr)
        {
            sequence->Free();
            sequence = nullptr;
        }
    }

    const T& operator[] (const int index) const
    {
        return this->sequence->Get(index);
    }

    int Size()
    {
        return this->sequence->GetLength();
    }

    void Push(const T& value)
    {
        this->sequence->Append(value);
    }

    void Pop()
    {
        T result = this->sequence->GetFirst();
        this->sequence->RemoveAt(0);
        //return result;
    }

    T Front()
    {
        T result = this->sequence->GetFirst();
        //this->sequence->DeleteAt(0);
        return result;
    }

    Queue<T>* Map(T(*fn)(T value))
    {
        Queue<T>* result = new Queue<T>();
        for (int i = 0; i < Size(); i++)
        {
            result->Push(fn(this->sequence->Get(i)));
        }
        return result;
    }

    Queue<T>* Where(bool (*fn)(T value))
    {
        Queue<T>* result = new Queue<T>();
        for (int i = 0; i < Size(); i++)
        {
            T t = this->sequence->Get(i);
            if (fn(t))
            {
                result->Push(t);
            }
        }
        return result;
    }

    T Reduce(T(*fn)(T value1, T value2), T c)
    {
        T result = fn(this->sequence->GetFirst(), c);
        for (int i = 1; i < Size(); i++)
        {
            result = fn(this->sequence->Get(i), result);
        }
        return result;
    }

    Queue<T>* Concat(Queue<T>* queue)
    {
        Sequence<T>* concat = this->sequence->Concat(queue->sequence);
        Queue<T>* result = new Queue<T>(*concat);
        return result;
    }

    Queue<T>* Sub(int startIndex, int endIndex)
    {
        Sequence<T>* subsequence = this->sequence->GetSubsequence(startIndex, endIndex);
        Queue<T>* result = new Queue<T>(*subsequence);
        return result;
    }

    bool Find(Queue<T>* queue)
    {
        int i = 0, j = 0;

        while (i < queue->sequence->GetLength() && j < this->sequence->GetLength())
        {
            if (queue->sequence->Get(i) == this->sequence->Get(j))
            {
                i++;
                j++;
            }
            else
            {
                j = j - i + 1;
                i = 0;
            }
        }

        return (queue->sequence->GetLength() > 0) && (i == queue->sequence->GetLength());
    }

    bool empty() {
        if (this->sequence->GetLength() == 0) return true;
        else return false;
    }
};

