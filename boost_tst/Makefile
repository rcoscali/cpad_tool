CXX = g++
CXXFLAGS = -std=c++11 -g -O3 -fpermissive 
CPPFLAGS = 
LDFLAGS = 
LIBS = -lboost_graph -lboost_serialization -luuid -lprotobuf 

PROTOC = protoc

PROGRAMS = $(BOOST_TST)

BOOST_TST = boost_tst
BOOST_TST_PROTOS = graph.proto
BOOST_TST_SRCS = main.cc $(patsubst %.proto, %.pb.cc, $(filter %.proto, $(BOOST_TST_PROTOS)))
BOOST_TST_OBJS = $(patsubst %.cc, %.o, $(filter %.cc, $(BOOST_TST_SRCS)))

%.pb.o: %.pb.cc %.pb.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS)-I. -c $< -o $@

%.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS)-I. -c $< -o $@

%.pb.cc: %.proto
	$(PROTOC) -I. --cpp_out=. $<

all: $(PROGRAMS)

$(BOOST_TST): $(BOOST_TST_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f *.pb.o *.pb.cc *.pb.h
	rm -f boost_tst *.o *~

.PHONY: all clean

main.o: main.cc graph.h vertex.h edge.h
graph.pb.o: graph.pb.cc graph.pb.h
graph.pb.cc: graph.proto
graph.pb.h: graph.proto
