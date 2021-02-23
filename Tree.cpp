#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Math.h>

struct pontos
{
	int x,y;
};

struct tree
{
	pontos p;
	tree *esq,*dir;
};
typedef struct tree T;

struct TpPilha
{
	int ini,fim,prof;
	TpPilha *prox;
};typedef struct TpPilha TpPilha;

char Vazia(TpPilha *p)
{
	return p==NULL;
}

void InserirP(TpPilha **p,TpPilha aux)
{
	TpPilha *novo=(TpPilha*)malloc(sizeof(TpPilha));
	novo->ini=aux.ini;
	novo->fim=aux.fim;
	novo->prof=aux.prof;
	novo->prox=*p;
	*p=novo;
}

void RetirarP(TpPilha **p,TpPilha &aux)
{
	TpPilha *auxiliar=*p;
	aux.ini=auxiliar->ini;
	aux.fim=auxiliar->fim;
	aux.prox=auxiliar->prox;
	*p=auxiliar->prox;
	free(auxiliar);
}

T*CriaNo(pontos p)
{
	T *novo=(T*)malloc(sizeof(T));
	novo->esq=NULL;
	novo->dir=NULL;
	novo->p.x=p.x;
	novo->p.y=p.y;
	return novo;
}

void RandomGera(int n,pontos vet[])
{
	srand(time(NULL));
	for(int i=0;i<n;i++)
	{
		vet[i].x=rand()%30;
		vet[i].y=rand()%30;
	}
}

void Inserir(pontos p,T **tree)
{
	T *aux=*tree,*ant,*novo;
	novo=CriaNo(p);
	int prof=0;
	if(*tree==NULL)
	{
		*tree=novo;
	}
	else
	{
		while(aux!=NULL)
		{
			ant=aux;
			if(prof==0)
			{
				if(aux->p.x>p.x)
				{
					aux=aux->esq;
				}
				else
				{
					aux=aux->dir;
				}
				prof=1;
			}
			else
			{
				if(aux->p.y>p.y)
				{
					aux=aux->esq;
				}
				else
				{
					aux=aux->dir;
				}
				prof=0;
			}
		}
		if(prof==1)
		{
			if(ant->p.x>p.x)
			{
				ant->esq=novo;
			}
			else
			{
				ant->dir=novo;
			}
		}
		else
		{
			if(ant->p.y>p.y)
			{
				ant->esq=novo;
			}
			else
			{
				ant->dir=novo;
			}
		}
	}
	
}

void Ordena(pontos vet[],TpPilha pi)
{
	pontos aux;
	if(pi.prof==0)
	{
		for(int i=pi.ini;i<pi.fim;i++)
		{
			for(int j=i+1;j<pi.fim;j++)
			{
				if(vet[i].x>vet[j].x)
				{
					aux=vet[i];
					vet[i]=vet[j];
					vet[j]=aux;
				}
			}
		}
	}
	else
	{
		for(int i=pi.ini;i<pi.fim;i++)
		{
			for(int j=i+1;j<pi.fim;j++)
			{
				if(vet[i].y>vet[j].y)
				{
					aux=vet[i];
					vet[i]=vet[j];
					vet[j]=aux;
				}
			}
		}
	}
}

T* Mediana(pontos vet[],int n)
{
	n--;
	TpPilha *p=NULL;
	TpPilha aux;
	T *tree=NULL;
	
	int prof=0,mediana;
	aux.ini=0;
	aux.fim=n;
	aux.prof=0;
	mediana=n;
	mediana=mediana/2;
	int mid=mediana;
	
	Ordena(vet,aux);
	Inserir(vet[mediana],&tree);
	aux.fim=mediana-1;
	aux.prof=1;
	InserirP(&p,aux);
	aux.ini=mediana+1;
	aux.fim=n;
	InserirP(&p,aux);
	prof=1;
	
	while(!Vazia(p))
	{
		RetirarP(&p,aux);
		Ordena(vet,aux);
		mediana=aux.fim+aux.ini;
		mediana=mediana/2;
		Inserir(vet[mediana],&tree);
		if(aux.fim!=aux.ini)
		{
			if(prof==0)
				prof=1;
			else
				prof=0;
			if(aux.fim-1!=aux.ini)
			{
				if(aux.fim>mid)
				{
					aux.fim=mediana-1;
					aux.prof=prof;
					InserirP(&p,aux);
					aux.ini=mediana+1;
					aux.fim=n;
					InserirP(&p,aux);
				}
				else
				{
					aux.fim=mediana-1;
					aux.prof=prof;
					InserirP(&p,aux);
					aux.ini=mediana+1;
					aux.fim=mid;
					InserirP(&p,aux);
				}			
			}
			else
			{
				Inserir(vet[mediana+1],&tree);
			}
			
		}		
	}
	return tree;
}

void Buscaponto(pontos vetor[],double dist_min,T *tree,int *TL,pontos p)
{	
	int plano = 0;
	double dist_aux;
	
	while(tree != NULL){
		
		dist_aux = sqrt(pow((p.x - tree->p.x),2) + pow((p.y - tree->p.y),2));
		
		if(dist_aux <= dist_min)
			vetor[(*TL)++] = tree->p;
		
		if(plano == 0){
			
			if(tree->p.x > p.x)
				tree = tree->esq;
			else
				tree = tree->dir;
				
			plano = 1;
		}		
		else{
			
			if(tree->p.y > p.y)
				tree = tree->esq;
			else
				tree = tree->dir;
				
			plano = 0;
		}		
	}	
}

void exibearvore(T *t)
{
	if(t!=NULL)
	{
		printf("(%d %d)\n",t->p.x,t->p.y);
		exibearvore(t->esq);		
		exibearvore(t->dir);		
	}
}
int main()
{
	int TL=0,dist;
	pontos v[50];
	pontos p;
	
	RandomGera(4,v);	
	T *tree=Mediana(v,4);
	printf("Arvore: \n");printf("\n");
	exibearvore(tree);	
	p.x=1;
	p.y=2;
	dist=15;
	Buscaponto(v,dist,tree,&TL,p);printf("\n");
	printf("Pontos proximos a (%d,%d):\n",p.x,p.y);
	if(TL==0)
		printf("Nao ha pontos proximos na arvore");
	else
	{
		for(int i=0;i<TL;i++)
			printf("(%d,%d) ",v[i].x,v[i].y);
	}
	printf("\n");printf("\n");
	
	RandomGera(9,v);	
	tree=Mediana(v,9);
	printf("Arvore: \n");printf("\n");
	exibearvore(tree);
	p.x=5;
	p.y=8;
	dist=2;
	Buscaponto(v,dist,tree,&TL,p);printf("\n");
	printf("Pontos proximos a (%d,%d):\n",p.x,p.y);
	if(TL==0)
		printf("Nao ha pontos proximos na arvore");
	else
	{
		for(int i=0;i<TL;i++)
			printf("(%d,%d) ",v[i].x,v[i].y);
	}
	printf("\n");printf("\n");
	
	RandomGera(15,v);	
	tree=Mediana(v,15);
	printf("Arvore: \n");printf("\n");
	exibearvore(tree);
	p.x=8;
	p.y=0;
	dist=6;
	Buscaponto(v,dist,tree,&TL,p);printf("\n");
	printf("Pontos proximos a (%d,%d):\n",p.x,p.y);
	if(TL==0)
		printf("Nao ha pontos proximos na arvore");
	else
	{
		for(int i=0;i<TL;i++)
			printf("(%d,%d) ",v[i].x,v[i].y);
	}
	printf("\n");printf("\n");
}
