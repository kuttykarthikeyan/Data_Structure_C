#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *lc;
    int data,height;
    struct node *rc;
};
struct node *root='\0';

struct node* newnode( int val)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->lc = temp->rc = '\0';
    temp->data=val;
    temp->height=-1;
    return temp;
}

int maximum(int a, int b) {
  return (a > b) ? a : b;
}


int height(struct node *t)
{
    if (t == NULL)
        return -1;
    else
        return t->height;
}

struct node* RR(struct node *K2)
{
 struct node *K1 = K2->lc;
 K2->lc = K1->rc;
 K1->rc = K2;
 K2->height = maximum(height(K2->lc),height(K2->rc))+1;
 K1->height = maximum(height(K1->lc),height(K1->rc))+1;
 return K1;
}

struct node* LL(struct node *K2)
{
 struct node *K1 = K2->rc;
 K2->rc = K1->lc;
 K1->lc = K2;
 K2->height = maximum(height(K2->lc),height(K2->rc))+1;
 K1->height = maximum(height(K1->lc),height(K1->rc))+1;
 return K1;
}

void RL(struct node *K3)
{
    K3->rc = RR(K3->rc);
    K3 = LL(K3);
}

void LR(struct node *K3)
{
    K3->lc = LL(K3->lc);
    K3 = RR(K3);
}



struct node* bsinsert(struct node *root,int val)
{
 if (root   == '\0')
    root = newnode(val);
 else if(root->data >val)
    root->lc = bsinsert(root->lc,val);
 else if(root->data <val)
    root->rc = bsinsert(root->rc,val);

 return root;
}

void insert(struct node *t,int val)
{
 if (t   == '\0')
    t=newnode(val);
 else if(t->data >val)
 {
    t=bsinsert(t->lc,val);
    if(height(t->lc) - height(t->rc) == 2 )
    {
        if(val < t->lc->data)
            RR(t);
        else
            LR(t);
    }
 }
 else if(t->data <val)
 {
    t=bsinsert(t->rc,val);
    if(height(t->rc) - height(t->lc) == 2 )
    {
        if(val < t->rc->data)
            LL(t);
        else
            RL(t);
    }
 }
    t->height = maximum(height(t->lc),height(t->rc))+1;
}

void inorder(struct node *root)
{
    if(root != '\0')
    {
        inorder(root->lc);
        printf("%d ",root->data);
        inorder(root->rc);
    }

}

int main()
{
    int opt,val;
    while(1)
    {
        printf("\n1.Insert\n2.Inorder\n3.Exit\n");
        printf("Enter the option ");
        scanf("%d",&opt);
        switch(opt)
        {
        case 1:
            printf("\nEnter value ");
            scanf("%d",&val);
            root=bsinsert(root,val);
            break;
        case 2:
            if(root == NULL)
                printf("No values to display\n");
            else
                inorder(root);printf("\n");
            break;
        case 3:
            return 0;
        }

    }
}

