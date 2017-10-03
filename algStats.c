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
	  if ((*(procs + procNdx))->end >= 0) {
         sum += ((*(procs + procNdx))->end - (*(procs + procNdx))->arv - (*(procs+ procNdx))->run);
         numFinished++;
	  }
   }

   return sum / numFinished;
}

float avgTurnaroundTime(Proc **procs, int numProcs) {
   int procNdx, numFinished = 0;
   float sum = 0;

   for (procNdx = 0; procNdx < numProcs; procNdx++) {
      if ((*(procs + procNdx))->end > 0/* && (*(procs + procNdx))->end > 0*/) {
         sum += ((*(procs + procNdx))->end - (*(procs + procNdx))->arv);
         numFinished++;
      }
   }

   return sum / numFinished;
}

float avgResponseTime(Proc **procs, int numProcs) {
   int procNdx, numFinished = 0;
   float sum = 0;
   for (procNdx = 0; procNdx < numProcs; procNdx++) {
      if((*(procs + procNdx))->end >= 0) {
          sum += ((*(procs + procNdx))->start - (*(procs + procNdx))->arv);
          numFinished++;
      }
   }
   
   return sum / numFinished;
}
float calcThroughput(Proc **procs, int numProcs) {
   int procNdx, numFinished = 0;;
   int highestQuanta = 0;

   for (procNdx = 0; procNdx < numProcs; procNdx++) {
      if ((*(procs + procNdx))->end >= 0) 
         numFinished++;
      if ((*(procs + procNdx))->end > highestQuanta)
          highestQuanta = (*(procs + procNdx))->end;
   }

   return ((float) numFinished / highestQuanta) / (numProcs / TOT_PROCS);

}

void algStats(Proc **procs, int numProcs) {
   printf("\n");
   printf("turnaround time : %f\n", avgTurnaroundTime(procs, numProcs));
   printf("wait time : %f\n", avgWaitTime(procs, numProcs));
   printf("response time: %f\n", avgResponseTime(procs, numProcs));
   printf("throughput: %f\n", calcThroughput(procs, numProcs));

}
