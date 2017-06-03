#SINGLE_TEST_EXE ?= no
SINGLE_TEST_EXE ?= yes

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
	FunctionMsg.cc \
	BasicBlockMsg.cc \
	EdgeMsg.cc \
	BuildMngtMsg.cc

CLT_SRCS = \
	clt_main.cc \
	plugin_request.pb.cc \
	build_mngt.pb.cc \
	cfg_request.pb.cc \
	VersionMsg.cc \
	InsertionPointMsg.cc \
	CompilationUnitMsg.cc \
	FunctionMsg.cc \
	BasicBlockMsg.cc \
	EdgeMsg.cc \
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
	tests/EndCfgToolingResponseTest.cc \
	tests/FunctionRequestTest.cc \
	tests/FunctionResponseTest.cc \
	tests/BasicBlockRequestTest.cc \
	tests/BasicBlockResponseTest.cc \
	tests/EdgeRequestTest.cc \
	tests/EdgeResponseTest.cc

GRPC_SRV_PLUGIN_SERVICES_SRCS = \
	PluginServices.cc \
	plugin_request.pb.cc \
	plugin_request.grpc.pb.cc \
	VersionMsg.cc \
	InsertionPointMsg.cc

GRPC_SRV_CFG_COLLECTION_SERVICES_SRCS = \
	CfgCollectionServices.cc \
	cfg_request.pb.cc \
	cfg_request.grpc.pb.cc \
	CompilationUnitMsg.cc \
	FunctionMsg.cc \
	BasicBlockMsg.cc \
	EdgeMsg.cc

GRPC_CLT_PLUGIN_SERVICES_SRCS = \
	PluginServicesClient.cc \
	plugin_request.pb.cc \
	plugin_request.grpc.pb.cc \
	VersionMsg.cc \
	InsertionPointMsg.cc

GRPC_CLT_CFG_COLLECTION_SERVICES_SRCS = \
	CfgCollectionServicesClient.cc \
	cfg_request.pb.cc \
	cfg_request.grpc.pb.cc \
	CompilationUnitMsg.cc \
	FunctionMsg.cc \
	BasicBlockMsg.cc \
	EdgeMsg.cc

LIBCPAD_OBJS = \
	plugin_request.pb.o \
	VersionMsg.o \
	InsertionPointMsg.o \
	cfg_request.pb.o \
	CompilationUnitMsg.o \
	FunctionMsg.o \
	BasicBlockMsg.o \
	EdgeMsg.o \
	build_mngt.pb.o \
	BuildMngtMsg.o

CPAD_OBJS = $(CPAD_SRCS:%.cc=%.o)
SRV_OBJS = $(SRV_SRCS:%.cc=%.o)
CLT_OBJS = $(CLT_SRCS:%.cc=%.o)
CFG_OBJS = $(CFG_SRCS:%.cc=%.o)
CPAD_CMD_OBJS = $(CPAD_CMD_SRCS:%.cc=%.o)
GRPC_SRV_PLUGIN_SERVICES_OBJS = $(GRPC_SRV_PLUGIN_SERVICES_SRCS:%.cc=%.o)
GRPC_CLT_PLUGIN_SERVICES_OBJS = $(GRPC_CLT_PLUGIN_SERVICES_SRCS:%.cc=%.o)
GRPC_SRV_CFG_COLLECTION_SERVICES_OBJS = $(GRPC_SRV_CFG_COLLECTION_SERVICES_SRCS:%.cc=%.o)
GRPC_CLT_CFG_COLLECTION_SERVICES_OBJS = $(GRPC_CLT_CFG_COLLECTION_SERVICES_SRCS:%.cc=%.o)

ALL_TESTS = \
	PluginServicesSrv \
	PluginServicesClt \
	CfgCollectionServicesSrv \
	CfgCollectionServicesClt

ifeq ($(SINGLE_TEST_EXE),no)
ALL_TESTS += $(MSG_TESTS_SRCS:%.cc=%)
else
ALL_TESTS += tests/alltests
endif

ALL_TESTS_OBJS = \
	$(MSG_TESTS_SRCS:%.cc=%.o) \
	PluginServices.o \
	PluginServicesClient.o \
	CfgCollectionServices.o \
	CfgCollectionServicesClient.o

GTEST_DIR = /usr/local/src/misc/googletest/googletest

ifeq ($(SINGLE_TEST_EXE),no)
GTEST_CPPFLAGS = -isystem $(GTEST_DIR)/include
else
GTEST_CPPFLAGS = -DSINGLE_TEST_EXE -isystem $(GTEST_DIR)/include
endif

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

ifeq ($(SINGLE_TEST_EXE),no)
tests/%: tests/%.cc
	$(CXX) $(CXXFLAGS) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) -I. -pthread $< libcpad.a libgtest.a $(CPAD_LDLIBS) -o $@
