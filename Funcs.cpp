#include <iostream>
#include <string.h>
#include "Process.h"
#include<bits/stdc++.h>
using namespace std;
#define MAX_SIZE 100

int getinput(process p[])
{

	FILE *fptr;
	int i = 0;
	fptr = fopen("process_queue.txt","r");
	if(!fptr)
	{
		cerr<<"Error opening the input file.\n";
		exit(1);
	}
	else
	{
		char in_line[100];
		char *pid;

		while(1)
		{
		    fscanf(fptr,"%s",in_line);
			if(feof(fptr))
				break;
		    pid = strtok(in_line,";");
		    strcpy(p[i].process_id,pid);
		    sscanf(strtok(NULL,";"), "%d", &p[i].arrival_time );
		    sscanf(strtok(NULL,";"), "%d", &p[i].burst_time );
		    sscanf(strtok(NULL,";"), "%d", &p[i].io_burst );
		    sscanf(strtok(NULL,";"), "%d", &p[i].cpu_burst );
		    p[i].completion_time = 0;
		    p[i].wait_time = 0;
		    p[i].turn_around_time = 0;
		    p[i].burst_t = p[i].burst_time;
		    p[i].arrival_t = p[i].arrival_time;
		    i++;
		}
	}
	fclose(fptr);
	return i;
}

void display(process p[],int n,int total_run_time)
{
	cout<<"Process \tArrival Time \tBurst Time \tIO Burst  \tCPU Burst  \tWaiting time \tTurn Around Time   Completion Time   Penalty Ratio\n";

	int i;
	float penalty_ratio;
	for(i=0 ; i<n ; i++)
	{
		penalty_ratio = (float)(p[i].completion_time - p[i].arrival_time) / (float)p[i].burst_time;
		cout<<p[i].process_id<<" \t\t"<<p[i].arrival_time<<" \t\t"<<p[i].burst_time<<" \t\t"<<p[i].io_burst<<" \t\t"<<p[i].cpu_burst<<" \t\t"
		    <<p[i].wait_time<<" \t\t"<<p[i].turn_around_time<<" \t\t   "<<p[i].completion_time<<" \t\t     "<<penalty_ratio<<endl;
	}
	cout<<"Throughput = "<<(float)n/(float)total_run_time<<"\n\n";
}

bool arrival_compare(process p1, process p2)
{
    return p1.arrival_t < p2.arrival_t;
}

bool burst_compare(process* p1, process* p2)
{
    return p1->burst_time < p2->burst_time;
}
