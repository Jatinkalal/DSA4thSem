#include<stdio.h>
#include<stdlib.h>

struct node
{
    int height;
    int balance;
    int data;
    struct node *left;
    struct node *right;
};

struct node *getnode(int key);
struct node *insert(struct node *curr,struct node *newnode);
int findHeight(struct node *root);
void inorder(struct node *root);
struct node *rotateRight(struct node *curr);
struct node *rotateLeft(struct node *curr);
struct node* _deleteNode(struct node *root,int key,struct node *par);
int getBalance(struct node *);

int main()
{
    struct node *root = NULL;
    struct node *newnode;
    int choice;
    int key;
    int deleteKey;

    while(1)
    {
        printf("Enter 1-Insert\n2-Delete\n3-Inorder\n4-Exit\n");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                        printf("Enter data:\n");
                        scanf("%d",&key);
                        newnode = getnode(key);
                        root = insert(root,newnode);
                        printf("root->data = %d\n",root->data);

                    break;

            case 2: printf("Enter key to be deleted:\n");
                    scanf("%d",&deleteKey);
                    root = _deleteNode(root,deleteKey,NULL);
                    if(root != NULL)
                    printf("root->data = %d\n",root->data);
                    break;

            case 3: findHeight(root);
                    inorder(root);
                    break;

            default: exit(0);
        }
    }

    return 0;

}
struct node *getnode(int key)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->left = newnode->right = NULL;
    newnode->data = key;
    newnode->height = 0;
    return newnode;

}
int findHeight(struct node *root)
{
    if(root == NULL)
        return 0;

    int l = findHeight(root->left);
    int r = findHeight(root->right);

    root->balance = l-r;

    if(l>r)
    {
        root->height =l;
        return 1+l;

    }
    else
    {
        root->height = r;
        return 1+r;

    }


}

struct node *insert(struct node *curr,struct node *newnode)
{
    if(curr == NULL)
        return  newnode;

    else if(newnode->data > curr->data)
        curr->right = insert(curr->right,newnode);

    else if(newnode->data <= curr->data)
        curr->left = insert(curr->left,newnode);


    findHeight(curr);
    int balance = curr->balance;


    if(balance > 1 && newnode->data < curr->left->data)
        // left left
        return rotateRight(curr);

    else if(balance < -1 && newnode->data > curr->right->data)
        return rotateLeft(curr);

    else if(balance > 1 && newnode->data > curr->left->data )
    {
        curr->left = rotateLeft(curr->left);
        return rotateRight(curr);

    }
    else if(balance <-1 && newnode->data < curr->right->data)
    {
        curr->right = rotateRight(curr->right);
        return rotateLeft(curr);

    }
    return curr;

}
void inorder(struct node *root)
{
    if(root == NULL)
        return ;

    inorder(root->left);
    printf("data = %d ",root->data);
    int balance = root->balance;
    printf("balance factor = %d\n",balance);
    inorder(root->right);
}

struct node *rotateLeft(struct node *curr)
{
    struct node *root = curr->right;
    struct node *temp = root->left;
    root->left = curr;
    curr->right = temp;
    return root;

}
struct node *rotateRight(struct node *curr)
{
    struct node *root = curr->left;
    struct node *temp = root->right;
    root->right = curr;
    curr->left = temp;
    return root;
}
 struct node* _deleteNode(struct node*root,int key,struct node *par)
{
    if(root == NULL)
    return NULL;

    else if(key > root->data)
    root->right = _deleteNode(root->right,key,root);
    else if(key < root->data)
    root->left = _deleteNode(root->left,key,root);

    else
    {
        // no child case or leaf Node case
        if( (root->left == NULL) && (root->right == NULL) )
        {
            struct node *temp = root;
            free(temp);
            root = NULL;

        }

        // only one node /only one child
        else if(root->left == NULL || root->right == NULL)
        {
            struct node *temp = root->left ? root->left :
                                             root->right;

            *root = *temp;
            free(temp);
        }
        // two children case
        else
        {
            struct node* in = root->right;
             while(in->left != NULL)
             {
                 in = in->left;
             }


            root->data = in->data;

            root->right = _deleteNode(root->right , in->data , root);
        }
    }

    if(root == NULL)
    {
       return root;
    }


    findHeight(root);
    int balance = getBalance(root);

    if((balance > 1 ) && getBalance(root->left) >= 0)
     return(rotateRight(root));

    else if((balance < -1 ) && getBalance(root->right) <= 0)
    return(rotateLeft(root));

    else if((balance > 1 ) && getBalance(root->left) < 0)
    {
        root->left = rotateLeft(root->left);
        return(rotateRight(root));
    }

    else if((balance < -1 ) && getBalance(root->right) > 0)
    {
        root->right = rotateRight(root->right);
        return(rotateLeft(root));
    }

    return root;

}

int getBalance(struct node *root)
{
    return(root->balance);
}
