#pragma once
#include <iostream>

namespace AgroResQ
{
    namespace DataStructures
    {
        template <typename T>
        struct Node
        {
            T data;
            Node<T>* next;
            Node<T>* prev;

            Node() : next(nullptr), prev(nullptr) {}
            Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
        };

        template <typename T>
        class LinkedList
        {
        private:
            Node<T>* head;
            Node<T>* tail;
            int count;

        public:
            LinkedList();
            ~LinkedList();

            void pushFront(const T& value);
            void pushBack(const T& value);
            void popFront();
            void popBack();
            T& front() const;
            T& back() const;
            bool isEmpty() const;
            int size() const;
            void clear();
            bool find(const T& value) const;
            bool remove(const T& value);
            void display() const;

            class Iterator
            {
            private:
                Node<T>* current;
            public:
                Iterator(Node<T>* node) : current(node) {}
                Iterator& operator++() { current = current->next; return *this; }
                Iterator& operator--() { current = current->prev; return *this; }
                bool operator!=(const Iterator& other) const { return current != other.current; }
                T& operator*() { return current->data; }
            };

            Iterator begin() const { return Iterator(head); }
            Iterator end() const { return Iterator(nullptr); }
        };


        template <typename T>
        LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

        template <typename T>
        LinkedList<T>::~LinkedList()
        {
            clear();
        }

        template <typename T>
        void LinkedList<T>::pushFront(const T& value)
        {
            Node<T>* newNode = new Node<T>(value);
            if (isEmpty())
            {
                head = tail = newNode;
            }
            else
            {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            count++;
        }

        template <typename T>
        void LinkedList<T>::pushBack(const T& value)
        {
            Node<T>* newNode = new Node<T>(value);
            if (isEmpty())
            {
                head = tail = newNode;
            }
            else
            {
                newNode->prev = tail;
                tail->next = newNode;
                tail = newNode;
            }
            count++;
        }

        template <typename T>
        void LinkedList<T>::popFront()
        {
            if (isEmpty()) return;
            Node<T>* temp = head;
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;
            delete temp;
            count--;
        }

        template <typename T>
        void LinkedList<T>::popBack()
        {
            if (isEmpty()) return;
            Node<T>* temp = tail;
            tail = tail->prev;
            if (tail) tail->next = nullptr;
            else head = nullptr;
            delete temp;
            count--;
        }

        template <typename T>
        T& LinkedList<T>::front() const
        {
            return head->data;
        }

        template <typename T>
        T& LinkedList<T>::back() const
        {
            return tail->data;
        }

        template <typename T>
        bool LinkedList<T>::isEmpty() const
        {
            return count == 0;
        }

        template <typename T>
        int LinkedList<T>::size() const
        {
            return count;
        }

        template <typename T>
        void LinkedList<T>::clear()
        {
            while (!isEmpty())
            {
                popFront();
            }
        }

        template <typename T>
        bool LinkedList<T>::find(const T& value) const
        {
            Node<T>* current = head;
            while (current)
            {
                if (current->data == value)
                    return true;
                current = current->next;
            }
            return false;
        }

        template <typename T>
        bool LinkedList<T>::remove(const T& value)
        {
            Node<T>* current = head;
            while (current)
            {
                if (current->data == value)
                {
                    if (current->prev) current->prev->next = current->next;
                    if (current->next) current->next->prev = current->prev;
                    if (current == head) head = current->next;
                    if (current == tail) tail = current->prev;
                    delete current;
                    count--;
                    return true;
                }
                current = current->next;
            }
            return false;
        }

        template <typename T>
        void LinkedList<T>::display() const
        {
            Node<T>* current = head;
            while (current)
            {
                std::cout << current->data << " ";
                current = current->next;
            }
            std::cout << "\n";
        }
    }
}