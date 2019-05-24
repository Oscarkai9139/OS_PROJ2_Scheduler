# OS_PROJ2_Scheduler
A simple simulation of FCFS, SJN, PS, SRTFS, RR scheduler

![image](https://github.com/Oscarkai9139/OS_PROJ2_Scheduler/blob/master/Diagram.png)

## How to compile

Just execute "make".

There would be 5 binaries in bin dir:
- fcfs 
- sjn
- srtfs
- ps
- rr

## How to run
fcfs  - First-come, First-served scheduling 
sjn   - Shortest Job Next
srtfs - Shortest Remaining time first scheduling
ps    - priority scheduling
rr    - round robin scheduling

ex1: if you wish to run priority scheduler on data_3.txt
bin/ps data_3.txt 

ex2 if you wish to run Shortest Job Next on data_2.txt
bin/sjn data_2.txt
