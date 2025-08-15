#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILENAME "payments.txt"
#define MAX_LINE_LENGTH 100

typedef struct {
    int studentID;
    int amount;
} Payment;

void displayMenu();
void makePayment();
void deletePayment(int studentIDToDelete);
void editPayment(int studentIDToEdit);
void searchPayment(int studentIDToSearch);
void printPayments();
int getIntInput(const char* prompt);

int main() {
    // Create file if it doesn't exist
    FILE* file = fopen(FILENAME, "a");
    if (file) fclose(file);
    
    int running = 1;
    while (running) {
        displayMenu();
        char choice = getchar();
        while (getchar() != '\n'); // Clear input buffer
        
        switch (choice) {
            case '1':
                makePayment();
                break;
                
            case '2': {
                int id = getIntInput("Enter Student ID to delete: ");
                if (id != -1) deletePayment(id);
                break;
            }
                
            case '3': {
                int id = getIntInput("Enter Student ID to edit: ");
                if (id != -1) editPayment(id);
                break;
            }
                
            case '4': {
                int id = getIntInput("Enter Student ID to search: ");
                if (id != -1) searchPayment(id);
                break;
            }
                
            case '5':
                printPayments();
                break;
                
            case '6':
                running = 0;
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice!\n");
                break;
        }
    }
    
    return 0;
}

void displayMenu() {
    printf("*****************************************************************\n");
    printf("*             Online College Payment System                     *\n");
    printf("*****************************************************************\n");
    printf("*                                                               *\n");
    printf("*        1 - Process a Payment                                  *\n");
    printf("*        2 - Delete Payment                                     *\n");
    printf("*        3 - Edit Payment                                       *\n");
    printf("*        4 - Search Payment                                     *\n");
    printf("*        5 - Print Payments                                     *\n");
    printf("*        6 - Exit                                               *\n");
    printf("*                                                               *\n");
    printf("*****************************************************************\n");
    printf("Enter your choice: ");
}

int getIntInput(const char* prompt) {
    printf("%s", prompt);
    int value;
    if (scanf("%d", &value) != 1) {
        printf("Invalid input! Please enter a number.\n");
        while (getchar() != '\n'); // Clear invalid input
        return -1;
    }
    while (getchar() != '\n'); // Clear the newline
    return value;
}

void makePayment() {
    Payment p;
    
    p.studentID = getIntInput("Enter Student ID: ");
    if (p.studentID == -1) return;
    
    p.amount = getIntInput("Enter Payment Amount: RM");
    if (p.amount == -1) return;
    
    FILE* file = fopen(FILENAME, "a");
    if (!file) {
        perror("Error opening file");
        return;
    }
    
    fprintf(file, "%d,%d\n", p.studentID, p.amount);
    fclose(file);
    
    printf("\nPayment successfully processed.\n\n");
}

void deletePayment(int studentIDToDelete) {
    FILE* file = fopen(FILENAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    
    FILE* temp = fopen("temp.txt", "w");
    if (!temp) {
        fclose(file);
        perror("Error creating temp file");
        return;
    }
    
    char line[MAX_LINE_LENGTH];
    int found = 0;
    
    while (fgets(line, sizeof(line), file)) {
        int studentID;
        if (sscanf(line, "%d,", &studentID) == 1) {
            if (studentID != studentIDToDelete) {
                fputs(line, temp);
            } else {
                found = 1;
            }
        }
    }
    
    fclose(file);
    fclose(temp);
    
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    
    printf(found ? "Payment deleted successfully!\n" : "Payment not found!\n");
}

void editPayment(int studentIDToEdit) {
    FILE* file = fopen(FILENAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    
    FILE* temp = fopen("temp.txt", "w");
    if (!temp) {
        fclose(file);
        perror("Error creating temp file");
        return;
    }
    
    char line[MAX_LINE_LENGTH];
    int found = 0;
    
    while (fgets(line, sizeof(line), file)) {
        int studentID, amount;
        if (sscanf(line, "%d,%d", &studentID, &amount) == 2) {
            if (studentID == studentIDToEdit) {
                printf("Enter new amount for %d: RM", studentID);
                if (scanf("%d", &amount) != 1) {
                    printf("Invalid amount!\n");
                    fputs(line, temp); // Keep original
                } else {
                    fprintf(temp, "%d,%d\n", studentID, amount);
                    found = 1;
                }
                while (getchar() != '\n'); // Clear input
            } else {
                fputs(line, temp);
            }
        }
    }
    
    fclose(file);
    fclose(temp);
    
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    
    printf(found ? "Payment updated successfully!\n" : "Payment not found!\n");
}

void searchPayment(int studentIDToSearch) {
    FILE* file = fopen(FILENAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    
    char line[MAX_LINE_LENGTH];
    int found = 0;
    
    while (fgets(line, sizeof(line), file)) {
        int studentID;
        if (sscanf(line, "%d,", &studentID) == 1) {
            if (studentID == studentIDToSearch) {
                printf("%s", line);
                found = 1;
                break;
            }
        }
    }
    
    fclose(file);
    
    if (!found) {
        printf("Payment not found!\n");
    }
}

void printPayments() {
    FILE* file = fopen(FILENAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    
    char line[MAX_LINE_LENGTH];
    int totalAmount = 0, numPayments = 0;
    
    printf("\nAll Payments:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        
        int amount;
        if (sscanf(line, "%*d,%d", &amount) == 1) {
            totalAmount += amount;
            numPayments++;
        }
    }
    
    fclose(file);
    
    double average = numPayments ? (double)totalAmount / numPayments : 0;
    time_t now = time(NULL);
    struct tm* tm = localtime(&now);
    
    printf("\n*****************************************************************\n");
    printf("*               Payment Overview                                *\n");
    printf("*****************************************************************\n");
    printf("*                                                               *\n");
    printf("*        Total amount paid: RM%-10d                    *\n", totalAmount);
    printf("*        Number of payments: %-10d                     *\n", numPayments);
    printf("*        Average payment: RM%-10.2f                    *\n", average);
    printf("*                                                               *\n");
    printf("*        Time/Date: %02d:%02d:%02d %02d/%02d/%04d               *\n",
           tm->tm_hour, tm->tm_min, tm->tm_sec,
           tm->tm_mon + 1, tm->tm_mday, tm->tm_year + 1900);
    printf("*****************************************************************\n");
    printf("*        THANK YOU FOR USING THE SERVICE                        *\n");
    printf("*****************************************************************\n\n");
}