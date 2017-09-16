# Process_Scheduling_Algorithms

Psuedo code
-------------------------------------
loop until end of quanta
   if no current process  (not at beginning of run)
      increment idle time count
   else
      set idle time count to zero

   if idle time equals 2
      send "idle time" message
   else
      if need to change current process
         replace process
         calculate response time
      calculate turnaround time
      calculate wait time 
 

To Do  (Doesn't have to be done in this order)
-------------------------------
O  count quanta (run processes)
O  find lowest expected run time - current run time (shortest remaining time)
O  find lowest expected run time (shortest run time) 
O  find highest priority  (lowest number)
O  calculate response time, wait time, turnaround time, throughput
