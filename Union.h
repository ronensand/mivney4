//
// Created by Ronen on 04/01/2020.
//

#ifndef UNION_H
#define UNION_H

// T Must have default c'tor
template <typename T>
class Union {
public:
    explicit Union(int n);
    ~Union();

    void merge(int id1, int id2);
    T& find(int id);

private:
    int get_root_id(int id) const;
    void fix_root(int id, int root);
    void validate_id(int id); // Throws if invalid id

    static const int NoParentID = 0;

    // Helper struct
    struct Node {
        Node() : parent_id(NoParentID), size(1), item() {}
        int parent_id;
        int size;
        T item;
    };

private:
    Node * _nodes;
    const int _n;
};

template<typename T>
Union<T>::Union(int n) :
    _nodes(new Node[n]), _n(n) {}


template<typename T>
Union<T>::~Union() {
    delete [] _nodes;
}

template<typename T>
void Union<T>::merge(int id1, int id2) {
    validate_id(id1);
    validate_id(id2);

    // Using get(without root fix) and not find, because we dont know the real root
    int root1 = get_root_id(id1);
    int root2 = get_root_id(id2);

    // Merge smaller to bigger
    if (_nodes[root1 - 1].size >= _nodes[root2 - 1].size){
        _nodes[root2 - 1].parent_id = root1;
        _nodes[root1 - 1].size += _nodes[root2 - 1].size;
    } else {
        _nodes[root1 - 1].parent_id = root2;
        _nodes[root2 - 1].size += _nodes[root1 - 1].size;
    }
}

template<typename T>
T &Union<T>::find(int id) {
    validate_id(id);

    int root = get_root_id(id);

    // Update our path nodes root.
    fix_root(id, root);

    return _nodes[root - 1].item;
}

template<typename T>
int Union<T>::get_root_id(int id) const {
    int parent_id = id;
    while(_nodes[parent_id - 1].parent_id != NoParentID) {
        parent_id = _nodes[parent_id - 1].parent_id;
    }

    return parent_id;
}

template<typename T>
void Union<T>::fix_root(int id, int root) {
    int parent_id = id;
    while(_nodes[parent_id - 1].parent_id != NoParentID) {
        int temp = _nodes[parent_id - 1].parent_id;
        _nodes[parent_id - 1].parent_id = root;
        parent_id = temp;
    }
}

template<typename T>
void Union<T>::validate_id(int id) {
    if (id > _n || id <= 0) throw std::exception();
}

#endif //UNION_H
