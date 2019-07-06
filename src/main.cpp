#include <iostream>
#include "protobuf.h"

// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
int main(int argc, char *argv[]) {
    char *file_name = "proto/txt.prototxt";
    char file_name_2[] = "binary.prototxt";
    Protobuf<tutorial::AddressBook> pro;
    tutorial::AddressBook address_book;
    tutorial::AddressBook address_book_2;
    tutorial::AddressBook address_book_3;
    tutorial::AddressBook address_book_4;

    if (argc != 2) {
        std::cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << std::endl;
        printf("    use dafaule address_book_file: %s\n", file_name);
    }
    else {
        file_name = argv[1];
    }
    
    std::cout << "/************read txt file***********************/" << std::endl;
    if(!pro.readProtoFromTextFile(file_name, &address_book))
    {
        std::cout<<"error opening train_val file"<<std::endl;
        return -1;
    }
    pro.printList(address_book);
   
    std::cout << "/***********add people and write binary file*****/" << std::endl;
    pro.readProtoFromBinaryFile(file_name_2, &address_book_2);
    pro.PromptForAddress(address_book_2.add_people());
    pro.printList(address_book_2);
    pro.writeProtoToBinaryFile(file_name_2, &address_book_2);
    
    std::cout << "/************read binary file********************/" << std::endl;
    if(!pro.readProtoFromBinaryFile(file_name_2, &address_book_3))
    {
        std::cout<<"error opening train_val file"<<std::endl;
        return -1;
    }
    pro.printList(address_book_3);
    
    std::cout << "/*************write-read string file*************/" << std::endl;
    std::string buff;
    pro.writeProtoToString(buff, &address_book_3);

    pro.readProtoFromString(buff, &address_book_4);

    pro.printList(address_book_4);
    return 0;
}
