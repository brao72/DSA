#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *left;
	struct node *right;
	struct node *parent;
};
struct node* create_node(int data)
{
	struct node *new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;
	return new_node;
}
void in(struct node* root , struct node* n)
{
	if(n->data > root->data)
	{
		if(root->right == NULL)
		{
			root->right = n;
			n->parent = root;
			return;
		}
		in(root->right , n);
	}
	else 
	{
		if(root->left == NULL)
		{
			root->left = n;
			n->parent = root;
			return;
		}
		in(root->left , n);
	}
}
void inord(struct node * n)
{
	if(n == NULL)
		return;
	inord(n->left);
	printf("%d ",n->data);
	inord(n->right);
}
void pre(struct node * n)
{
	if(n == NULL)
		return;
	printf("%d ",n->data);
	pre(n->left);
	pre(n->right);
}
void post(struct node * n)
{
	if(n == NULL)
		return;
	post(n->left);
	post(n->right);
	printf("%d ",n->data);
}
struct node* min(struct node*n)
{
	if(n->left == NULL)
		return n;
	return min(n->left);
}
struct node* succ(struct node*n, struct node* root)
{
	if(n->right != NULL)
		return min(n->right);
	struct node *temp = n;
	while(temp!=root && temp->parent->right == temp)	
		temp = temp->parent;
	return temp->parent;
}
void del(struct node* n , struct node**  root)
{
	if(n->left == NULL && n->right == NULL)
	{
		if(n == *root)
			*root = NULL;
		else if(n->parent->left == n)
			n->parent->left = NULL;
		else
			n->parent->right = NULL;
	}
	else if(n->left == NULL)
	{
		if(n == *root)
		{
			*root = n->right;
			n->right->parent = NULL;
		}
		else
		{
			n->right->parent = n->parent;
			if(n->parent->right == n)
				n->parent->right = n->right;
			else
				n->parent->left = n->right;
		}
	}
	else if(n->right == NULL)
	{
		if(n == *root)
		{
			*root = n->left;
			n->left->parent = NULL;
		}
		else
		{
			n->left->parent = n->parent;
			if(n->parent->right == n)
				n->parent->right = n->left;
			else
				n->parent->left = n->left;
		}
	}
	else
	{
		struct node* temp = min(n->right);
		n->data = temp->data;
		del(temp,root);
	}
}
int main()
{	
	struct node* root = create_node(15);
	struct node* n1 = create_node(6);
	struct node* n2 = create_node(18);
	struct node* n3 = create_node(17);
	struct node* n4 = create_node(20);
	struct node* n5 = create_node(3);
	struct node* n6 = create_node(7);
	struct node* n7 = create_node(2);
	struct node* n8 = create_node(4);
	struct node* n9 = create_node(13);
	struct node* n10 = create_node(9);
	in(root , n1);
	in(root , n2);
	in(root , n3);
	in(root , n4);
	in(root , n5);
	in(root , n6);
	in(root , n7);
	in(root , n8);
	in(root , n9);
	in(root , n10);
	struct node **temp = &root;
	del(root,temp);
	inord(root);

}
