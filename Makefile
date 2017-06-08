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

# CPAD prototype (obsolete, we decided to use Boost Graph Library)
CPAD_SRCS = \
	main.cc \
	Filter.cc \
	Cpad.cc \
	CUnit.cc \
	Func.cc 
CPAD_OBJS = $(CPAD_SRCS:%.cc=%.o)

# CPAD cmd
CPAD_CMD_SRCS = \
	cpad_cmd.cc \
	cfg_request.pb.cc \
	plugin_request.pb.cc \
	build_mngt.pb.cc \
	VersionMsg.cc \
	InsertionPointMsg.cc \
	CompilationUnitMsg.cc \
	BuildMngtMsg.cc
CPAD_CMD_OBJS = $(CPAD_CMD_SRCS:%.cc=%.o)

# Config prototype (obsolete)
CFG_SRCS = \
	cfgtest.cc \
	Graph.cc \
	Func.cc \
	CUnit.cc \
	Node.cc \
	Edge.cc
CFG_OBJS = $(CFG_SRCS:%.cc=%.o)

# Server prototype (obsolete, we decided to go with grpc)
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
SRV_OBJS = $(SRV_SRCS:%.cc=%.o)

# Client prototype (obsolete, we decided to go with grpc)
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
CLT_OBJS = $(CLT_SRCS:%.cc=%.o)

# All messaging objects tests (6 tests per class)
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

# Library for tests
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

# gRPC server for services in plugin_request.proto
GRPC_SRV_PLUGIN_SERVICES_SRCS = \
	plugin_request.pb.cc \
	plugin_request.grpc.pb.cc \
	PluginServices.cc \
	VersionMsg.cc \
	InsertionPointMsg.cc

# gRPC server for services in cfg_request.proto
GRPC_SRV_CFG_COLLECTION_SERVICES_SRCS = \
	cfg_request.pb.cc \
	cfg_request.grpc.pb.cc \
	CfgCollectionServices.cc \
	CompilationUnitMsg.cc \
	FunctionMsg.cc \
	BasicBlockMsg.cc \
	EdgeMsg.cc

# gRPC server for services in build_mngt.proto
GRPC_SRV_BUILD_MNGT_SERVICES_SRCS = \
	build_mngt.pb.cc \
	build_mngt.grpc.pb.cc \
	BuildMngtServices.cc \
	BuildMngtMsg.cc

# gRPC client for services in plugin_request.proto
GRPC_CLT_PLUGIN_SERVICES_SRCS = \
	plugin_request.pb.cc \
	plugin_request.grpc.pb.cc \
	PluginServicesClient.cc \
	VersionMsg.cc \
	InsertionPointMsg.cc

# gRPC client for services in cfg_request.proto
GRPC_CLT_CFG_COLLECTION_SERVICES_SRCS = \
	cfg_request.pb.cc \
	cfg_request.grpc.pb.cc \
	CfgCollectionServicesClient.cc \
	CompilationUnitMsg.cc \
	FunctionMsg.cc \
	BasicBlockMsg.cc \
	EdgeMsg.cc

# gRPC client for services in build_mngt.proto
GRPC_CLT_BUILD_MNGT_SERVICES_SRCS = \
	build_mngt.pb.cc \
	build_mngt.grpc.pb.cc \
	BuildMngtServicesClient.cc \
	BuildMngtMsg.cc

#
# For building one exe per test, we rename the object file
# for server from <SVC>Services.o to <SVC>ServicesSvc.o
# and
# for client from <SVC>ServicesClient.o to <SVC>ServicesClt.o
# This way we build server/client
# with <SVC>ServicesSvc.o/<SVC>ServicesClt.o for one exe per test
# and
# with <SVC>Services.o/<SVC>ServicesClient.o for one exe for all tests
#
ifeq ($(SINGLE_TEST_EXE),no)
GRPC_SRV_PLUGIN_SERVICES_OBJS = $(subst PluginServices.o,PluginServicesSrv.o,$(GRPC_SRV_PLUGIN_SERVICES_SRCS:%.cc=%.o))
GRPC_CLT_PLUGIN_SERVICES_OBJS = $(subst PluginServicesClient.o,PluginServicesClt.o,$(GRPC_CLT_PLUGIN_SERVICES_SRCS:%.cc=%.o))
else
GRPC_SRV_PLUGIN_SERVICES_OBJS = $(GRPC_SRV_PLUGIN_SERVICES_SRCS:%.cc=%.o)
GRPC_CLT_PLUGIN_SERVICES_OBJS = $(GRPC_CLT_PLUGIN_SERVICES_SRCS:%.cc=%.o)
endif

