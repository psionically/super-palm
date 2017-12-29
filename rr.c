/*
Scheduler Programs
Round Robin scheduling
*/

/* 
This program will implement the RR scheduling algorithm.
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

typedef enum { false, true } bool;

int main(){
	
   FILE *input;
   FILE *output;
   struct in_data jobs[1000];
   struct out_data out[1000];
   int count = 0;
   int line[20];
   char *item;
   int time = 0;
   int t[100];
   int time_quantum = 10;
   char in_file[100];
   char out_file[100];
   bool done = false;
   int temp;
   int temp_name[50];

   
   /* get input file from user */
   printf("\nEnter the input filename for RR: ");
   scanf("%s", in_file);
   
   /* get output file from user */
   printf("Enter the output filename for RR: ");
   scanf("%s", out_file);
   
   printf("\nThe input file for RR is %s \nThe output file for RR is %s \n", in_file, out_file);
   
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
   
   for(int s = 0; s < count; s++)
   {
   	t[s] = jobs[s].time_needed;
   }
   
   /* calculating wait_time */
   while(done != true)
   {
   	for(int i = 0; i<count; i++)
   	{
   		/* will exit the while loop when all jobs have completed */
   		done = true;

   		if(t[i] > 0)
   		{
   			done = false;
   			if(t[i] > time_quantum)
   			{
   				/* time of time quantum has passed so add time quantum to the clock/total time */
   				time += time_quantum;
   				/* subtract the time_quantum to get the new time_needed */
   				t[i] -= time_quantum;
			}
			else
			{
				/* time passing by time_needed */
				time += t[i];
				out[i].wait_time = time - jobs[i].time_needed;
				/* time_needed now = 0 */
				t[i] = 0;
			}
		}
	}
}
	
   /* calculating clock_time */
   for(int j = 0; j < count; j++)
   {
   	out[j].clock_time = jobs[j].time_needed + out[j].wait_time;
   }
   
   /* copying information from input to output struct */
   for(int n = 0; n < count; n++)
   {
   	strcpy(out[n].job_name, jobs[n].job_name);
   	out[n].arrival_time = jobs[n].arrival_time;
   }
   
   /* sorting by clock_time for output*/
   for(int k = 0; k < count; k++)
	{	
		for(int p = k + 1; p < count; p++)
		{
			if(out[p].clock_time < out[k].clock_time)
			{		
				temp = out[k].wait_time;
				out[k].wait_time = out[p].wait_time;
				out[p].wait_time = temp;
		
				strcpy(temp_name, out[k].job_name);
				strcpy(out[k].job_name, out[p].job_name);
				strcpy(out[p].job_name, temp_name);
				
				temp = out[k].arrival_time;
				out[k].arrival_time = out[p].arrival_time;
				out[p].arrival_time = temp;
				
				temp = out[k].clock_time;
				out[k].clock_time = out[p].clock_time;
				out[p].clock_time = temp;
			}
		}
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
