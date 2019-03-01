#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "heapBin.h"
#include "fibHeap.h"
#include "heapBinomialFra.h"
#include "graph.h"

list newList(){
	return NULL;
}

void freeList(list l){
	if (l==NULL) return;
	freeList(l->next);
	free(l);
	return;
}


list insertHead(list l,int v,int weight){
	list res = malloc(sizeof(struct node));
	res->next=l;
	res->v=v;
	res->weight=weight;
	return res;
}

graph newGraph(int n){
	graph res=malloc(sizeof(struct graph));
	res->dim=n;
	res->node=malloc(n*sizeof(list));
	int i;
	for(i=0;i<n;i++) res->node[i]=newList(); 
	return res;
}

void freeGraph(graph g){
	int i;
	for(i=0;i<g->dim;i++) freeList(g->node[i]);
	free(g);
	return;
}

graph newRandomGraphErdos(int n,double p,int minW,int range){
	graph g=newGraph(n);	
	int i,j,w;
	list l;
	for(i=0;i<g->dim;i++){
		l=newList();
		for(j=0;j<g->dim;j++){
			if((i!=j) && (((double)rand()/(double)RAND_MAX)<p)){
				// sbagliato w=rand()range + minW;
				w=(int)floor(((double)rand()/(double)RAND_MAX*(double)range)) + minW;
				l=insertHead(l,j,w);
			}		
		}
		g->node[i]=l;
	}
	return g;
}

void printGraph(graph g){
	int i;
	list l;
	for(i=0;i<g->dim;i++){
		l=g->node[i];
		while(l!=NULL){
			printf("(%d %d %d)\n",i,l->v,l->weight);
			l=l->next;
		}
	}
}

void saveGraph(graph g,char*path){
	FILE*fout=fopen(path,"w");
	int i;
	list l;
	fprintf(fout,"%d\n",g->dim);
	for(i=0;i<g->dim;i++){
		l=g->node[i];
		while(l!=NULL){
			fprintf(fout,"%d %d %d\n",i,l->v,l->weight);
			l=l->next;
		}
	}
	fclose(fout);
}

graph loadGraph(char*path){
	FILE*fin=fopen(path,"r");
	int n,i,j,w;
	if(!fscanf(fin,"%d\n",&n))return NULL;
	graph res = newGraph(n);
	while(fscanf(fin,"%d %d %d\n",&i,&j,&w)!=EOF) res->node[i]=insertHead(res->node[i],j,w);
	fclose(fin);
	return res;
}

void dijkstraBinHeap(graph g,int s,int*p,int*d){
	binHeap h = newBinHeap(g->dim);
	list com;	
	char color[g->dim];
	int i,cn,cd;
	for(i=0;i<g->dim;i++){
		color[i]='w';
		p[i]=-1;
		d[i]=-1;	
	}
	p[s]=s;
	d[s]=0;
	insertElementBinHeap(h,0,s);
	while(h->size>0){
		cn=getMinDestinationBinHeap(h);
		cd=getMinDistanceBinHeap(h);
		deleteMinBinHeap(h);
		if(color[cn]=='w'){
			color[cn]='b';
			com=g->node[cn];
			while(com!=NULL){
				if(color[com->v]=='w'){
					if ((d[com->v]==-1)||d[com->v]>com->weight+d[cn]){						
						d[com->v]=com->weight+d[cn];
						p[com->v]=cn;
						insertElementBinHeap(h,d[com->v],com->v);
					}
				}
				com=com->next;			
			}
		}
	}
	freeBinHeap(h);
}

void dijkstraFibHeap(graph g,int s,int*p,int*d){
	fibHeap h = newFibHeap((g->dim*(g->dim-1)));
	list com;	
	char color[g->dim];
	int i,cn,cd;
	for(i=0;i<g->dim;i++){
		color[i]='w';
		p[i]=-1;
		d[i]=-1;	
	}
	p[s]=s;
	d[s]=0;
	insertElementFibHeap(h,0,s);	
	while(h->size>0){
		cn=getMinDestFibHeap(h);
		cd=getMinDistanceFibHeap(h);
		deleteMinFibHeap(h);
		if(color[cn]=='w'){
			color[cn]='b';
			com=g->node[cn];
			while(com!=NULL){
				if(color[com->v]=='w'){
					if ((d[com->v]==-1)||d[com->v]>com->weight+d[cn]){						
						d[com->v]=com->weight+d[cn];
						p[com->v]=cn;
						insertElementFibHeap(h,d[com->v],com->v);
					}
				}
				com=com->next;			
			}
		}
	}
	freeFibHeap(h);
}

void dijkstraBinomialHeap(graph g,int s,int*p,int*d){
	bHeap h=newEmptyBinomialHeap();
	list com;
	char color[g->dim];
	int i,cn,cd;
	for(i=0;i<g->dim;i++){
		color[i]='w';
		p[i]=-1;
		d[i]=-1;	
	}
	p[s]=s;
	d[s]=0;
	h=insertElementBinomialHeap(h,0,s);	
	while(notEmpty(h)){
		cn=getMinDest(h);
		cd=getMinDistance(h);
		h=deleteMinBinomialHeap(h);
		if(color[cn]=='w'){
			color[cn]='b';
			com=g->node[cn];
			while(com!=NULL){
				if(color[com->v]=='w'){
					if ((d[com->v]==-1)||d[com->v]>com->weight+d[cn]){						
						d[com->v]=com->weight+d[cn];
						p[com->v]=cn;
						h=insertElementBinomialHeap(h,d[com->v],com->v);
					}
				}
				com=com->next;			
			}
		}
	}
}
