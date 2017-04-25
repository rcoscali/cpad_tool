
PROGRAMS = $(BOOST_TST)

BOOST_TST = boost_tst
BOOST_TST_SRCS = main.cc
BOOST_TST_OBJS = $(BOOST_TST_SRCS:%.c=%.o)

%.o: %.cc
	$(CXX) -std=c++11 -g -O3 -I. -c $* -o $@

all: $(PROGRAMS)

$(BOOST_TST): $(BOOST_TST_OBJS)
	$(CXX) -std=c++11 -g -O3 $^ -o $@ -lboost_graph -luuid

.PHONY: all
