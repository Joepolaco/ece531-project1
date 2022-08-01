#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXC 256
#define true i<=6

void helpme(){
  printf("\n\nWelcome.  This is a thermostat application. \n\n");
  printf("It runs on an ARM image and contacts a cloud API.\n");
  printf("It will download temperature time settings and then begin to run \n");
  printf("To enter imput for these settings go to http://54.1XX.XXX.XX/themxxxx.php/\n");
  printf("Once there, enter IoT Thermostat settings and hit submit\n");
  printf("Now, once the thermostat application is running you can see the status.\n");
  printf("Look for the Thermostat Status at the top of the page.\n");
  printf("You will need to refresh this page to see the updates to the status.\n");
  printf("The application will send updates every 10 seconds.\n\n");
  printf("Enjoy.. by Joseph Polaco\n\n");
  exit(0);
}

int main(int argc, char *argv[])
{
  int j;
  if(argc > 1) {
      for(j = 1; j < argc; j++) {
         if (strncmp(argv[j], "-h",2) == 0) {
         helpme(); printf("Run 'help' \n");
         }
         else if (strncmp(argv[j], "--help",5) == 0) {
         helpme(); printf("Run '--help' \n");
         }
         else {
         printf("You must enter either -h or --help");
         exit(1);
         }
      }
  }
    printf("\nThe program is now running\n\n");

    int hours, minutes, seconds;
    int time_morning, time_evening, time_night;
    int set_temp, temp1, temp2, temp3;
    double time_now, time1, time2, time3;

    int temp_now;
    char tm_stmp[100]="";

    time_t now;

    //for(int i = 0; true; i++){

/*----This will go to the cloud API and HTTP GET time temperature settings data----*/
    char buf[MAXC] = "";    /* buffer to hold MAXC chars at a time */
    int nval = 0;           /* total number of integers found */
    int ctr = 0;
    int setting[50];

    /*  Get data from cloud ------------------------------------------------*/
    //system("curl -s http://54.XXX.XXX.XX/temp.txt -o /tmp/temp.txt");
    //sleep(1);
    /* Parse data from cloud ---------------------------------------------*/
    /*FILE *data_file = fopen("/tmp/temp.txt", "r"); //: stdin;
         if (data_file == NULL) {
            printf("Error! Could not open cloud time set file\n");
            exit(-1);
         }*/
    /* Store this data ---------------------------------------------------------*/
    /*time_morning=setting[0],/*AM*/ //time_evening=setting[2]/*PM*/,time_night=setting[4]/*PM*/;
    //temp1=setting[1],temp2=setting[3],temp3=setting[5];
    //fclose (data_file);

    //time1=time_morning, time2=time_evening+12, time3=time_night+12;
/*--------------------------------------------------------------------------------------------*/

     /* open the professor's temp values------------------------------------------*/
        FILE *in_file  = fopen("/tmp/temp", "r"); // read only
        if (in_file == NULL) {
          printf("Error! Could not open temperature file\n");
          exit(-1);
        }
        fscanf(in_file, "%d\n", &temp_now); // read the current temperature from file /temp
        fclose(in_file);

  /*  Get local time ------------------------------------------------------*/
        time(&now);

        struct tm *local = localtime(&now);
        hours = local->tm_hour;  /* get hours since midnight (0-23) */
        minutes = local->tm_min; /* get minutes passed after the hour (0-59) */
        seconds = local->tm_sec; /* get seconds passed after a minute (0-59) */
        time_now = (double)hours + (double)minutes/60 + (double)seconds/3600;//current time in fractions//
        snprintf(tm_stmp, sizeof(tm_stmp), "%02d:%02d:%02d", hours, minutes, seconds);
        if (hours < 12) {    /* before midday */
           printf("  Time is %02d:%02d:%02d am\n", hours, minutes, seconds);
        }
        else {    /* after midday */
           printf("  Time is %02d:%02d:%02d pm\n", hours-12, minutes, seconds);
        }

    return 0;
}
