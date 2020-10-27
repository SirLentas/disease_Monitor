#include <iostream>
using namespace std;

class HeapNode
{
public:
    char *value;
    int counter;
    HeapNode *next;
};

class HList
{
public:
    HeapNode *head, *tail;

    HList();
    ~HList();
    HeapNode *add_node(char *);
    bool search(char *);
    void print();
    int length();
};
