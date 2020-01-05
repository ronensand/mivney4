#include "hash_table.h"
#include <map>
#include <cstdlib>
#include <iostream>
#include <ctime>

int main() {
	HashTable<int> table = HashTable<int>();
	std::map<int, int> map = std::map<int, int>();

	std::srand(std::time(nullptr)); // use current time as seed for random generator

	try {
		for (int i = 0; i < 10000; ++i) {
			int r1 = rand() % 100000 + 1;
			int r2 = rand() % 100000 + 1;
			if (map.find(r1) == map.end()) {
				map.insert(std::pair<int, int>(r1, r2));
				table.insert(r1, r2);
			}
		}

		table.print();
		int j = 0;
		for (auto it = map.cbegin(); it != map.cend();) {
			if (++j % 4 == 0) {
				++it;
				continue;
			}
			table.remove(it->first);
			map.erase(it++);
		}

		for (auto & it : map) {
			int i = table.find(it.first);
			if (i!=it.second) {
				std::cout << "BUG";
			}
		}

		table.print();
	} catch (std::exception& e) {
		std::cout << e.what();
	}
}
