#****************************************************************************
#
# Makefile for grpc
# Henry
# 2020-03-17
#
#****************************************************************************

CXX	:= g++

INC_LIBS:= 
INC_HEAD:= 
INC_SLIB:= 
CXXFLAGS:= -Wall -c -fPIC -Wno-deprecated -g $(INC_HEAD) $(INC_SLIB)

LIBS	:= -shared
AR	:= ar rc

LIBSPATH:= ./

OUTPUT	:= libtdgrpc.so
ARLIB	:= libtdgrpc.a

SOURCES = $(shell ls *.cc)
OBJECTS = $(SOURCES:.cc=.o)

CLIENT_SOURCES = client.cpp
CLIENT_OBJECTS = $(CLIENT_SOURCES:.cpp=.o) $(OBJECTS)

SERVER_SOURCES = server.cpp
SERVER_OBJECTS = $(SERVER_SOURCES:.cpp=.o) $(OBJECTS)

BIN_CXXFLAGS:= -Wall -fPIC -Wno-deprecated -g $(INC_HEAD) $(INC_SLIB)
BIN_CXXFLAGS += `pkg-config --libs protobuf grpc++` -lgrpc++_reflection

BIN_PATH := ./
CLIENT		:= client
SERVER		:= server

.PHONY: all
all:$(OUTPUT)

$(OUTPUT):$(OBJECTS)
	@$(CXX) -o $@ $(LIBS) $(OBJECTS) $(INC_HEAD) $(INC_LIBS) $(INC_SLIB)
	$(AR) $(ARLIB) $(OBJECTS) 


.PHONY: client
client:$(CLIENT_OBJECTS)
	$(CXX) $(INC_LIBS) -o $(BIN_PATH)/$@ $(CLIENT_OBJECTS) $(BIN_CXXFLAGS)

.PHONY: server
server:$(SERVER_OBJECTS)
	$(CXX) $(INC_LIBS) -o $(BIN_PATH)/$@ $(SERVER_OBJECTS) $(BIN_CXXFLAGS)


PROTOC = protoc
PROTOS_PATH = ./
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`
TYPT_PROTO = data.proto
SERVICE_PROTO = data_service.proto
OUT_PATH = .

.PHONY: grpc
grpc:
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=$(OUT_PATH) --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $(SERVICE_PROTO)
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=$(OUT_PATH) $(TYPT_PROTO) $(SERVICE_PROTO)

.PHONY: clean
clean:
	rm -f *.o *~

.PHONY: cleanall
cleanall:
	rm -f *.so *.o *~ $(OUTPUT) $(ARLIB) $(LIBSPATH)/$(OUTPUT) $(BIN_PATH)/$(CLIENT)
