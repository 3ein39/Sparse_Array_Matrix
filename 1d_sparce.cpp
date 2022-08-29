#include<iostream>
using namespace std;

class Node {
public:
    int value;
    int idx;
    Node* next{};
    Node* prev{};
    
    // default constructor
    Node() : next(nullptr), prev(nullptr) {}

    Node(int val, int idx) {
        this->value = val;
        this->idx = idx;
    }
};

class ArrayLinkedList {
private:
    Node* head{};
    Node* tail{};
    int length = 0;         // total number of nodes
    int array_length {};    // total number of array elements

    void link(Node* first, Node* second) {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    Node* embed_after(Node* node_before, int value, int idx) {
        Node* middle = new Node(value, idx);
        ++length;

        Node* node_after = node_before->next;
        link(node_before, middle);

        if (!node_after)
            tail = middle;
        else
            link(middle, node_after);

        return middle;
    }

    Node* get_index(int idx, bool is_create_if_missing) {
        Node* prev_index = head;

        while(prev_index->next && prev_index->next->idx < idx)
            prev_index = prev_index->next;

        bool found = prev_index->next && prev_index->next->idx == idx;

        if (found)
            return prev_index->next;

        if (!is_create_if_missing)
            return nullptr;

        return embed_after(prev_index, 0, idx);
    }
public:
    // default constructor
    ArrayLinkedList() : head(nullptr), tail(nullptr) {}

    ArrayLinkedList(int array_length) :
            array_length(array_length) {
        // Reading: https://en.wikipedia.org/wiki/Sentinel_node
        tail = head = new Node(0, -1);
        ++length;
    }

    void set_value(int val, int idx) {
        get_index(idx, true)->value = val;
    }

    void print_array() {
        Node* cur = head->next;

        for (int i = 0; i < array_length; ++i) {
            if (cur && cur->idx == i) {
                cout << cur->value << " ";
                cur = cur->next;
            } else
                cout << "0 ";
        }
        cout << "\n";
    }

    void print_array_nonzero() {
        for (Node* cur = head->next; cur; cur = cur->next)
            cout << cur->value << " ";
        cout << "\n";
    }

    const int& get_value(int _idx) {
        // assuming that given idx is in range
        Node* p = head;

        while(p) {
            if (p->idx == _idx)
                return p->value;
            p = p->next;
        }
        return 0;
    }

    void add(const ArrayLinkedList& other) {
        Node* first = this->head;
        Node* second = other.head;

        while (second && first) {
            first->value += second->value;

            first = first->next, second = second->next;
        }
    }
};

int main() {
    ArrayLinkedList list(10);
    list.set_value(50, 5);
    list.set_value(10, 1);
    list.set_value(60, 6);
    list.set_value(20, 2);

    ArrayLinkedList list2(10);
    list2.set_value(5, 5);
    list2.set_value(99, 0);

    list.add(list2);

    list.print_array();
    list.print_array_nonzero();

    return 0;
}