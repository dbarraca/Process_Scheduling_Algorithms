
/**
 An arrival time: a float value from 0 through 99 (measured in quanta).
 An expected total run time: a float value from 0.1 through 10 quanta.
 A priority: integer 1, 2, 3, or 4 (1 is highest)
*/
typedef struct Proc{
	float arrivalTime;
	float expectedRunTime;
	int priority;
	float currRunTime;

} Proc;

Proc *randomProc(int arrival, int run, int priority);
Proc **generateProcs(int numProc);
Proc **removeProc(Proc **processes, int numProc, int removeIndex);
void printProc(Proc *proc);
void printProcs(Proc **processes, int numProc);
