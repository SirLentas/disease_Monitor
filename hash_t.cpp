#include "hash_t.h"
#include <string.h>
using namespace std;

pNode::pNode(int n)
{
    treeHead = new AVL *[n];
    howmany = 0;
}

HashChain::HashChain()
{
    head = NULL;
    tail = NULL;
};

void HashChain::add_node(DataNode *ptr) 
{
    AVL *tree=NULL;
    tree=Insert(tree,ptr);

    if (head == NULL)
    {
        pNode *tmp = new pNode(this->max);
        tmp->treeHead[tmp->howmany] = tree;
        (tmp->howmany)++;
        head = tmp;
        tail = tmp;
    }
    else
    {
        if (tail->howmany < this->max)
        {
            tail->treeHead[tail->howmany] = tree;
            (tail->howmany)++;
        }
        else
        {
            pNode *tmp = new pNode(this->max);
            tmp->treeHead[tmp->howmany] = tree;
            (tmp->howmany)++;
            tail->pNext = tmp;
            tail = tail->pNext;
        }
    }
}

int hashFunction(const char *key, int TABLE_SIZE) //sdbm
{
    const char *str = key;
    unsigned int hash = 0;
    int c;
    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;
    return hash % TABLE_SIZE;
}

bool HashChain::findKey(DataNode *key, bool mode) //mode==1 disease, mode==0 country
{
    pNode *sherlock;
    sherlock = this->head;
    if (sherlock == NULL)
        return 0;
    while (sherlock != NULL)    
    {
        if (mode == 1)  // αναλογα το mode κανει τους αναλογους ελεγχους ειτε για disease ειτε για country
        {
            for (int i = 0; i < this->max; i++)
            {
                if (sherlock->treeHead[i] != NULL)
                {

                    if (strcmp(sherlock->treeHead[i]->Data_ptr->dis, key->dis) == 0)
                    {
                        sherlock->treeHead[i]=Insert(sherlock->treeHead[i],key);
                        return 1;
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < this->max; i++)
            {
                if (sherlock->treeHead[i] != NULL)
                {

                    if (strcmp(sherlock->treeHead[i]->Data_ptr->cntr, key->cntr) == 0)
                    {
                        sherlock->treeHead[i]=Insert(sherlock->treeHead[i],key);
                        return 1;
                    }
                }
            }
        }
        sherlock = sherlock->pNext;
    }
    return 0;
}

AVL *HashChain::ret_root(char *key)
{
    pNode *sherlock;
    sherlock = this->head;
    if (sherlock == NULL)
        return 0;
    while (sherlock != NULL)
    {

        for (int i = 0; i < this->max; i++)
        {
            if (sherlock->treeHead[i] != NULL)
            {

                if (strcmp(sherlock->treeHead[i]->Data_ptr->cntr, key) == 0)
                {
                    return sherlock->treeHead[i];
                }
                if (strcmp(sherlock->treeHead[i]->Data_ptr->dis, key) == 0)
                {
                    return sherlock->treeHead[i];
                }
            }
        }
        sherlock = sherlock->pNext;
    }
    return NULL;
}

HashChain::~HashChain()
{
    pNode *temp;
    pNode *temp_next;

    temp = head;
    while (NULL != temp)
    {
        temp_next = temp->pNext;
        for (int i = 0; i < max; i++)
        { 
            temp->treeHead[i]->destr(temp->treeHead[i]);  
        }
        delete[] temp->treeHead;
        delete temp;
        temp = temp_next;
    }     
}