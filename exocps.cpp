#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

struct Payment {
    int studentID;
    int amount;
};

void displayMenu();
void makePayment(ofstream& outputFile);
void deletePayment(int studentIDToDelete, ifstream& inputFile, ofstream& tempFile);
void editPayment(int studentIDToEdit, ifstream& inputFile, ofstream& tempFile);
void searchPayment(int studentIDToSearch, ifstream& inputFile);
void printPayments(ifstream& inputFile);

int main() {
    const string FILENAME = "payments.txt";
    ofstream outputFile(FILENAME, ios::app);
    outputFile.close();

    char menuChoice;
    int studentID;

    do {
        displayMenu();
        cin >> menuChoice;

        switch (menuChoice) {
            case '1':
                makePayment(outputFile);
                break;

            case '2':
                cout << "Enter Student ID to delete : ";
                cin >> studentID;
                {
                    ifstream inputFile(FILENAME); // New instance of ifstream
                    ofstream tempFile("temp.txt");
                    deletePayment(studentID, inputFile, tempFile);
                }
                break;

            case '3':
                cout << "Enter Student ID to edit : ";
                cin >> studentID;
                {
                    ifstream inputFile(FILENAME); // New instance of ifstream
                    ofstream tempFile("temp.txt");
                    editPayment(studentID, inputFile, tempFile);
                }
                break;

            case '4':
                cout << "Enter Student ID to search : ";
                cin >> studentID;
                {
                    ifstream inputFile(FILENAME); // New instance of ifstream
                    searchPayment(studentID, inputFile);
                }
                break;

            case '5':
                {
                    ifstream inputFile(FILENAME); // New instance of ifstream
                    printPayments(inputFile);
                }
                break;

            case '6':
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (menuChoice != '6');

    return 0;
}


void displayMenu() {
    cout << "*****************************************************************" << endl;
    cout << "*                                                               *" << endl;
    cout << "*             Online College Payment System                     *" << endl;
    cout << "*                                                               *" << endl;
    cout << "*****************************************************************" << endl;
    cout << "*                                                               *" << endl;
    cout << "*        	1 - Process a Payment                           *" << endl;
    cout << "*        	2 - Delete Payment                              *" << endl;
    cout << "*        	3 - Edit Payment                                *" << endl;
    cout << "*        	4 - Search Payment                              *" << endl;
    cout << "*        	5 - Print Payments                              *" << endl;
    cout << "*        	6 - Exit                                        *" << endl;
    cout << "*                                                               *" << endl;
    cout << "*****************************************************************\n" << endl;
    cout << "Enter your choice : ";
}

void makePayment(ofstream& outputFile) {
    Payment payment;

    cout << "Enter Student ID : ";
    cin >> payment.studentID;

    cout << "Enter Payment Amount : RM";
    cin >> payment.amount;

    outputFile.open("payments.txt", ios::app);
    outputFile << payment.studentID << ',' << payment.amount << endl;
    outputFile.close();

    cout << "\nPayment successfully processed.\n" << endl;
}

void deletePayment(int studentIDToDelete, ifstream& inputFile, ofstream& tempFile) {
    string line;
    bool found = false;

    while (getline(inputFile, line)) {
        size_t pos = line.find(',');

        int studentID = stoi(line.substr(0, pos));

        if (studentID != studentIDToDelete) {
            tempFile << line << endl;
        } else {
            found = true;
        }
    }

    inputFile.close();
    tempFile.close();

    remove("payments.txt");
    rename("temp.txt", "payments.txt");

    if (found) {
        cout << "Payment deleted successfully !" << endl;
    } else {
        cout << "Payment not found !" << endl;
    }
}

void editPayment(int studentIDToEdit, ifstream& inputFile, ofstream& tempFile) {
    string line;
    bool found = false;

    while (getline(inputFile, line)) {
        size_t pos = line.find(',');

        int studentID = stoi(line.substr(0, pos));

        if (studentID == studentIDToEdit) {
            found = true;
            int newAmount;

            cout << "Enter New Amount for  " << studentID << ": RM";
            cin >> newAmount;

            tempFile << studentID << ',' << newAmount << endl;
        } else {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    remove("payments.txt");
    rename("temp.txt", "payments.txt");

    if (found) {
        cout << "Payment information successfully updated !" << endl;
    } else {
        cout << "Payment not found !" << endl;
    }
}

void searchPayment(int studentIDToSearch, ifstream& inputFile) {
    string line;
    bool found = false;

    while (getline(inputFile, line)) {
        size_t pos = line.find(',');

        int studentID = stoi(line.substr(0, pos));

        if (studentID == studentIDToSearch) {
            found = true;
            cout << line << endl;
            break;
        }
    }

    if (!found) {
        cout << "Payment not found !" << endl;
    }
}

void printPayments(ifstream& inputFile) {
    string line;
    int numPayments = 0;
    int totalAmount = 0;

    while (getline(inputFile, line)) {
        cout << line << endl;

        size_t pos = line.find(',');
        int amount = stoi(line.substr(pos + 1));

        numPayments++;
        totalAmount += amount;
    }

    double averagePayment = 0;

    if (numPayments > 0) {
        averagePayment = static_cast<double>(totalAmount) / numPayments;
    }

    time_t now = time(0);
    tm* tm_now = localtime(&now);

    int hour = tm_now->tm_hour % 12;
    if (hour == 0) {
        hour = 12;
    }

    cout << "\n*****************************************************************" << endl;
    cout << "*		Payment Overview		 	        *" << endl;
    cout << "*****************************************************************" << endl;
    cout << "*								*" << endl;
    cout << "*		Total amount paid : RM" << totalAmount << "			*" << endl;
    cout << "*		Number of payments : " << numPayments << "				*" << endl;
    cout << "*								*" << endl;
    cout << "*		Time/Date : " << hour << ":" << tm_now->tm_min << ":" << tm_now->tm_sec << " " << tm_now->tm_mon + 1 << "/" << tm_now->tm_mday << "/" << tm_now->tm_year + 1900 << "			*" << endl;
    cout << "*****************************************************************" << endl;
    cout << "*		THANK YOU FOR USING THE SERVICE 	        *" << endl;
    cout << "*****************************************************************\n" << endl;
}

