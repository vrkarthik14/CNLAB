#include<stdio.h>
#include<stdlib.h>

void main()
{
int lq[10],hq[10],i=0,ch,j=0,l=0,k=0,n=0,d=0;
for(n=0;n<4;n++)
{
	printf("Enter packets for %d th itnervals",n);
	scanf("%d",&d);
	printf("Enter the priority of the packets High(1) low(0)");
	scanf("%d",&ch);
	if(ch==0)
		lq[i++]=d;
	else
		hq[k++]=d;
}

printf("Processing order of the packets are:");
while(l<k)
{
	printf("%d->",hq[l++]);
}
while(j<i)
{
	printf("%d->",lq[j++]);
}	

}
