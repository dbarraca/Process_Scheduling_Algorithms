#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"
#include "timeSchedAlgs.h"
#include "roundRobin.h"
#include "highestPriority.h"

#define TRUE 1
#define FALSE 0

int main() {

   printf("Processes used corresponding to each run of each algorithm.\n");
   printAllProcs(TOT_PROCS,NUM_RUNS);

   printf("\nFirst Come First Serve\n");
   multipleRuns(TOT_PROCS, FALSE, NUM_RUNS, earlyArv);

   printf("\nShortest Job Time\n");
   multipleRuns(TOT_PROCS, FALSE, NUM_RUNS, shortExp);

   printf("\nShortest Remaining Time\n");
   multipleRuns(TOT_PROCS, TRUE, NUM_RUNS, shortRemain);

   printf("\nRound Robin\n");
   roundRobinRuns(TOT_PROCS);

   printf("\nNon-Preemptive Highest Priority");
   HPFRuns(TOT_PROCS, FALSE);

   printf("\nPreemptive Highest Priority");
   HPFRuns(TOT_PROCS, TRUE);

   return 0;
}
