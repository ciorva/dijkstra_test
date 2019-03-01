#ifndef GRAPH_H
#define GRAPH_H

typedef struct node{
	int v;
	int weight;
	struct node*next;
}*list;

typedef struct graph{
	int dim;	
	list * node;
}*graph;

list newList();
void freeList(list l);
list insertHead(list l,int v,int weight);


graph newGraph(int n);
void freeGraph(graph g);
graph newRandomGraphErdos(int n,double p,int minW,int range);
graph newRandomGraphBarabasi(int n,int k0,int k,int minW,int range);
void printGraph(graph g);
void saveGraph(graph g,char*path);

void dijkstraBinHeap(graph g,int s,int*p,int*d);
void dijkstraFibHeap(graph g,int s,int*p,int*d);
void dijkstraBinomialHeap(graph g,int s,int*p,int*d);

#endif
