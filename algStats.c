#include <stdio.h>
#include "process.h"

float avgRunTime(Proc **procs, int numProcs) {
   int procNdx;
   float sum = 0;

   for (procNdx = 0; procNdx < numProcs; procNdx++) {
      sum += ((*(procs + procNdx))->run);
   }

   return sum / numProcs;
}

float avgWaitTime(Proc **procs, int numProcs) {
   int procNdx;
   float sum = 0;

   for (procNdx = 0; procNdx < numProcs; procNdx++) {
      sum += ((*(procs + procNdx))->start - (*(procs + procNdx))->arv);
   }

   return sum / numProcs;
}

float avgTurnaroundTime(Proc **procs, int numProcs) {
   int procNdx;
   float sum = 0;

   for (procNdx = 0; procNdx < numProcs; procNdx++) {
      sum += ((*(procs + procNdx))->end - (*(procs + procNdx))->arv);
   }

   return sum / numProcs;
}

void algStats(Proc **procs, int numProcs) {

   printf("run time : %f \n", avgRunTime(procs, numProcs));
   printf("wait time : %f \n", avgWaitTime(procs, numProcs));
   printf("turnaround time : %f \n", avgTurnaroundTime(procs, numProcs));

}
