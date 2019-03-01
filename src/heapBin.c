#include <stdlib.h>
#include <stdio.h>
#include "heapBin.h"

binHeap newBinHeap(int maxSize){
	int i;    
	binHeap h = malloc(sizeof(struct binHeap));
	h->elem=malloc(sizeof(elementHeap)*maxSize);
	h->hash=malloc(sizeof(int)*maxSize);	
	h->maxSize=maxSize;
    h->size = 0;
	for(i=0;i<maxSize;i++)h->hash[i]=-1;
    return h ;
}

void insertElementBinHeap(binHeap h,int distance, int dest) {	
	int i;
	elementHeap nN;
	if (h->hash[dest]==-1){	
		nN = malloc(sizeof(struct elementHeap));
		nN->distance=distance;
		nN->dest=dest;
    	i = (h->size)++;
	}else{
		if(h->elem[h->hash[dest]]->distance>distance){
			h->elem[h->hash[dest]]->distance=distance;
			i=h->hash[dest];
			nN=h->elem[h->hash[dest]];
		}else return;		
	}
    while(i && distance < h->elem[PARENT(i)]->distance){
        h->elem[i] = h->elem[PARENT(i)];
		h->hash[h->elem[PARENT(i)]->dest]=i;
        i = PARENT(i);
    }
    h->elem[i] = nN;
	h->hash[nN->dest]=i;
}

int getMinDistanceBinHeap(binHeap h){
	if (h->size>0) return h->elem[0]->distance;
	else return -1;
}

int getMinDestinationBinHeap(binHeap h){
	if (h->size>0) return h->elem[0]->dest;
	else return -1;
}

void heapify(binHeap h, int i){
    elementHeap temp;
	int smallest = (LCHILD(i) < h->size && h->elem[LCHILD(i)]->distance < h->elem[i]->distance) ? LCHILD(i) : i ;
    if(RCHILD(i) < h->size && h->elem[RCHILD(i)]->distance < h->elem[smallest]->distance) {
        smallest = RCHILD(i) ;
    }
    if(smallest != i){
		h->hash[h->elem[i]->dest]=smallest;
		h->hash[h->elem[smallest]->dest]=i;        
		temp=h->elem[i];
		h->elem[i]=h->elem[smallest];
		h->elem[smallest]=temp;		
		heapify(h, smallest);
    }
}

void deleteMinBinHeap(binHeap h) {
	if (h->size==0) return;    
	h->hash[h->elem[0]->dest]=-1;	
	free(h->elem[0]);    
	h->elem[0] = h->elem[--(h->size)];
    heapify(h, 0);
}


void freeBinHeap(binHeap h){
	int i;
	for(i=0;i<h->size;i++) free(h->elem[i]);
	free(h->hash);	
	free(h->elem);
	free(h);
}

void printHeap(binHeap h){
	int i;
	printf("HEAP:\n");
	for(i=0;i<h->size;i++){
		printf("element %d size %d \n\n",h->elem[i]->dest,h->elem[i]->distance);
	}
}








