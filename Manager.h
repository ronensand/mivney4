//
// Created by t-rosand on 1/7/2020.
//

#ifndef MIVNEY4_MANAGER_H
#define MIVNEY4_MANAGER_H

#include "Union.h"
#include "DataCenter.h"
#include "Server.h"
#include "rank_avl_tree.h"
#include "hash_table.h"

class InvalidArgumentException : public std::exception {
    const char* what() const noexcept override {
        return "Manager received an invalid argument";
    }
};

class Manager {
public:
    explicit Manager(int n);
    ~Manager() = default;
    void merge(int id1, int id2);
    void addServer(int dataCenterId, int serverID, int traffic = 0);
    void removeServer(int serverID);
    void set_traffic(int serverID, int traffic);
    int SumHighestTrafficServers(int dataCenterId, int k);

private:
    const int _size;
    Union<DataCenter> _union;
    ServerTree _tree;
    HashTable<Server *> _hash_table;
};


#endif //MIVNEY4_MANAGER_H
