#define TRUE 1
#define FALSE 0
#define TOT_PROCS 6
#define QUANT_MAX 20
#define TIME_SLICE 1
#define NUM_RUNS 1

typedef struct Proc{
   float arv;            //arrival time
   float exp;            //expected run time
   int pri;              //priority
   float run;            //current elapsed run time
   char name;            //name of process
   int start;
   int end;
} Proc;

/**
 * Generates a single random process with random values
 */
Proc *randomProc(int arv, int run, int pri, char name);

/**
 * Generates |numProc| processes
 */
Proc **generateProcs(int numProc);


/**
 * Makes a copy of the processes with the process to be removed
 */
Proc **removeProc(Proc **procs, int numProc, int rmvNdx);

/**
 * Free each process in the group of the given processes
 */
void freeProcs(Proc **procs, int numProc);

/**
 * Return a pointer to a copy of all the given processes
 *
 */
Proc **copyProcs(Proc **procs, int numProc);

/**
 * Print arrival time, run time, and priority of the given process
 */
void printProc(Proc *proc);

/**
 * Print the name of the process at the given index if there is one.
 */
void printProcName(Proc  **procs, int ndx);
/**
 * Print arrival time, run time, and priority of all the given processes
 */
void printProcs(Proc **procs, int numProc);

int changeCurrProc(Proc **procs, int numProc, int quantum, int curNdx);

/**
 * Sets the start time of the process.
 * The start time as the given quantum if it has not been set.
 * The process with the set start time is at the provided index
 * within the given processes.
 */
void setProcStart(Proc **procs, int ndx, int quantum);
