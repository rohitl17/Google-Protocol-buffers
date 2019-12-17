#include<bits/stdc++.h>
#include "library.pb.h"
using namespace std;

void AskDetails(tutorial::Student* student)
{

cout<<"Enter the roll no. of the student";
int roll_no;
cin>>roll_no;
student->set_roll_no(roll_no);
cin.ignore(256,'\n');

cout<<"Enter the name of the student";
getline(cin, *student->mutable_name());

cout<<"Enter the email address of the student";
string email;
getline(cin,email);
student->set_email(email);

while (true) {
    cout << "Enter a book ID (or leave blank to finish): ";
    string id;
    getline(cin, id);
    if (id.empty()) {
      break;
    }

    tutorial::Student::BookNumber* book_number = student->add_books();
    book_number->set_id(id);

    cout << "Is this book a Novel,Fictional,Non_fictional";
    string type;
    getline(cin, type);
    if (type == "novel") {
      book_number->set_type(tutorial::Student::NOVEL);
    } else if (type == "fiction") {
      book_number->set_type(tutorial::Student::FICTION);
    } else if (type == "non_fiction") {
      book_number->set_type(tutorial::Student::NON_FICTION);
    } else {
      cout << "Unknown phone type.  Using default." << endl;
    }

	cout<<"Enter the name of the book";
	getline(cin, *book_number->mutable_bookname());
  }
}

int main(int argc, char *argv[])
{
 GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
    return -1;
  }

  tutorial::LibraryRecords lib_book;

 {
    fstream input(argv[1], ios::in | ios::binary);
    if (!input) {
      cout << argv[1] << ": File not found.  Creating a new file." << endl;
    } else if (!lib_book.ParseFromIstream(&input)) {
      cerr << "Failed to parse address book." << endl;
      return -1;
    }
  }

AskDetails(lib_book.add_students());
{
        fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    if (!lib_book.SerializeToOstream(&output)) {
      cerr << "Failed to write library book." << endl;
      return -1;
    }
  }

 google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
