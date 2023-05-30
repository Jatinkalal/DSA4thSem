#include<stdio.h>
#include<stdlib.h>
#define QSIZE 10

typedef struct
{
    int q[QSIZE];
    int front,rear,index;
} queue;

void insertRandomNumbers(int arr[100],int size,FILE *fp);
int full(queue dq);
int empty(queue dq);
void QueueFile(queue *dq,FILE *fp);
void insertRear(queue *dq,int arr[100],FILE *Qfp,FILE *enqfp,FILE *opfp);
void insertFront(queue *dq,int arr[100],FILE *Qfp,FILE *enqfp,FILE *opfp);
void deleteFront(queue *dq,FILE *Qfp,FILE *deqfp,FILE *opfp);
void deleteRear(queue *dq,FILE *Qfp,FILE *deqfp,FILE *opfp);

int main()
{
    int arr[100];
    int choice1;
    int choice2;
    int rangeOfRandomNum;

    queue dq;
    dq.front = 0; // always 0
    dq.rear = -1;
    dq.index = 0;

    FILE *ifp =fopen("QueueInput.txt","a"); // input file of random numbers
    FILE *enqfp = fopen ("EnQueue.txt","a"); // Inserted numbers
    FILE *deqfp = fopen("DeQueue.txt","a");  // Deleted numbers
    FILE *opfp = fopen("Operations.txt","a"); // operations performed
    FILE *Qfp;

    printf("Enter range of random numbers:\n");
    scanf("%d",&rangeOfRandomNum);
    insertRandomNumbers(arr,rangeOfRandomNum,ifp);

    for(int i = 0 ; i < 5; i++)
    {
        printf("Enter 1-Inserting element\n2-Deleting element\n");
        scanf("%d",&choice1);

        if(choice1 == 1)
        {
            if(full(dq))
            {
                printf("Queue full\n");
            }
            else
            {

                 printf("Enter 1-Insert front\n2-Insert rear\n");
                 scanf("%d",&choice2);

                 if(choice2 == 1)
                  {
                    insertFront(&dq,arr,Qfp,enqfp,opfp);
                  }

                else if(choice2 == 2)
                {
                   insertRear(&dq,arr,Qfp,enqfp,opfp);
                }

            } // end of !full

        }

        else
        {
            if(empty(dq))
            {
                printf("Queue Empty\n");

            }
            else
            {
                  printf("Entter 1- Delete Front\n2-Delete rear\n");
                  scanf("%d",&choice2);


               if(choice2 == 1)
                {
                  deleteFront(&dq,Qfp,deqfp,opfp);
                }

               else if(choice2 == 2)
                {
                   deleteRear(&dq,Qfp,deqfp,opfp);
                }

            } // end of !empty else


        } // end of else of choice 1

    } // end of for loop
    fclose(enqfp);
    fclose(deqfp);
    fclose(opfp);

    return 0;





}

void insertRandomNumbers(int arr[100],int size,FILE *fp)
{
    int randNum;
    for(int i = 0 ; i<size; i++)
    {
        randNum= rand()%size;
        arr[i] = randNum;
        fprintf(fp,"%d ",randNum);
    }
    fclose(fp);
}

int full(queue dq)
{
    return(dq.rear == QSIZE-1);
}

int empty(queue dq)
{
    return(dq.front > dq.rear);
}

void insertFront(queue *dq,int arr[100],FILE *Qfp,FILE *enqfp,FILE *opfp)
{
   int i = dq->rear;
   for(int i = dq->rear; i != -1 ; i--)
   {
       dq->q[i+1] = dq->q[i];
   }
   dq->rear = dq->rear + 1;
   int num = arr[dq->index];
   dq->index =dq->index + 1;
   dq->q[dq->front] = num;
   QueueFile(dq,Qfp);
   fprintf(enqfp,"%d ",num);
   fprintf(opfp,"%s","insertFront ");

}
void insertRear(queue *dq,int arr[100],FILE *Qfp,FILE *enqfp,FILE *opfp)
{
    int num = arr[dq->index];
    dq->rear = dq->rear + 1;
    dq->q[dq->rear] = num;
    dq->index = dq->index + 1;
    QueueFile(dq,Qfp);
    fprintf(enqfp,"%d ",num);
    fprintf(opfp,"%s","insertRear ");

}
void deleteFront(queue *dq,FILE *Qfp,FILE *deqfp,FILE *opfp)
{
    int data = dq->q[dq->front];
    int i = 1;
    while(i <= dq->rear)
    {
        dq->q[i-1] = dq->q[i];
        i++;
    }
    dq->rear = dq->rear - 1;
    QueueFile(dq,Qfp);
    fprintf(deqfp,"%d ",data);
    fprintf(opfp,"%s","deleteFront ");
}
void deleteRear(queue *dq,FILE *Qfp,FILE *deqfp,FILE *opfp)
{
    int data = dq->q[dq->rear];
    dq->rear = dq->rear - 1;
    QueueFile(dq,Qfp);
    fprintf(deqfp,"%d ",data);
    fprintf(opfp,"%s","deleteRear ");

}

void QueueFile(queue *dq,FILE *fp)
{
    // copy all the data from the queue to the file
    fp = fopen("Queue.txt","w");
    for(int i = dq->front ; i <=dq->rear ; i++)
    {
        int queueData = dq->q[i];
        fprintf(fp,"%d ",queueData);
    }
    fclose(fp);
}

