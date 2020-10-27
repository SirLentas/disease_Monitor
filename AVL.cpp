#include "AVL.h"
#include <iostream>

AVL *New_Node(DataNode *ptr, AVL *lchild, AVL *rchild, int height)
{
	AVL *p_avl = new AVL;
	p_avl->Data_ptr = ptr;
	p_avl->lchild = lchild;
	p_avl->rchild = rchild;
	p_avl->height = height;
	return p_avl;
}

inline int getHeight(AVL *node)
{
	return (node == NULL) ? -1 : node->height;
}

inline int max(int a, int b)
{
	return a > b ? a : b;
}

AVL *RR_Rotate(AVL *k2) // περιστρεφει το δεντρο προς τα δεξια, το αριστερο παιδι του root γινεται root, με δεξι παιδι το παλιο root
{
	AVL *k1 = k2->lchild;
	k2->lchild = k1->rchild;  // Αν το νεο root ειχε δεξι παιδι τοτε αυτο γινεται αριστερο παιδι του παλιου root 
                            // (Αν δεν υπαρχει σημαινει οτι ηταν NULL, αρα δεν υπαρχει ελεγχος)
	k1->rchild = k2;
	k2->height = max(getHeight(k2->lchild), getHeight(k2->rchild)) + 1; 
	k1->height = max(getHeight(k1->lchild), k2->height) + 1;
	return k1;
}

AVL *LL_Rotate(AVL *k2) // περιστρεφει το δεντρο προς τα αριστερα, το δεξι παιδι του root γινεται root, με αριστερο παιδι το παλιο root
{
	AVL *k1 = k2->rchild;
	k2->rchild = k1->lchild;  // Αν το νεο root ειχε αριστερο παιδι τοτε αυτο γινεται δεξι παιδι του παλιου root 
	k1->lchild = k2;
	k2->height = max(getHeight(k2->lchild), getHeight(k2->rchild)) + 1;
	k1->height = max(getHeight(k1->rchild), k2->height) + 1;
	return k1;
}
AVL *LR_Rotate(AVL *k3)
{
	k3->lchild = LL_Rotate(k3->lchild); // κανει μια αριστερη περιστροφη στο αριστερο παιδι της ριζας
	return RR_Rotate(k3);               // και στο τελος κανει μια δεξια περιστροφη σε ολοκληρο το δεντρο
}

AVL *RL_Rotate(AVL *k3)
{
	k3->rchild = RR_Rotate(k3->rchild);
	return LL_Rotate(k3);
}

AVL *Insert(AVL *root, DataNode *ptr)
{
	if (root == NULL)
		return (root = New_Node(ptr, NULL, NULL));
	else if (ptr->inDate < root->Data_ptr->inDate)
		root->lchild = Insert(root->lchild, ptr);   // αναδρομικα βρισκει το σημειο που θα κανει insert
	else 
		root->rchild = Insert(root->rchild, ptr);

	root->height = max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
	if (getHeight(root->lchild) - getHeight(root->rchild) == 2)   // ισορροπει το δεντρο μετα την εισαγωγη
	{
		if (ptr->inDate < root->lchild->Data_ptr->inDate)
			root = RR_Rotate(root); 
		else
			root = LR_Rotate(root);
	}
	else if (getHeight(root->rchild) - getHeight(root->lchild) == 2)
	{
		if (ptr->inDate < root->rchild->Data_ptr->inDate)
			root = RL_Rotate(root);
		else
			root = LL_Rotate(root);
	}
	return root;
}


// οι παρακατω συναρτησεις ελεγχουν αναδρομικα το δεντρο και εξαγουν αποτελεσματα, τα οποια φαινονται στο readme
void InOrder(AVL *root)
{
	if (root == NULL)
		return;
	else
		orderie(root);
}

void orderie(AVL *x)
{
	if (x == NULL)
		return;
	orderie(x->lchild);
	printNode(x);
	orderie(x->rchild);
}

void printNode(AVL *x)
{
	cout << x->Data_ptr->fn << " " << x->Data_ptr->ln << " " << x->Data_ptr->dis << " " << x->Data_ptr->cntr << " " << x->Data_ptr->inDate << " " << x->Data_ptr->outDate << endl;
}

