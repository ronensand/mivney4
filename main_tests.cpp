#include "library2.h"
#include <cassert>
#include <iostream>
using std::cout;

void test2(){
    void** DS=new (void*);
    *DS=Init(4);
    assert(*DS!=nullptr);
    StatusType s=AddServer(*DS,5,5);
    assert(s==INVALID_INPUT);
    s=AddServer(*DS,0,5);
    assert(s==INVALID_INPUT);
    s=AddServer(*DS,-1,5);
    assert(s==INVALID_INPUT);
    s=AddServer(*DS,5,0);
    assert(s==INVALID_INPUT);
    s=AddServer(*DS,5,-1);
    assert(s==INVALID_INPUT);
    s=AddServer(nullptr,5,-44);
    assert(s==INVALID_INPUT);
    s=AddServer(*DS,1,1);
    assert(s==SUCCESS);
    s=AddServer(*DS,2,1);
    assert(s==FAILURE);
    s=AddServer(*DS,2,2);
    assert(s==SUCCESS);
    s=AddServer(*DS,2,3);
    assert(s==SUCCESS);
    s=AddServer(*DS,2,4);
    assert(s==SUCCESS);
    s=AddServer(*DS,2,5);
    assert(s==SUCCESS);
    s=AddServer(*DS,3,5);
    assert(s==FAILURE);
    s=AddServer(*DS,3,6);
    assert(s==SUCCESS);
    s=AddServer(*DS,3,7);
    assert(s==SUCCESS);
    s=AddServer(*DS,4,8);
    assert(s==SUCCESS);
    s=AddServer(*DS,4,9);
    assert(s==SUCCESS);
    s=AddServer(*DS,4,10);
    assert(s==SUCCESS);//check hash table has been successfully updated!!!
    int sum=0;
    s=SumHighestTrafficServers(*DS,1,-1,&sum);
    assert(s==INVALID_INPUT);
    s=SumHighestTrafficServers(*DS,5,1,&sum);
    assert(s==INVALID_INPUT);
    s=SumHighestTrafficServers(*DS,-1,5,&sum);
    assert(s==INVALID_INPUT);
    s=SumHighestTrafficServers(nullptr,1,5,&sum);
    assert(s==INVALID_INPUT);
    s=SumHighestTrafficServers(*DS,1,5, nullptr);
    assert(s==INVALID_INPUT);
    s=SumHighestTrafficServers(*DS,1,0,&sum);
    assert(s==SUCCESS && sum==0);
    s=SumHighestTrafficServers(*DS,0,0,&sum);
    assert(s==SUCCESS && sum==0);
    s=SetTraffic(nullptr,3,3);
    assert(s==INVALID_INPUT);
    s=SetTraffic(*DS,0,3);
    assert(s==INVALID_INPUT);
    s=SetTraffic(*DS,-1,3);
    assert(s==INVALID_INPUT);
    s=SetTraffic(*DS,1,-1);
    assert(s==INVALID_INPUT);
    s=SetTraffic(*DS,5,-1);
    assert(s==INVALID_INPUT);
    s=SetTraffic(*DS,11,3);
    assert(s==FAILURE);
    s=SetTraffic(*DS,1,1);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,0,1,&sum);
    assert(s==SUCCESS && sum==1);
    s=SumHighestTrafficServers(*DS,0,0,&sum);
    assert(s==SUCCESS && sum==0);
    s=SumHighestTrafficServers(*DS,0,12,&sum);
    assert(s==SUCCESS && sum==1);
    s=SumHighestTrafficServers(*DS,1,0,&sum);
    assert(s==SUCCESS && sum==0);
    s=SumHighestTrafficServers(*DS,1,1,&sum);
    assert(s==SUCCESS && sum==1);
    s=SumHighestTrafficServers(*DS,1,2,&sum);
    assert(s==SUCCESS && sum==1);
    s=SetTraffic(*DS,2,2);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,3,3);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,4,4);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,5,5);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,2,1,&sum);
    assert(s==SUCCESS && sum==5);
    s=SumHighestTrafficServers(*DS,2,2,&sum);
    assert(s==SUCCESS && sum==9);
    s=SumHighestTrafficServers(*DS,2,3,&sum);
    assert(s==SUCCESS && sum==12);
    s=SumHighestTrafficServers(*DS,2,4,&sum);
    assert(s==SUCCESS && sum==14);
    s=SetTraffic(*DS,6,6);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,7,7);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,8,8);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,9,9);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,10,10);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,3,1,&sum);
    assert(s==SUCCESS && sum==7);
    s=SumHighestTrafficServers(*DS,3,2,&sum);
    assert(s==SUCCESS && sum==13);
    s=SumHighestTrafficServers(*DS,3,3,&sum);
    assert(s==SUCCESS && sum==13);
    s=SumHighestTrafficServers(*DS,4,0,&sum);
    assert(s==SUCCESS && sum==0);
    s=SumHighestTrafficServers(*DS,4,1,&sum);
    assert(s==SUCCESS && sum==10);
    s=SumHighestTrafficServers(*DS,4,2,&sum);
    assert(s==SUCCESS && sum==19);
    s=SumHighestTrafficServers(*DS,4,3,&sum);
    assert(s==SUCCESS && sum==27);
    s=SumHighestTrafficServers(*DS,0,0,&sum);
    assert(s==SUCCESS && sum==0);
    s=SumHighestTrafficServers(*DS,0,1,&sum);
    assert(s==SUCCESS && sum==10);
    s=SumHighestTrafficServers(*DS,0,2,&sum);
    assert(s==SUCCESS && sum==19);
    s=SumHighestTrafficServers(*DS,0,3,&sum);
    assert(s==SUCCESS && sum==27);
    s=SumHighestTrafficServers(*DS,0,4,&sum);
    assert(s==SUCCESS && sum==34);
    s=SumHighestTrafficServers(*DS,0,5,&sum);
    assert(s==SUCCESS && sum==40);
    s=SumHighestTrafficServers(*DS,0,6,&sum);
    assert(s==SUCCESS && sum==45);
    s=SumHighestTrafficServers(*DS,0,7,&sum);
    assert(s==SUCCESS && sum==49);
    s=SumHighestTrafficServers(*DS,0,8,&sum);
    assert(s==SUCCESS && sum==52);
    s=SumHighestTrafficServers(*DS,0,9,&sum);
    assert(s==SUCCESS && sum==54);
    s=SumHighestTrafficServers(*DS,0,10,&sum);
    assert(s==SUCCESS && sum==55);
    s=SumHighestTrafficServers(*DS,0,11,&sum);
    assert(s==SUCCESS && sum==55);
    s=MergeDataCenters(*DS,0,2);
    assert(s==INVALID_INPUT);
    s=MergeDataCenters(*DS,2,0);
    assert(s==INVALID_INPUT);
    s=MergeDataCenters(*DS,5,2);
    assert(s==INVALID_INPUT);
    s=MergeDataCenters(*DS,2,5);
    assert(s==INVALID_INPUT);
    s=MergeDataCenters(*DS,-1,2);
    assert(s==INVALID_INPUT);
    s=MergeDataCenters(*DS,1,-2);
    assert(s==INVALID_INPUT);
    s=MergeDataCenters(nullptr,1,2);
    assert(s==INVALID_INPUT);
    s=MergeDataCenters(*DS,1,2);//check data_center_id of all servers which merged became 1 in the hash table!!!
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,1,1,&sum);
    assert(s==SUCCESS && sum==5);
    s=SumHighestTrafficServers(*DS,1,2,&sum);
    assert(s==SUCCESS && sum==9);
    s=SumHighestTrafficServers(*DS,1,3,&sum);
    assert(s==SUCCESS && sum==12);
    s=SumHighestTrafficServers(*DS,1,4,&sum);
    assert(s==SUCCESS && sum==14);
    s=SumHighestTrafficServers(*DS,1,5,&sum);
    assert(s==SUCCESS && sum==15);
    s=SumHighestTrafficServers(*DS,2,1,&sum);
    assert(s==SUCCESS && sum==5);
    s=SumHighestTrafficServers(*DS,2,2,&sum);
    assert(s==SUCCESS && sum==9);
    s=SumHighestTrafficServers(*DS,2,3,&sum);
    assert(s==SUCCESS && sum==12);
    s=SumHighestTrafficServers(*DS,2,4,&sum);
    assert(s==SUCCESS && sum==14);
    s=SumHighestTrafficServers(*DS,2,5,&sum);
    assert(s==SUCCESS && sum==15);
    s=MergeDataCenters(*DS,3,2);// check id of main data_center is 1!
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,3,1,&sum);
    assert(s==SUCCESS && sum==7);
    s=SumHighestTrafficServers(*DS,3,2,&sum);
    assert(s==SUCCESS && sum==13);
    s=SumHighestTrafficServers(*DS,2,3,&sum);
    assert(s==SUCCESS && sum==18);
    s=SumHighestTrafficServers(*DS,2,4,&sum);
    assert(s==SUCCESS && sum==22);
    s=SumHighestTrafficServers(*DS,1,5,&sum);
    assert(s==SUCCESS && sum==25);
    s=SumHighestTrafficServers(*DS,1,6,&sum);
    assert(s==SUCCESS && sum==27);
    s=SumHighestTrafficServers(*DS,1,7,&sum);
    assert(s==SUCCESS && sum==28);
    s=SetTraffic(*DS,2,11);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,8,11);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,6,12);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,3,1,&sum);
    assert(s==SUCCESS && sum==12);
    s=SumHighestTrafficServers(*DS,3,2,&sum);
    assert(s==SUCCESS && sum==23);
    s=SumHighestTrafficServers(*DS,3,3,&sum);
    assert(s==SUCCESS && sum==30);
    s=SumHighestTrafficServers(*DS,3,4,&sum);
    assert(s==SUCCESS && sum==35);
    s=SumHighestTrafficServers(*DS,3,5,&sum);
    assert(s==SUCCESS && sum==39);
    s=SumHighestTrafficServers(*DS,3,6,&sum);
    assert(s==SUCCESS && sum==42);
    s=SumHighestTrafficServers(*DS,2,7,&sum);
    assert(s==SUCCESS && sum==43);
    s=SumHighestTrafficServers(*DS,0,1,&sum);
    assert(s==SUCCESS && sum==12);
    s=SumHighestTrafficServers(*DS,0,2,&sum);
    assert(s==SUCCESS && sum==23);
    s=SumHighestTrafficServers(*DS,0,3,&sum);
    assert(s==SUCCESS && sum==34);
    s=SumHighestTrafficServers(*DS,0,4,&sum);
    assert(s==SUCCESS && sum==44);
    s=SumHighestTrafficServers(*DS,0,5,&sum);
    assert(s==SUCCESS && sum==53);
    s=SumHighestTrafficServers(*DS,0,6,&sum);
    assert(s==SUCCESS && sum==60);
    s=SumHighestTrafficServers(*DS,0,7,&sum);
    assert(s==SUCCESS && sum==65);
    s=SumHighestTrafficServers(*DS,0,8,&sum);
    assert(s==SUCCESS && sum==69);
    s=RemoveServer(*DS,11);
    assert(s==FAILURE);
    s=RemoveServer(*DS,0);
    assert(s==INVALID_INPUT);
    s=RemoveServer(*DS,-1);
    assert(s==INVALID_INPUT);
    s=RemoveServer(nullptr,9);
    assert(s==INVALID_INPUT);
    s=RemoveServer(*DS,2);//check server removed from hash table!
    assert(s==SUCCESS);
    s=RemoveServer(*DS,4);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,3,1,&sum);
    assert(s==SUCCESS && sum==12);
    s=SumHighestTrafficServers(*DS,3,2,&sum);
    assert(s==SUCCESS && sum==19);
    s=SumHighestTrafficServers(*DS,3,3,&sum);
    assert(s==SUCCESS && sum==24);
    s=SumHighestTrafficServers(*DS,2,4,&sum);
    assert(s==SUCCESS && sum==27);
    s=SumHighestTrafficServers(*DS,1,5,&sum);
    assert(s==SUCCESS && sum==28);
    s=SumHighestTrafficServers(*DS,1,6,&sum);
    assert(s==SUCCESS && sum==28);
    s=SumHighestTrafficServers(*DS,2,0,&sum);
    assert(s==SUCCESS && sum==0);
    s=SumHighestTrafficServers(*DS,0,1,&sum);
    assert(s==SUCCESS && sum==12);
    s=SumHighestTrafficServers(*DS,0,2,&sum);
    assert(s==SUCCESS && sum==23);
    s=SumHighestTrafficServers(*DS,0,3,&sum);
    assert(s==SUCCESS && sum==33);
    s=SumHighestTrafficServers(*DS,0,4,&sum);
    assert(s==SUCCESS && sum==42);
    s=SumHighestTrafficServers(*DS,0,5,&sum);
    assert(s==SUCCESS && sum==49);
    s=SumHighestTrafficServers(*DS,0,6,&sum);
    assert(s==SUCCESS && sum==54);
    s=SumHighestTrafficServers(*DS,0,7,&sum);
    assert(s==SUCCESS && sum==57);
    s=SumHighestTrafficServers(*DS,0,8,&sum);
    assert(s==SUCCESS && sum==58);
    s=RemoveServer(*DS,9);//check server removed from hash table+main_tree+(4)_tree!
    assert(s==SUCCESS);
    s=RemoveServer(*DS,6);//check server removed from hash table+main_tree+(1,2,3)_tree!
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,1,1,&sum);
    assert(s==SUCCESS && sum==7);
    s=SumHighestTrafficServers(*DS,1,2,&sum);
    assert(s==SUCCESS && sum==12);
    s=SumHighestTrafficServers(*DS,3,3,&sum);
    assert(s==SUCCESS && sum==15);
    s=SumHighestTrafficServers(*DS,2,4,&sum);
    assert(s==SUCCESS && sum==16);
    s=SumHighestTrafficServers(*DS,0,1,&sum);
    assert(s==SUCCESS && sum==11);
    s=SumHighestTrafficServers(*DS,0,2,&sum);
    assert(s==SUCCESS && sum==21);
    s=SumHighestTrafficServers(*DS,0,3,&sum);
    assert(s==SUCCESS && sum==28);
    s=SumHighestTrafficServers(*DS,0,4,&sum);
    assert(s==SUCCESS && sum==33);
    s=SumHighestTrafficServers(*DS,0,5,&sum);
    assert(s==SUCCESS && sum==36);
    s=SumHighestTrafficServers(*DS,0,6,&sum);
    assert(s==SUCCESS && sum==37);
    s=RemoveServer(*DS,3);
    assert(s==SUCCESS);
    s=RemoveServer(*DS,8);
    assert(s==SUCCESS);
    s=RemoveServer(*DS,7);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,2,0,&sum);
    assert(s==SUCCESS && sum==0);
    s=SumHighestTrafficServers(*DS,1,1,&sum);
    assert(s==SUCCESS && sum==5);
    s=SumHighestTrafficServers(*DS,3,2,&sum);
    assert(s==SUCCESS && sum==6);
    s=SumHighestTrafficServers(*DS,4,3,&sum);
    assert(s==SUCCESS && sum==10);
    s=SumHighestTrafficServers(*DS,0,1,&sum);
    assert(s==SUCCESS && sum==10);
    s=SumHighestTrafficServers(*DS,0,2,&sum);
    assert(s==SUCCESS && sum==15);
    s=SumHighestTrafficServers(*DS,0,3,&sum);
    assert(s==SUCCESS && sum==16);
    s=RemoveServer(*DS,3);
    assert(s==FAILURE);
    s=RemoveServer(*DS,1);
    assert(s==SUCCESS);
    s=RemoveServer(*DS,5);
    assert(s==SUCCESS);
    s=RemoveServer(*DS,10);//check main_tree+(1,2,3)_tree+(4)_tree+hash table are empty!
    assert(s==SUCCESS);
    s=AddServer(*DS,1,1);//check server 1 was inserted to hash table!
    assert(s==SUCCESS);
    s=SetTraffic(*DS,1,5);//check server 1 was inserted to (1,2,3)_tree+main_tree!
    assert(s==SUCCESS);

    Quit(DS);
    delete DS;

    cout<<"***************~~~~~~~~~~~~~~~~~~~~~~~~~***************"<<"\n";
    cout<<"**********~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~**********"<<"\n";
    cout<<"*****~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*****"<<"\n";
    cout<<"~~~~~~~~~~~~~~~~~~~~CONGRATULATIONS~~~~~~~~~~~~~~~~~~~~"<<"\n";
    cout<<"*****~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*****"<<"\n";
    cout<<"**********~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~**********"<<"\n";
    cout<<"***************~~~~~~~~~~~~~~~~~~~~~~~~~***************"<<"\n";
}

