//
// Created by t-rosand on 1/7/2020.
//

#ifndef MIVNEY4_SERVER_H
#define MIVNEY4_SERVER_H

#include "rank_avl_tree.h"

class Server {
public:
     Server(int id, int dataCenterID, int traffic);

    int get_score() const { return _score; }
    void set_score(int score) { _score = score; }
    int get_data_center_id() const { return _dataCenterID; }


    class Compare{
    public:
        bool operator()(const Server* obj, const Server* obj2) {
            return obj->_score == obj2->_score && obj->_id == obj2->_id;}
    };

    class GreaterScore{
    public:
        bool operator()(const Server* obj, const Server* obj2) {
            if (obj->_score == obj2->_score)
                return obj->_id < obj2->_id;
            return obj->_score > obj2->_score;
        }
    };

private:
    const int _id;
    int _dataCenterID;
    int _score;
};

using ServerNode = RankAVLTreeNode<Server *, Server::Compare, Server::GreaterScore>;
using ServerTree = RankAVLTree<Server *, Server::Compare, Server::GreaterScore>;


#endif //MIVNEY4_SERVER_H
