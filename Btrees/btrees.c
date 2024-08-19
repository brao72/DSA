#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct bnode
{
    int n;
    int *k;
    bool leaf;
    struct bnode **c;
} bnode;
bnode* btree_create(int t)
{
	bnode* x = (bnode*)malloc(sizeof(bnode));
	x->leaf = true;
	x->n = 0;
	x->k = (int*)malloc(sizeof(int)*(t+t-1));
	x->c = (bnode**)malloc(sizeof(bnode*)*(t+t));
	return x;
}
void btree_split_child(bnode * x , int i , int t)
{
	bnode* y = (x->c)[i];
	bnode* z = btree_create(t);
	z->leaf = y->leaf;
	z->n = t-1;
	(x->n)++;
	//keys of x
	for(int j = (x->n)-1; j > i; j--)
		(x->k)[j] = (x->k)[j-1];
	(x->k)[i] = (y->k)[t-1];
	// keys of z
	for(int j = 0; j < t-1; j++)
		(z->k)[j] = (y->k)[t+j];
	// children of x
	for(int j = (x->n); j > i+1; j--)
		(x->c)[j] = (x->c)[j-1];
	(x->c)[i+1] = z;
	(y->n) = t-1;
	//children of z
	if(y->leaf == false)
		for(int j = 0; j < t; j++)
			(z->c)[j] = (y->c)[j+t];
}
bnode* split_root(bnode * root , int t)
{
	bnode* new_root = btree_create(t);
	(new_root)->n = 0;
	(new_root)->leaf = false;
	((new_root)->c)[0] = root;
	btree_split_child(new_root , 0 , t);
	return new_root;
}
void btree_insert_nonfull(bnode * x , int key , int t)
{
	int i = 0;
	while(i < (x->n) && key > (x->k)[i])
		i++;
	if(x->leaf == false)
	{
		if(((x->c)[i])->n == t+t-1)
		{
			btree_split_child(x,i,t);
			if(key > (x->k)[i] )
				i++;
		}
		btree_insert_nonfull((x->c)[i] , key,t);
	}
	else
	{
		(x->n)++;
		for(int j = x->n - 1; j > i; j--)
			(x->k)[j] = (x->k)[j-1];
		(x->k)[i] = key;
	}
}
void btree_insert(bnode **root , int key ,  int t)
{
	if((*root)->n == t+t-1)
		*root = split_root(*root , t);
	btree_insert_nonfull(*root , key , t);
}
void inorder(bnode * x)
{
	if(x->leaf)
	{
		for(int i = 0; i < (x->n); i++)
			printf("%d " , (x->k)[i]);
		return;
	}
	for(int i = 0; i < (x->n); i++)
	{
		inorder((x->c)[i]);
		printf("%d " , (x->k)[i]);
	}	
	inorder((x->c)[x->n]);
}
bool btree_search(bnode * x ,int key)
{
	int i = 0;
	while(i < (x->n) && key > (x->k)[i])
		i++;
	if(i != (x->n) && (x->k)[i] == key)
		return true;
	if(x->leaf == false)
		return btree_search((x->c)[i] , key);
	return false;
}
int btree_min(bnode *x)
{
	if(x->leaf == true)
		return (x->k)[0];
	return btree_min((x->c)[0]);
}
int main()
{
}
