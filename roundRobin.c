#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"
#include "algStats.h"

/**
 * Find the index of the next process with arrival time past the given quantum.
 * If the last processes is reached,start checking first process.
 * If the original process is checked. end checking and return no ready process found, -1.
 */
int nextReadyProc(Proc **procs, int numProcs, int startNdx, int quantum) {
   int nextReadyNdx = startNdx + 1, numChecked = 0;

   if (nextReadyNdx >= numProcs) { //check if at last process
      nextReadyNdx = 0; //got first process index
   }

   //loop through proceesses
   while (((quantum > QUANT_MAX && (*(procs + nextReadyNdx))->start < 0)
    || (*(procs + nextReadyNdx))->arv > quantum) && numChecked < numProcs) {
       numChecked++; //indcement number checked
       nextReadyNdx++; //move to next index

       if (nextReadyNdx >= numProcs) { //check if at last process
          nextReadyNdx = 0;//got first process index
       }
    }

   // check if looped through all processes and none are ready
    if (numChecked >= numProcs)
       nextReadyNdx = -1; //set return to no ready process found

    return nextReadyNdx; //return next ready process' index
}

void roundRobin(Proc **procs, int numProcs) {
   int quantum, sliceQuanta = 0, curNdx = 0;

   //count quanta
   for (quantum = 0; (quantum < QUANT_MAX || curNdx >= 0)
   && numProcs > 0; quantum++) {

      sliceQuanta++; //increment time slice
      if (sliceQuanta >= TIME_SLICE) { // check if reached end of time slice
         sliceQuanta = 0; //reset time slice
         // if end of process set to beginning
         curNdx = curNdx < numProcs ? curNdx : 0;
         //get next ready process index
         curNdx = nextReadyProc(procs, numProcs, curNdx, quantum);
         setProcStart(procs, curNdx, quantum); // set start of process
      }

//      printf(" %i ",quantum);
      //check if there is a valid ready process
      if (curNdx >= 0 && (*(procs + curNdx))->arv <= quantum) {

         printf("%i", (*(procs + curNdx))->name); // print process name
         (*(procs + curNdx))->run++; // increment process run time
         // check if reached end of process
         if ((*(procs + curNdx))->run >= (*(procs + curNdx))->exp) {
            //set end of process
            (*(procs + curNdx))->end = quantum;
            procs = removeProc(procs, numProcs, curNdx);// remove process
            numProcs--; //decrement number of processes
         }
      }
      printf(","); //print delimiter
//      printf("\n");
   }
}

void roundRobinRuns(int numProcs) {
   int seed = 1, run;
   Proc **procs = NULL,
    **allProcs = malloc(sizeof(Proc *) * NUM_RUNS * numProcs);

   srand(seed); //start random number generator

   for (run = 0; run < NUM_RUNS; run++) { // loop through runs
      printf("RUN %i\n", run + 1); // print run number
      procs = generateProcs(TOT_PROCS); //generate processes
//      printProcs(procs, TOT_PROCS); //print all generated processes
      roundRobin(procs, TOT_PROCS); //run round robin
      algStats(procs, TOT_PROCS); //print stastistics
//      printProcs(procs, TOT_PROCS); //print all generated processes
      memcpy(allProcs + run * numProcs, procs, sizeof(Proc *) * numProcs);
      free(procs); //free processes pointer
      printf("\n"); //print new line
   }


   algStats(allProcs, NUM_RUNS * TOT_PROCS); //print stastics on all processes
   freeProcs(allProcs, NUM_RUNS * TOT_PROCS); //free processes
}
