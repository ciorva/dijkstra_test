/* C program to implement Binomial Heap tree */
 
#include <stdio.h>
#include <stdlib.h>
#include "heapBinomialFra.h"

//****** CREATE BINOMIAL HEAP *******//
bHeap newEmptyBinomialHeap(){
	return NULL;
};

//****** INSERT ELEMENT HEAP *******//
bHeap insertElementBinomialHeap(bHeap h,int distance, int dest){
	bHeap r = newEmptyBinomialHeap();
	//costruisco il nuovo nodo
	bHeap new = malloc(sizeof(struct binomialHeapNode));
	new->father=NULL;
	new->child=NULL;
	//come fratello inserisco il puntatore al vecchio heap. il nuovo nodo diventa quindi il primo della lista
	new->sibling=h;
	//ovviamente ha livello zero
	new->degree=0;
	//creo la struttura del contenuto e riempio
	elementHeap el=malloc(sizeof(struct elementHeap));
	el->dest=dest;
	el->distance=distance;
	new->elem=el;
	//chiamo la fixHeap: se c'è un altro nodo singolo vanno fusi
	r=fixHeap(new);
	return r;
};

//****** NOT EMPTY *******//
int notEmpty(bHeap h){
	if (h!=NULL) return 1;
	else return 0;
}

//****** GET MIN DISTANCE *******//
int getMinDistance(bHeap h){
	elementHeap x = NULL;
	int dist;
	if (h==NULL) return -1;
	//prendo la prima distanza come base per il minimo
	dist=(h->elem)->distance;
	//cerco altri elementi e aggiorno
	while (1){
		if ((h->elem)->distance < dist){
			dist=(h->elem)->distance;
		}
		h=h->sibling;
		if(h==NULL) break;
	}
	return dist;
};



//****** GET MIN DESTINATION *******//
int getMinDest(bHeap h){
	elementHeap x = NULL;
	int dist,dest;
	if (h==NULL) return -1;
	//prendo la prima distanza come base per il minimo
	dist=(h->elem)->distance;
	dest=(h->elem)->dest;
	//cerco altri elementi e aggiorno
	while (1){
		if ((h->elem)->distance < dist){
			dist=(h->elem)->distance;
			dest=(h->elem)->dest;
		}
		h=h->sibling;
		if(h==NULL) break;
	}
	return dest;
};

// controlla se ci sono due alberi della stessa dimensione: se si, li fonde e si richiama ricorsivamente
bHeap fixHeap(bHeap h){
	//dichiarazione di variabili ausiliarie
	bHeap smaller,greater, next, prev=NULL;
	int flag=1;
	h=DegreeOrder(h);
	//variabile per lo scorrimento
	bHeap t=h;
	//controllo albero vuoto
	if (h==NULL) {
		return NULL;
	}
	//printBin(h);
	//controllo se ci sono due alberi dello stesso grado
	while(t->sibling!=NULL){
		//controllo se due alberi hanno lo stesso grado
		if (t->degree == t->sibling->degree) {
			//attivo il flag per la nuova chiamata ricorsiva
			flag=0;
			//verifico quale dei due alberi abbia il valore minore
			if (t->elem->distance < t->sibling->elem->distance){
				smaller = t;
				greater = t->sibling;
			} else {
				smaller = t->sibling;
				greater = t;
			}
			//metto da parte il nodo a cui va collegato il nuovo albero
			next=t->sibling->sibling;
			t=mergeBinomialHeaps(smaller,greater);
			t->sibling=next;
			if (prev==NULL) {
				h=t;
			}
			if (prev!=NULL){ 
				prev->sibling=t;
			}
		}
		prev=t;
		t=t->sibling;
		//controllo se interrompere il ciclo...a causa delle merge potrei avere t=NULL creando problemi al prossimo controllo del ciclo
		if (t==NULL) break;
	}
	//printBin(h);
	//se ho fatto dei merge richiamo ricorsivamente, altrimenti esco
	if (flag) return h;
	else return fixHeap(h);
};

