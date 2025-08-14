import os
from datetime import datetime

class Payment:
    def __init__(self, student_id=0, amount=0):
        self.student_id = student_id
        self.amount = amount

def display_menu():
    print("*****************************************************************")
    print("*                                                               *")
    print("*             Online College Payment System                     *")
    print("*                                                               *")
    print("*****************************************************************")
    print("*                                                               *")
    print("*        1 - Process a Payment                           *")
    print("*        2 - Delete Payment                              *")
    print("*        3 - Edit Payment                                *")
    print("*        4 - Search Payment                              *")
    print("*        5 - Print Payments                              *")
    print("*        6 - Exit                                        *")
    print("*                                                               *")
    print("*****************************************************************\n")
    print("Enter your choice: ", end="")

def make_payment():
    payment = Payment()
    
    try:
        payment.student_id = int(input("Enter Student ID: "))
        payment.amount = int(input("Enter Payment Amount: RM"))
    except ValueError:
        print("Invalid input. Please enter numbers only.")
        return

    with open("payments.txt", "a") as file:
        file.write(f"{payment.student_id},{payment.amount}\n")
    
    print("\nPayment successfully processed.\n")

def delete_payment(student_id_to_delete):
    found = False
    temp_lines = []
    
    try:
        with open("payments.txt", "r") as file:
            lines = file.readlines()
        
        for line in lines:
            student_id = int(line.split(',')[0])
            if student_id != student_id_to_delete:
                temp_lines.append(line)
            else:
                found = True
        
        with open("payments.txt", "w") as file:
            file.writelines(temp_lines)
            
    except FileNotFoundError:
        print("No payments file found!")
        return
    
    if found:
        print("Payment deleted successfully!")
    else:
        print("Payment not found!")

def edit_payment(student_id_to_edit):
    found = False
    temp_lines = []
    
    try:
        with open("payments.txt", "r") as file:
            lines = file.readlines()
        
        for line in lines:
            parts = line.split(',')
            student_id = int(parts[0])
            
            if student_id == student_id_to_edit:
                found = True
                try:
                    new_amount = int(input(f"Enter New Amount for {student_id}: RM"))
                    temp_lines.append(f"{student_id},{new_amount}\n")
                except ValueError:
                    print("Invalid amount. Keeping original payment.")
                    temp_lines.append(line)
            else:
                temp_lines.append(line)
        
        with open("payments.txt", "w") as file:
            file.writelines(temp_lines)
            
    except FileNotFoundError:
        print("No payments file found!")
        return
    
    if found:
        print("Payment information successfully updated!")
    else:
        print("Payment not found!")

def search_payment(student_id_to_search):
    found = False
    
    try:
        with open("payments.txt", "r") as file:
            for line in file:
                parts = line.strip().split(',')
                student_id = int(parts[0])
                
                if student_id == student_id_to_search:
                    found = True
                    print(line.strip())
                    break
    except FileNotFoundError:
        print("No payments file found!")
        return
    
    if not found:
        print("Payment not found!")

def print_payments():
    num_payments = 0
    total_amount = 0
    
    try:
        with open("payments.txt", "r") as file:
            lines = file.readlines()
            
            if not lines:
                print("No payments found!")
                return
                
            print("\nAll Payments:")
            for line in lines:
                print(line.strip())
                parts = line.strip().split(',')
                amount = int(parts[1])
                num_payments += 1
                total_amount += amount
    except FileNotFoundError:
        print("No payments file found!")
        return
    
    average_payment = total_amount / num_payments if num_payments > 0 else 0
    now = datetime.now()
    
    print("\n*****************************************************************")
    print("*               Payment Overview                                *")
    print("*****************************************************************")
    print("*                                                               *")
    print(f"*        Total amount paid: RM{total_amount}                    *")
    print(f"*        Number of payments: {num_payments}                    *")
    print(f"*        Average payment: RM{average_payment:.2f}              *")
    print("*                                                               *")
    print(f"*        Time/Date: {now.strftime('%I:%M:%S %p %m/%d/%Y')}     *")
    print("*****************************************************************")
    print("*        THANK YOU FOR USING THE SERVICE                        *")
    print("*****************************************************************\n")

def main():
    # Create empty file if it doesn't exist
    if not os.path.exists("payments.txt"):
        open("payments.txt", "w").close()
    
    while True:
        display_menu()
        menu_choice = input().strip()
        
        if menu_choice == '1':
            make_payment()
        elif menu_choice == '2':
            try:
                student_id = int(input("Enter Student ID to delete: "))
                delete_payment(student_id)
            except ValueError:
                print("Invalid Student ID. Please enter a number.")
        elif menu_choice == '3':
            try:
                student_id = int(input("Enter Student ID to edit: "))
                edit_payment(student_id)
            except ValueError:
                print("Invalid Student ID. Please enter a number.")
        elif menu_choice == '4':
            try:
                student_id = int(input("Enter Student ID to search: "))
                search_payment(student_id)
            except ValueError:
                print("Invalid Student ID. Please enter a number.")
        elif menu_choice == '5':
            print_payments()
        elif menu_choice == '6':
            print("Exiting program...")
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
