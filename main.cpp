#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
#include "Algos.cpp"
#define MAX_SIZE 100
using namespace std;

int main()
{
	process p[MAX_SIZE];
	int n;
	int ch;
	while(ch!=3)
	{
		cout<<"1) FCFS\n";
		cout<<"2) SJF\n";
		cout<<"3) Exit\n";
		cin>>ch;
		n = getinput(p);
		switch(ch)
		{
			case 1:
			{
			  FCFS(p,n);
				break;
			}
			case 2:
			{
			  SJF_nonpreempt(p,n);
				break;
			}
			case 5:
			{
				cout<<"Thank You!!";
				break;
			}
		}
	}
  return 0;
}
