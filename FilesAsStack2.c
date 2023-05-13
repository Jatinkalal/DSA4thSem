#include<stdio.h>
#include<stdlib.h>

int isEmpty (FILE *fp);
int main()
{
    int range;
    int operationsNum;
    int randomNum;
    int fetchNum1;
    int fetchNum2;
    int choice;
    int pushOperations = 0;

    char push[6] = "push ";
    char pop[6] = "pop ";



    FILE *ifp; // input file
    FILE *sfp; // stack file
    FILE *pushfp; // push file
    FILE *popfp; // pop file
    FILE *opfp; // operation file

    printf("Enter range:\n");
    scanf("%d",&range);

    ifp = fopen("inputFile.txt","a");

    for(int i = 0 ; i < range ; i++)
    {
        randomNum = rand()%range;
        fprintf(ifp,"%d ",randomNum);

    }

    fclose(ifp);

    ifp = fopen("inputFile.txt","r+");
    pushfp = fopen("PushFile.txt","a");
    popfp = fopen("PopFile.txt","a");
    opfp = fopen("OperationFile.txt","a");

    printf("Enter number of operations:\n");
    scanf("%d",&operationsNum);

    for(int j = 0 ; j < operationsNum; j++)
    {
        printf("\nPress\n1-Push\n2-Pop\n");
        scanf("%d",&choice);

        if(choice == 1)
        {
            if(pushOperations > range)
            {
                printf("File overflow");
                break;
            }
            sfp = fopen("Stack.txt","a");
            fscanf(ifp,"%d",&fetchNum1);
            fprintf(sfp,"%d",fetchNum1);
            fprintf(pushfp,"%d",fetchNum1);
            fprintf(opfp,"%s",push);
            fclose(sfp);
            pushOperations++;

        }

        else if(choice == 2)
        {

            if(sfp == NULL || isEmpty(sfp))
            {
                printf("File empty\n");
                break;
            }

            sfp = fopen("Stack.txt","r");

            fscanf(sfp,"%d",&fetchNum2);
            fprintf(popfp,"%d",fetchNum2);
            fprintf(opfp,"%s",pop);
        }

    } // end of for loop

        fclose(ifp);
        fclose(opfp);
        fclose(pushfp);
        fclose(popfp);

        return 0;

}

int isEmpty (FILE *fp)
{
    return(feof(fp));
}
