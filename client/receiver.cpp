#include<bits/stdc++.h>
#include "library.pb.h"
using namespace std;

void ListOfStudents(const tutorial::LibraryRecords &lib_book)
{
for (int i = 0; i < lib_book.students_size(); i++) {
    const tutorial::Student& student = lib_book.students(i);

    cout << "Person ID: " << student.roll_no() << endl;
    cout << "  Name: " << student.name() << endl;
      cout << "  E-mail address: " << student.email() << endl;

    for (int j = 0; j < student.books_size(); j++) {
      const tutorial::Student::BookNumber& book_number = student.books(j);

      switch (book_number.type()) {
        case tutorial::Student::NOVEL:
          cout << "NOVEL";
          break;
        case tutorial::Student::FICTION:
          cout << "FICTION";
          break;
        case tutorial::Student::NON_FICTION:
          cout << "NON_FICTION";
          break;
      }
      cout << book_number.id() << endl;
    }
  }

}

int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << "LIBRARY_BOOK" << endl;
    return -1;
  }

  tutorial::LibraryRecords lib_book;

  {
    // Read the existing address book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!lib_book.ParseFromIstream(&input)) {
      cerr << "Failed to parse address book." << endl;
      return -1;
    }
  }

  ListOfStudents(lib_book);

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
