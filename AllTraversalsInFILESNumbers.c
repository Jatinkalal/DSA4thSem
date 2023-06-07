#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};
 void randomCharGen(int *arr,int size);
 void inputToFile(int *arr,int size, FILE*fp);
 struct node *getnode(int key);
 struct node *insert(struct node *curr, struct node *newnode);
 void inorder(struct node *root,FILE *fp);
 void preorder(struct node *root,FILE *fp);
 void postorder(struct node *root,FILE *fp);

int main()
{
    struct node *root = NULL;
    struct node *newnode;
    int arr[1000];
    int size;
    int key;

    FILE *inputFP;
    FILE *inorderFP = fopen("Inorder.txt","w+");
    FILE *preorderFP = fopen("Preorder.txt","w+");
    FILE *postorderFP = fopen("Postorder.txt","w+");

    printf("Enter size of the input characters:\n");
    scanf("%d",&size);

    randomNumGen(arr,size);
    inputToFile(arr,size,inputFP);

    for(int i =0 ; i<size; i++)
    {
        key = arr[i];
        newnode = getnode(key);
        root = insert(root,newnode);
    }

    inorder(root,inorderFP);
    fclose(inorderFP);

    preorder(root,preorderFP);
    fclose(preorderFP);

    postorder(root,postorderFP);
    fclose(postorderFP);

    return 0;
}



 void randomNumGen(int *arr,int size)
{
        int ch;
        int count =0;
        for(int i = 0 ; i<size; i++)
        {
            ch = rand()%50;
            arr[i]=ch;
        }

}

void inputToFile(int *arr,int size, FILE*fp)
{
    fp = fopen("InputTree.txt","w+");
    int ch;
    for(int i = 0 ; i < size; i++)
    {
        ch = arr[i];
        fprintf(fp,"%d ",ch);
    }
    fclose(fp);
}

struct node *getnode(int key)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->left = newnode->right = NULL;

    newnode->data = key;
    return newnode;

}
struct node *insert(struct node *curr, struct node *newnode)
{
    if(curr==NULL)
    {
        return newnode;
    }
    else if((newnode->data) <= (curr->data))
    {
        curr->left=insert(curr->left,newnode);
    }
    else if((newnode->data) > (curr->data))
    {
        curr->right=insert(curr->right,newnode);
    }
    return curr;

}

void inorder(struct node *root,FILE *fp)
{
    int ch;
    if(root == NULL)
        return;

    inorder(root->left,fp);
    ch = root->data;
    fprintf(fp,"%d ",ch);
    inorder(root->right,fp);
}
void preorder(struct node *root,FILE *fp)
{
    int ch;
    if(root == NULL)
        return;

        ch = root->data;
    fprintf(fp,"%d ",ch);
    preorder(root->left,fp);
    preorder(root->right,fp);
}
void postorder(struct node *root,FILE *fp)
{
    int ch;
    if(root == NULL)
        return;


    postorder(root->left,fp);
    postorder(root->right,fp);
    ch = root->data;
    fprintf(fp,"%d ",ch);

}






