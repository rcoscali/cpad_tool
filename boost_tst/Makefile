
PROGRAMS = $(BOOST_TST)

BOOST_TST = boost_tst
BOOST_TST_SRCS = main.cc
BOOST_TST_OBJS = $(BOOST_TST_SRCS:%.c=%.o)

%.o: %.cc
	$(CXX) -std=c++11 -g -O3 -I. -c $* -o $@

all: $(PROGRAMS)

$(BOOST_TST): $(BOOST_TST_OBJS)
	$(CXX) -fpermissive -std=c++11 -g -O3 $^ -o $@ -lboost_graph -luuid

clean:
	rm -f boost_tst *.o *~

.PHONY: all clean

main.o: main.cc graph.h vertex.h edge.h
