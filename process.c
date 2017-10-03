#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"



Proc *randomProc(int arv, int run, int pri, int name){
   Proc *proc = malloc(sizeof(Proc));

   proc->arv = arv % ARV_MAX; // set arrival time
   proc->exp = run % RUN_MAX; // set expected run time time
   if(proc->exp == 0) {
      proc->exp += 1;
   }
   proc->pri = pri % PRI_MAX; // set priority time
   if(proc->pri == 0) {
      proc->pri += 1;
   }
   proc->run = 0; // set run time to zero
   proc->name = name; // set name
   proc->start = -1; // set start so process has not ran
   proc->end = -1; // set end so process has not ran

   return proc; // return process
}

Proc **generateProcs(int numProc) {
   int procNdx = 0;
   Proc **procs = malloc(sizeof(Proc *) * numProc);


   for (procNdx = 0; procNdx < numProc; procNdx++) { // loop through process
      // generate a random process
      *(procs + procNdx) = randomProc(rand(), rand(), rand(), procNdx);
   }

   return procs; //return all processes
}

Proc **removeProc(Proc **procs, int numProc, int rmvNdx) {
   Proc **procsCopy = malloc(sizeof(Proc *) * (numProc - 1));

   //copy processes before given index
   memcpy(procsCopy, procs, sizeof(Proc *) * rmvNdx);
   //copy processes after given index
   memcpy(procsCopy + rmvNdx, procs + (rmvNdx + 1),
    sizeof(Proc *) * (numProc - rmvNdx - 1));

   return procsCopy; //return new set of processes
}

int changeCurrProc(Proc **procs, int numProc, int quantum, int curNdx) {
   int procNdx = 0;
   int retNdx = curNdx;
   Proc *oldProc = *(procs + curNdx);
   float shortRun = oldProc->exp - oldProc->run;

   if (curNdx >= 0) { //check if there is a current process
      for (procNdx = 0; procNdx < numProc; procNdx++) { //loop through process
         Proc *curProc = *(procs + procNdx); // set current process

         //check is current process has shorter remaing run time
         if(quantum >= curProc->arv && curProc->exp - curProc->run < shortRun &&
          oldProc->exp - oldProc->run > curProc->exp - curProc->run) {
            retNdx = procNdx; //set new return index
            shortRun = curProc->exp - curProc->run; //get shortest run
         }
      }
   }

   return retNdx; //return index
}

void setProcStart(Proc ** procs, int ndx, int quantum) {
   if (ndx >= 0 && (*(procs + ndx))->start < 0) { //check if already started
      (*(procs + ndx))->start = quantum; // set process start;
   }
}

void freeProcs(Proc **procs, int numProc) {
   int procNdx;

   for (procNdx = 0; procNdx < numProc; procNdx++) { //loop through process
      free(*(procs + procNdx)); //free current process
   }
   free(procs); //free pointer to processes

}

Proc **copyProcs(Proc **procs, int numProc) {
   int procNdx;
   Proc **procsCopy = malloc(sizeof(Proc *) * numProc);

   for(procNdx = 0; procNdx < numProc; procNdx++) { //loop through processes
     //initialize process
     *(procsCopy + procNdx) = malloc(sizeof(Proc));
     //copy process
      memcpy(*(procsCopy + procNdx), *(procs + procNdx), sizeof(Proc));
   }

   return procsCopy; //return  copy of processes
}

void printProc(Proc *proc) {
   //print relevant process information
   printf("Name: %i   arrival:%.0f   expected run:%.0f   priority:%i\n",
    proc->name, proc->arv, proc->exp, proc->pri);
}

void printProcName(Proc  **procs, int ndx) {
    if (ndx >= 0) { //check for valid index
       printf("%i", (*(procs + ndx))->name); // print process name
    }
}

void printProcs(Proc **procs, int numProc) {
   int procNdx;

   for (procNdx = 0; procNdx < numProc; procNdx++) { //loop through processes
      printProc(*(procs + procNdx)); //print process
   }
   printf("\n"); //print new line
}

void printAllProcs(int numProcs, int numRuns) {
   int seed = 1, run;
   Proc **procs = NULL;

   srand(seed); // set random number generator
   for (run = 0; run < numRuns; run++) { // loop thrgouh runs
      printf("RUN %i  \n", run + 1); // print run number
      procs = generateProcs(TOT_PROCS);  //generate processes
      printProcs(procs, TOT_PROCS);  //print all generated processes
      freeProcs(procs, numProcs); // free all processes
   }
}
