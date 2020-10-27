#include <iostream>
#include <string.h>
#include "HeapList.h"
using namespace std;

class MaxHeap
{
    HeapNode **arr;     
    int capacity; 
    int size;     

    int parent(int i);
    int left(int i);
    int right(int i);
    bool isLeaf(int i);
    void siftup(int i);
    void siftdown(int i);

public:
    MaxHeap(int capacity);
    ~MaxHeap();
    int getSize();
    void insert(HeapNode*);
    HeapNode* extractMax();
};

