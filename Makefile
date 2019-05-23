CXX:=g++
#scheduler selector 
FCFS=1
SJN=0
SRTFS=0
PS=0
RR=0

#debug mode for developer
DEBUG=1

DFLAGS=
ifeq ($(FCFS), 1)
	DFLAGS=-DFCFS
else ifeq ($(SJN), 1)
	DFLAGS=-DSJN
else ifeq ($(SRTFS), 1)
	DFLAGS=-SRTFS
else ifeq ($(PS), 1)
	DFLAGS=-DPS
else ifeq ($(RR), 1)
	DFLAGS=-DRR
endif

ifeq ($(DEBUG),1)
	DFLAGS += -DDEBUG
endif

TARGET=scheduler

$(TARGET): main.cpp
	$(CXX) -o $@ $(foreach n,$(DFLAGS),$(n)=1) $<
fcfs: main.cpp
	$(CXX) -o $(TARGET) $(DFLAGS)=1 -DFCFS=1 $<
sjn: main.cpp
	$(CXX) -o $(TARGET) $(DFLAGS)=1 -DSJN=1 $<
srtfs: main.cpp
	$(CXX) -o $(TARGET) $(DFLAGS)=1 -DSRTFS=1 $<
ps: main.cpp
	$(CXX) -o $(TARGET) $(DFLAGS)=1 -DPS=1 $<
rr: main.cpp
	$(CXX) -o $(TARGET) $(DFLAGS)=1 -DRR=1 $<

clean:
	rm -rf $(TARGET)
