#include<iostream>
#include <cassert>

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
        Node* node = get_index(_idx, false);
        if (!node)
            return 0;
        return node->value;
    }

    void add(ArrayLinkedList &other) {
        assert(array_length == other.array_length);

        // Iterate on the other first, and add it to the current one
        for (Node* other_cur = other.head->next; other_cur; other_cur = other_cur->next) {
            Node* this_idx = get_index(other_cur->idx, true);  // **
            this_idx->value += other_cur->value;
        }
        // ** We can make this function more efficient, but let's keep simple
    }
};
void test_index() {
    ArrayLinkedList array(10);	// length 10
    array.set_value(50, 5);
    array.set_value(20, 2);
    array.set_value(70, 7);
    array.set_value(40, 4);
    array.print_array();
    // 0 0 20 0 40 50 0 70 0 0
    array.print_array_nonzero();
    // 20 40 50 70
    cout << array.get_value(7) << "\n";	// 70

    ArrayLinkedList array2(10);
    array2.set_value(1, 4);
    array2.set_value(3, 7);
    array2.set_value(4, 6);

    array.add(array2);
    array.print_array();
    // 0 0 20 0 41 50 4 73 0 0
}

int main() {
    test_index();

    cout << "\n\n\nNO RTE\n";

    return 0;
}