//****** DELETE MIN ELEMENT OF A BINOMIAL HEAP *******//
bHeap deleteMinBinomialHeap(bHeap h){
	// dichiaro una serie di variabili di supporto
	bHeap deletable,t,prov, prev,next;
	int counter=0,minCounter,i=0,dist;
	elementHeap x = NULL;
	//se l'heap è vuoto ritorno semplicemente NULL
	if (h==NULL) return h;
	//**** prima parte: controllo dove si trovi il minimo ***//
	//prendo la prima distanza come base per il minimo
	dist=(h->elem)->distance;
	//metto da parte il primo elemento
	minCounter=counter;
	//cerco altri elementi e aggiorno
	t=h;
	while (t->sibling != NULL){
		counter++;
		t=t->sibling;
		if ((t->elem)->distance < dist){
			minCounter=counter;
			dist=(t->elem)->distance;
		}
	}
	counter=minCounter;
	//**** seconda parte: lo elimino ricollegando i puntatori ****//
	/* due casi da gestire:
	*  1) l'albero contiene solo un nodo
	*  2) il minimo si trova al primo posto (counter=0)
	*  3) il caso generico
	*/
	t=h;
	//primo caso
	if (t->sibling==NULL && t->child==NULL){
		freeBheap(t);
		return NULL;
	}
	//secondo caso
	if (counter==0) {
		//vedo se il minimo ha figli e mi comporto di conseguenza
		if (t->child==NULL){
			//il minimo non ha figli: scalo di 1 la lista e faccio la free sul primo elemento
			deletable=t;
			h=h->sibling;
			freeBheap(deletable);
			h=fixHeap(h);
			return h;
		} else {
			deletable=t;
			//puntatore al figlio dell'elemento da cancellare
			prov=deletable->child;
			//scorro fino a raggiungere l'ultimo elemento di secondo livello sotto deletable
			while (prov->sibling!=NULL) prov=prov->sibling;
			//riaggancio questo al secondo elemento della lista
			prov->sibling=t->sibling;
			//la nuova testa dell'albero diventa il figlio del primo elemento
			t=t->child;
			//faccio controlli e restituisco il puntatore all'albero
			h=fixHeap(h);
			return t;
		}
	} else{
	//terzo caso
		//utilizzando il contatore, punto il minimo e tengo traccia di predecessore e successore
		/*
		for (i=0;i<counter;i++){
			printf("\n giro1 \n");
			prev=t;
			printf("\n giro2 \n");
			t=t->sibling;
			printf("\n giro3 \n");
			next=t->sibling;
			printf("\n giro4 \n");
		}
		*/
		while ((counter)!=0){
			counter--;
			prev=t;
			t=t->sibling;
			next=t->sibling;
		}

		//gestisco il caso in cui t non ha figli (è possibile? non sono sicuro)
		if (t->child==NULL){
			//semplicemente faccio un bypass sul nodo radice successivo
			prev->sibling=next;
			//svuoto il nodo minimo e ricontrollo l'integrità dell'albero
			freeBheap(t);
			h=fixHeap(h);
			return h;
		}
		//gestisco il caso in cui t ha figli
		else {
			//metto da parte il figlio
			prov=t->child;
			//attacco il nodo precedente al figlio di t
			prev->sibling=t->child;
			//scorro tutti i nodi di primo livello figli di t
			while (prov->sibling!=NULL) prov=prov->sibling;
			//riattacco l'ultimo di questi nodi di primo livello con next
			prov->sibling=next;
			//svuoto il nodo minimo e ricontrollo l'integrità dell'albero
			freeBheap(t);
			h=fixHeap(h);
			return h;
		}
		
	}
	return h;
};

//****************************************//
//****** SUPPORT FUNCTION SECTION ********//
//****************************************//

