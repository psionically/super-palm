/*
Job Scheduling Performance
*/

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 

/*structure for output data*/
struct data
{
	char job_name[10];
	int arrival_time;
	int wait_time;
	int clock_time;
};

void ex(char file1[], char file2[], char file3[], char file4[]);
float average(int count, struct data* sched);
float variance(int count, float avg, struct data* sched);


int main()
{
  char rr[] = "rr.exe";
  char srt[] = "srt.exe";
  char hpf[] = "hpf.exe";
  char fcfs[] = "fcfs.exe";
  struct data r_data[1000];
  struct data s_data[1000];
  struct data h_data[1000];
  struct data f_data[1000];
  FILE *rr_out;
  FILE *srt_out;
  FILE *hpf_out;
  FILE *fcfs_out;
  char rr_file[100] = "rr_output.txt";
  char srt_file[100] = "srt_output.txt";
  char hpf_file[100] = "hpf_output.txt";
  char fcfs_file[100]= "fcfs_output.txt";
  int rr_count = 0;
  int srt_count = 0;
  int hpf_count = 0;
  int fcfs_count = 0;
  int r_line[100];
  int s_line[100];
  int h_line[100];
  int f_line[100]; 
  char *r_item;
  char *s_item;
  char *h_item;
  char *f_item;
  float f_avg = 0;
  float r_avg = 0;
  float s_avg = 0;
  float h_avg = 0;
  
  /* executing each scheduling program */
  ex(rr, srt, hpf, fcfs);
  
/* open each output file */
  rr_out = fopen(rr_file, "r");
  srt_out = fopen(srt_file, "r");
  hpf_out = fopen(hpf_file, "r");
  fcfs_out = fopen(fcfs_file, "r");
  
/* analyze data in output files
   I would have put this into a function as well, but I just ran out of time */
  
 	/* reading data into struct */
	while(fgets(r_line, 19, rr_out) != NULL)
   {  
   	r_item = strtok(r_line, " ");
   	strcpy(r_data[rr_count].job_name, r_item);
   	
   	r_item = strtok(NULL, " ");
   	r_data[rr_count].arrival_time = atoi(r_item);
   	
   	r_item = strtok(NULL, " ");
   	r_data[rr_count].wait_time = atoi(r_item);
   	
   	r_item = strtok(NULL, "\n");
   	r_data[rr_count].clock_time = atoi(r_item);
   	
   	rr_count++;
   }
   /* reading data into struct */
	while(fgets(s_line, 19, srt_out) != NULL)
   {  
   	s_item = strtok(s_line, " ");
   	strcpy(s_data[srt_count].job_name, s_item);
   	
   	s_item = strtok(NULL, " ");
    s_data[srt_count].arrival_time = atoi(s_item);
   	
   	s_item = strtok(NULL, " ");
   	s_data[srt_count].wait_time = atoi(s_item);
   	
   	s_item = strtok(NULL, "\n");
   	s_data[srt_count].clock_time = atoi(s_item);
   	
   	srt_count++;
   }
   /* reading data into struct */
	while(fgets(h_line, 19, hpf_out) != NULL)
   {  
   	h_item = strtok(h_line, " ");
   	strcpy(h_data[hpf_count].job_name, h_item);
   	
   	h_item = strtok(NULL, " ");
   	h_data[hpf_count].arrival_time = atoi(h_item);
   	
   	h_item = strtok(NULL, " ");
   	h_data[hpf_count].wait_time = atoi(h_item);
   	
   	h_item = strtok(NULL, "\n");
   	h_data[hpf_count].clock_time = atoi(h_item);
   	
   	hpf_count++;
   }
   /* reading data into struct */
	while(fgets(f_line, 19, fcfs_out) != NULL)
   {  
   	f_item = strtok(f_line, " ");
   	strcpy(f_data[fcfs_count].job_name, f_item);
   	
   	f_item = strtok(NULL, " ");
   	f_data[fcfs_count].arrival_time = atoi(f_item);
   	
   	f_item = strtok(NULL, " ");
   	f_data[fcfs_count].wait_time = atoi(f_item);
   	
   	f_item = strtok(NULL, "\n");
   	f_data[fcfs_count].clock_time = atoi(f_item);
   	
   	fcfs_count++;
   }
   
   /* call average function */
   f_avg = average(fcfs_count, &f_data);
   r_avg = average(rr_count, &r_data);
   s_avg = average(srt_count, &s_data);
   h_avg = average(hpf_count, &h_data);

   /* output each avg wait to compare */
   printf("\nAverage FCFS wait time: %f\n", f_avg);
   printf("Average RR wait time: %f\n", r_avg);
   printf("Average SRT wait time: %f\n", s_avg);
   printf("Average HPF wait time: %f\n", h_avg);
   
   /* output each variance to compare */
	printf("\nFCFS wait time variance: %f\n", variance(fcfs_count, f_avg, &f_data));
	printf("RR wait time variance: %f\n", variance(rr_count, r_avg, &r_data));
	printf("SRT wait time variance: %f\n", variance(srt_count, s_avg, &s_data));
	printf("HPF wait time variance: %f\n", variance(hpf_count, h_avg, &h_data));

  
  
  return 0;
}

/*--------------------------------------------------------------------------*/
/* This function will execute the programs from previous assignment. */
void ex(char file1[], char file2[], char file3[], char file4[])
{
  system(file1);
  system(file2);
  system(file3);
  system(file4);
}

/*--------------------------------------------------------------------------*/
/* This function will find and return the average wait time */
float average(int count, struct data* sched)
{
	float avg = 0;
	float total = 0;
	
    for(int j = 0; j < count; j++)
    {
  	  total = total + sched[j].wait_time;
    }
  
    avg = total / count;
    
    return avg;
}

/*--------------------------------------------------------------------------*/
/* This function will find and return the variance of wait time */
float variance(int count, float avg, struct data* sched)
{
	float total = 0;
	float var = 0;
	
	for(int k = 0; k < count; k++)
	{
		total = total + pow((sched[k].wait_time - avg), 2);
	}
	
	var = total / count;
	
	return var;
}

