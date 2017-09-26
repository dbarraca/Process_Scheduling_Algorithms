#define TRUE 1
#define FALSE 0
#define TOT_PROCS 5
#define QUANT_MAX 20
#define TIME_SLICE 1


/**
 An arrival time: a float value from 0 through 99 (measured in quanta).
 An expected total run time: a float value from 0.1 through 10 quanta.
 A priority: integer 1, 2, 3, or 4 (1 is highest)
*/
typedef struct Proc{
   float arv;    //arrival time
   float exp;    //expected run time
   int pri;    //priority
   float run;    //current elapsed run time
   char name;    //name of process
   int start;
   int end;
} Proc;

/**
 * Generates process with random values
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
 * Print arrival time, run time, and priority of all the given processes
 */
void printProcs(Proc **procs, int numProc);
