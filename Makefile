SRCS = main.cc Filter.cc Cpad.cc CUnit.cc Func.cc 
OBJS = $(SRCS:%.cc=%.o)

CXXFLAGS = -g -O1 -std=c++11

LDFLAGS = -g -O1 -std=c++11
LDLIBS = -lboost_program_options -lstdc++

%.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: all cpad clean

all: cpad

cpad: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

clean:
	rm -f *.o cpad
	rm -f *~ \#*\#

Cpad.o : Cpad.h CUnit.h Func.h Filter.h
Filter.o: Filter.h
Func.o: Func.h
CUnit.o: CUnit.h

