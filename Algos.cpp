#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
#include "Process.h"
#include "Funcs.cpp"
#define MAX_SIZE 100
using namespace std;

void FCFS(process p[],int n)
{
    if(n > 0)
    {
        //SORT THEM ON ARRIVAL TIME
        sort(p,p+n,arrival_compare);
        //A QUEUE OF TYPE Process
        queue<process*> q;
        int i,st,iot,prev_st;
        //START TIME IS THE ARRIVAL TIME OF FIRST PROCESS
        st = p[0].arrival_time;
        //PUSH THE FIRST PROCESS
        q.push(&p[0]);
        i = 1;
        //IF THERE IS ANY OTHER PROCESS WHICH ARRIVES BEFORE OR EQUAL TO First
        //THEN PUSH IT TO THE QUEUE
        while(i<n && p[i].arrival_time<=st)
        {
            q.push(&p[i]);
            i++;
        }

        //NUMBER OF PROCESSES
        int count_pro_done;
        int j,tat;
        count_pro_done = j = 0;
        iot = 0;

        while(count_pro_done != n && !q.empty())
        {
            //TAKE THE FIRST PROCESS FROM QUEUE
            process *temp = q.front();
            //cout<<temp->process_id<<"(Arrival time: "<<temp->arrival_t<<", Wait time till now: "<<temp->wait_time<<", IO_Q till now: "<<iot<<") is being executed at time "<<st<<" with burst time "<<temp->burst_t<<"\n";
            //REMOVE FROM QUEUE
            q.pop();

            prev_st = st;

            //IF THE BURST TIME OF THE PROCESS IS MORE THAN CPU BURST, THEN WILL GO IN IO QUEUE
            if(temp->burst_t >= temp->cpu_burst)
            {
                //IF THE PROCESS HAS COMPLETED PARTIALLY BEFORE
                //HOW MUCH THE PROCESS HAD TO WAIT IN QUEUE
                if(temp->completion_time != 0)
                    temp->wait_time += st - temp->completion_time - temp->io_burst;
                else

                    temp->wait_time += st - temp->arrival_t;

                //TIME FOR WHICH PROCESS EXECUTED
                st += temp->cpu_burst;
                //REDUCE THE BURST TIME OF PROCESS TILL WHICH EXECUTED
                temp->burst_t -= temp->cpu_burst;
                //THE AMOUNT OF WHICH WORK COMPLETED BY THE PROCESS TILL NOW
                temp->completion_time = st;

                //IF THE EXECUTION OF PROCESS IS COMPLETE
                if(temp->burst_t == 0)
                {
                    //WILL PUSH AT THE END OF THE READY QUEUE
                    temp->arrival_t = INT_MAX;
                    //CALCULATE THE TOTAL TURN AROUND TIME OF THIS PROCESS
                    temp->turn_around_time = temp->burst_time + temp->wait_time;
                }
                //INCASE TIME IN IO QUEUE IS LESS THAN EQUAL TO THE CALCULATED st COMPLETITION TIME
                else if(iot<=st)
                {
                    //THE NEW ARRIVAL TIME OF THE PARTIALLY COMPLETED PROCESS JUST STARTS AFTER IO
                    temp->arrival_t = iot = st + temp->io_burst;
                }
                else
                {
                    //IN CASE IOT>ST THE PROCESS WAIT FOR ADDITIONAL IOT-ST TIME IN THE QUEUE BEFORE IT ARRIVES
                    temp->arrival_t = iot = iot + temp->io_burst;
                }
            }
            //IF THE PROCESSES' BURST TIME IS LESS THAN THE CPU BURST SIMPLE EXECUTION
            else
            {
                if(temp->completion_time != 0)
                    temp->wait_time += st - temp->completion_time - temp->io_burst;
                st += temp->burst_t;
                //COMPLETELY EXECUTED
                temp->burst_t = 0;
                temp->completion_time = st;
                temp->turn_around_time = temp->burst_time + temp->wait_time;
                //PUSHED AT LAST IN THE QUEUE
                temp->arrival_t = INT_MAX;
                //COUNTER OF PROCESS INCREEMENTED
                count_pro_done++;
            }
            for(i=0 ; i<n ; i++)
            {
                //INSERT ALL THE PROCESSES WHOSE ARRIVAL TIME IS LESS THEN THE COMPLETED TIME
                //BUT GREATER THAN THE PREVIOUS COMPLETION TIME
                if(p[i].arrival_t<=st && p[i].arrival_t> prev_st)
                    q.push(&p[i]);
            }
            //EXECUTION OF THE REMAINING PROCESS EVEN AFTER THE READY QUEUE BECOMES EMPTY
            if(q.empty() && count_pro_done!=n)
            {
                for(i=0 ; i<n ; i++)
                {
                    if(p[i].burst_t != 0)
                    {
                        q.push(&p[i]);
                        if(p[i].burst_t != p[i].burst_time)
                        {
                            st = p[i].arrival_t;
                        }
                        else
                        {
                            st = p[i].arrival_time;
                        }
                        break;
                    }
                }
            }
        }
        display(p,n,st);
    }
}

