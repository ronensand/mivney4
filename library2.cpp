//
// Created by t-rosand on 1/7/2020.
//

#include <new>
#include "library2.h"
#include "Manager.h"

template <typename Func>
static StatusType exception_wrapper(Func f){
    try {
        f();
        return SUCCESS;
    }
    catch(const std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    catch(const InvalidArgumentException&) {
        return INVALID_INPUT;
    }
    catch (...){
        return FAILURE;
    }
}

void *Init(int n) {
    // TODO: 0 is a possible value?
    if (n <= 0) return nullptr;
    Manager * manager = nullptr;
    exception_wrapper([&](){
        manager = new Manager(n);
    });

    // We dont return exception_wrapper, in case of failure manager will stay null;
    return manager;
}

StatusType MergeDataCenters(void *DS, int dataCenter1, int dataCenter2) {
    if (nullptr == DS) return INVALID_INPUT;

    return exception_wrapper([&](){
        auto manager = reinterpret_cast<Manager *>(DS);

        manager->merge(dataCenter1, dataCenter2);
    });
}

StatusType AddServer(void *DS, int dataCenterID, int serverID) {
    if (nullptr == DS) return INVALID_INPUT;

    return exception_wrapper([&](){
        auto manager = reinterpret_cast<Manager *>(DS);

        manager->addServer(dataCenterID, serverID);
    });
}

StatusType RemoveServer(void *DS, int serverID) {
    if (nullptr == DS) return INVALID_INPUT;

    return exception_wrapper([&](){
        auto manager = reinterpret_cast<Manager *>(DS);

        manager->removeServer(serverID);
    });
}

StatusType SetTraffic(void *DS, int serverID,  int traffic) {
    if (nullptr == DS) return INVALID_INPUT;

    return exception_wrapper([&](){
        auto manager = reinterpret_cast<Manager *>(DS);

        manager->set_traffic(serverID, traffic);
    });
}

StatusType SumHighestTrafficServers(void *DS, int dataCenterID,  int k, int *traffic) {
    if (nullptr == DS || nullptr == traffic) return INVALID_INPUT;

    return exception_wrapper([&](){
        auto manager = reinterpret_cast<Manager *>(DS);

        *traffic = manager->SumHighestTrafficServers(dataCenterID, k);
    });
}

void Quit(void **DS) {
    if (nullptr == DS || nullptr == *DS) return;
    exception_wrapper([&](){
        auto manager = reinterpret_cast<Manager *>(*DS);

        delete manager;
        *DS = nullptr;
    });
}