void test1(){
    void** DS=new (void*);
    *DS=Init(10);
    assert(*DS!=nullptr);
    StatusType s=AddServer(*DS,11,10);
    assert(s==INVALID_INPUT);
    s=AddServer(*DS,0,10);
    assert(s==INVALID_INPUT);
    s=AddServer(*DS,-1,10);
    assert(s==INVALID_INPUT);
    s=AddServer(*DS,5,0);
    assert(s==INVALID_INPUT);
    s=AddServer(*DS,5,-44);
    assert(s==INVALID_INPUT);
    s=AddServer(nullptr,5,-44);
    assert(s==INVALID_INPUT);
    s=AddServer(*DS,5,1);
    assert(s==SUCCESS);
    s=AddServer(*DS,5,1);
    assert(s==FAILURE);
    s=AddServer(*DS,1,1);
    assert(s==FAILURE);
    s=AddServer(*DS,1,2);
    assert(s==SUCCESS);
    s=AddServer(*DS,1,3);
    assert(s==SUCCESS);
    s=AddServer(*DS,2,3);
    assert(s==FAILURE);
    s=AddServer(*DS,2,4);
    assert(s==SUCCESS);
    s=AddServer(*DS,10,5);
    assert(s==SUCCESS);
    s=AddServer(*DS,10,6);
    assert(s==SUCCESS);
    s=AddServer(*DS,9,6);
    assert(s==FAILURE);
    s=AddServer(*DS,9,7);
    assert(s==SUCCESS);
    s=AddServer(*DS,9,8);
    assert(s==SUCCESS);
    s=AddServer(*DS,8,9);
    assert(s==SUCCESS);
    s=AddServer(*DS,8,10);
    assert(s==SUCCESS);
    s=AddServer(*DS,8,11);
    assert(s==SUCCESS);
    s=AddServer(*DS,7,12);
    assert(s==SUCCESS);
    s=AddServer(*DS,7,13);
    assert(s==SUCCESS);
    s=AddServer(*DS,6,14);
    assert(s==SUCCESS);
    s=AddServer(*DS,5,15);
    assert(s==SUCCESS);
    s=AddServer(*DS,5,16);
    assert(s==SUCCESS);
    s=AddServer(*DS,4,17);
    assert(s==SUCCESS);
    s=AddServer(*DS,4,18);
    assert(s==SUCCESS);
    s=AddServer(*DS,3,19);
    assert(s==SUCCESS);
    s=AddServer(*DS,3,20);
    assert(s==SUCCESS);
    s=RemoveServer(*DS,4);
    assert(s==SUCCESS);
    s=RemoveServer(*DS,4);
    assert(s==FAILURE);
    s=RemoveServer(*DS,10);
    assert(s==SUCCESS);
    s=RemoveServer(*DS,21);
    assert(s==FAILURE);
    s=RemoveServer(*DS,0);
    assert(s==INVALID_INPUT);
    s=RemoveServer(nullptr,9);
    assert(s==INVALID_INPUT);
    s=SetTraffic(nullptr,3,3);
    assert(s==INVALID_INPUT);
    s=SetTraffic(*DS,0,3);
    assert(s==INVALID_INPUT);
    s=SetTraffic(*DS,-1,3);
    assert(s==INVALID_INPUT);
    s=SetTraffic(*DS,21,3);
    assert(s==FAILURE);
    s=SetTraffic(*DS,4,3);
    assert(s==FAILURE);
    s=SetTraffic(*DS,10,3);
    assert(s==FAILURE);
    s=SetTraffic(*DS,1,-1);
    assert(s==INVALID_INPUT);
    s=SetTraffic(*DS,5,-1);
    assert(s==INVALID_INPUT);
    s=SetTraffic(*DS,10,-1);
    assert(s==INVALID_INPUT);
    s=SetTraffic(*DS,9,-1);
    assert(s==INVALID_INPUT);
    s=SetTraffic(*DS,4,-1);
    assert(s==INVALID_INPUT);
    s=SetTraffic(*DS,14,-1);
    assert(s==INVALID_INPUT);
    s=SetTraffic(*DS,14,5);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,20,11);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,3,11);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,2,3);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,6,4);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,13,7);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,18,25);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,16,12);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,12,12);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,7,5);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,8,5);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,8,10);
    assert(s==SUCCESS);
    int sum=0;
    s=SumHighestTrafficServers(nullptr,5,1,&sum);
    assert(s==INVALID_INPUT);
    s=SumHighestTrafficServers(*DS,5,-1,&sum);
    assert(s==INVALID_INPUT);
    s=SumHighestTrafficServers(*DS,21,1,&sum);
    assert(s==INVALID_INPUT);
    s=SumHighestTrafficServers(*DS,-1,1,&sum);
    assert(s==INVALID_INPUT);
    s=SumHighestTrafficServers(*DS,0,1,&sum);
    assert(s==SUCCESS && sum==25);
    s=SumHighestTrafficServers(*DS,0,3,&sum);
    assert(s==SUCCESS && sum==49);
    s=SumHighestTrafficServers(*DS,0,5,&sum);
    assert(s==SUCCESS && sum==71);
    s=SetTraffic(*DS,3,2);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,0,5,&sum);
    assert(s==SUCCESS && sum==70);
    s=SetTraffic(*DS,9,21);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,0,5,&sum);
    assert(s==SUCCESS && sum==81);
    s=SumHighestTrafficServers(*DS,5,3,&sum);
    assert(s==SUCCESS && sum==12);
    s=SetTraffic(*DS,15,2);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,5,3,&sum);
    assert(s==SUCCESS && sum==14);
    s=SetTraffic(*DS,1,1);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,5,3,&sum);
    assert(s==SUCCESS && sum==15);
    s=MergeDataCenters(nullptr,5,2);
    assert(s==INVALID_INPUT);
    s=MergeDataCenters(*DS,4,0);
    assert(s==INVALID_INPUT);
    s=MergeDataCenters(*DS,0,4);
    assert(s==INVALID_INPUT);
    s=MergeDataCenters(*DS,21,4);
    assert(s==INVALID_INPUT);
    s=MergeDataCenters(*DS,4,23);
    assert(s==INVALID_INPUT);
    s=MergeDataCenters(*DS,4,5);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,4,3,&sum);
    assert(s==SUCCESS && sum==39);
    s=SumHighestTrafficServers(*DS,5,3,&sum);
    assert(s==SUCCESS && sum==39);
    s=SetTraffic(*DS,16,8);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,5,3,&sum);
    assert(s==SUCCESS && sum==35);
    s=SumHighestTrafficServers(*DS,5,1,&sum);
    assert(s==SUCCESS && sum==25);
    s=SumHighestTrafficServers(*DS,5,2,&sum);
    assert(s==SUCCESS && sum==33);
    s=SumHighestTrafficServers(*DS,5,4,&sum);
    assert(s==SUCCESS && sum==36);
    s=SumHighestTrafficServers(*DS,5,5,&sum);
    assert(s==SUCCESS && sum==36);
    s=SumHighestTrafficServers(*DS,4,3,&sum);
    assert(s==SUCCESS && sum==35);
    s=SumHighestTrafficServers(*DS,4,1,&sum);
    assert(s==SUCCESS && sum==25);
    s=SumHighestTrafficServers(*DS,4,2,&sum);
    assert(s==SUCCESS && sum==33);
    s=SumHighestTrafficServers(*DS,4,4,&sum);
    assert(s==SUCCESS && sum==36);
    s=SumHighestTrafficServers(*DS,4,5,&sum);
    assert(s==SUCCESS && sum==36);
    s=AddServer(*DS,4,10);
    assert(s==SUCCESS );
    s=SetTraffic(*DS,10,30);
    assert(s==SUCCESS );
    s=SumHighestTrafficServers(*DS,4,2,&sum);
    assert(s==SUCCESS && sum==55);
    s=SumHighestTrafficServers(*DS,5,2,&sum);
    assert(s==SUCCESS && sum==55);
    s=MergeDataCenters(*DS,4,9);
    assert(s==SUCCESS);
    s=SetTraffic(*DS,8,60);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,4,1,&sum);
    assert(s==SUCCESS && sum==60);
    s=SumHighestTrafficServers(*DS,5,1,&sum);
    assert(s==SUCCESS && sum==60);
    s=SumHighestTrafficServers(*DS,9,1,&sum);
    assert(s==SUCCESS && sum==60);
    s=SumHighestTrafficServers(*DS,4,2,&sum);
    assert(s==SUCCESS && sum==90);
    s=SumHighestTrafficServers(*DS,5,2,&sum);
    assert(s==SUCCESS && sum==90);
    s=SumHighestTrafficServers(*DS,9,2,&sum);
    assert(s==SUCCESS && sum==90);
    s=SumHighestTrafficServers(*DS,5,4,&sum);
    assert(s==SUCCESS && sum==123);
    s=SumHighestTrafficServers(*DS,0,1,&sum);
    assert(s==SUCCESS && sum==60);
    s=SumHighestTrafficServers(*DS,0,3,&sum);
    assert(s==SUCCESS && sum==115);
    s=RemoveServer(*DS,8);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,5,1,&sum);
    assert(s==SUCCESS && sum==30);
    s=SetTraffic(*DS,7,100);
    assert(s==SUCCESS);
    s=SumHighestTrafficServers(*DS,0,1,&sum);
    assert(s==SUCCESS && sum==100);
    s=SumHighestTrafficServers(*DS,5,1,&sum);
    assert(s==SUCCESS && sum==100);
    s=SumHighestTrafficServers(*DS,5,2,&sum);
    assert(s==SUCCESS && sum==130);
    s=SumHighestTrafficServers(*DS,9,2,&sum);
    assert(s==SUCCESS && sum==130);
    s=SumHighestTrafficServers(*DS,4,2,&sum);
    assert(s==SUCCESS && sum==130);
    s=SumHighestTrafficServers(*DS,5,6,&sum);
    assert(s==SUCCESS && sum==166);
    s=SumHighestTrafficServers(*DS,4,6,&sum);
    assert(s==SUCCESS && sum==166);
    s=SumHighestTrafficServers(*DS,9,6,&sum);
    assert(s==SUCCESS && sum==166);
    Quit(DS);
    delete DS;
    cout<<"*******************************************************"<<"\n";
    cout<<"*******************************************************"<<"\n";
    cout<<"YOU HAVE PASSED THE TEST ^___^"<<"\n"<<"GOOD LUCK IN THE FINAL EXAM";
    cout<<"\n"<<"*******************************************************"<<"\n";
    cout<<"*******************************************************"<<"\n";
}

