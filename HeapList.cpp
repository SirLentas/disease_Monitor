#include <iostream>
#include <string.h>
#include "HeapList.h"
using namespace std;

HList::HList()
{
    head = NULL;
    tail = NULL;
};

HeapNode *HList::add_node(char *value)
{
    HeapNode * tmp=new HeapNode;
    tmp->value=new char[strlen(value) + 1];
    strcpy(tmp->value,value);
    tmp->counter=1; // θετει τον counter =1 γιατι ειανι το 1ο στοιχειο
    tmp->next=NULL;

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

bool HList::search(char *value)
{
    HeapNode * sherlock;
    sherlock=head;
    while (sherlock != NULL)
    {
        if (strcmp(sherlock->value, value) == 0)
        {
            (sherlock->counter)++;
            return 1;
        }

        sherlock = sherlock->next;
    }
    return 0;
}

int HList::length()
{
    int counter=0;
    HeapNode * sherlock;
    sherlock=head;
    while (sherlock != NULL)
    {
        counter++;
        sherlock = sherlock->next;
    }
    return counter;
}

HList::~HList()
{
    HeapNode *temp;
    HeapNode *temp_next;

    temp = head;
    while (NULL != temp)
    {        
        temp_next = temp->next;
        delete temp->value;
        delete temp;
        temp = temp_next;
    }
}