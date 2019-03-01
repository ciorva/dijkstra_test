#ifndef FIBHEAP_H
#define FIBHEAP_H

#include "heapType.h"

typedef struct fibNode{
	int mDegree;
	struct fibNode* mNext;
	struct fibNode* mPrev;
	struct fibNode* mParent;
	struct fibNode* mChild;
	int mIsMarked;
	elementHeap el;
}* fibNode;

typedef struct fibHeap{
	int size;
	fibNode min;
	fibNode*hash;
}* fibHeap;

typedef struct fibList{
	fibNode item;
	struct fibList* next;
}* fibList;

fibNode newFibNode(int dest, int distance);

fibHeap newFibHeap(int n);

fibNode mergeLists(fibNode one, fibNode two);

fibHeap merge(fibHeap one, fibHeap two);

void insertElementFibHeap(fibHeap fH,int distance, int dest);

int getMinDistanceFibHeap(fibHeap hF);

int getMinDestFibHeap(fibHeap hF);

void deleteMinFibHeap(fibHeap fH);

void cutNode(fibHeap hF,fibNode entry);

void decreaseKey(fibHeap hF, fibNode entry, int nD);

void printFibHeap(fibNode bn,int lev);

void freeFibHeap(fibHeap fH);

#endif

