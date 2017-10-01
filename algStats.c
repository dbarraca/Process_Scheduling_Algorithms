#include <stdio.h>
#include "process.h"

float avgRunTime(Proc **procs, int numProcs) {
   int procNdx, numFinished = 0;;
   float sum = 0;

   for (procNdx = 0; procNdx < numProcs; procNdx++) {
      sum += ((*(procs + procNdx))->run);
      numFinished++;
   }

   return sum / numFinished;
}

float avgWaitTime(Proc **procs, int numProcs) {
   int procNdx, numFinished = 0;
   float sum = 0;

   for (procNdx = 0; procNdx < numProcs; procNdx++) {
	  if ((*(procs + procNdx))->start > 0) {
         sum += ((*(procs + procNdx))->start - (*(procs + procNdx))->arv);
         numFinished++;
	  }
   }

   return sum / numFinished;
}

float avgTurnaroundTime(Proc **procs, int numProcs) {
   int procNdx, numFinished = 0;;
   float sum = 0;

   for (procNdx = 0; procNdx < numProcs; procNdx++) {
      if ((*(procs + procNdx))->start > 0) {
         sum += ((*(procs + procNdx))->end - (*(procs + procNdx))->arv);
         numFinished++;
      }
   }

   return sum / numFinished;
}

void algStats(Proc **procs, int numProcs) {

   printf("run time : %f \n", avgRunTime(procs, numProcs));
   printf("wait time : %f \n", avgWaitTime(procs, numProcs));
   printf("turnaround time : %f \n", avgTurnaroundTime(procs, numProcs));

}
