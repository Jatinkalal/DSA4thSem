#include<stdio.h>
#include<stdlib.h>
#define QSIZE 5

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
void deleteFront(queue *dq,FILE *Qfp,FILE *deqfp,FILE *opfp);

int main()
{
    int arr[100];
    int choice1;
    int rangeOfRandomNum;

    queue dq;
    dq.front = QSIZE -1;
    dq.rear = QSIZE -1;
    dq.index = 0;

    FILE *ifp =fopen("CQueueInput.txt","a"); // input file of random numbers
    FILE *enqfp = fopen ("CEnQueue.txt","a"); // Inserted numbers
    FILE *deqfp = fopen("CDeQueue.txt","a");  // Deleted numbers
    FILE *opfp = fopen("COperations.txt","a"); // operations performed
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
                insertRear(&dq,arr,Qfp,enqfp,opfp);
            }


        }

        else
        {
            if(empty(dq))
            {
                printf("Queue Empty\n");

            }
            else
            {

                deleteFront(&dq,Qfp,deqfp,opfp);

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
    int rear = dq.rear;
    return((rear +1 ) % QSIZE == dq.front);
}

int empty(queue dq)
{
    return(dq.rear == dq.front);
}

void insertRear(queue *dq,int arr[100],FILE *Qfp,FILE *enqfp,FILE *opfp)
{
    int num = arr[dq->index];
    int rear = dq->rear;
    dq->rear = (rear + 1)% QSIZE;
    dq->q[dq->rear] = num;
    dq->index = dq->index + 1;
    QueueFile(dq,Qfp);
    fprintf(enqfp,"%d ",num);
    fprintf(opfp,"%s","insertRear ");

}
void deleteFront(queue *dq,FILE *Qfp,FILE *deqfp,FILE *opfp)
{
    int data = dq->q[dq->front];
    int front = dq->front;
    dq->front = (front + 1) % QSIZE;
    QueueFile(dq,Qfp);
    fprintf(deqfp,"%d ",data);
    fprintf(opfp,"%s","deleteFront ");
}
void QueueFile(queue *dq,FILE *fp)
{
    // copy all the data from the queue to the file
    fp = fopen("Queue.txt","w");
    for(int i = dq->front ; i != dq->rear ; i = (i+1)%QSIZE)
    {
        int queueData = dq->q[i];
        fprintf(fp,"%d ",queueData);
    }
    fclose(fp);
}



