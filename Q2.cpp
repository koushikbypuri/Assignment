#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class MyHashMap {
private:
    static const int SIZE = 10007; // Prime number for hash distribution
    std::vector<std::pair<int, int>> buckets[SIZE];

    int hash(int key) {
        return key % SIZE;
    }

public:
    MyHashMap() {}

    void put(int key, int value) {
        int idx = hash(key);
        for (auto& kv : buckets[idx]) {
            if (kv.first == key) {
                kv.second = value;
                return;
            }
        }
        buckets[idx].emplace_back(key, value);
    }

    int get(int key) {
        int idx = hash(key);
        for (const auto& kv : buckets[idx]) {
            if (kv.first == key)
                return kv.second;
        }
        return -1;
    }

    void remove(int key) {
        int idx = hash(key);
        auto& bucket = buckets[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                return;
            }
        }
    }
};

int main() {
    MyHashMap map;
    std::string line;

    std::cout << "Enter commands (put <key> <value>, get <key>, remove <key>, exit):\n";

    while (true) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "exit") {
            break;
        } else if (cmd == "put") {
            int key, value;
            iss >> key >> value;
            map.put(key, value);
        } else if (cmd == "get") {
            int key;
            iss >> key;
            std::cout << map.get(key) << std::endl;
        } else if (cmd == "remove") {
            int key;
            iss >> key;
            map.remove(key);
        } else {
            std::cout << "Invalid command.\n";
        }
    }

    return 0;
}
