PLATFORM  := linux
MKDIR     := mkdir -p 
CXX	      := g++
BUILD     := build
LIB       := 
INC       := ./include
OBJS	  := state-test.o StateMachine.o Sequence.o
CXX_FLAGS := -g -std=c++0x -Wall
CXX_LIBS  += -L${LIB} -L/usr/lib/x86_64-linux-gnu -lpthread
CXX_INCS  += -I${INC}

all: state-test

state-test: $(OBJS)
	$(CXX) $(CXX_FLAGS) build/*.o -o state-test ${CXX_INCS} $(CXX_LIBS)

state-test.o: state-test.cpp
	$(MKDIR) $(BUILD)
	$(CXX) -c $(CXX_FLAGS) state-test.cpp -o build/state-test.o $(CXX_INCS)

StateMachine.o: StateMachine.cpp
	$(MKDIR) $(BUILD)
	$(CXX) -c $(CXX_FLAGS) StateMachine.cpp -o build/StateMachine.o $(CXX_INCS)

Sequence.o: Sequence.cpp
	$(MKDIR) $(BUILD)
	$(CXX) -c $(CXX_FLAGS) Sequence.cpp -o build/Sequence.o $(CXX_INCS)

clean:
	rm build/*
	rm state-test
