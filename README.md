# OS_PROJ2_Scheduler
A simple simulation of FCFS, SJN, PS, SRTFS, RR scheduler

![image](https://github.com/Oscarkai9139/OS_PROJ2_Scheduler/blob/master/Diagram.png)

## How to compile
You can specify scheduling method by two ways:

### Specify in Makefile
Change the scheduling method you desired to 1:
```
FCFS=1
SJN=0
SRTFS=0
PS=0
RR=0
```
And then just `make`. Notice that you can only choose 1 method per time.

For example, the above would choose FCFS as scheduling method.
If you don't let any of them be 1, it would cause error.

### Specify by make target
Execute `make the_method_you_desired` would choose the method.
Notice that you have to be **SMALL CAPITAL** when entering method.

E.g., `make fcfs` would choose FCFS as scheduling method.
