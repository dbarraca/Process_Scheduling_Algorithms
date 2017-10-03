#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "process.h"
#include "highestPriority.h"
#include "algStats.h"
#include "timeSchedAlgs.h"

int countPriority(Proc **procs, int numProcs, int priority) {
   int ndx, numPriorProcs = 0;

   for (ndx = 0; ndx < numProcs;  ndx++) {
      if ((*(procs + ndx))->pri == priority) {
         numPriorProcs++;
      }
   }

   return numPriorProcs;
}

int *countAllPriority(Proc **procs, int numProcs) {
   int curPri, *priorities = malloc(sizeof(int) * (PRI_MAX - 1));

   for(curPri = 1; curPri < PRI_MAX; curPri++) {
      priorities[curPri - 1] = countPriority(procs, numProcs, curPri);
   }
   return priorities;
}

Proc **priorityProcs(Proc **procs, int numProcs, int priority) {
   Proc **retProcs = NULL;
   int ndx, numPriorProcs = countPriority(procs, numProcs, priority);

   //printf("numPriorProcs %i\n", numPriorProcs);
   retProcs  = malloc(sizeof(Proc *) * numPriorProcs);

   for (ndx = 0; ndx < numProcs;  ndx++) {
      if ((*(procs + ndx))->pri == priority) {
         memcpy(retProcs + --numPriorProcs, procs + ndx, sizeof(Proc *));
      }
   }

   return retProcs;
}

Proc ***priorityQueues(Proc **procs, int numProcs) {
   Proc ***priorityQueues = malloc(sizeof(Proc **) * PRI_MAX - 1);
   int curPri;
   for (curPri = 1; curPri < PRI_MAX; curPri++) {
      *(priorityQueues + curPri - 1) =
       orderProcs(priorityProcs(procs, numProcs, curPri),
       countPriority(procs, numProcs, curPri), earlyArv);
   }

   return priorityQueues;
}


void nonpreHighestPriority(Proc **procs, int numProcs) {
   int quantum, queueNdx = 0, foundProc = FALSE, numStarted = 0,
    *queueLengths = countAllPriority(procs, numProcs); //get priority queue lengths
   //make priority queues
   Proc ***priQueues = priorityQueues(procs, numProcs), *curProc = NULL;

   //count quanta and continue if there is still a running process
   for (quantum = 0; (curProc != NULL && curProc->end < 0 && curProc->start > 0) ||
     numStarted > 0 || quantum < QUANT_MAX; quantum++) {
      printf("%i ", quantum); //print current process
      foundProc = FALSE; //set found available process flag to false

      if(numStarted > 0) { //check number of started processes
         printf("%i", curProc->name); //print process name
         curProc->run++; //increment running process run time

         if (curProc->run >= curProc->exp) { //check if process reached end of run
            curProc->end = quantum; //set end of process
            //remove process for its respective queue
            (*(priQueues + queueNdx - 1)) = removeProc(*((priQueues + queueNdx - 1))
             , (*(queueLengths + queueNdx - 1))--, 0);
            numStarted--; //decrement number of started processes
         }
      }
      else {
      //iterate over queues until a available process is found
         for (queueNdx = 0; queueNdx < PRI_MAX - 1 && foundProc == FALSE;
          queueNdx++) {

            curProc = (**(priQueues + queueNdx));  //get first process in current queue
            //check if the process is ready
            if (*(queueLengths + queueNdx) > 0 && curProc->arv <= quantum &&
               (curProc->start >= 0 || quantum < QUANT_MAX)){

               foundProc = TRUE;  //set found available process flag to true

               if (curProc->start < 0) {//check if process has had first response
                  curProc->start = quantum; //set start of process
                  numStarted++; //increment number of started processes
               }

               printf("%i", curProc->name); //print process name
               curProc->run++; //increment running process run time
               if (curProc->run >= curProc->exp) { //check if process reached end of run
                  curProc->end = quantum; //set end of process
                  //remove process for its respective queue
                  (*(priQueues + queueNdx)) = removeProc(*((priQueues + queueNdx))
                   , (*(queueLengths + queueNdx))--, 0);
                  numStarted--; //decrement number of started processes
               }

            }
         }
      }
      printf("\n");
   }
   free(priQueues); //free queues
}

