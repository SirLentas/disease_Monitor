#include <iostream>
using namespace std;

class DataNode
{
public:
    char *key;
    char *fn;
    char *ln;
    char *dis;
    char *cntr;
    int inDate;
    int outDate;
    DataNode *next;
};

class List
{
public:
    DataNode *head, *tail;

    List();
    ~List();
    DataNode *add_node(char *key, char *fn, char *ln, char *dis, char *c, int in, int out); 
    bool searchKey(char *);
    bool changeED(char *x,int out);
    void print();
};