else
tests/%.o: tests/%.cc
	$(CXX) $(CXXFLAGS) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) -I. -pthread -c $< -o $@
endif

.PHONY: all cls clean tests

all: cfgtest cpad tests PluginServicesSrv

PluginServicesSrv: $(GRPC_SRV_PLUGIN_SERVICES_OBJS)
	$(CXX) $(CXXFLAGS) -I. -pthread $^ `pkg-config --libs grpc++` $(CPAD_LDLIBS) -o $@

PluginServicesClt: $(GRPC_CLT_PLUGIN_SERVICES_OBJS)
	$(CXX) $(CXXFLAGS) -I. -pthread $^ `pkg-config --libs grpc++` $(CPAD_LDLIBS) -o $@

CfgCollectionServicesSrv: $(GRPC_SRV_CFG_COLLECTION_SERVICES_OBJS)
	$(CXX) $(CXXFLAGS) -I. -pthread $^ `pkg-config --libs grpc++` $(CPAD_LDLIBS) -o $@

CfgCollectionServicesClt: $(GRPC_CLT_CFG_COLLECTION_SERVICES_OBJS)
	$(CXX) $(CXXFLAGS) -I. -pthread $^ `pkg-config --libs grpc++` $(CPAD_LDLIBS) -o $@

libgtest.a: 
	$(CXX) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc
	$(AR_CMD) libgtest.a gtest-all.o

libcpad.a: $(LIBCPAD_OBJS)
	$(AR_CMD) libcpad.a $(LIBCPAD_OBJS)

$(ALL_TESTS): libgtest.a libcpad.a

ifeq ($(SINGLE_TEST_EXE),no)
tests: $(ALL_TESTS)
	for t in $(ALL_TESTS); do \
		./$$t; \
	done
