#include <stdio.h>
#include "process.h"

float avgRunTime(Proc **procs, int numProcs) {
   int procNdx, numFinished = 0;;
   float sum = 0;

   for (procNdx = 0; procNdx < numProcs; procNdx++) { //loop through processes
      sum += ((*(procs + procNdx))->run); //add current process run time
      numFinished++; //count number of finished processes
   }

   return sum / numFinished; // calculate average run time
}

float avgWaitTime(Proc **procs, int numProcs) {
   int procNdx, numFinished = 0;
   float sum = 0;

   for (procNdx = 0; procNdx < numProcs; procNdx++) { //loop through processes
	  if ((*(procs + procNdx))->end >= 0) { //check if process was ran
	     //add current process wait time
         sum += ((*(procs + procNdx))->end - (*(procs + procNdx))->arv - (*(procs+ procNdx))->run);
         numFinished++; //count number of finished processes
	  }
   }

   return sum / numFinished; // calculate average time
}

float avgTurnaroundTime(Proc **procs, int numProcs) {
   int procNdx, numFinished = 0;
   float sum = 0;

   for (procNdx = 0; procNdx < numProcs; procNdx++) { //loop through processes
      if ((*(procs + procNdx))->end > 0) { //check if process was ran
         //add current process turnaround time
         sum += ((*(procs + procNdx))->end - (*(procs + procNdx))->arv);
         numFinished++; //count number of finished processes
      }
   }

   return sum / numFinished; // calculate average turnaround time
}

float avgResponseTime(Proc **procs, int numProcs) {
   int procNdx, numFinished = 0;
   float sum = 0;
   for (procNdx = 0; procNdx < numProcs; procNdx++) { //loop through processeses
      if((*(procs + procNdx))->end >= 0) { //check if process was ran
         //add current process response time
          sum += ((*(procs + procNdx))->start - (*(procs + procNdx))->arv);
          numFinished++; //count number of finished processes
      }
   }
   
   return sum / numFinished; // calculate average response time
}
float calcThroughput(Proc **procs, int numProcs) {
   int procNdx, numFinished = 0;;
   int highestQuanta = 0;

   for (procNdx = 0; procNdx < numProcs; procNdx++) { //loop through processes
      if ((*(procs + procNdx))->end >= 0)  //check if process was ran
         numFinished++; //count number of finished processes
      if ((*(procs + procNdx))->end > highestQuanta) //find last quanta
          highestQuanta = (*(procs + procNdx))->end;
   }

   // calculate throughput
   return ((float) numFinished / highestQuanta) / (numProcs / TOT_PROCS);

}

void algStats(Proc **procs, int numProcs) {
   printf("\n");
   printf("turnaround time : %f\n", avgTurnaroundTime(procs, numProcs));
   printf("wait time : %f\n", avgWaitTime(procs, numProcs));
   printf("response time: %f\n", avgResponseTime(procs, numProcs));
   printf("throughput: %f\n", calcThroughput(procs, numProcs));

}
