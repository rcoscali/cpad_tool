CXX = g++
CXXFLAGS = -std=c++11 -g -O3 -fpermissive 
CPPFLAGS = -DGENERATE_RANDOM_GRAPHS
LDFLAGS = 
LIBS = -lboost_graph

PROGRAMS = $(BOOST_TST)

BOOST_TST = graphviz_subgraph
BOOST_TST_SRCS = subdot.cc 
BOOST_TST_OBJS = $(patsubst %.cc, %.o, $(filter %.cc, $(BOOST_TST_SRCS)))

%.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS)-I. -c $< -o $@

all: $(PROGRAMS)

$(BOOST_TST): $(BOOST_TST_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f *.pb.o *.pb.cc *.pb.h
	rm -f $(BOOST_TST) *.o *~

.PHONY: all clean

subdot.o: subdot.cc
