//
// Created by t-rosand on 1/7/2020.
//

#ifndef MIVNEY4_DATACENTER_H
#define MIVNEY4_DATACENTER_H


#include "Server.h"
#include "rank_avl_tree.h"

class DataCenter {
public:
    DataCenter() = default;
    void add(Server * server);
    void remove(Server * server);
    void merge(DataCenter& center);
    int get_score_by_rank(int k);
    bool operator==(const DataCenter& center) const { return _id == center._id; };

    void set_id(int id) { _id = id; }
private:
    int _id;
    ServerTree _tree;
};


#endif //MIVNEY4_DATACENTER_H
