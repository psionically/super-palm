/*
Scheduler Programs
First Come First Served scheduling
*/

/* 
This program will implement the FCFS scheduling algorithm.
Input will come from a data file.
Output will be sent to a file as a list of jobs as they complete, 
arrival time, waiting time and the clock time for the job completed.
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
   int ctr = 1;
   int i = 0;
   char in_file[100];
   char out_file[100];

   
   /* get input file from user */
   printf("\nEnter the input filename for FCFS: ");
   scanf("%s", in_file);
   
   /* get output file from user */
   printf("Enter the output filename for FCFS: ");
   scanf("%s", out_file);
   
   printf("\nThe input file for FCFS is %s \nThe output file for FCFS is %s \n", in_file, out_file);
   /* open input file */
   input = fopen(in_file, "r");
   
   /* reading data into struct */
	while(fgets(line, 19, input) != NULL)
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
   
   /* calculating wait_time and clock_time */
   out[0].wait_time = 0;
   
   while(ctr < count)
   {
   	out[ctr].wait_time = 0;
   	
   	while(i < ctr)
   	{
   		out[ctr].wait_time = out[i].wait_time + jobs[i].time_needed;
   	    out[i].clock_time = out[i].wait_time + jobs[i].time_needed;
   	    out[ctr].clock_time = out[i].clock_time + jobs[ctr].time_needed;

   		i++;
	}
	
   	ctr++;
   }
   
    /* copying information from input to output struct */
   for(int j = 0; j < count; j++)
   {
   	strcpy(out[j].job_name, jobs[j].job_name);
   	out[j].arrival_time = jobs[j].arrival_time;
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

