#include "protobuf.h"

template <typename T> Protobuf<T>::Protobuf()
{
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

}

template <typename T> Protobuf<T>::~Protobuf() {
    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();
}

template <typename T> bool Protobuf<T>::readProtoFromTextFile(const char* 
        filename, T* proto) {
  int fd = open(filename, O_RDONLY);
  google::protobuf::io::FileInputStream* input = (
          new google::protobuf::io::FileInputStream(fd));
  bool success = google::protobuf::TextFormat::Parse(input, proto);
  delete input;
  close(fd);
  return success;
}

template <typename T> bool Protobuf<T>::readProtoFromBinaryFile(const char* 
        filename, T* proto) {
    std::ifstream model_file(filename);
    return proto->ParseFromIstream(&model_file);
}

template <typename T> bool Protobuf<T>::writeProtoToBinaryFile(const char* 
        filename, T* proto) {
    std::fstream model_file(filename,std::ios::out |std::ios::trunc |std::ios::binary);
    return proto->SerializeToOstream(&model_file);
}

template <typename T> bool Protobuf<T>::readProtoFromString(std::string &buff, 
        T* proto) {
    return proto->ParseFromString(buff);
}

template <typename T> bool Protobuf<T>::writeProtoToString(std::string &buff, T* proto) {
    return proto->SerializeToString(&buff);
}

// Iterates though all people in the AddressBook and prints info about them.
template <typename T> void Protobuf<T>::printList(const T &address_book) {
    for (int i = 0; i < address_book.people_size(); i++) {
        const tutorial::Person &person = address_book.people(i);
        std::cout << "Person ID: " << person.id() << std::endl;
        std::cout << "  Name: " << person.name() << std::endl;
        if (person.has_email()) {
            std::cout << "  E-mail address: " << person.email() << std::endl;
        }
        for (int j = 0; j < person.phones_size(); j++) {
            const tutorial::Person::PhoneNumber &phone_number = person.phones(j);
            switch (phone_number.type()) {
                case tutorial::Person::MOBILE:
                    std::cout << "  Mobile phone #: ";
                    break;
                case tutorial::Person::HOME:
                    std::cout << "  Home phone #: ";
                    break;
                case tutorial::Person::WORK:
                    std::cout << "  Work phone #: ";
                    break;
            }
            std::cout << phone_number.number() << std::endl;
        }
    }
}

template <typename T> void Protobuf<T>::PromptForAddress(tutorial::Person *person) {
    std::cout << "Enter person ID number: ";
    int id;
    std::cin >> id;
    person->set_id(id);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
//     std::cin.ignore(256, '\n');//忽略最后的回车

    std::cout << "Enter name: ";
    getline(std::cin, *person->mutable_name());

    std::cout << "Enter email address (blank for none): ";
    std::string email;
    getline(std::cin, email);
    if (!email.empty()) {
        person->set_email(email);
    }
    while (true) {
        std::cout << "Enter a phone number (or leave blank to finish): ";
        std::string number;
        getline(std::cin, number);
        if (number.empty()) {
            break;
        }
        tutorial::Person::PhoneNumber *phone_number = person->add_phones();
        phone_number->set_number(number);
        std::cout << "Is this a mobile, home, or work phone? ";
        std::string type;
        getline(std::cin, type);
        if (type == "mobile") {
            phone_number->set_type(tutorial::Person::MOBILE);
        } else if (type == "home") {
            phone_number->set_type(tutorial::Person::HOME);
        } else if (type == "work") {
            phone_number->set_type(tutorial::Person::WORK);
        } else {
            std::cout << "Unknown phone type.  Using default." << std::endl;
        }
    }
}

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