ifeq ($(SINGLE_TEST_EXE),no)
GRPC_SRV_CFG_COLLECTION_SERVICES_OBJS = $(subst CfgCollectionServices.o,CfgCollectionServicesSrv.o,$(GRPC_SRV_CFG_COLLECTION_SERVICES_SRCS:%.cc=%.o))
GRPC_CLT_CFG_COLLECTION_SERVICES_OBJS = $(subst CfgCollectionServicesClient.o,CfgCollectionServicesClt.o,$(GRPC_CLT_CFG_COLLECTION_SERVICES_SRCS:%.cc=%.o))
else
GRPC_SRV_CFG_COLLECTION_SERVICES_OBJS = $(GRPC_SRV_CFG_COLLECTION_SERVICES_SRCS:%.cc=%.o)
GRPC_CLT_CFG_COLLECTION_SERVICES_OBJS = $(GRPC_CLT_CFG_COLLECTION_SERVICES_SRCS:%.cc=%.o)
endif

ifeq ($(SINGLE_TEST_EXE),no)
GRPC_SRV_BUILD_MNGT_SERVICES_OBJS = $(subst BuildMngtServices.o,BuildMngtServicesSrv.o,$(GRPC_SRV_BUILD_MNGT_SERVICES_SRCS:%.cc=%.o))
GRPC_CLT_BUILD_MNGT_SERVICES_OBJS = $(subst BuildMngtServicesClient.o,BuildMngtServicesClt.o,$(GRPC_CLT_BUILD_MNGT_SERVICES_SRCS:%.cc=%.o))
else
GRPC_SRV_BUILD_MNGT_SERVICES_OBJS = $(GRPC_SRV_BUILD_MNGT_SERVICES_SRCS:%.cc=%.o)
GRPC_CLT_BUILD_MNGT_SERVICES_OBJS = $(GRPC_CLT_BUILD_MNGT_SERVICES_SRCS:%.cc=%.o)
endif

# All tests are clients & servers for Plugin, CfgCollection & BuildMngt
ifeq ($(SINGLE_TEST_EXE),no)
ALL_TESTS = \
	PluginServicesSrv \
	PluginServicesClt \
	CfgCollectionServicesSrv \
	CfgCollectionServicesClt \
	BuildMngtServicesSrv \
	BuildMngtServicesClt \
	$(MSG_TESTS_SRCS:%.cc=%)
else
ALL_TESTS = tests/alltests
endif

ALL_TESTS_OBJS = \
	plugin_request.pb.o \
	plugin_request.grpc.pb.o \
	cfg_request.pb.o \
	cfg_request.grpc.pb.o \
	build_mngt.pb.o \
	build_mngt.grpc.pb.o \
	$(MSG_TESTS_SRCS:%.cc=%.o) \
	PluginServicesClient.o \
	PluginServices.o \
	CfgCollectionServicesClient.o \
	CfgCollectionServices.o \
	BuildMngtServicesClient.o \
	BuildMngtServices.o

ifeq ($(SINGLE_TEST_EXE),yes)
ALL_TESTS_OBJS += tests/alltests.o
endif

# Location of dir googletest in cloned git repository
GTEST_DIR = /usr/local/src/misc/googletest/googletest

ifeq ($(SINGLE_TEST_EXE),no)
GTEST_CPPFLAGS = -USINGLE_TEST_EXE -isystem $(GTEST_DIR)/include
else
GTEST_CPPFLAGS = -DSINGLE_TEST_EXE -isystem $(GTEST_DIR)/include
endif

