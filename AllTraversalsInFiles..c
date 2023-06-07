#include<stdio.h>
#include<stdlib.h>

struct node
{
    char data;
    struct node *left;
    struct node *right;
};
 void randomCharGen(int *arr,int size);
 void inputToFile(int *arr,int size, FILE*fp);
 struct node *getnode(char key);
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
    char ch;

    FILE *inputFP;
    FILE *inorderFP = fopen("Inorder.txt","w+");
    FILE *preorderFP = fopen("Preorder.txt","w+");
    FILE *postorderFP = fopen("Postorder.txt","w+");

    printf("Enter size of the input characters:\n");
    scanf("%d",&size);

    randomCharGen(arr,size);
    inputToFile(arr,size,inputFP);

    for(int i =0 ; i<size; i++)
    {
        ch = arr[i];
        newnode = getnode(ch);
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



 void randomCharGen(int *arr,int size)
{
        char ch;
        int count =0;
        while(1)
        {
            if(count >= size)
            break;

            ch = rand()%255;
            if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch<= 'Z'))
            {
                //printf("%c ",ch);
                arr[count] = ch;
                count++;
            }

        }

}

void inputToFile(int arr[1000],int size, FILE *fp)
{
    fp = fopen("InputTree.txt","w+");
    char ch;
    int i;
    for(i = 0 ; i < size; i++)
    {
        //ch = arr[i];
        //printf("%c ",ch);

        fprintf(fp,"%c ",arr[i]);
        //putc(arr[i] ,fp);
        //ch = ' ';
        //putc(ch,fp);

    }
    fclose(fp);
}

struct node *getnode(char key)
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
    else if(tolower(newnode->data) <= tolower(curr->data))
    {
        curr->left=insert(curr->left,newnode);
    }
    else if(tolower(newnode->data) > tolower(curr->data))
    {
        curr->right=insert(curr->right,newnode);
    }
    return curr;

}

void inorder(struct node *root,FILE *fp)
{
    char ch;
    if(root == NULL)
        return;

    inorder(root->left,fp);
    ch = root->data;
    fprintf(fp,"%c",ch);
    inorder(root->right,fp);
}
void preorder(struct node *root,FILE *fp)
{
    char ch;
    if(root == NULL)
        return;

        ch = root->data;
    fprintf(fp,"%c ",ch);
    preorder(root->left,fp);
    preorder(root->right,fp);
}
void postorder(struct node *root,FILE *fp)
{
    char ch;
    if(root == NULL)
        return;


    postorder(root->left,fp);
    postorder(root->right,fp);
    ch = root->data;
    fprintf(fp,"%c ",ch);

}





