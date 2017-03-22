CPAD_SRCS = main.cc Filter.cc Cpad.cc CUnit.cc Func.cc 
SRV_SRCS = srv_main.cc Server.cc plugin_request.pb.cc
CLT_SRCS = clt_main.cc Client.cc
CPAD_OBJS = $(CPAD_SRCS:%.cc=%.o)
SRV_OBJS = $(SRV_SRCS:%.cc=%.o)
CLT_OBJS = $(CLT_SRCS:%.cc=%.o)

CXXFLAGS = -g -O1 -std=c++11
PROTOC := protoc
PROTOC_FLAGS = --proto_path=. --cpp_out=. 

LDFLAGS := -g -O1 -std=c++11
LDLIBS := -lboost_program_options -lstdc++

CPAD_LDLIBS := $(LDLIBS)
SRV_LDLIBS := -lprotobuf -lboost_system -lboost_iostreams $(LDLIBS)
CLT_LDLIBS := -lprotobuf -lboost_system -lboost_iostreams $(LDLIBS)

%.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

%.pb.cc: %.proto
	$(PROTOC) $(PROTOC_FLAGS) $< 

.PHONY: all cpad clean cpad_srv cpad_clt

all: cpad

cpad: $(CPAD_OBJS)
	$(CXX) $(LDFLAGS) $(CPAD_OBJS) -o $@ $(CPAD_LDLIBS)

cpad_srv: $(SRV_OBJS)
	$(CXX) $(LDFLAGS) $(SRV_OBJS) -o $@ $(SRV_LDLIBS)

cpad_clt: $(CLT_OBJS)
	$(CXX) $(LDFLAGS) $(CLT_OBJS) -o $@ $(CLT_LDLIBS)

clean:
	rm -f *.o cpad
	rm -f *~ \#*\#
	rm -f *.pb.cc *.pb.h

Cpad.o : Cpad.h CUnit.h Func.h Filter.h
Filter.o: Filter.h
Func.o: Func.h
CUnit.o: CUnit.h
srv_main.o: Server.h
Server.o: Server.h
plugin_request.pb.o: plugin_request.pb.h
plugin_request.pb.cc: plugin_request.proto
