#ifndef MIVNEY4_HASH_TABLE_H
#define MIVNEY4_HASH_TABLE_H

#include <exception>
#include <iostream>

int DELETE_SIGN = 0;
int NOT_FOUND = -1;
int START_SIZE = 16;

template <class Value>
class HashTableItem {
public:
	int key;
	Value value;

	HashTableItem(int key, Value value) : key(key), value(value) {};
	virtual ~HashTableItem() = default;
};

class KeyNotFoundException : public std::exception {
	const char* what() const noexcept override {
		return "Key wasn't found in hash table";
	}
};

class KeyAlreadyExistsException : public std::exception {
	const char* what() const noexcept override {
		return "Already exists";
	}
};

// This hash table uses positive ints as keys
template <class Value>
class HashTable {
	int size;
	int capacity;
	HashTableItem<Value>** array;

	int search(int key) {
		int h = hash(key);
		int i = 0;
		while (array[h] != nullptr && array[h]->key != key && i < capacity) {
			h = rehash(h);
			++i;
		}

		return array[h] == nullptr || i == size ? NOT_FOUND : h;
	}

	int hash(int key) {
		return key % capacity;
	}

	int rehash(int key) {
		return (key + 1) % capacity;
	}

	void increase_capacity() {
		auto* old_array = array;
		capacity *= 2;
		array = new HashTableItem<Value>*[capacity];
		size = 0;
		for (int i=0; i<capacity/2; ++i) {
			insert(old_array[i]->key, old_array[i]->value);
			delete old_array[i];
		}
		delete [] old_array;
	}

	void decrease_capacity() {
		auto* old_array = array;
		capacity /= 2;
		array = new HashTableItem<Value>*[capacity];
		size = 0;
		for (int i=0; i<capacity*2; ++i) {
			if (nullptr == old_array[i] ||
			DELETE_SIGN == old_array[i]->key) continue;
			insert(old_array[i]->key, old_array[i]->value);
			delete old_array[i];
		}
		delete [] old_array;
	}

public:
	HashTable() : size(0), capacity(START_SIZE),
	array(new HashTableItem<Value>*[START_SIZE]) {}

	~HashTable(){
		for (int i=0; i<capacity; ++i) {
			delete array[i];
		}
		delete [] array;
	};

	void insert(int key, Value value) {
		if (NOT_FOUND != this->search(key)) {
			throw KeyAlreadyExistsException();
		}

		if (size == capacity) increase_capacity();

		int h = hash(key);
		// by resizing before the array is full, and by guaranteeing
		// the rehash cycles through the whole array, we guarantee
		// that this won't be an infinite while loop
		while (array[h] != nullptr && array[h]->key != DELETE_SIGN) {
			h = rehash(h);
		}

		if (nullptr == array[h]) {
			array[h] = new HashTableItem<Value>(key, value);
		}
		else {
			array[h]->key = key;
			array[h]->value = value;
		}
		++size;
	}

	void remove(int key) {
		int index = search(key);
		if (NOT_FOUND == index) {
			throw KeyNotFoundException();
		}

		array[index]->key = DELETE_SIGN;
		--size;

		if (size < capacity / 4 && capacity > START_SIZE)
			decrease_capacity();
		}

	Value find(int key) {
		int index = search(key);
		if (NOT_FOUND == index) {
			throw KeyNotFoundException();
		}

		return array[index]->value;
	}

	void print() {
		std::cout << "Hash Table: Capacity: " << capacity << " Size: "
		<< size << "\n";
//		for (int i=0; i<capacity; ++i) {
//			if (array[i] != nullptr) {
//				std::cout << "index: " << i << " key: " << array[i]->key
//				<< " value: " << array[i]->value << "\n";
//			} else {
//				std::cout << "index: " << i << " NULL\n";
//			}
//		}
	}
};

#endif //MIVNEY4_HASH_TABLE_H
