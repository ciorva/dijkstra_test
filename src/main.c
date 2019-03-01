#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

#define DEF_NOTESTS 100
#define DEF_NONODES 100


int nameToNum(char*str){
	int i=0;
	int res=0;	
	while(str[i]!=0){
		res=res*10+(str[i]-'0');
		i++;
	}
	return res;
}

void numToName(int num,char*str){
	sprintf(str,"%d",num);
	return;
}


long int getExecTime(struct timeval start,struct timeval end){
	long int sec = end.tv_sec-start.tv_sec;
	long int msec = end.tv_usec-start.tv_usec;
	return sec*1000000LL + msec;
}

//**** MAIN FUNCTION ****//

int main(int argc,char* argv[]){
	int nT = DEF_NOTESTS;
	int n = DEF_NONODES;
	if(argc>1){
		nT=atoi(argv[1]);
		if (argc>2) n=atoi(argv[2]);
	}
	struct rusage usage;
	struct timeval start, end;
	int i;
	srand(time(NULL));
	int p[n];
	int d[n];
	printf("Testing Erdos-Reni:");
	FILE*fout=fopen("./outputTest.txt","w");
	for(i=0;i<nT;i++){
		graph g=newRandomGraphErdos(n,0.02,0,100);
		printf("Generated #%d ",i+1);
		getrusage(RUSAGE_SELF, &usage);
		start = usage.ru_utime;
		dijkstraBinHeap(g,0,p,d);
		getrusage(RUSAGE_SELF, &usage);
		end = usage.ru_utime;
		fprintf(fout,"%ld ",getExecTime(start,end));
		getrusage(RUSAGE_SELF, &usage);
		start = usage.ru_utime;
		dijkstraBinomialHeap(g,0,p,d);
		getrusage(RUSAGE_SELF, &usage);
		end = usage.ru_utime;
		fprintf(fout,"%ld ",getExecTime(start,end));
		getrusage(RUSAGE_SELF, &usage);
		start = usage.ru_utime;
		dijkstraFibHeap(g,0,p,d);
		getrusage(RUSAGE_SELF, &usage);
		end = usage.ru_utime;
		fprintf(fout,"%ld\n",getExecTime(start,end));
		printf("Tested #%d\n",i+1);
		freeGraph(g);
	}
	fclose(fout);
	return 0;
}