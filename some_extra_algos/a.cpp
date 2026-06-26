#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <limits>
#include <algorithm>

using namespace std;

struct Student {
    string name;
    int roll_no;
    int prn;
    unsigned long long mob;
    string email;
};

bool is_all_alpha(const string &s) {
    for (char c : s) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}

bool is_valid_number(const string &s, int length_required) {
    if (s.length() != (size_t)length_required) return false;
    return all_of(s.begin(), s.end(), ::isdigit);
}

bool end_email_part(const string &email, const string &domain) {
    if (email.length() < domain.length()) return false;
    return email.compare(email.length() - domain.length(), domain.length(), domain) == 0;
}

bool is_valid_email(const string &email) {
    return end_email_part(email, "@gmail.com") || end_email_part(email, "@vit.edu");
}

void print_student(const Student &s) {
    cout << "Name   : " << s.name << '\n';
    cout << "Roll No: " << s.roll_no << '\n';
    cout << "PRN    : " << s.prn << '\n';
    cout << "Mobile : " << s.mob << '\n';
    cout << "Email  : " << s.email << '\n';
}

int main() {
    const int max_stu = 100;
    vector<Student> students;
    int num;

    cout << "Enter the number of students (<= " << max_stu << "): ";
    while (!(cin >> num) || num <= 0 || num > max_stu) {
        cout << "Invalid input. Enter a valid number (1 to " << max_stu << "): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(); // Clear newline

    while (true) {
        char choice;
        cout << "Enter 'C' to continue or 'Q' to quit: ";
        cin >> choice;
        cin.ignore();

        if (choice == 'Q') {
            cout << "Thanks!\n";
            break;
        } else if (choice != 'C') {
            cout << "Invalid choice.\n";
            continue;
        }

        if ((int)students.size() >= num) {
            cout << "Maximum number of students reached.\n";
            break;
        }

        Student s;
        bool valid;

        // Name
        do {
            cout << "Name: ";
            getline(cin, s.name);
            valid = is_all_alpha(s.name);
            if (!valid) cout << "Use only alphabets.\n";
        } while (!valid);

        // Roll No
        do {
            cout << "Roll No: ";
            string input;
            getline(cin, input);
            try {
                s.roll_no = stoi(input);
                valid = s.roll_no > 0 &&
                        none_of(students.begin(), students.end(), [&](const Student& stu) {
                            return stu.roll_no == s.roll_no;
                        });
                if (!valid) cout << "Roll number already exists or is invalid.\n";
            } catch (...) {
                cout << "Invalid roll number.\n";
                valid = false;
            }
        } while (!valid);

        // PRN
        do {
            cout << "PRN (8 digits): ";
            string input;
            getline(cin, input);
            valid = is_valid_number(input, 8) && input[0] == '1' &&
                    none_of(students.begin(), students.end(), [&](const Student& stu) {
                        return stu.prn == stoi(input);
                    });
            if (valid)
                s.prn = stoi(input);
            else
                cout << "Invalid or duplicate PRN.\n";
        } while (!valid);

        // Mobile
        do {
            cout << "Mobile: ";
            string input;
            getline(cin, input);
            valid = is_valid_number(input, 10) && (input[0] >= '6' && input[0] <= '9') &&
                    none_of(students.begin(), students.end(), [&](const Student& stu) {
                        return stu.mob == stoull(input);
                    });
            if (valid)
                s.mob = stoull(input);
            else
                cout << "Invalid or duplicate mobile number.\n";
        } while (!valid);

        // Email
        do {
            cout << "Email: ";
            getline(cin, s.email);
            int at_count = count(s.email.begin(), s.email.end(), '@');
            int dot_count = count(s.email.begin(), s.email.end(), '.');
            valid = isalnum(s.email[0]) && at_count == 1 && dot_count >= 1 &&
                    all_of(s.email.begin(), s.email.end(), [](char c) {
                        return isalnum(c) || c == '@' || c == '.';
                    }) &&
                    is_valid_email(s.email) &&
                    none_of(students.begin(), students.end(), [&](const Student& stu) {
                        return stu.email == s.email;
                    });
            if (!valid) cout << "Invalid email format or duplicate.\n";
        } while (!valid);

        students.push_back(s);
        cout << "Entry successful!\n";
    }

    // Search
    while (true) {
        int choice;
        cout << "\nSearch menu (6 to quit):\n";
        cout << "1. By Name\n2. By Roll No\n3. By PRN\n4. By Mobile\n5. By Email\n6. Quit\nChoice: ";
        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore();

        bool found = false;
        if (choice == 1) {
            string name;
            cout << "Enter name: ";
            getline(cin, name);
            for (const auto& s : students)
                if (s.name == name) { print_student(s); found = true; }

        } else if (choice == 2) {
            int roll;
            cout << "Enter roll no: ";
            if (cin >> roll) {
                for (const auto& s : students)
                    if (s.roll_no == roll) { print_student(s); found = true; }
            } else {
                cout << "Invalid input.\n";
                cin.clear();
            }
            cin.ignore();

        } else if (choice == 3) {
            int prn;
            cout << "Enter PRN: ";
            if (cin >> prn) {
                for (const auto& s : students)
                    if (s.prn == prn) { print_student(s); found = true; }
            } else {
                cout << "Invalid input.\n";
                cin.clear();
            }
            cin.ignore();

        } else if (choice == 4) {
            unsigned long long mob;
            cout << "Enter mobile number: ";
            if (cin >> mob) {
                for (const auto& s : students)
                    if (s.mob == mob) { print_student(s); found = true; }
            } else {
                cout << "Invalid input.\n";
                cin.clear();
            }
            cin.ignore();

        } else if (choice == 5) {
            string email;
            cout << "Enter email: ";
            getline(cin, email);
            for (const auto& s : students)
                if (s.email == email) { print_student(s); found = true; }

        } else if (choice == 6) {
            cout << "Thanks!\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }

        if (!found && choice >= 1 && choice <= 5)
            cout << "No record found.\n";
    }

    return 0;
}
