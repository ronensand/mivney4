//
// Created by Ronen on 28/12/2019.
//

#include <vector>
#include <cassert>
#include "Union.h"

int main() {
    Union<int> u (10);

    for (int i = 1; i <= 10; ++i) {
        u.find(i) = i;
    }

    for (int i = 1; i <= 10; ++i) {
        assert(u.find(i) == i);
    }

    u.merge(1,2);
    u.merge(1,10);

    // Now 1, 2 and 10 are under the same group (1 root)
    assert(u.find(1) == 1);
    assert(u.find(2) == 1);
    assert(u.find(10) == 1);

    u.merge(3,4);
    u.merge(4,5);
    u.merge(5,6);

    // Now 3, 4 ,5 and 6 under the same group (3 root)
    assert(u.find(3) == 3);
    assert(u.find(4) == 3);
    assert(u.find(5) == 3);
    assert(u.find(6) == 3);

    u.merge(2, 6);

    // now all (except 7 8 9 ) in the same group (3 root)
    assert(u.find(1) == 3);
    assert(u.find(2) == 3);
    assert(u.find(10) == 3);
    assert(u.find(3) == 3);
    assert(u.find(4) == 3);
    assert(u.find(5) == 3);
    assert(u.find(6) == 3);

}