void test3() {

    void **DS = new (void *);
    *DS = Init(10);
    assert(*DS != nullptr);
    StatusType s = AddServer(*DS, 11, 10);
    assert(s == INVALID_INPUT);
    s = AddServer(*DS, 0, 10);
    assert(s == INVALID_INPUT);
    s = AddServer(*DS, -1, 10);
    assert(s == INVALID_INPUT);
    s = AddServer(*DS, 5, 0);
    assert(s == INVALID_INPUT);
    s = AddServer(*DS, 5, -44);
    assert(s == INVALID_INPUT);
    s = AddServer(nullptr, 5, -44);
    assert(s == INVALID_INPUT);
    s = AddServer(*DS, 5, 1);
    assert(s == SUCCESS);
    s = AddServer(*DS, 5, 1);
    assert(s == FAILURE);
    s = AddServer(*DS, 1, 1);
    assert(s == FAILURE);
    s = AddServer(*DS, 1, 2);
    assert(s == SUCCESS);
    s = AddServer(*DS, 1, 3);
    assert(s == SUCCESS);
    s = AddServer(*DS, 2, 3);
    assert(s == FAILURE);
    s = AddServer(*DS, 2, 4);
    assert(s == SUCCESS);
    s = AddServer(*DS, 10, 5);
    assert(s == SUCCESS);
    s = AddServer(*DS, 10, 6);
    assert(s == SUCCESS);
    s = AddServer(*DS, 9, 6);
    assert(s == FAILURE);
    s = AddServer(*DS, 9, 7);
    assert(s == SUCCESS);
    s = AddServer(*DS, 9, 8);
    assert(s == SUCCESS);
    s = AddServer(*DS, 8, 9);
    assert(s == SUCCESS);
    s = AddServer(*DS, 8, 10);
    assert(s == SUCCESS);
    s = AddServer(*DS, 8, 11);
    assert(s == SUCCESS);
    s = AddServer(*DS, 7, 12);
    assert(s == SUCCESS);
    s = AddServer(*DS, 7, 13);
    assert(s == SUCCESS);
    s = AddServer(*DS, 6, 14);
    assert(s == SUCCESS);
    s = AddServer(*DS, 5, 15);
    assert(s == SUCCESS);
    s = AddServer(*DS, 5, 16);
    assert(s == SUCCESS);
    s = AddServer(*DS, 4, 17);
    assert(s == SUCCESS);
    s = AddServer(*DS, 4, 18);
    assert(s == SUCCESS);
    s = AddServer(*DS, 3, 19);
    assert(s == SUCCESS);
    s = AddServer(*DS, 3, 20);
    assert(s == SUCCESS);
    s = RemoveServer(*DS, 4);
    assert(s == SUCCESS);
    s = RemoveServer(*DS, 4);
    assert(s == FAILURE);
    s = RemoveServer(*DS, 10);
    assert(s == SUCCESS);
    s = RemoveServer(*DS, 21);
    assert(s == FAILURE);
    s = RemoveServer(*DS, 0);
    assert(s == INVALID_INPUT);
    s = RemoveServer(nullptr, 9);
    assert(s == INVALID_INPUT);
    s = SetTraffic(nullptr, 3, 3);
    assert(s == INVALID_INPUT);
    s = SetTraffic(*DS, 0, 3);
    assert(s == INVALID_INPUT);
    s = SetTraffic(*DS, -1, 3);
    assert(s == INVALID_INPUT);
    s = SetTraffic(*DS, 21, 3);
    assert(s == FAILURE);
    s = SetTraffic(*DS, 4, 3);
    assert(s == FAILURE);
    s = SetTraffic(*DS, 10, 3);
    assert(s == FAILURE);
    s = SetTraffic(*DS, 1, -1);
    assert(s == INVALID_INPUT);
    s = SetTraffic(*DS, 5, -1);
    assert(s == INVALID_INPUT);
    s = SetTraffic(*DS, 10, -1);
    assert(s == INVALID_INPUT);
    s = SetTraffic(*DS, 9, -1);
    assert(s == INVALID_INPUT);
    s = SetTraffic(*DS, 4, -1);
    assert(s == INVALID_INPUT);
    s = SetTraffic(*DS, 14, -1);
    assert(s == INVALID_INPUT);
    s = SetTraffic(*DS, 14, 5);
    assert(s == SUCCESS);
    s = SetTraffic(*DS, 20, 11);
    assert(s == SUCCESS);
    s = SetTraffic(*DS, 3, 11);
    assert(s == SUCCESS);
    s = SetTraffic(*DS, 2, 3);
    assert(s == SUCCESS);
    s = SetTraffic(*DS, 6, 4);
    assert(s == SUCCESS);
    s = SetTraffic(*DS, 13, 7);
    assert(s == SUCCESS);
    s = SetTraffic(*DS, 18, 25);
    assert(s == SUCCESS);
    s = SetTraffic(*DS, 16, 12);
    assert(s == SUCCESS);
    s = SetTraffic(*DS, 12, 12);
    assert(s == SUCCESS);
    s = SetTraffic(*DS, 7, 5);
    assert(s == SUCCESS);
    s = SetTraffic(*DS, 8, 5);
    assert(s == SUCCESS);
    s = SetTraffic(*DS, 8, 10);
    assert(s == SUCCESS);
    int sum = 0;
    s = SumHighestTrafficServers(nullptr, 5, 1, &sum);
    assert(s == INVALID_INPUT);
    s = SumHighestTrafficServers(*DS, 5, -1, &sum);
    assert(s == INVALID_INPUT);
    s = SumHighestTrafficServers(*DS, 21, 1, &sum);
    assert(s == INVALID_INPUT);
    s = SumHighestTrafficServers(*DS, -1, 1, &sum);
    assert(s == INVALID_INPUT);
    s = SumHighestTrafficServers(*DS, 0, 1, &sum);
    assert(s == SUCCESS && sum == 25);
    s = SumHighestTrafficServers(*DS, 0, 3, &sum);
    assert(s == SUCCESS && sum == 49);
    s = SumHighestTrafficServers(*DS, 0, 5, &sum);
    assert(s == SUCCESS && sum == 71);
    s = SetTraffic(*DS, 3, 2);
    assert(s == SUCCESS);
    s = SumHighestTrafficServers(*DS, 0, 5, &sum);
    assert(s == SUCCESS && sum == 70);
    s = SetTraffic(*DS, 9, 21);
    assert(s == SUCCESS);
    s = SumHighestTrafficServers(*DS, 0, 5, &sum);
    assert(s == SUCCESS && sum == 81);
    s = SumHighestTrafficServers(*DS, 5, 3, &sum);
    assert(s == SUCCESS && sum == 12);
    s = SetTraffic(*DS, 15, 2);
    assert(s == SUCCESS);
    s = SumHighestTrafficServers(*DS, 5, 3, &sum);
    assert(s == SUCCESS && sum == 14);
    s = SetTraffic(*DS, 1, 1);
    assert(s == SUCCESS);
    s = SumHighestTrafficServers(*DS, 5, 3, &sum);
    assert(s == SUCCESS && sum == 15);
    s = MergeDataCenters(nullptr, 5, 2);
    assert(s == INVALID_INPUT);
    s = MergeDataCenters(*DS, 4, 0);
    assert(s == INVALID_INPUT);
    s = MergeDataCenters(*DS, 0, 4);
    assert(s == INVALID_INPUT);
    s = MergeDataCenters(*DS, 21, 4);
    assert(s == INVALID_INPUT);
    s = MergeDataCenters(*DS, 4, 23);
    assert(s == INVALID_INPUT);
    s = MergeDataCenters(*DS, 4, 5);
    assert(s == SUCCESS);
    s = SumHighestTrafficServers(*DS, 4, 3, &sum);
    assert(s == SUCCESS && sum == 39);
    s = SumHighestTrafficServers(*DS, 5, 3, &sum);
    assert(s == SUCCESS && sum == 39);
    s = SetTraffic(*DS, 16, 8);
    assert(s == SUCCESS);
    s = SumHighestTrafficServers(*DS, 5, 3, &sum);
    assert(s == SUCCESS && sum == 35);
    s = SumHighestTrafficServers(*DS, 5, 1, &sum);
    assert(s == SUCCESS && sum == 25);
    s = SumHighestTrafficServers(*DS, 5, 2, &sum);
    assert(s == SUCCESS && sum == 33);
    s = SumHighestTrafficServers(*DS, 5, 4, &sum);
    assert(s == SUCCESS && sum == 36);
    s = SumHighestTrafficServers(*DS, 5, 5, &sum);
    assert(s == SUCCESS && sum == 36);
    s = SumHighestTrafficServers(*DS, 4, 3, &sum);
    assert(s == SUCCESS && sum == 35);
    s = SumHighestTrafficServers(*DS, 4, 1, &sum);
    assert(s == SUCCESS && sum == 25);
    s = SumHighestTrafficServers(*DS, 4, 2, &sum);
    assert(s == SUCCESS && sum == 33);
    s = SumHighestTrafficServers(*DS, 4, 4, &sum);
    assert(s == SUCCESS && sum == 36);
    s = SumHighestTrafficServers(*DS, 4, 5, &sum);
    assert(s == SUCCESS && sum == 36);
    s = AddServer(*DS, 4, 10);
    assert(s == SUCCESS);
    s = SetTraffic(*DS, 10, 30);
    assert(s == SUCCESS);
    s = SumHighestTrafficServers(*DS, 4, 2, &sum);
    assert(s == SUCCESS && sum == 55);
    s = SumHighestTrafficServers(*DS, 5, 2, &sum);
    assert(s == SUCCESS && sum == 55);
    s = MergeDataCenters(*DS, 4, 9);
    assert(s == SUCCESS);
    s = SetTraffic(*DS, 8, 60);
    assert(s == SUCCESS);
    s = SumHighestTrafficServers(*DS, 4, 1, &sum);
    assert(s == SUCCESS && sum == 60);
    s = SumHighestTrafficServers(*DS, 5, 1, &sum);
    assert(s == SUCCESS && sum == 60);
    s = SumHighestTrafficServers(*DS, 9, 1, &sum);
    assert(s == SUCCESS && sum == 60);
    s = SumHighestTrafficServers(*DS, 4, 2, &sum);
    assert(s == SUCCESS && sum == 90);
    s = SumHighestTrafficServers(*DS, 5, 2, &sum);
    assert(s == SUCCESS && sum == 90);
    s = SumHighestTrafficServers(*DS, 9, 2, &sum);
    assert(s == SUCCESS && sum == 90);
    s = SumHighestTrafficServers(*DS, 5, 4, &sum);
    assert(s == SUCCESS && sum == 123);
    s = SumHighestTrafficServers(*DS, 0, 1, &sum);
    assert(s == SUCCESS && sum == 60);
    s = SumHighestTrafficServers(*DS, 0, 3, &sum);
    assert(s == SUCCESS && sum == 115);
    s = RemoveServer(*DS, 8);
    assert(s == SUCCESS);
    s = SumHighestTrafficServers(*DS, 5, 1, &sum);
    assert(s == SUCCESS && sum == 30);
    s = SetTraffic(*DS, 7, 100);
    assert(s == SUCCESS);
    s = SumHighestTrafficServers(*DS, 0, 1, &sum);
    assert(s == SUCCESS && sum == 100);
    s = SumHighestTrafficServers(*DS, 5, 1, &sum);
    assert(s == SUCCESS && sum == 100);
    s = SumHighestTrafficServers(*DS, 5, 2, &sum);
    assert(s == SUCCESS && sum == 130);
    s = SumHighestTrafficServers(*DS, 9, 2, &sum);
    assert(s == SUCCESS && sum == 130);
    s = SumHighestTrafficServers(*DS, 4, 2, &sum);
    assert(s == SUCCESS && sum == 130);
    s = SumHighestTrafficServers(*DS, 5, 6, &sum);
    assert(s == SUCCESS && sum == 166);
    s = SumHighestTrafficServers(*DS, 4, 6, &sum);
    assert(s == SUCCESS && sum == 166);
    s = SumHighestTrafficServers(*DS, 9, 6, &sum);
    assert(s == SUCCESS && sum == 166);
    Quit(DS);
    delete DS;
    cout << "*******************************************************" << "\n";
    cout << "*******************************************************" << "\n";
    cout << "YOU HAVE PASSED THE TEST ^___^" << "\n"
         << "GOOD LUCK IN THE FINAL EXAM";
    cout << "\n" << "*******************************************************"
         << "\n";
    cout << "*******************************************************" << "\n";
}
int main() {

    test1();
    test2();
    test3();

    return 0;
}