#pragma once
#include "LinkedList.h"

namespace AgroResQ
{
    namespace DataStructures
    {
        template <typename T>
        class Queue
        {
        private:
            LinkedList<T> list;

        public:
            Queue();
            ~Queue();

            void enqueue(const T& value);
            void dequeue();
            T& front() const;
            T& back() const;
            bool isEmpty() const;
            int size() const;
            void clear();
            void display() const;
        };



        template <typename T>
        Queue<T>::Queue() {}

        template <typename T>
        Queue<T>::~Queue() {}

        template <typename T>
        void Queue<T>::enqueue(const T& value)
        {
            list.pushBack(value);
        }

        template <typename T>
        void Queue<T>::dequeue()
        {
            list.popFront();
        }

        template <typename T>
        T& Queue<T>::front() const
        {
            return list.front();
        }

        template <typename T>
        T& Queue<T>::back() const
        {
            return list.back();
        }

        template <typename T>
        bool Queue<T>::isEmpty() const
        {
            return list.isEmpty();
        }

        template <typename T>
        int Queue<T>::size() const
        {
            return list.size();
        }

        template <typename T>
        void Queue<T>::clear()
        {
            list.clear();
        }

        template <typename T>
        void Queue<T>::display() const
        {
            list.display();
        }
    }
}