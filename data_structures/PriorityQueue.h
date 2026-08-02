#pragma once
#include <vector>
#include <algorithm>

namespace AgroResQ
{
namespace DataStructures
{

template <typename T>
class PriorityQueue
{
private:
    std::vector<T> heap;

    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[index] < heap[parent])
                break;
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void heapifyDown(int index)
    {
        int size = heap.size();
        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && heap[left] > heap[largest])
                largest = left;
            if (right < size && heap[right] > heap[largest])
                largest = right;

            if (largest == index)
                break;

            std::swap(heap[index], heap[largest]);
            index = largest;
        }
    }

public:
    PriorityQueue() = default;

    void push(const T& value)
    {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    void pop()
    {
        if (isEmpty())
            return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!isEmpty())
            heapifyDown(0);
    }

    T top() const
    {
        if (isEmpty())
            return T();
        return heap[0];
    }

    bool isEmpty() const
    {
        return heap.empty();
    }

    int size() const
    {
        return heap.size();
    }

    void clear()
    {
        heap.clear();
    }
};

}
}