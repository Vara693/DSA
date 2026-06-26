#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>
#include <unordered_map>

using namespace std;

struct Student {
    string name;
    int roll_no;
    int prn;
    unsigned long long mob;
    string email;
    Student* next;
};

class StudentList {
private:
    Student* head;

    bool isAllAlpha(const string &s) {
        for (char c : s) {
            if (!isalpha(c) && c != ' ')
                return false;
        }
        return !s.empty();
    }

    bool isValidNumber(const string &s, int length_required) {
        if ((int)s.size() != length_required) return false;
        for (char c : s) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

    bool endsWith(const string &email, const string &domain) {
        if (email.size() <= domain.size()) return false;
        return email.compare(email.size() - domain.size(), domain.size(), domain) == 0;
    }

    bool isValidEmail(const string &email) {
        int at_pos = email.find('@');
        if (at_pos == string::npos || at_pos == 0) return false;

        for (int i = 0; i < at_pos; i++) {
            if (!isalnum(email[i]) && email[i] != '.' && email[i] != '_') return false;
            if (i > 0 && (email[i] == '.' || email[i] == '_') && 
                (email[i - 1] == '.' || email[i - 1] == '_')) return false;
        }
        if (!isalnum(email[0]) || !isalnum(email[at_pos - 1])) return false;

        return endsWith(email, "@gmail.com") || endsWith(email, "@vit.edu");
    }

    bool isUniqueRoll(int roll) {
        Student* temp = head;
        while (temp != nullptr) {
            if (temp->roll_no == roll) return false;
            temp = temp->next;
        }
        return true;
    }

    bool isUniquePRN(int prn) {
        Student* temp = head;
        while (temp != nullptr) {
            if (temp->prn == prn) return false;
            temp = temp->next;
        }
        return true;
    }

    bool isUniqueMob(unsigned long long mob) {
        Student* temp = head;
        while (temp != nullptr) {
            if (temp->mob == mob) return false;
            temp = temp->next;
        }
        return true;
    }

    bool isUniqueEmail(const string &email) {
        Student* temp = head;
        while (temp != nullptr) {
            if (temp->email == email) return false;
            temp = temp->next;
        }
        return true;
    }

    void printStudent(const Student* s) {
        cout << "Name   : " << s->name << "\n";
        cout << "Roll No: " << s->roll_no << "\n";
        cout << "PRN    : " << s->prn << "\n";
        cout << "Mobile : " << s->mob << "\n";
        cout << "Email  : " << s->email << "\n";
    }

    string inputLine(const string &prompt) {
        cout << prompt;
        string s;
        getline(cin, s);
        return s;
    }

public:
    StudentList() {
        head = nullptr;
    }

    void createStudent() {
        Student* s = new Student();

        bool valid = false;
        while (!valid) {
            s->name = inputLine("Name: ");
            if (isAllAlpha(s->name)) valid = true;
            else cout << "Use only alphabets.\n";
        }

        valid = false;
        while (!valid) {
            string temp = inputLine("Roll No: ");
            bool all_digits = !temp.empty() && all_of(temp.begin(), temp.end(), ::isdigit);                                                                                                                                                                                                                                                                                                                                                                                                           
            if (all_digits) {
                int r = stoi(temp);
                if (r > 0 && isUniqueRoll(r)) {
                    s->roll_no = r;
                    valid = true;
                } else cout << "Invalid or duplicate roll number.\n";
            } else cout << "Invalid roll number.\n";
        }

        valid = false;
        while (!valid) {
            string temp = inputLine("PRN (8 digits): ");
            if (isValidNumber(temp, 8) && temp[0] == '1') {
                int prn = stoi(temp);
                if (isUniquePRN(prn)) {
                    s->prn = prn;
                    valid = true;
                } else cout << "PRN already exists.\n";
            } else cout << "Invalid PRN.\n";
        }

        valid = false;
        while (!valid) {
            string temp = inputLine("Mobile (10 digits): ");
            if (isValidNumber(temp, 10) && (temp[0] >= '6' && temp[0] <= '9')) {
                unsigned long long mob = stoull(temp);
                if (isUniqueMob(mob)) {
                    s->mob = mob;
                    valid = true;
                } else cout << "Mobile already exists.\n";
            } else cout << "Invalid Mobile.\n";
        }

        valid = false;
        while (!valid) {
            s->email = inputLine("Email: ");
            if (isValidEmail(s->email) && isUniqueEmail(s->email)) valid = true;
            else cout << "Invalid or duplicate email.\n";
        }

        s->next = nullptr;

        if (head == nullptr) head = s;
        else {
            Student* temp = head;
            while (temp->next != nullptr) temp = temp->next;
            temp->next = s;
        }
        cout << "Entry successful!\n";
    }

    void displayAll() {
        Student* temp = head;
        if (temp == nullptr) cout << "No records.\n";
        while (temp != nullptr) {
            printStudent(temp);
            cout << "------------------\n";
            temp = temp->next;
        }
    }

    void search(int choice) {
        string input;
        int intInput;
        unsigned long long mobInput;
        Student* temp = head;
        bool found = false;

        if (choice == 1) {
            input = inputLine("Enter Name: ");
            while (temp != nullptr) {
                if (temp->name == input) {
                    printStudent(temp);
                    found = true;
                }
                temp = temp->next;
            }
        } else if (choice == 2) {
            cout << "Enter Roll No: ";
            cin >> intInput; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (temp != nullptr) {
                if (temp->roll_no == intInput) {
                    printStudent(temp);
                    found = true;
                }
                temp = temp->next;
            }
        } else if (choice == 3) {
            cout << "Enter PRN: ";
            cin >> intInput; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (temp != nullptr) {
                if (temp->prn == intInput) {
                    printStudent(temp);
                    found = true;
                }
                temp = temp->next;
            }
        } else if (choice == 4) {
            cout << "Enter Mobile: ";
            cin >> mobInput; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (temp != nullptr) {
                if (temp->mob == mobInput) {
                    printStudent(temp);
                    found = true;
                }
                temp = temp->next;
            }
        } else if (choice == 5) {
            input = inputLine("Enter Email: ");
            while (temp != nullptr) {
                if (temp->email == input) {
                    printStudent(temp);
                    found = true;
                }
                temp = temp->next;
            }
        }

        if (!found) cout << "No record found.\n";
    }

    void updateStudent(int roll) {
        Student* temp = head;
        while (temp != nullptr && temp->roll_no != roll) {
            temp = temp->next;
        }
        if (temp == nullptr) {
            cout << "Student not found.\n";
            return;
        }

        cout << "Updating student with Roll No: " << roll << "\n";
        cout << "Re-enter details:\n";
        createStudent();
        deleteStudent(roll);
    }

    void deleteStudent(int roll) {
        if (head == nullptr) {
            cout << "No records.\n";
            return;
        }

        if (head->roll_no == roll) {
            Student* del = head;
            head = head->next;
            delete del;
            cout << "Deleted successfully.\n";
            return;
        }

        Student* temp = head;
        while (temp->next != nullptr && temp->next->roll_no != roll) {
            temp = temp->next;
        }
        if (temp->next == nullptr) cout << "Student not found.\n";
        else {
            Student* del = temp->next;
            temp->next = temp->next->next;
            delete del;
            cout << "Deleted successfully.\n";
        }
    }
};

int main() {
    StudentList sl;
    int main_choice = 0;
    while (main_choice != 6) {
        cout << "\nMenu:\n1. Create Student\n2. Display All\n3. Search\n4. Update\n5. Delete\n6. Quit\nChoice: ";
        cin >> main_choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (main_choice == 1) {
            sl.createStudent();
        } else if (main_choice == 2) {
            sl.displayAll();
        } else if (main_choice == 3) {
            int sc;
            cout << "Search by:\n1. Name\n2. Roll No\n3. PRN\n4. Mobile\n5. Email\nChoice: ";
            cin >> sc; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            sl.search(sc);
        } else if (main_choice == 4) {
            int r;
            cout << "Enter Roll No to update: ";
            cin >> r; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            sl.updateStudent(r);
        } else if (main_choice == 5) {
            int r;
            cout << "Enter Roll No to delete: ";
            cin >> r; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            sl.deleteStudent(r);
        } else if (main_choice == 6) {
            cout << "Thanks!\n";
        } else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}
