#ifndef MIVNEY2_DOUBLELINKEDLIST_H
#define MIVNEY2_DOUBLELINKEDLIST_H

#include <cassert>

template <typename T>
class Node {
public:
    explicit Node() : value(), next(nullptr), prev(nullptr) {}
    explicit Node(const T& value) : value(value), next(nullptr), prev(nullptr) {}

    T& get() { return value;}

    void insert(Node<T>* next_node) {
        // If this node is connected to other list, we cant insert it.
        assert(nullptr == next_node->next || nullptr == next_node->prev);

        Node * prev_next = next;
        next = next_node;

        next_node->prev = this;
        next_node->next = prev_next;

        if (prev_next) {
            prev_next->prev = next_node;
        }
    }

    void insert_before(Node<T>* prev_node) {
        // If this node is connected to other list, we cant insert it.
        assert(nullptr == prev_node->next || nullptr == prev_node->prev);

        Node * old_prev = prev;
        prev = prev_node;

        prev_node->next = this;
        prev_node->prev = old_prev;

        if (old_prev) {
            old_prev->next = prev_node;
        }
    }
    Node * remove() {
        if (nullptr != prev) {
            prev->next = next;
        }
        if (nullptr != next) {
            next->prev = prev;
        }

        next = nullptr;
        prev = nullptr;

        return this;
    }

    T value;
    Node * next;
    Node * prev;
};

template <typename T>
class DoubleLinkedList {
public:
    DoubleLinkedList() : _head(nullptr), _tail(nullptr) {}

    // This list is not freeing anything! if you want it to free call destroy
    virtual ~DoubleLinkedList() = default;

    Node<T> * head() {return _head;}
    Node<T> * tail() {return _tail;}

    void append(Node<T> * node) {
        if (empty()){
            assert(_head == nullptr);
            _head = node;
            _tail = node;
        } else {
            _tail->insert(node);
            _tail = node;
        }
    }

    void append(const T& value) {
        // This function is nothrow so we cant leak.
        append(new Node<T>(value));
    }

    void push(Node<T> * node) {
        if (empty()){
            assert(_head == nullptr);
            _head = node;
            _tail = node;
        } else {
            _head->insert_before(node);
            _head = node;
        }
    }

    void push(const T& value) {
        // This function is nothrow so we cant leak.
        push(new Node<T>(value));
    }

    // It the user responsibility to free the removed node
    Node<T> * remove(Node<T> * node) {
        if (_head == node) {
            _head = node->next;
        }

        if (_tail == node) {
            _tail = node->prev;
        }

        return node->remove();
    }

    bool empty() const {
        return nullptr == _head;
    }

    void destroy(){
        while (head()){
            delete remove(head());
        }
    }

private:
    Node<T> * _head;
    Node<T> * _tail;
};


#endif //MIVNEY2_DOUBLELINKEDLIST_H