int queueRoundRobin(Proc ***priQueues, int queueNdx, int quantum,
 int *queueLengths, Proc **curProc) {
   int procNdx;
   *curProc = (**(priQueues + queueNdx));

   for (procNdx = 0; procNdx + 1 < (*(queueLengths + queueNdx)) &&
      (*(*(priQueues + queueNdx) + procNdx + 1)) != NULL &&
      (*(*(priQueues + queueNdx) + procNdx + 1))->arv <= quantum &&
       (*(*(priQueues + queueNdx) + procNdx))->run >
       (*(*(priQueues + queueNdx) + procNdx + 1))->run
       && (quantum < QUANT_MAX || (*(*(priQueues + queueNdx) + procNdx + 1))->start >= 0);
       procNdx++) {
         *curProc = (*(*(priQueues + queueNdx) + procNdx + 1));
   }

   return procNdx;
}

void preempHighestPriority(Proc **procs, int numProcs) {
   int quantum, queueNdx = 0, foundProc = FALSE, numStarted = 0,
    *queueLengths = countAllPriority(procs, numProcs), procNdx; //get priority queue lengths
   //make priority queues
   Proc ***priQueues = priorityQueues(procs, numProcs), *curProc = NULL;

   //count quanta and continue if there is still a running process
   for (quantum = 0; (curProc != NULL && curProc->end < 0 && curProc->start > 0) ||
     numStarted > 0 || quantum < QUANT_MAX; quantum++) {
      printf("%i ", quantum); //print current process
      foundProc = FALSE; //set found available process flag to false

      //iterate over queues until a available process is found
      for (queueNdx = 0; queueNdx < PRI_MAX - 1 && foundProc == FALSE;
       queueNdx++) {

         curProc = (**(priQueues + queueNdx));  //get first process in current queue
         if(curProc != NULL)
         //check if the process is ready
         if (*(queueLengths + queueNdx) > 0 && curProc->arv <= quantum &&
            (curProc->start >= 0 || quantum < QUANT_MAX)){

            procNdx = queueRoundRobin(priQueues, queueNdx, quantum,
             queueLengths, &curProc);  //get first process in current queue

            foundProc = TRUE;  //set found available process flag to true

            if (curProc->start < 0) {//check if process has had first response
               curProc->start = quantum; //set start of process
               numStarted++; //increment number of started processes
            }

            printf("%i", curProc->name); //print process name
            curProc->run++; //increment running process run time
            if (curProc->run >= curProc->exp) { //check if process reached end of run
               curProc->end = quantum; //set end of process
               //remove process for its respective queue
               (*(priQueues + queueNdx)) = removeProc((*(priQueues + queueNdx))
                , (*(queueLengths + queueNdx))--, procNdx );
               numStarted--; //decrement number of started processes
            }
         }
      }
      printf("\n");
   }
   free(priQueues); //free queues
}

void HPFRuns(int numProcs, int preemp) {
   int seed = 1, run;
   Proc **procs = NULL,
    **allProcs = malloc(sizeof(Proc *) * NUM_RUNS * numProcs);

   srand(seed);

   for (run = 0; run < NUM_RUNS; run++) {
      printf("\nRUN %i   ", run + 1); //print run number
      procs = generateProcs(TOT_PROCS); //generate processes
      printProcs(procs, TOT_PROCS); //print all generated processes
      if (preemp == TRUE)
         preempHighestPriority(procs, TOT_PROCS); //run preemp HPF
      else
         nonpreHighestPriority(procs, TOT_PROCS); //run non-premp HPF
      // printProcs(procs, TOT_PROCS); //print all generated processes
      //copy HPF run processes
      memcpy(allProcs + run * numProcs, procs, sizeof(Proc *) * numProcs);
      algStats(procs, TOT_PROCS); //print statistics for run
      free(procs); //free runs processes pointer
   }

   algStats(allProcs, NUM_RUNS * TOT_PROCS); //print statistics
   freeProcs(allProcs, NUM_RUNS * TOT_PROCS); //free processes
}