else
tests/alltests: tests/alltests.o libgtest.a libcpad.a $(ALL_TESTS_OBJS)
	$(CXX) $(CXXFLAGS) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) -I. -pthread tests/*.o libcpad.a libgtest.a $(CPAD_LDLIBS) -o $@

tests: $(ALL_TESTS)
	./tests/alltests
endif

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
	rm -f *.o cpad tests/*.o
	rm -f *~ \#*\#
	rm -f *.pb.cc *.pb.h
	rm -f libgtest.a $(ALL_TESTS) tests/alltests libcpad.a

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
CompilationUnitMsg.o: cfg_request.pb.cc cfg_request.pb.h CompilationUnitMsg.cc CompilationUnitMsg.h
FunctionMsg.o: cfg_request.pb.cc cfg_request.pb.h FunctionMsg.cc FunctionMsg.h
BasicBlockMsg.o: cfg_request.pb.cc cfg_request.pb.h BasicBlockMsg.cc BasicBlockMsg.h
EdgeMsg.o: cfg_request.pb.cc cfg_request.pb.h EdgeMsg.cc EdgeMsg.h
cfgtest.o: cfgtest.cc Graph.h Func.h CUnit.h Node.h Edge.h
cpad_cmd.o: plugin_request.pb.cc build_mngt.pb.cc
ifeq ($(SINGLE_TEST_EXE),yes)
tests/CompilationUnitEndRequestTest.o: tests/CompilationUnitEndRequestTest.cc CompilationUnitMsg.o CompilationUnitMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/CompilationUnitEndResponseTest.o: tests/CompilationUnitEndResponseTest.cc CompilationUnitMsg.o CompilationUnitMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/CompilationUnitStartRequestTest.o: tests/CompilationUnitStartRequestTest.cc CompilationUnitMsg.o CompilationUnitMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/CompilationUnitStartResponseTest.o: tests/CompilationUnitStartResponseTest.cc CompilationUnitMsg.o CompilationUnitMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/FunctionRequestTest.o: tests/FunctionRequestTest.cc FunctionMsg.o FunctionMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/FunctionResponseTest.o: tests/FunctionResponseTest.cc FunctionMsg.o FunctionMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/BasicBlockRequestTest.o: tests/BasicBlockRequestTest.cc BasicBlockMsg.o BasicBlockMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/BasicBlockResponseTest.o: tests/BasicBlockResponseTest.cc BasicBlockMsg.o BasicBlockMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/EdgeRequestTest.o: tests/EdgeRequestTest.cc EdgeMsg.o EdgeMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/EdgeResponseTest.o: tests/EdgeResponseTest.cc EdgeMsg.o EdgeMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/EndCfgCollectionRequestTest.o: tests/EndCfgCollectionRequestTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/EndCfgCollectionResponseTest.o: tests/EndCfgCollectionResponseTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/EndCfgToolingRequestTest.o: tests/EndCfgToolingRequestTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/EndCfgToolingResponseTest.o: tests/EndCfgToolingResponseTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/InsertionPointRequestTest.o: tests/InsertionPointRequestTest.cc InsertionPointMsg.o InsertionPointMsg.h plugin_request.pb.cc plugin_request.pb.h
tests/InsertionPointResponseTest.o: tests/InsertionPointResponseTest.cc InsertionPointMsg.o InsertionPointMsg.h plugin_request.pb.cc plugin_request.pb.h
tests/StartCfgCollectionRequestTest.o: tests/StartCfgCollectionRequestTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/StartCfgCollectionResponseTest.o: tests/StartCfgCollectionResponseTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/StartCfgToolingRequestTest.o: tests/StartCfgToolingRequestTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/StartCfgToolingResponseTest.o: tests/StartCfgToolingResponseTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/VersionRequestTest.o: tests/VersionRequestTest.cc VersionMsg.o VersionMsg.h plugin_request.pb.cc plugin_request.pb.h
tests/VersionResponseTest.o: tests/VersionResponseTest.cc VersionMsg.o VersionMsg.h plugin_request.pb.cc plugin_request.pb.h
tests/alltests.o: tests/alltests.cc
tests/alltests: tests/alltests.o
else
tests/CompilationUnitEndRequestTest: tests/CompilationUnitEndRequestTest.cc CompilationUnitMsg.o CompilationUnitMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/CompilationUnitEndResponseTest: tests/CompilationUnitEndResponseTest.cc CompilationUnitMsg.o CompilationUnitMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/CompilationUnitStartRequestTest: tests/CompilationUnitStartRequestTest.cc CompilationUnitMsg.o CompilationUnitMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/CompilationUnitStartResponseTest: tests/CompilationUnitStartResponseTest.cc CompilationUnitMsg.o CompilationUnitMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/FunctionRequestTest: tests/FunctionRequestTest.cc FunctionMsg.o FunctionMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/FunctionResponseTest: tests/FunctionResponseTest.cc FunctionMsg.o FunctionMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/BasicBlockRequestTest: tests/BasicBlockRequestTest.cc BasicBlockMsg.o BasicBlockMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/BasicBlockResponseTest: tests/BasicBlockResponseTest.cc BasicBlockMsg.o BasicBlockMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/EdgeRequestTest: tests/EdgeRequestTest.cc EdgeMsg.o EdgeMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/EdgeResponseTest: tests/EdgeResponseTest.cc EdgeMsg.o EdgeMsg.h cfg_request.pb.cc cfg_request.pb.h
tests/EndCfgCollectionRequestTest: tests/EndCfgCollectionRequestTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/EndCfgCollectionResponseTest: tests/EndCfgCollectionResponseTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/EndCfgToolingRequestTest: tests/EndCfgToolingRequestTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/EndCfgToolingResponseTest: tests/EndCfgToolingResponseTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/InsertionPointRequestTest: tests/InsertionPointRequestTest.cc InsertionPointMsg.o InsertionPointMsg.h plugin_request.pb.cc plugin_request.pb.h
tests/InsertionPointResponseTest: tests/InsertionPointResponseTest.cc InsertionPointMsg.o InsertionPointMsg.h plugin_request.pb.cc plugin_request.pb.h
tests/StartCfgCollectionRequestTest: tests/StartCfgCollectionRequestTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/StartCfgCollectionResponseTest: tests/StartCfgCollectionResponseTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/StartCfgToolingRequestTest: tests/StartCfgToolingRequestTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/StartCfgToolingResponseTest: tests/StartCfgToolingResponseTest.cc BuildMngtMsg.o BuildMngtMsg.h build_mngt.pb.cc build_mngt.pb.h
tests/VersionRequestTest: tests/VersionRequestTest.cc VersionMsg.o VersionMsg.h plugin_request.pb.cc plugin_request.pb.h
tests/VersionResponseTest: tests/VersionResponseTest.cc VersionMsg.o VersionMsg.h plugin_request.pb.cc plugin_request.pb.h
endif
PluginServices.o: PluginServices.cc plugin_request.grpc.pb.cc plugin_request.grpc.pb.h plugin_request.pb.cc plugin_request.pb.h 
PluginServicesClient.o: PluginServicesClient.cc plugin_request.grpc.pb.cc plugin_request.grpc.pb.h plugin_request.pb.cc plugin_request.pb.h 
CfgCollectionServices.o: CfgCollectionServices.cc cfg_request.grpc.pb.cc cfg_request.grpc.pb.h cfg_request.pb.cc cfg_request.pb.h 
CfgCollectionServicesClient.o: CfgCollectionServicesClient.cc cfg_request.grpc.pb.cc cfg_request.grpc.pb.h cfg_request.pb.cc cfg_request.pb.h 
