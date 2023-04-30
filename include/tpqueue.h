// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
  // реализация шаблона очереди с приоритетом на связанном списке
 private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;
    Node* create(const T& value) {
        Node* node = new Node;
        node->value = value;
        node->next = nullptr;
        node->prev = nullptr;
        return node;
    }

 public:
    TPQueue():head(nullptr), tail(nullptr) {}

    void push(const T& value) {
        if (head == nullptr) {
            head = tail = create(value);
        } else if (value.prior <= tail->value.prior) {
            tail->next = create(value);
            tail->next->prev = tail;
            tail = tail->next;
        } else if (head == tail) {
            tail->prev = create(value);
            head = tail->prev;
            head->next = tail;
        } else if (tail->value.prior < value.prior) {
            Node* temp = tail;
            while (temp != head && value.prior > temp->value.prior) {
                temp = temp->prev;
            }
            if (temp->value.prior >= value.prior) {
                Node* node = create(value);
                temp->next->prev = node;
                node->next = temp->next;
                temp->next = node;
                node->prev = temp;
            } else if (temp == head && temp->value.prior < value.prior) {
                head->prev = create(value);
                head = head->prev;
                head->next = temp;
                temp->prev = head;
            }
        }
    }

    const T& pop() {
        if (!head) {
            throw std::string("Queue is empty.");
        } else {
            Node* temp = head->next;
            T value = head->value;
            delete head;
            head = temp;
            return value;
        }
    }

    Node* search(const T& value) {
        Node* temp = tail;
        while (temp != nullptr && value.prior > temp->value.prior) {
            temp = temp->prev;
        }
        return temp;
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
