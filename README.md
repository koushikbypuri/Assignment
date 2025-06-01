# Assignment
Q1
I implemented an LRU (Least Recently Used) Cache in C++ using a hash map and a doubly linked list to ensure O(1) time for get() and put() operations. The list maintains usage order, allowing quick removal of the least recently used item when capacity is reached. This design efficiently supports up to 10⁵ operations and is ideal for memory-sensitive applications.

Q2
I built a custom HashMap in Java without using built-in map classes. It uses chaining with linked lists to handle collisions and supports put, get, and remove in average-case O(1) time. This low-level implementation demonstrates the core principles of hashing and efficient data access, while handling keys and values up to 10⁶.
