#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
int queue[MAXSIZE];
typedef struct process
{
	int at;
	int bt;
	int ct;
	int tt;
	int wt;
	int ft;
	int rt;
}Process;
int front = 0;
int rear = -1;
int isempty(){
	if(front > rear)
	{
		return 1;
	}
	return 0;
}
void enqueue(int item)
{
	if(rear == MAXSIZE-1)
	{
		printf("Queue Overloaded! Exceded max size");
		exit(0);
	}
	rear = rear+1;
	queue[rear] = item;
	printf("rear =%d item = %d ",rear,queue[rear]);
}
int dequeue(){
	int item;
	if(isempty())
	{
		return -1;
	}
	item = queue[front++];
	return item;
}
void round_robin(int n){
	int i,j,qtime,time,time_slice,item,counter,max;
	int sorted_process[n],temp[n];
	Process p[n];
	for(i = 0; i<n; ++i)
	{
		sorted_process[i]=0;
		printf("%d ",sorted_process[i]);
	}
	for(i = 0; i<n; ++i)
	{
		temp[i]=0;
		printf("%d ",temp[i]);
	}
	printf("Enter the arrival time for %d processes:\n", n);
	for(i = 0; i<n; ++i)
	{
		scanf("%d",&(p[i].at));
		temp[i] = (p[i].at);
	}
	printf("Enter the burst time for %d processes:\n", n);
	for(i = 0; i<n; ++i)
	{
		scanf("%d",&(p[i].bt));
	}
	printf("Enter the quantum time :");
	scanf("%d",&qtime);
	//sort the processes based on arrival time
	//selection sort is used here
	printf("\n");
	for(i=n-1; i>=0; --i)
	{
		max = -1;
		for(j=n-1; j>=0; --j)
		{
			if(temp[j]>max){
				max = temp[j];
				sorted_process[i] = j;
			}
		}
			temp[sorted_process[i]] = -1;
	}
	for(i = 0; i<n; ++i)
	{
		//sorted_process[i]=0;
		printf("%d ",sorted_process[i]);
	}
	for(i = 0; i<n; ++i)
	{
		//temp[i]=0;
		printf("%d ",temp[i]);
	}
	enqueue(sorted_process[0]);
	time = p[sorted_process[0]].at;
	counter = 1;
	printf("qqqq %d %d\n",p[sorted_process[counter]].at,time);
	//for(i = counter;p[sorted_process[i]].at<=time;++i,++counter){
			//printf("%d %d ",i,counter);
			//enqueue(sorted_process[i]);
	//	}

	for(;front<=rear;){
		printf("hello");
		item = dequeue();
		if(p[item].bt>qtime)
		{
			time_slice = qtime;

		}
		else
		{
			time_slice = p[item].bt;
		}
		printf("hello world");
		p[item].bt -= time_slice;
		time += time_slice;
		for(i = counter;p[sorted_process[i]].at<=time;++i,++counter){
			enqueue(sorted_process[i]);
		}
		if(p[item].bt!=0){
			enqueue(item);
		}
		else
		{
			p[item].ct = time;
		}

	}
	// for(i = 0;i<n;i++)
	// {
	// 	printf("%d", p[i].ct);
	// }
}
int main(int argc, char const *argv[])
{
	int n;
	printf("Enter the no of processes:");
	scanf("%d",&n);
	round_robin(n);
	return 0;
}