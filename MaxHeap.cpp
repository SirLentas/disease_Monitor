#include <iostream>
#include "MaxHeap.h"
using namespace std;


MaxHeap::MaxHeap(int capacity)
{
  arr = new HeapNode *[capacity];
  this->capacity = capacity;
  this->size = 0; 
}

MaxHeap::~MaxHeap()
{
  delete[] arr;
}


int MaxHeap::getSize()
{
  return size;
}

int MaxHeap::parent(int child)
{
  if (child % 2 == 0)
    return (child / 2) - 1;
  else
    return (child / 2);
}

int MaxHeap::left(int parent)
{
  return (2 * parent + 1);
}

int MaxHeap::right(int parent)
{
  return (2 * parent + 2);
}
void MaxHeap::siftup(int i)
{
  if (i == 0)
    return; //  επιστρεφει επειδη υπαρχει μονο 1 στοιχειο

  int parent_index = parent(i);

  if (arr[parent_index]->counter < arr[i]->counter)
  {
    HeapNode *temp = arr[parent_index]; //Αν η τιμη στο parent_index ειναι μικτροτερη απο τη τιμη μου βαλαμε τους αλλαζει θεση
    arr[parent_index] = arr[i];         
    arr[i] = temp;
    siftup(parent_index); // εκτελειται αναδρομικα εως οτου να ικανοποιηθει η συνθηκη του ορισμου της MAx Heap
  }
}
void MaxHeap::insert(HeapNode *k)
{
  arr[size] = k; // εισαγει την τιμη στον πινακα
  siftup(size);
  size++; // αυξανει τον αριθμο των τιμων στο πινακα
}

bool MaxHeap::isLeaf(int i)
{
  if (i >= size)
    return true;
  return false;
}
void MaxHeap::siftdown(int i) // εκτελειται αναδρομικα μετα την εξαγωγη του μεγιστου, με σκοπο να επαναφερει το Max Heap σε φθινουσα σειρα
{
  int l = left(i);
  int r = right(i);

  if (isLeaf(l))
    return;

  int maxIndex = i;
  if (arr[l]->counter > arr[i]->counter)  // αν ο counter του αριστερου παιδιου ειναι μεγαλυτερος το maxIndex γινεται l
  {
    maxIndex = l;
  }

  if (!isLeaf(r) && (arr[r]->counter > arr[maxIndex]->counter))  // αν ο counter του δεξιου παιδιου ειναι μεγαλυτερος το maxIndex γινεται r
  {
    maxIndex = r;
  }

  if (maxIndex != i)     // αν εχει αλλαξει το max index τοτε συνεχισε σε χαμηλοτερο επιπεδο
  {
    HeapNode *temp = arr[i];
    arr[i] = arr[maxIndex];
    arr[maxIndex] = temp;
    siftdown(maxIndex);
  }
}
HeapNode *MaxHeap::extractMax()
{

  if (size <= 0)
  {
    //cout << "No more info" << endl;
    return NULL;
  }
  HeapNode *max = arr[0];
  cout << max->value << " " << max->counter<< endl;
  arr[0] = arr[size - 1];

  size--;

  siftdown(0);
  return max;
}

