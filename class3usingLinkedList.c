#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct node
{

    int number;
    struct node *next;
};

int main()
{
    FILE *fp;
    int i , j;
    clock_t start,end;
    int random;
    struct node * head;
    head = NULL;
    struct node * temp;
    fp = fopen("E:\2nd sem docs\Third sem DS Appln","w+");
    for (i = 0 ; i<1000; i++)
    {
        random = rand() % 1001;
        temp = (struct node *) malloc(sizeof(struct node));
        temp->next = NULL;
        temp->number = random;

        if(head == NULL)
            head = temp;

        else if(head->next == NULL)
            head ->next = temp;

        else
        {
            struct node *bro = head;
            while(bro ->next != NULL)
                bro = bro->next;

            bro->next = temp;
        }

    }



// sorting the linked list
struct node * temp1;
struct node *temp2;
start=clock();
struct node *temp3 = head;
while(temp3->next != NULL)
{
    temp1 = temp3;
    temp2 = temp3->next;
    while(temp2!= NULL )
{
    int x1 = temp1->number;
    int x2 = temp2->number;

    if(x2 < x1)
    {
        int s = x1;
        temp1->number = temp2->number;
        temp2->number = s;
    }
    //temp1= temp1->next;
    temp2= temp2->next;
}

temp3 = temp3->next;



}

struct node * trav = head;

while(trav != NULL)
{
    printf("%d\n",trav->number);
    trav = trav->next;
}

end=clock();
double x=((double)(end-start)/CLOCKS_PER_SEC);
printf("time = %f",x);


}
