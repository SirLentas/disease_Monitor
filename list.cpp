#include <iostream>
#include <string.h>
#include "list.h"
using namespace std;

List::List()
{
    head = NULL;
    tail = NULL;
};

DataNode *List::add_node(char *key, char *fn, char *ln, char *dis, char *c, int in, int out)
{
    DataNode *tmp = new DataNode;
    tmp->key = new char[strlen(key) + 1];
    strcpy(tmp->key, key);
    tmp->fn = new char[strlen(fn) + 1];
    strcpy(tmp->fn, fn);
    tmp->ln = new char[strlen(ln) + 1];
    strcpy(tmp->ln, ln);
    tmp->dis = new char[strlen(dis) + 1];
    strcpy(tmp->dis, dis);
    tmp->cntr = new char[strlen(c) + 1];
    strcpy(tmp->cntr, c);
    tmp->inDate = in;
    tmp->outDate = out;
    tmp->next = NULL;

    if (head == NULL)
    {
        head = tmp;
        tail = tmp;
    }
    else
    {
        tail->next = tmp;
        tail = tail->next;
    }
    return tmp;
}
void List::print()
{
    DataNode *sherlock;
    sherlock = head;
    while (sherlock != NULL)
    {
        cout << sherlock->key << " " << sherlock->fn << " " << sherlock->ln << " " << sherlock->dis << " " << sherlock->cntr << " " << sherlock->inDate << " " << sherlock->outDate << endl;

        sherlock = sherlock->next;
    }
    return;
}

bool List::searchKey(char *x)
{
    DataNode *sherlock;
    sherlock = head;
    while (sherlock != NULL)
    {
        if (strcmp(sherlock->key, x) == 0)
        {
            cout << "Same ID found" << endl;
            return 1;
        }

        sherlock = sherlock->next;
    }
    return 0;
}

bool List::changeED(char *x, int out)
{
    DataNode *sherlock;
    sherlock = head;
    while (sherlock != NULL)
    {
        if (strcmp(sherlock->key, x) == 0)
        {
            if (out < sherlock->inDate)
            {
                cout << "outDate<inDate" << endl;
                return 0;
            }
            else
            {

                sherlock->outDate = out;
                cout << "Record updated" << endl;
                return 1;
            }
        }

        sherlock = sherlock->next;
    }
    cout << "Not found" << endl;
    return 0;
}

List::~List()
{
    DataNode *temp;
    DataNode *temp_next;

    temp = head;
    while (NULL != temp)
    {
        temp_next = temp->next;
        delete[] temp->key;
        delete[] temp->fn;
        delete[] temp->ln;
        delete[] temp->dis;
        delete[] temp->cntr;
        delete temp;
        temp = temp_next;
    }
}