void SJF_nonpreempt(process p[],int n)
{
    if(n > 0)
    {
        //INITIALLY SORT THE PROCESS IN ARRIVAL TIME
        sort(p,p+n,arrival_compare);
        //ALLOW TO PUSH/POP THE PROCESSES FROM BOTH SIDES
        deque<process*> q;
        int i,st,iot,prev_st;
        //TAKE THE FIRST PROCESS
        st = p[0].arrival_time;
        //PUSH IT ONTO THE QUEUE
        q.push_back(&p[0]);
        i = 1;

        //IF THERE IS ANY OTHER PROCESS WHICH ARRIVES BEFORE OR EQUAL TO FIRST
        //THEN PUSH IT TO THE QUEUE
        while(i<n && p[i].arrival_time<=st)
        {
            q.push_back(&p[i]);
            i++;
        }

        //COUNTER FOR NUMBER OF PROCESSES DONE TILL NOW
        int count_pro_done;
        int j,tat;
        count_pro_done = j = 0;
        iot = 0;

        while(count_pro_done != n && !q.empty())
        {
            //SORT MY READY QUEUE ON THE BASIS OF THE (REMAINING) BURST TIME
            sort(q.begin(),q.end(),burst_compare);
            //PROCESS ON THE TOP
            process *temp = q.front();
            //cout<<temp->process_id<<"(Arrival time: "<<temp->arrival_t<<", Wait time till now: "<<temp->wait_time<<", IO_Q till now: "<<iot<<") is being executed at time "<<st<<" with burst time "<<temp->burst_t<<"\n";
            q.pop_front();

            //SAVE THE START TIME IN CPU CHART TILL NOW
            prev_st = st;

            //IF THE BURST TIME OF THE PROCESS IS MORE THAN CPU BURST, THEN WILL GO IN IO QUEUE
            if(temp->burst_t >= temp->cpu_burst)
            {
                //IF THE PROCESS HAS ALREADY EXECUTED FOR SOME TIME
                if(temp->completion_time != 0)
                    temp->wait_time += st - temp->completion_time - temp->io_burst;
                else
                    //IF THE PROCESS HAS JUST STARTED,
                    temp->wait_time += st - temp->arrival_t;
                //THE TIME TILL WHICH THIS PROCESS RUNS
                st += temp->cpu_burst;
                //REDUCE THE BURST TIME WHICH REMAINS AFTER THIS PARTIAL RUN
                temp->burst_t -= temp->cpu_burst;
                //UPDATE THE TIME TILL WHICH THE PROCESS HAS EXECUTED (PARTIALLY)
                temp->completion_time = st;

                //IF THE EXECUTION OF PROCESS IS COMPLETE
                if(temp->burst_t == 0)
                {
                    //PUSH THIS PROCESS AT THE END OF THE QUEUE
                    temp->arrival_t = INT_MAX;
                    //FIND THE COMPLETITON TIME
                    temp->turn_around_time = temp->burst_time + temp->wait_time;
                }
                ////INCASE TIME IN IO QUEUE IS LESS THAN EQUAL TO THE CALCULATED st COMPLETITION TIME
                //THAT IS JUST AFTER OR EQUAL TO ST, IOT END THEN IT CAN ARRIVE AT THAT INSTANT ONLY
                else if(iot<=st)
                {
                    temp->arrival_t = iot = st + temp->io_burst;
                }
                else
                {
                    //IN CASE IOT>ST THE PROCESS WAIT FOR ADDITIONAL IOT-ST TIME IN THE QUEUE BEFORE IT ARRIVES
                    temp->arrival_t = iot = iot + temp->io_burst;
                }
            }
            //IF THE PROCESSES' BURST TIME IS LESS THAN THE CPU BURST SIMPLE EXECUTION
            else
            {
                if(temp->completion_time != 0)
                    temp->wait_time += st - temp->completion_time - temp->io_burst;
                st += temp->burst_t;
                temp->burst_t = 0;
                temp->completion_time = st;
                temp->turn_around_time = temp->burst_time + temp->wait_time;
                temp->arrival_t = INT_MAX;
                count_pro_done++;
            }
            for(i=0 ; i<n ; i++)
            {
              //INSERT ALL THE PROCESSES WHOSE ARRIVAL TIME IS LESS THEN THE COMPLETED TIME
              //BUT GREATER THAN THE PREVIOUS COMPLETION TIME
                if(p[i].arrival_t<=st && p[i].arrival_t> prev_st)
                    q.push_back(&p[i]);
            }
            //EXECUTION OF THE REMAINING PROCESS EVEN AFTER THE READY QUEUE BECOMES EMPTY
            if(q.empty() && count_pro_done!=n)
            {
                for(i=0 ; i<n ; i++)
                {
                    //ALL THE PROCESS WHO HAVE STILL NOT EXECUTED
                    if(p[i].burst_t != 0)
                    {
                        q.push_back(&p[i]);
                        //IF THE REMAINING BURST TIME IS NOT EQUAL TO THE BURST TIME
                        if(p[i].burst_t != p[i].burst_time)
                        {
                            //THEN ARRIVE AT THE CURRENTLY ENDED COMPLETITION TIME IN CPU LINE
                            st = p[i].arrival_t;
                        }
                        else
                        {
                            //OTHERWISE ARRIVE AT THEIR RESPECTIVE ARRIVAL TIME
                            st = p[i].arrival_time;
                        }
                        break;
                    }
                }
            }
        }
        display(p,n,st);
    }
}
