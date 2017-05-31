CXX = g++
PROTOC ?= protoc
GCC ?= gcc
GXX ?= gxx
HOST_GCC ?= $(GCC)
HOST_GXX ?= $(GXX)
BUILD_GCC ?= $(HOST_GCC)
BUILD_GXX ?= $(HOST_GXX)
TARGET_GCC ?= $(BUILD_GCC)
TARGET_GXX ?= $(BUILD_GXX)
AR ?= ar
AR_CMD ?= $(AR) -rv

CPAD_SRCS = \
	main.cc \
	Filter.cc \
	Cpad.cc \
	CUnit.cc \
	Func.cc 

CPAD_CMD_SRCS = \
	cpad_cmd.cc \
	cfg_request.pb.cc \
	plugin_request.pb.cc \
	build_mngt.pb.cc \
	VersionMsg.cc \
	InsertionPointMsg.cc \
	CompilationUnitMsg.cc \
	BuildMngtMsg.cc

CFG_SRCS = \
	cfgtest.cc \
	Graph.cc \
	Func.cc \
	CUnit.cc \
	Node.cc \
	Edge.cc

SRV_SRCS = \
	srv_main.cc \
	Server.cc \
	cfg_request.pb.cc \
	plugin_request.pb.cc \
	build_mngt.pb.cc \
	VersionMsg.cc \
	InsertionPointMsg.cc \
	CompilationUnitMsg.cc \
	BuildMngtMsg.cc

CLT_SRCS = \
	clt_main.cc \
	plugin_request.pb.cc \
	build_mngt.pb.cc \
	VersionMsg.cc \
	InsertionPointMsg.cc \
	CompilationUnitMsg.cc \
	BuildMngtMsg.cc

MSG_TESTS_SRCS = \
	tests/VersionRequestTest.cc \
	tests/VersionResponseTest.cc \
	tests/InsertionPointRequestTest.cc \
	tests/InsertionPointResponseTest.cc \
	tests/CompilationUnitStartRequestTest.cc \
	tests/CompilationUnitStartResponseTest.cc \
	tests/CompilationUnitEndRequestTest.cc \
	tests/CompilationUnitEndResponseTest.cc \
	tests/StartCfgCollectionRequestTest.cc \
	tests/StartCfgCollectionResponseTest.cc \
	tests/EndCfgCollectionRequestTest.cc \
	tests/EndCfgCollectionResponseTest.cc \
	tests/StartCfgToolingRequestTest.cc \
	tests/StartCfgToolingResponseTest.cc \
	tests/EndCfgToolingRequestTest.cc \
#	tests/EndCfgToolingResponseTest.cc

LIBCPAD_OBJS = \
	plugin_request.pb.o \
	VersionMsg.o \
	InsertionPointMsg.o \
	cfg_request.pb.o \
	CompilationUnitMsg.o \
	build_mngt.pb.o \
	BuildMngtMsg.o

CPAD_OBJS = $(CPAD_SRCS:%.cc=%.o)
SRV_OBJS = $(SRV_SRCS:%.cc=%.o)
CLT_OBJS = $(CLT_SRCS:%.cc=%.o)
CFG_OBJS = $(CFG_SRCS:%.cc=%.o)
CPAD_CMD_OBJS = $(CPAD_CMD_SRCS:%.cc=%.o)

ALL_TESTS = \
	$(MSG_TESTS_SRCS:%.cc=%)

GTEST_DIR = /usr/local/src/misc/googletest/googletest
GTEST_CPPFLAGS = -isystem $(GTEST_DIR)/include

