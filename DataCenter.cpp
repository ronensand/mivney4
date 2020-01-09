//
// Created by t-rosand on 1/7/2020.
//

#include "DataCenter.h"

void DataCenter::add(Server *server) {
    _tree.insert(server, server->get_score());
}

void DataCenter::remove(Server *server) {
    _tree.remove(server);
}

void DataCenter::merge(DataCenter &center) {
    // We need to create new merged tree.
    // TODO:
    auto merged_tree = ServerTree(_tree, center._tree);
    _tree.swap(merged_tree);
}

int DataCenter::get_score_by_rank(int k) {
    return _tree.get_score_by_rank(k);
}

