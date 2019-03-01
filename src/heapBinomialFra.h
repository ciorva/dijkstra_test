#ifndef BINOMIALHEAP
#define BINOMIALHEAP

#include "heapType.h"

typedef struct binomialHeapNode {
    struct binomialHeapNode* child;
	struct binomialHeapNode* sibling;
	struct binomialHeapNode* father;
	int degree;
    elementHeap elem ;
}*bHeap;

/*
typedef struct binomialHeap {
	bNode root ;
    int maxDim;
    int* father;    
}* bHeap;
*/

bHeap newEmptyBinomialHeap();
bHeap insertElementBinomialHeap(bHeap h,int distance, int dest);
bHeap deleteMinBinomialHeap(bHeap h);
int notEmpty(bHeap h);
int getMinDistance(bHeap h);
int getMinDest(bHeap h);

bHeap mergeBinomialHeaps(bHeap smaller, bHeap greater);
bHeap fixHeap(bHeap h);
bHeap DegreeOrder(bHeap h);
void printBin(bHeap h1);
bHeap mergeBinomialHeaps(bHeap smaller, bHeap greater);
void printSubHeap(bHeap p);
void freeBheap(bHeap t);
void printBinDestination(bHeap H);
void printSubHeapDestination(bHeap p);

#endif