CXXFLAGS = -g -O1 -std=c++11
PROTOC := protoc
PROTOC_FLAGS = --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` --proto_path=. --cpp_out=. --grpc_out=.

CPPFLAGS := -I/usr/include/uuid

LDFLAGS := -g -O1 -std=c++11
LDLIBS := -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -lprotobuf -lboost_program_options -lboost_system -lstdc++ -lpthread -ldl

CPAD_LDLIBS := $(LDLIBS)
CFG_LDLIBS := -luuid
SRV_LDLIBS := -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -lprotobuf -lboost_system -lboost_iostreams $(LDLIBS) -lpthread -lrt -ldl
CLT_LDLIBS := -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -lprotobuf -lboost_system -lboost_iostreams $(LDLIBS) -lpthread -lrt -ldl

%.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

%.grpc.pb.cc %.grpc.pb.h %.pb.cc %.pb.h: %.proto
	$(PROTOC) $(PROTOC_FLAGS) $<

tests/%: tests/%.cc
	$(CXX) $(CXXFLAGS) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) -I. -pthread $< libcpad.a libgtest.a $(CPAD_LDLIBS) -o $@

.PHONY: all cls clean tests

libgtest.a: 
	$(CXX) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc
	$(AR_CMD) libgtest.a gtest-all.o

libcpad.a: $(LIBCPAD_OBJS)
	$(AR_CMD) libcpad.a $(LIBCPAD_OBJS)

tests: libgtest.a libcpad.a $(ALL_TESTS)
	for t in $(ALL_TESTS); do \
		./$$t; \
	done

all: cfgtest cpad

cls:
	clear || true

cpad_cmd: $(CPAD_CMD_OBJS)

cpad: cpad_srv cpad_clt $(CPAD_OBJS)
	$(CXX) $(LDFLAGS) $(CPAD_OBJS) -o $@ $(CPAD_LDLIBS)

cpad_srv: cls $(SRV_OBJS)
	$(CXX) $(LDFLAGS) $(SRV_OBJS) -o $@ $(SRV_LDLIBS)

cpad_clt: cls $(CLT_OBJS)
	$(CXX) $(LDFLAGS) $(CLT_OBJS) -o $@ $(CLT_LDLIBS)

cfgtest: cls $(CFG_OBJS)
	$(CXX) $(LDFLAGS) $(CFG_OBJS) -o $@ $(CFG_LDLIBS)

clean:
	rm -f *.o cpad
	rm -f *~ \#*\#
	rm -f *.pb.cc *.pb.h
	rm -f libgtest.a $(ALL_TESTS) libcpad.a

Cpad.o : Cpad.cc Cpad.h CUnit.h Func.h Filter.h
Filter.o: Filter.cc Filter.h
Graph.o: Graph.cc Graph.h
Node.o: Node.cc Node.h
Edge.o: Edge.cc Edge.h
Func.o: Func.cc Func.h
CUnit.o: CUnit.cc CUnit.h
srv_main.o: srv_main.cc Server.h plugin_request.pb.cc VersionMsg.h InsertionPointMsg.h CompilationUnitMsg.h
clt_main.cc: plugin_request.pb.cc VersionMsg.h InsertionPointMsg.h CompilationUnitMsg.h
Server.o: Server.cc Server.h plugin_request.pb.cc plugin_request.pb.h
plugin_request.pb.o: plugin_request.pb.cc plugin_request.pb.h
plugin_request.pb.cc: plugin_request.proto
plugin_request.pb.h: plugin_request.proto
cfg_request.pb.o: cfg_request.pb.cc cfg_request.pb.h
cfg_request.pb.cc: cfg_request.proto
cfg_request.pb.h: cfg_request.proto
VersionMsg.o: plugin_request.pb.cc plugin_request.pb.h
InsertionPointMsg.o: plugin_request.pb.cc plugin_request.pb.h InsertionPointMsg.cc InsertionPointMsg.h
ComplilationUnitMsg.o: cfg_request.pb.cc cfg_request.pb.h ComplilationUnitMsg.cc ComplilationUnitMsg.h
cfgtest.o: cfgtest.cc Graph.h Func.h CUnit.h Node.h Edge.h
cpad_cmd.o: plugin_request.pb.cc build_mngt.pb.cc
tests/VersionRequestTest: VersionMsg.o VersionMsg.h plugin_request.pb.cc plugin_request.pb.h
tests/VersionResponseTest: VersionMsg.o VersionMsg.h plugin_request.pb.cc plugin_request.pb.h
tests/InsertionPointRequestTest: InsertionPointMsg.o InsertionPointMsg.h plugin_request.pb.cc plugin_request.pb.h
tests/CompilationUnitStartRequestTest: CompilationUnitMsg.o CompilationUnitMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/StartCfgCollectionRequestTest: BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/StartCfgCollectionResponseTest: BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/EndCfgCollectionRequestTest: BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/EndCfgCollectionResponseTest: BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/StartCfgToolingRequestTest: BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/StartCfgToolingResponseTest: BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/EndCfgToolingRequestTest: BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/EndCfgToolingResponseTest: BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
