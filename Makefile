CXX:=g++

#debug mode for developer
DEBUG=0

BINDIR=bin
TARGET=fcfs sjn srtfs ps rr

all: $(TARGET)

fcfs: main.cpp
	@mkdir -p $(BINDIR)    
	$(CXX) -o $(BINDIR)/$@ -DDEBUG=$(DEBUG) -DFCFS=1 $<
sjn: main.cpp
	@mkdir -p $(BINDIR)    
	$(CXX) -o $(BINDIR)/$@ -DDEBUG=$(DEBUG) -DSJN=1 $<
srtfs: main.cpp
	@mkdir -p $(BINDIR)    
	$(CXX) -o $(BINDIR)/$@ -DDEBUG=$(DEBUG) -DSRTFS=1 $<
ps: main.cpp
	@mkdir -p $(BINDIR)    
	$(CXX) -o $(BINDIR)/$@ -DDEBUG=$(DEBUG) -DPS=1 $<
rr: main.cpp
	@mkdir -p $(BINDIR)    
	$(CXX) -o $(BINDIR)/$@ -DDEBUG=$(DEBUG) -DRR=1 $<

clean:
	rm -rf $(BINDIR)
