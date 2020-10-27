#include <iostream>
#include "AVL.h"
using namespace std;

class pNode
{
public:
    AVL **treeHead;
    int howmany;
    pNode *pNext;

    pNode(int n);
};

class HashChain
{
public:
    pNode *head, *tail;
    int max;
    HashChain();
    ~HashChain();
    void add_node(DataNode *ptr);
    bool findKey(DataNode *, bool);
    AVL* ret_root(char*);
    void print();
};

int hashFunction(const char *key, int TABLE_SIZE);
