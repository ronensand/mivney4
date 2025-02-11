//
// Created by t-rosand on 1/7/2020.
//

#include "Manager.h"

Manager::Manager(int n) : _size(n), _union(n), _tree(), _hash_table() {}

void Manager::merge(int id1, int id2) {
    if (0 >= id1 || _size < id1 || 0 >= id2 || _size < id2 ) throw InvalidArgumentException();

    _union.merge(id1, id2);
}

void Manager::addServer(int dataCenterId, int serverID, int traffic) {
    if (0 >= dataCenterId || _size < dataCenterId || 0 >= serverID) throw InvalidArgumentException();

    DataCenter& center = _union.find(dataCenterId);

    auto server = new Server(serverID, dataCenterId, traffic);
    try {
        _hash_table.insert(serverID, server);
        if (traffic != 0) {
            _tree.insert(server, server->get_score());
            center.add(server);
        }
    }
    catch(...) {
        delete server;
        throw; // rethrow;
    }
}

void Manager::removeServer(int serverID) {
    if (0 >= serverID) return throw InvalidArgumentException();

    Server * server = _hash_table.find(serverID);
    _hash_table.remove(serverID);

    // If the server has score the he is inside score trees.
    if (server->get_score() != 0) {

        DataCenter& dataCenter = _union.find(server->get_data_center_id());
        dataCenter.remove(server);
        _tree.remove(server);
    }

    delete server;
}

void Manager::set_traffic(int serverID, int traffic) {
    if (0 >= serverID || 0 > traffic) return throw InvalidArgumentException();

    Server * server = _hash_table.find(serverID);
    int dataCenterID = server->get_data_center_id();

    removeServer(serverID); // Will delete server (must not use server from here)
    addServer(dataCenterID, serverID, traffic);
}

int Manager::SumHighestTrafficServers(int dataCenterId, int k) {
    if (0 > dataCenterId || _size < dataCenterId || 0 > k)  throw InvalidArgumentException();

    if (0 == k) return 0;

    if  (dataCenterId == 0) {
        return _tree.get_score_by_rank(k);
    }

    return _union.find(dataCenterId).get_score_by_rank(k);
}