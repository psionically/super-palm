/*
Scheduler Programs
Highest Priority First scheduling 
*/

/* 
This program will implement the HPF scheduling algorithm.
Input will come from a data file.
Output will be sent to a file as a list of jobs as they complete, 
arrival time, waiting time and the clock time for the job completed.
If two jobs have the same priority, the jobs will be executed depending
on their arrival time.
This is a non-preemptive implementation.
Sample data lines:
A1 6 30 4
A2 9 11 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*structure for input data*/
struct in_data
{
	char job_name[10];
	int arrival_time;
	int time_needed;
	int priority;
	
};

/*structure for output data*/
struct out_data
{
	char job_name[10];
	int arrival_time;
	int wait_time;
	int clock_time;
};

int main(){
	
   FILE *input;
   FILE *output;
   struct in_data jobs[1000];
   struct out_data out[1000];
   int count = 0;
   int line[20];
   char *item;
   int place;
   int temp;
   int temp_name[10];
   int ctr = 1;
   int k = 0;
   char in_file[100];
   char out_file[100];

   
   /* get input file from user */
   printf("\nEnter the input filename for HPF: ");
   scanf("%s", in_file);
   
   /* get output file from user */
   printf("Enter the output filename HPF: ");
   scanf("%s", out_file);
   
   printf("\nThe input file for HPF is %s \nThe output file for HPF is %s \n", in_file, out_file);
   /* open input file */
   input = fopen(in_file, "r");
   
   /* reading data into struct */
	while(fgets(line, 19, input) !=NULL)
   { 
   	item = strtok(line, " ");
   	strcpy(jobs[count].job_name, item);
   	
   	item = strtok(NULL, " ");
   	jobs[count].arrival_time = atoi(item);
   	
   	item = strtok(NULL, " ");
   	jobs[count].time_needed = atoi(item);
   	
   	item = strtok(NULL, "\n");
   	jobs[count].priority = atoi(item);
   	
   	count++;
   }
   
   /* close input file */
   fclose(input);
   
   /* sort priority, time_needed, job_name and arrival_time fields */
   for(int i = 0; i < count; i++)
   {
   	for(int j = i + 1; j < count; j++)
   	{
   		if(jobs[j].priority < jobs[i].priority)
   		{
   			temp = jobs[i].priority;
			jobs[i].priority = jobs[j].priority;
			jobs[j].priority = temp;
	
			temp = jobs[i].time_needed;
			jobs[i].time_needed = jobs[j].time_needed;
			jobs[j].time_needed = temp;
	
			strcpy(temp_name,jobs[i].job_name);
			strcpy(jobs[i].job_name, jobs[j].job_name);
			strcpy(jobs[j].job_name, temp_name);
			
			temp = jobs[i].arrival_time;
			jobs[i].arrival_time = jobs[j].arrival_time;
			jobs[j].arrival_time = temp;
		}
	}
   }
   
   /* calculating wait_time and clock_time */
   out[0].wait_time = 0;
   
   while(ctr < count)
   {
   	out[ctr].wait_time = 0;
   	
   	while(k < ctr)
   	{
   		out[ctr].wait_time = out[k].wait_time + jobs[k].time_needed;
   		out[k].clock_time = out[k].wait_time + jobs[k].time_needed;
   	    out[ctr].clock_time = out[k].clock_time + jobs[ctr].time_needed;
   		k++;
	}
   	
   	ctr++;
   }
   
    /* copying information from input to output struct */
   for(int n = 0; n < count; n++)
   {
   	strcpy(out[n].job_name, jobs[n].job_name);
   	out[n].arrival_time = jobs[n].arrival_time;
   	out[n].clock_time = out[n].wait_time + jobs[n].time_needed;
   }
   
   /* open output file */
   output = fopen(out_file, "a");
   
   /* generate output */   
   for(int m = 0; m < count; m++)
   {
   	fprintf(output, "%s %d %d %d\n", out[m].job_name, out[m].arrival_time, out[m].wait_time, out[m].clock_time);
   }
	   
   /* close output file */
   fclose(output);
   
   return 0;
}
