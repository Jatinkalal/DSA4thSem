
#include<stdio.h>

main()
{
    int n,i,x,j,temp;
    int arr[9];
    char s[1000];
    FILE *fp;
    fp=fopen("RandomNumbers.txt","r+");
    fscanf(fp,"%d",&n);
    for(i=0;i<n;i++)
    {
        fscanf(fp,"%d",&x);
        arr[i]=x;
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(arr[j+1]>arr[j])
            {
                temp=arr[j+1];
                arr[j+1]=arr[j];
                arr[j]=temp;
            }
        }
    }
    fclose(fp);
    for(i=0;i<n;i++)
    {
        printf("%d\n",arr[i]);
    }
    fp=fopen("RandomNumbers.txt","r+");
      for(i=0;i<n;i++)
    {
        x=arr[i];
        fprintf(fp,"%d\n",x);
    }
    fclose(fp);
}