CXXFLAGS = -g -O1 -std=c++11
PROTOC := protoc
PROTOC_FLAGS := --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` --proto_path=. --cpp_out=. --grpc_out=.

CPPFLAGS := -I.

LDFLAGS := -g -O1 -std=c++11
LDFLAGS += `pkg-config --libs-only-L grpc++`
LDFLAGS += `pkg-config --libs-only-L grpc++_reflection`
LDFLAGS += `pkg-config --libs-only-L protobuf` 

LDLIBS = `pkg-config --libs grpc++`
LDLIBS += -Wl,--no-as-needed `pkg-config --libs-only-l grpc++_reflection` -Wl,--as-needed 
LDLIBS += -lboost_program_options -lboost_system -lboost_iostreams 
LDLIBS += `pkg-config --libs-only-l protobuf` -lstdc++ -lrt -ldl

CPAD_LDLIBS := $(LDLIBS)
CFG_LDLIBS := -luuid
SRV_LDLIBS := $(LDLIBS)
CLT_LDLIBS := $(LDLIBS)

%.o: %.cc
	$(CXX) $(GTEST_CPPFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

%.grpc.pb.cc %.grpc.pb.h %.pb.cc %.pb.h: %.proto
	$(PROTOC) $(PROTOC_FLAGS) $<

ifeq ($(SINGLE_TEST_EXE),no)
tests/%:  tests/%.cc
	$(CXX) $(CXXFLAGS) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) -I. -pthread $< libcpad.a libgtest.a $(CPAD_LDLIBS) -o $@
else
tests/%.o: tests/%.cc
	$(CXX) $(CXXFLAGS) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) -I. -pthread -c $< -o $@
endif

.PHONY: all cls clean tests

all: cfgtest cpad tests PluginServicesSrv PluginServicesClt CfgCollectionServicesSrv CfgCollectionServicesClt BuildMngtServicesSrv BuildMngtServicesClt

gtest-all.o: $(GTEST_DIR)/src/gtest-all.cc
	$(CXX) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc

libgtest.a: gtest-all.o
	$(AR_CMD) $@ $^

libcpad.a: $(LIBCPAD_OBJS)
	$(AR_CMD) $@ $^

## Let's add targets for the one exe per test config
ifeq ($(SINGLE_TEST_EXE),no)
PluginServicesSrv.o: PluginServices.cc
	$(CXX) -USINGLE_TEST_EXE $(GTEST_CPPFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

PluginServicesSrv: libgtest.a libcpad.a $(GRPC_SRV_PLUGIN_SERVICES_OBJS)
	$(CXX) $(CXXFLAGS) $(GTEST_CPPFLAGS) -I. -pthread $^ `pkg-config --libs grpc++` $(CPAD_LDLIBS) -o $@

PluginServicesClt.o: PluginServicesClient.cc
	$(CXX) -USINGLE_TEST_EXE $(GTEST_CPPFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

PluginServicesClt: libgtest.a libcpad.a $(GRPC_CLT_PLUGIN_SERVICES_OBJS)
	$(CXX) $(CXXFLAGS) $(GTEST_CPPFLAGS) -I. -pthread $^ `pkg-config --libs grpc++` $(CPAD_LDLIBS) -o $@

CfgCollectionServicesSrv.o: CfgCollectionServices.cc
	$(CXX) -USINGLE_TEST_EXE $(GTEST_CPPFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

CfgCollectionServicesSrv: libgtest.a libcpad.a $(GRPC_SRV_CFG_COLLECTION_SERVICES_OBJS)
	$(CXX) $(CXXFLAGS) $(GTEST_CPPFLAGS) -I. -pthread $^ `pkg-config --libs grpc++` $(CPAD_LDLIBS) -o $@

CfgCollectionServicesClt.o: CfgCollectionServicesClient.cc
	$(CXX) -USINGLE_TEST_EXE $(GTEST_CPPFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

CfgCollectionServicesClt: libgtest.a libcpad.a $(GRPC_CLT_CFG_COLLECTION_SERVICES_OBJS)
	$(CXX) $(CXXFLAGS) $(GTEST_CPPFLAGS) -I. -pthread $^ `pkg-config --libs grpc++` $(CPAD_LDLIBS) -o $@

BuildMngtServicesSrv.o: BuildMngtServices.cc
	$(CXX) -USINGLE_TEST_EXE $(GTEST_CPPFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

BuildMngtServicesSrv: libgtest.a libcpad.a $(GRPC_SRV_BUILD_MNGT_SERVICES_OBJS)
	$(CXX) $(CXXFLAGS) $(GTEST_CPPFLAGS) -I. -pthread $^ `pkg-config --libs grpc++` $(CPAD_LDLIBS) -o $@

BuildMngtServicesClt.o: BuildMngtServicesClient.cc
	$(CXX) -USINGLE_TEST_EXE $(GTEST_CPPFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

BuildMngtServicesClt: libgtest.a libcpad.a $(GRPC_CLT_BUILD_MNGT_SERVICES_OBJS)
	$(CXX) $(CXXFLAGS) $(GTEST_CPPFLAGS) -I. -pthread $^ `pkg-config --libs grpc++` $(CPAD_LDLIBS) -o $@

tests: $(ALL_TESTS)
	for t in $(ALL_TESTS); do \
		if test "$$t" = "PluginServicesSrv"; then \
			echo "==> Launching plugin_request.proto services server"; \
			bash -c "./$$t &"; \
			sleep 1; \
		elif test "$$t" = "CfgCollectionServicesSrv"; then \
			echo "==> Launching cfg_request.proto services server"; \
			bash -c "./$$t &"; \
			sleep 1; \
		elif test "$$t" = "BuildMngtServicesSrv"; then \
			echo "==> Launching build_mngt.proto services server"; \
			bash -c "./$$t &"; \
			sleep 1; \
		elif test "$$t" = "PluginServicesClt"; then \
			echo "==> Launching plugin_request.proto services client"; \
			./$$t; \
			sleep 1; \
			echo "==> Killing plugin_request.proto services server"; \
			killall -TERM PluginServicesSrv; \
			sleep 1; \
		elif test "$$t" = "CfgCollectionServicesClt"; then \
			echo "==> Launching cfg_request.proto services client"; \
			./$$t; \
			sleep 1; \
			echo "==> Killing cfg_request.proto services server"; \
			killall -TERM CfgCollectionServicesSrv; \
			sleep 1; \
		elif test "$$t" = "BuildMngtServicesClt"; then \
			echo "==> Launching build_mngt.proto services client"; \
			./$$t; \
			sleep 1; \
			echo "==> Killing build_mngt.proto services server"; \
			killall -TERM BuildMngtServicesSrv; \
			sleep 1; \
		else \
			./$$t; \
		fi; \
	done
else
tests/alltests: libgtest.a libcpad.a $(ALL_TESTS_OBJS) tests/alltests.o
	$(CXX) $(CXXFLAGS) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) -I. -pthread $(ALL_TESTS_OBJS) libcpad.a libgtest.a $(CPAD_LDLIBS) -o $@

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
cpad_cmd.o: plugin_request.pb.cc cfg_request.pb.cc build_mngt.pb.cc
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
tests/alltests: tests/alltests.o PluginServices.o PluginServicesClient.o CfgCollectionServices.o CfgCollectionServicesClient.o BuildMngtServices.o BuildMngtServicesClient.o
PluginServices.o: plugin_request.grpc.pb.cc plugin_request.grpc.pb.h plugin_request.pb.cc plugin_request.pb.h 
PluginServicesClient.o: PluginServicesClient.cc plugin_request.grpc.pb.cc plugin_request.grpc.pb.h plugin_request.pb.cc plugin_request.pb.h 
CfgCollectionServices.o: cfg_request.grpc.pb.cc cfg_request.grpc.pb.h cfg_request.pb.cc cfg_request.pb.h 
CfgCollectionServicesClient.o: cfg_request.grpc.pb.cc cfg_request.grpc.pb.h cfg_request.pb.cc cfg_request.pb.h 
BuildMngtServices.o: build_mngt.grpc.pb.cc build_mngt.grpc.pb.h build_mngt.pb.cc build_mngt.pb.h 
BuildMngtServicesClient.o: build_mngt.grpc.pb.cc build_mngt.grpc.pb.h build_mngt.pb.cc build_mngt.pb.h 
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
PluginServicesSrv.o: PluginServices.cc
PluginServicesClt.o: PluginServicesClient.cc
PluginServicesSrv: PluginServicesSrv.o 
PluginServicesClt: PluginServicesClt.o
CfgCollectionServicesSrv.o: CfgCollectionServices.cc
CfgCollectionServicesClt.o: CfgCollectionServicesClient.cc
CfgCollectionServicesSrv: CfgCollectionServicesSrv.o
CfgCollectionServicesClt: CfgCollectionServicesClt.o
BuildMngtServicesSrv.o: BuildMngtServices.cc
BuildMngtServicesClt.o: BuildMngtServicesClient.cc
BuildMngtServicesSrv: BuildMngtServicesSrv.o
BuildMngtServicesClt: BuildMngtServicesClt.o
PluginServicesSvc.o: plugin_request.grpc.pb.cc plugin_request.grpc.pb.h plugin_request.pb.cc plugin_request.pb.h 
PluginServicesClt.o: PluginServicesClient.cc plugin_request.grpc.pb.cc plugin_request.grpc.pb.h plugin_request.pb.cc plugin_request.pb.h 
CfgCollectionServicesSvc.o: cfg_request.grpc.pb.cc cfg_request.grpc.pb.h cfg_request.pb.cc cfg_request.pb.h 
CfgCollectionServicesClt.o: cfg_request.grpc.pb.cc cfg_request.grpc.pb.h cfg_request.pb.cc cfg_request.pb.h 
BuildMngtServicesSvc.o: build_mngt.grpc.pb.cc build_mngt.grpc.pb.h build_mngt.pb.cc build_mngt.pb.h 
BuildMngtServicesClt.o: build_mngt.grpc.pb.cc build_mngt.grpc.pb.h build_mngt.pb.cc build_mngt.pb.h 
endif

