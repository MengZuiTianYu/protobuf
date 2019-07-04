PROTO_FILE=addressbook
PROTO_SRC_DIR=./proto
PROTO_DST_DIR=./proto

#　生成访问类
cpp_out:
	if [ ! -d $(PROTO_DST_DIR) ];then mkdir -p $(PROTO_DST_DIR); fi
	protoc -I=$(PROTO_SRC_DIR) --cpp_out=$(PROTO_DST_DIR) $(PROTO_SRC_DIR)/$(PROTO_FILE).proto


CXX=g++
LDFLAGS=-std=c++11 -O1 -g -w -fopenmp

CFLAGS = -lprotobuf

LIBS=`pkg-config --cflags --libs protobuf`

TARGET=protobuf.app
SRC=protobuf.cpp

SRCS=$(PROTO_SRC_DIR)/$(PROTO_FILE).pb.cc $(SRC) 

#　编译工程，生成可执行文件
run:
	@echo "Compilling......"
	$(CXX) $(LDFLAGS) $(SRCS) -o $(TARGET) $(CFLAGS) $(LIBS)

	
.PHONY:clean
clean:
	rm -rf $(TARGET) $(PROTO_DST_DIR)/*.pb.cc $(PROTO_DST_DIR)/*pb.h *.prototxt


