#ifndef __PROTOBUF_H__
#define __PROTOBUF_H__

#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
#include <limits>
#include "proto/addressbook.pb.h"

template <typename T> class Protobuf {
    private:

    public:
    Protobuf();
    ~Protobuf();
    
    bool readProtoFromTextFile(const char* filename, T* proto);
    bool readProtoFromBinaryFile(const char* filename, T* proto);
    bool writeProtoToBinaryFile(const char* filename, T* proto);

    bool readProtoFromString(std::string &buff, T* proto);
    bool writeProtoToString(std::string &buff, T* proto);
        
    void printList(const T &address_book);
    void PromptForAddress(tutorial::Person *person);
};



#endif