void ret_list(AVL* root,HList &list, int in, int out)
{
  if (root == NULL)
    cout << "Tree is empty" << endl;
  else
    rettie(root, list, in, out);
  //cout << endl;
}

void rettie(AVL* x, HList &list, int in, int out)
{
  if (x == NULL)
    return;
  rettie(x->lchild, list, in, out);
  if (x->Data_ptr->inDate >= in && x->Data_ptr->inDate <= out && list.search(x->Data_ptr->dis) == 0)
    list.add_node(x->Data_ptr->dis);
  rettie(x->rchild, list, in, out);
}

void ret_list_d(AVL* root,HList &list, int in, int out)
{
  if (root == NULL)
    cout << "Tree is empty" << endl;
  else
    rettie_d(root, list, in, out);
  //cout << endl;
}

void rettie_d(AVL* x, HList &list, int in, int out)
{
  if (x == NULL)
    return;
  rettie_d(x->lchild, list, in, out);
  if (x->Data_ptr->inDate >= in && x->Data_ptr->inDate <= out && list.search(x->Data_ptr->cntr) == 0)
    list.add_node(x->Data_ptr->cntr);
  rettie_d(x->rchild, list, in, out);
}


int count(AVL* root,int from, int to)
{
  int a = 0;
  if (root == NULL)
    return a;
  else
    countie(root, a, from, to);
  return a;
}

void countie(AVL* x, int &a, int from, int to)
{
  if (x == NULL)
    return;
  countie(x->lchild, a, from, to);
  if (x->Data_ptr->inDate >= from && x->Data_ptr->inDate <= to)
    a++;
  countie(x->rchild, a, from, to);
}

int dis_f(AVL* root,char *country, int from, int to)
{
  int a = 0;
  if (root == NULL)
    return a;
  else
    dis_fie(root, country, a, from, to);
  return a;
}

void dis_fie(AVL* x, char *country, int &a, int from, int to)
{
  if (x == NULL)
    return;

  dis_fie(x->lchild, country, a, from, to);
  if (x->Data_ptr->inDate >= from && x->Data_ptr->inDate <= to && (strcmp(x->Data_ptr->cntr, country) == 0))
    a++;
  dis_fie(x->rchild, country, a, from, to);
}

int count_cur(AVL* root)
{
  int a = 0;
  if (root == NULL)
    return a;
  else
    cur_countie(root, a);
  return a;
}

void cur_countie(AVL* x, int &a)
{
  if (x == NULL)
    return;
  cur_countie(x->lchild, a);
  if (x->Data_ptr->outDate == 800000)
    a++;
  cur_countie(x->rchild, a);
}




void AVL::destr(AVL* root) //αντι destructor
{
  if (root == NULL)
    return;
  else
    destrHelp(root);
}

void AVL::destrHelp(AVL *x)
{
  if (x == NULL)
    return;
  destrHelp(x->lchild);
  destrHelp(x->rchild);
  delete x;

}


void create_m_h(AVL *ax, int k, int in, int out)
{
  HList heap_l;
  ret_list(ax,heap_l, in, out); // δημιουργει μια λιστα οπου περιεχονται τα στατιστικα για το δεντρο
  MaxHeap mh(heap_l.length());
  HeapNode *sherlock;
  sherlock = heap_l.head;
  while (sherlock != NULL)  // εισαγει καθε κομβο στο Max Heap
  {
    mh.insert(sherlock);
    sherlock = sherlock->next;
  }
  for (int i = 0; i < k; i++) // κανει k φορες εξαγωγη του μεγιστου
  {
    mh.extractMax();
  }
}

void create_m_h_d(AVL *ax, int k, int in, int out)
{
  HList heap_l;
  ret_list_d(ax,heap_l, in, out);
  MaxHeap mh(heap_l.length());
  HeapNode *sherlock;
  sherlock = heap_l.head;
  while (sherlock != NULL)
  {
    
    mh.insert(sherlock);
    sherlock = sherlock->next;
  }
  for (int i = 0; i < k; i++)
  {
    mh.extractMax();
  }
}