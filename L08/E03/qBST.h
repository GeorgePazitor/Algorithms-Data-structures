#ifndef LAB8_3_QBST_H
#define LAB8_3_QBST_H
#include <stdlib.h>
#include <float.h>
#include "quot.h"

typedef struct binarysearchtree *BST;

BST BSTinit() ;
void BSTfree(BST bst);
quot BSTsearch(BST bst, data k);
void BSTinsert_leafR(BST bst, quot x);
int BSTmodify(BST bst, data k, ora o, int v, int n);
float BSTceckbalance(BST bst, float s);
void BSTbalance(BST bst);
void inOrderDTRic(BST bst,data d1, data d2);





#endif //LAB8_3_QBST_H