//da controllare!!
//dati due alberi (il primo DEVE essere quello con chiave minore), li fonde e restituisce il puntatore all'albero
bHeap mergeBinomialHeaps(bHeap smaller, bHeap greater){
	//gestisco il caso in cui i nodi hanno grado 0)
	if (smaller->child==NULL){
	smaller->child=greater;
	smaller->sibling=NULL;
	greater->sibling=NULL;
	smaller->degree=smaller->degree+1;
	return smaller;
	} else {
	//gestisco il caso generico: greater deve essere collegato al livello dei figli di smaller
	bHeap t=smaller->child;
	greater->sibling=NULL;
	//smaller->sibling=NULL;
	while (t!=NULL){
		if (t->sibling==NULL){
			t->sibling=greater;
			break;
			}
		t=t->sibling;
		}
	smaller->degree=smaller->degree+1;
	return smaller;
	}
}

void freeBheap(bHeap t){
	free(t->elem);
	free(t);
	return;
}

//da controllare!!
//riordina la lista di alberi in maniera da lasciarla sempre nel corretto ordine di grado
bHeap DegreeOrder(bHeap h){
	int flag=1;
	bHeap a=h;
	bHeap swap;
	//fino a che posso scorrere ancora le radici degli alberi
	while (a->sibling!=NULL) {
		//controllo se il grado che sto controllando ora sia più grande di quello successivo
		if (a->degree > a->sibling->degree){
			//metto il flag a zero: devo fare almeno un altro giro della funzione per controllare che sia tutto ok
			flag=0;
			//metto il nodo "incriminato" in una variabile provvisoria
			swap=a->sibling;
			//collego il nodo attuale all'elemento che segue quello da spostare (può essere NULL)
			a->sibling=a->sibling->sibling;
			//collego il nodo da spostare all'inizio della lista
			swap->sibling=h;
			//il nodo da spostare diventa la cima della lista
			h=swap;
			//ripeto il ciclo per controllare se anche il nuovo elemento 
		}
		//mi muovo avanti nella lista verificando il prossimo elemento
		a=a->sibling;
	}
	//se in questa iterazione era tutto ok, restituisco l'albero altrimenti richiamo la funzione di nuovo
	if (flag) return h;
	else return DegreeOrder(h);
}


void printBin(bHeap H){
	int counter=1;
	bHeap p;
    if (H == NULL) {
        printf("\nHEAP EMPTY \n");
        return;
    }
    printf("\nTHE ROOT NODES ARE:-\n");
    p = H;
    while (p != NULL) {
        printf("%d", (p->elem)->distance);
        if (p->sibling != NULL)
            printf("-->");
        p = p->sibling;
    }
    printf("\n");
    printf("\nHEAPS:\n");
    p = H;
    while (p != NULL) {
        printf("Heaps number %d: %d, ", counter,(p->elem)->distance);
        if (p->child!=NULL) printSubHeap(p->child);
        p = p->sibling;
        counter++;
        printf("\n");
    }
    printf("\n");
    return;
}

void printBinDestination(bHeap H){
	int counter=1;
	bHeap p;
    if (H == NULL) {
        printf("\nHEAP EMPTY \n");
        return;
    }
    printf("\nTHE ROOT NODES ARE:-\n");
    p = H;
    while (p != NULL) {
        printf("%d", (p->elem)->dest);
        if (p->sibling != NULL)
            printf("-->");
        p = p->sibling;
    }
    printf("\n");
    printf("\nHEAPS:\n");
    p = H;
    while (p != NULL) {
        printf("Heaps number %d: %d, ", counter,(p->elem)->dest);
        if (p->child!=NULL) printSubHeapDestination(p->child);
        p = p->sibling;
        counter++;
        printf("\n");
    }
    printf("\n");
    return;
}

void printSubHeap(bHeap p){
	printf("%d ", (p->elem)->distance);
	if (p->sibling!=NULL) printSubHeap(p->sibling);
	if (p->child!=NULL) printSubHeap(p->child);
	return;
}

void printSubHeapDestination(bHeap p){
	printf("%d ", (p->elem)->dest);
	if (p->sibling!=NULL) printSubHeap(p->sibling);
	if (p->child!=NULL) printSubHeap(p->child);
	return;
}