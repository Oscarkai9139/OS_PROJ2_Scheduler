CXX:=g++
FCFS=0
SJN=0
SRTFS=0
PS=0
RR=1

ifeq ($(FCFS), 1)
	SCHEDULER=FCFS
else ifeq ($(SJN), 1)
	SCHEDULER=SJN
else ifeq ($(SRTFS), 1)
	SCHEDULER=SRTFS
else ifeq ($(PS), 1)
	SCHEDULER=PS
else ifeq ($(RR), 1)
	SCHEDULER=RR
endif

TARGET=scheduler

$(TARGET): main.cpp
	$(CXX) -o $@ -D$(SCHEDULER)=1 $<
fcfs: main.cpp
	$(CXX) -o $(TARGET) -DFCFS=1 $<
sjn: main.cpp
	$(CXX) -o $(TARGET) -DSJN=1 $<
srtfs: main.cpp
	$(CXX) -o $(TARGET) -DSRTFS=1 $<
ps: main.cpp
	$(CXX) -o $(TARGET) -DPS=1 $<
rr: main.cpp
	$(CXX) -o $(TARGET) -DRR=1 $<

clean:
	rm -rf $(TARGET)
