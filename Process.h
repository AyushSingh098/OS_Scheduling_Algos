#ifndef Process_h
#define Process_h

typedef struct process_type
{
	char process_id[20];
	int arrival_t;
	int arrival_time;
	int burst_t;
	int burst_time;
	int completion_time;
	int turn_around_time;
	int wait_time;
	int io_burst;
	int cpu_burst;
}process;

int getinput(process p[]);
void display(process p[],int n,int total_run_time);
void FCFS(process p[],int n);
bool arrival_compare(process p1, process p2);
bool burst_compare(process* p1, process* p2);
void SJF_nonpreempt(process p[],int n);

#endif
