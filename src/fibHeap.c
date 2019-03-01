#include <stdlib.h>
#include <stdio.h>
#include "fibHeap.h"

fibNode newFibNode(int dest, int distance){
	fibNode res = malloc(sizeof(struct fibNode));
	res->mNext=res;
	res->mPrev=res;
	res->mChild=NULL;
	res->mParent=NULL;
	elementHeap el = malloc(sizeof (struct elementHeap));
	el->dest=dest;
	el->distance=distance;
	res->el=el;
	res->mIsMarked=0;
	res->mDegree=0;
	return res;
}

fibHeap newFibHeap(int n){
	int i;
	fibHeap fH=malloc(sizeof(struct fibHeap));
	fH->min=NULL;
	fH->size=0;
	fH->hash=malloc(sizeof(fibHeap*)*n);
	for(i=0;i<n;i++)fH->hash[i]=NULL;
	return fH;
}

fibNode mergeLists(fibNode one, fibNode two){
	if (one == NULL && two == NULL) return NULL;
	if (one != NULL && two == NULL) return one;
	if (one == NULL && two != NULL) return two;
	fibNode oneNext = one->mNext;
	one->mNext = two->mNext;
	one->mNext->mPrev = one;
	two->mNext = oneNext;
	two->mNext->mPrev = two;
	return one->el->distance < two->el->distance? one : two;
}

fibHeap merge(fibHeap one, fibHeap two){
	fibHeap result = newFibHeap(one->size + two->size);
	result-> min = mergeLists(one->min, two->min);
	result->size = one->size + two->size;
	free(two);
	free(one);
	return result;
}

void insertElementFibHeap(fibHeap fH,int distance, int dest){
	if(fH->hash[dest]==NULL){
		fibNode fN=newFibNode(dest,distance);
		fH->size++;
		fH->min=mergeLists(fH->min,fN);
		fH->hash[dest]=fN;
		return;
	}
	if(fH->hash[dest]->el->distance<=distance) return;
	decreaseKey(fH,fH->hash[dest],distance);
}

int getMinDistanceFibHeap(fibHeap hF){
	return hF->min->el->distance;
}

int getMinDestFibHeap(fibHeap hF){
	return hF->min->el->dest;
}

void deleteMinFibHeap(fibHeap fH){
	if (fH->size==0) return;
	fibNode curr;	
	fibNode temp = fH->min;
	fH->hash[temp->el->dest]=NULL;
	fH->size--;
	if(fH->min==fH->min->mNext){
		fH->min=NULL;
	}else{
		fH->min->mPrev->mNext = fH->min->mNext;
		fH->min->mNext->mPrev = fH->min->mPrev;
		fH->min=fH->min->mNext;
	}
	if (temp->mChild != NULL) {
		curr = temp->mChild;
		do{
			curr->mParent = NULL;
			curr=curr->mNext;
		}while(curr!=temp->mChild);
	}
	fH->min=mergeLists(fH->min,temp->mChild);
	if (fH->min == NULL) return;
	fibNode treeTable[fH->size];
	int i=0;
	fibList toVisit = NULL;
	for(curr=fH->min;toVisit==NULL || fH->min!=curr;curr=curr->mNext){
		fibList insTemp = toVisit;
		toVisit=malloc(sizeof(struct fibList));
		toVisit->item=curr;
		toVisit->next=insTemp;
	}
	while(toVisit!=NULL){
		while(1){
			while(toVisit->item->mDegree>=i){
				treeTable[i]=NULL;
				i++;			
			}
			if(treeTable[toVisit->item->mDegree]==NULL){
				treeTable[toVisit->item->mDegree]=toVisit->item;
				break;			
			}
			fibNode other = treeTable[toVisit->item->mDegree];
			treeTable[toVisit->item->mDegree]=NULL;
			fibNode min = (other->el->distance < toVisit->item->el->distance)? other : toVisit->item;
			fibNode max = (other->el->distance < toVisit->item->el->distance)? toVisit->item  : other;
			max->mNext->mPrev = max->mPrev;
			max->mPrev->mNext = max->mNext;
			max->mNext = max->mPrev = max;
			min->mChild = mergeLists(min->mChild,max);
			max->mParent=min;
			max->mIsMarked = 0;
			min->mDegree++;
			toVisit->item=min;
		}
		
		if (toVisit->item->el->distance <= fH->min->el->distance) fH->min = toVisit->item;		
		fibList delTemp=toVisit;
		toVisit=toVisit->next;
		free(delTemp);	
	}
	free(temp->el);
	free(temp);
}

void cutNode(fibHeap hF,fibNode entry){
	entry->mIsMarked=0;
	if (entry->mParent == NULL) return;
	if (entry->mNext != entry) {
		entry->mNext->mPrev = entry->mPrev;
		entry->mPrev->mNext = entry->mNext;
	}
	if(entry->mParent->mChild==entry){
		if (entry->mNext != entry) {
			entry->mParent->mChild = entry->mNext;
		}else{
			entry->mParent->mChild = NULL;
		}
	}
	entry->mParent->mDegree-=1;
	entry->mPrev = entry->mNext = entry;
    hF->min = mergeLists(hF->min, entry);
	if (entry->mParent->mIsMarked) cutNode(hF,entry->mParent);
	else entry->mParent->mIsMarked = 1;
	entry->mParent = NULL;

}

void decreaseKey(fibHeap hF, fibNode entry, int nD){
	entry->el->distance = nD;
	if (entry->mParent != NULL && entry->el->distance <= entry->mParent->el->distance) cutNode(hF,entry);
	if (entry->el->distance <= hF->min->el->distance) hF->min = entry;
}

void printFibHeap(fibNode bn,int lev){
	if (bn==NULL) return;
	int i;
	fibNode curr;
	curr=bn;
	do{
		for(i=0;i<lev;i++) printf("\t");
		printf("(%d,%d)\n",curr->el->distance,curr->el->dest);
		printFibHeap(curr->mChild,lev+1);
		curr=curr->mNext;
	}while(curr!=bn);
}

void freeFibHeapCom(fibNode bn){
	if (bn==NULL) return;
	fibNode curr,temp;
	curr=bn;
	do{
		freeFibHeapCom(curr->mChild);
		temp=curr->mNext;
		free(curr->el);
		free(curr);
		curr=temp;
	}while(curr!=bn);
}

void freeFibHeap(fibHeap fH){
	freeFibHeapCom(fH->min);
	free(fH->hash);
}
















