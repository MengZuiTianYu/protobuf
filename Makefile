CXX=g++
LDFLAGS=-std=c++11 -O1 -g -w -fopenmp

CFLAGS = -lprotobuf

LIBS=`pkg-config --cflags --libs protobuf`

PROTO_FILE=addressbook
PROTO_SRC_DIR=./proto
PROTO_DST_DIR=./proto

TARGET=main.app


INC_PROTO = $(PROTO_DST_DIR)
INCLUDE_BASE = ./include
INC_PROTOBUF = $(INCLUDE_BASE)/protobuf

INCLUDE_DIR = -I"$(INCLUDE_BASE)" \
			  -I"$(INC_PROTO)" \
			  -I"$(INC_PROTOBUF)" \

SRC_PROTO = $(PROTO_SRC_DIR)/$(PROTO_FILE)
SRC_BASE = ./src
SRC_PROTOBUF = $(SRC_BASE)/protobuf

SRCS := $(wildcard $(SRC_BASE)/*.cpp) \
		$(wildcard $(SRC_PROTOBUF)/*.cpp) \

OBJS := $(SRCS:%.cpp=%.o)




#　编译工程，生成可执行文件
all:$(OBJS) $(SRC_PROTO).pb.o 
	@echo "Compilling......"
	$(CXX)  $(LDFLAGS) -o $(TARGET) $^ $(CFLAGS) $(LIBS)

%.o:%.cpp
	$(CXX) $(LDFLAGS) -c $< -o $@ $(LIBS) $(CFLAGS) $(INCLUDE_DIR)
	@echo " "

$(SRC_PROTO).pb.o:$(SRC_PROTO).pb.cc 
	$(CXX) $(LDFLAGS) -c $< -o $@ $(LIBS) $(CFLAGS) $(INCLUDE_DIR)
	@echo " "

#　生成访问类
cpp_out:
	if [ ! -d $(PROTO_DST_DIR) ];then mkdir -p $(PROTO_DST_DIR); fi
	protoc -I=$(PROTO_SRC_DIR) --cpp_out=$(PROTO_DST_DIR) $(PROTO_SRC_DIR)/$(PROTO_FILE).proto

	
.PHONY:clean
clean:
	rm -rf $(TARGET) $(PROTO_DST_DIR)/*.pb.cc $(PROTO_DST_DIR)/*pb.h $(PROTO_DST_DIR)/*pb.o $(OBJS) *.prototxt


