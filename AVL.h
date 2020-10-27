#include <iostream>
#include "list.h"
#include "MaxHeap.h"
using namespace std;

typedef int KEY_TYPE;

class AVL
{
public:
	DataNode *Data_ptr;
	int height;
	struct AVL *lchild;
	struct AVL *rchild;

	void destr(AVL*);
	void destrHelp(AVL*);
};

AVL *New_Node(DataNode *, AVL *lchild, AVL *rchild, int height = 0);
inline int getHeight(AVL *node);

AVL *RR_Rotate(AVL *k2);
AVL *LL_Rotate(AVL *k2);

AVL *LR_Rotate(AVL *k3);

AVL *RL_Rotate(AVL *k3);

AVL *Insert(AVL *root, DataNode *key);

void InOrder(AVL *root);
void orderie(AVL *root);
void printNode(AVL *);

void ret_list(AVL*,HList &, int, int);
void rettie(AVL *, HList &, int, int);
void ret_list_d(AVL*,HList &, int, int);
void rettie_d(AVL *, HList &, int, int);
int count(AVL*,int, int);
void countie(AVL *, int &, int, int);
int dis_f(AVL*,char *, int, int);
void dis_fie(AVL *, char *, int &, int, int);

int count_cur(AVL*);
void cur_countie(AVL *, int &);

void create_m_h(AVL *, int, int, int);
void create_m_h_d(AVL *, int, int, int);
