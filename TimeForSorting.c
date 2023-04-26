
#include<stdio.h>
#include<time.h>

main()
{
int arr[1000],i,j,temp;
clock_t start,end;
FILE *fp;
fp=fopen("FileTime.txt","w+");
for(i=0;i<1000;i++)
{
    arr[i]=rand()%(1001);
    fprintf(fp,"%d\n",arr[i]);
    printf("%d\n",arr[i]);
}
start=clock();
for(i=0;i<1000;i++)
{
    for(j=0;j<1000;j++)
    {
        if(arr[j+1]>arr[j])
        {
            temp=arr[j+1];
            arr[j+1]=arr[j];
            arr[j]=temp;
        }
    }
}
end=clock();
double x=((double)(end-start)/CLOCKS_PER_SEC);
printf("%f",x);
fclose(fp);
fp=fopen("FileTime.txt","w+");
for(i=0;i<1000;i++)
{
    fprintf(fp,"%d\n",arr[i]);
}
}
