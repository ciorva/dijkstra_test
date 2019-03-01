#ifndef HEAPBIN_H
#define HEAPBIN_H

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

#include "heapType.h"

typedef struct binHeap {
    int size;
	int maxSize;
    elementHeap*elem ;
	int*hash;
}*binHeap;

binHeap newBinHeap(int maxSize);

void insertElementBinHeap(binHeap h,int distance, int dest);

int getMinDistanceBinHeap(binHeap h);

int getMinDestinationBinHeap(binHeap h);

void heapify(binHeap h, int i);

void deleteMinBinHeap(binHeap h);

void freeBinHeap(binHeap h);

void printHeap(binHeap h);

#endif


