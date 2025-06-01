#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>

class LRUCache {
private:
    struct Node {
        int key, value;
        Node* prev;
        Node* next;
        Node(int k, int v): key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    std::unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    void remove(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insertToFront(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

public:
    LRUCache(int capacity): capacity(capacity) {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            remove(node);
            insertToFront(node);
            return node->value;
        }
        return -1;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            node->value = value;
            remove(node);
            insertToFront(node);
        } else {
            if (cache.size() == capacity) {
                Node* lru = tail->prev;
                remove(lru);
                cache.erase(lru->key);
                delete lru;
            }
            Node* newNode = new Node(key, value);
            insertToFront(newNode);
            cache[key] = newNode;
        }
    }

    ~LRUCache() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    int cap;
    std::cout << "Enter cache capacity: ";
    std::cin >> cap;
    std::cin.ignore(); // clear newline

    LRUCache lru(cap);
    std::string line;

    std::cout << "Enter commands (put <key> <value>, get <key>, exit):\n";
    while (true) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "exit") break;
        else if (cmd == "put") {
            int key, value;
            iss >> key >> value;
            lru.put(key, value);
        } else if (cmd == "get") {
            int key;
            iss >> key;
            std::cout << lru.get(key) << std::endl;
        } else {
            std::cout << "Invalid command. Use put/get/exit.\n";
        }
    }

    return 0;
}
