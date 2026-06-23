#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Abstraction
class ExpenseBase {
public:
    virtual void display() const = 0;     
    virtual void saveToFile(ofstream &out) const = 0;
    virtual ~ExpenseBase() {} 
};

class Expense : public ExpenseBase {
private:
    string category;
    double amount;
    string date;
    string description;

public:
    Expense(string c, double a, string d, string desc)
        : category(c), amount(a), date(d), description(desc) {}

    // Encapsulation
    string getCategory() const { return category; }
    double getAmount() const { return amount; }
    string getDate() const { return date; }
    string getDescription() const { return description; }

    void setAmount(double a) { amount = a; }
    void setCategory(string c) { category = c; }

    // Polymorphic Behavior
    void display() const override {
        cout << left << setw(15) << category
             << setw(10) << amount
             << setw(15) << date
             << setw(25) << description << endl;
    }

    void saveToFile(ofstream &out) const override {
        out << category << "," << amount << "," << date << "," << description << "\n";
    }
};

class ExpenseManager {
private:
    vector<Expense*> expenses;
    double budget;

public:
    ExpenseManager() : budget(0.0) {}

    ~ExpenseManager() {
        for (auto e : expenses)
            delete e;
    }

    void addExpense() {
        string cat, date, desc;
        double amt;
        cout << "Enter category: ";
        cin >> cat;
        cout << "Enter amount: ";
        cin >> amt;
        cout << "Enter date (dd-mm-yyyy): ";
        cin >> date;
        cin.ignore();
        cout << "Enter description: ";
        getline(cin, desc);

        Expense* e = new Expense(cat, amt, date, desc);
        expenses.push_back(e);

        cout << "\nExpense added successfully!\n";
        checkBudgetAlert();
    }

    void displayExpenses() const {
        if (expenses.empty()) {
            cout << "\nNo expenses recorded yet.\n";
            return;
        }

        cout << "\n------------ Expense List ------------\n";
        cout << left << setw(15) << "Category" 
             << setw(10) << "Amount" 
             << setw(15) << "Date" 
             << setw(25) << "Description" << endl;
        cout << "--------------------------------------\n";

        for (auto e : expenses)
            e->display();
    }

    // Files
    void saveExpensesToFile(const string &filename) const {
        ofstream out(filename);
        for (auto e : expenses)
            e->saveToFile(out);
    }

    void loadExpensesFromFile(const string &filename) {
        ifstream in(filename);
        if (!in)
            return;

        string cat, date, desc, amtStr;
        double amt;
        while (getline(in, cat, ',')) {
            getline(in, amtStr, ',');
            amt = stod(amtStr);
            getline(in, date, ',');
            getline(in, desc);
            Expense* e = new Expense(cat, amt, date, desc);
            expenses.push_back(e);
        }
    }

    void setBudget(double b) { budget = b; }
    double getBudget() const { return budget; }

    double getTotalExpense() const {
        double total = 0;
        for (auto e : expenses)
            total += e->getAmount();
        return total;
    }

    double getRemainingBudget() const {
        return budget - getTotalExpense();
    }

    void checkBudgetAlert() const {
        double total = getTotalExpense();
        if (budget > 0 && total > budget)
            cout << "\nAlert! You have exceeded your budget by Rs. "
                 << total - budget << "!\n";
    }

    void saveBudgetToFile(const string &file) const {
        ofstream out(file);
        out << budget;
    }

    void loadBudgetFromFile(const string &file) {
        ifstream in(file);
        if (in)
            in >> budget;
    }
};

int main() {
    ExpenseManager manager;
    manager.loadExpensesFromFile("expenses.txt");
    manager.loadBudgetFromFile("budget.txt");

    int choice;
    double newBudget;

    do {
        cout << "\n==== PERSONAL EXPENSE TRACKER ====\n";
        cout << "1. Add Expense\n";
        cout << "2. View All Expenses\n";
        cout << "3. View Total & Remaining Balance\n";
        cout << "4. Set/Update Budget\n";
        cout << "5. Save & Exit\n";
        cout << "----------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addExpense();
                break;

            case 2:
                manager.displayExpenses();
                break;

            case 3: {
                double total = manager.getTotalExpense();
                double budget = manager.getBudget();
                cout << "\nTotal Expense: Rs." << total << endl;
                if (budget > 0)
                    cout << "Budget: Rs." << budget << "\nRemaining: Rs." 
                         << manager.getRemainingBudget() << endl;
                else
                    cout << "No budget set yet.\n";
                manager.checkBudgetAlert();
                break;
            }

            case 4:
                cout << "Enter new monthly budget: ";
                cin >> newBudget;
                manager.setBudget(newBudget);
                manager.saveBudgetToFile("budget.txt");
                cout << "Budget updated successfully!\n";
                break;

            case 5:
                manager.saveExpensesToFile("expenses.txt");
                manager.saveBudgetToFile("budget.txt");
                cout << "\nData saved. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
