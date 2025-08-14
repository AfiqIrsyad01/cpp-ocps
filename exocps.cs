using System;
using System.Collections.Generic;
using System.IO;

namespace PaymentSystem
{
    public class Payment
    {
        public int StudentId { get; set; }
        public int Amount { get; set; }

        public override string ToString() => $"{StudentId},{Amount}";
    }

    class Program
    {
        private const string FilePath = "payments.txt";

        static void Main()
        {
            if (!File.Exists(FilePath))
                File.Create(FilePath).Close();

            while (true)
            {
                DisplayMenu();
                string choice = Console.ReadLine();

                switch (choice)
                {
                    case "1":
                        MakePayment();
                        break;

                    case "2":
                        Console.Write("Enter Student ID to delete: ");
                        if (int.TryParse(Console.ReadLine(), out int idToDelete))
                            DeletePayment(idToDelete);
                        else
                            Console.WriteLine("Invalid ID!");
                        break;

                    case "3":
                        Console.Write("Enter Student ID to edit: ");
                        if (int.TryParse(Console.ReadLine(), out int idToEdit))
                            EditPayment(idToEdit);
                        else
                            Console.WriteLine("Invalid ID!");
                        break;

                    case "4":
                        Console.Write("Enter Student ID to search: ");
                        if (int.TryParse(Console.ReadLine(), out int idToSearch))
                            SearchPayment(idToSearch);
                        else
                            Console.WriteLine("Invalid ID!");
                        break;

                    case "5":
                        PrintPayments();
                        break;

                    case "6":
                        Console.WriteLine("Exiting...");
                        return;

                    default:
                        Console.WriteLine("Invalid choice!");
                        break;
                }
            }
        }

        static void DisplayMenu()
        {
            Console.WriteLine("*****************************************************************");
            Console.WriteLine("*             Online College Payment System                     *");
            Console.WriteLine("*****************************************************************");
            Console.WriteLine("*                                                               *");
            Console.WriteLine("*        1 - Process a Payment                                  *");
            Console.WriteLine("*        2 - Delete Payment                                     *");
            Console.WriteLine("*        3 - Edit Payment                                       *");
            Console.WriteLine("*        4 - Search Payment                                     *");
            Console.WriteLine("*        5 - Print Payments                                     *");
            Console.WriteLine("*        6 - Exit                                               *");
            Console.WriteLine("*                                                               *");
            Console.WriteLine("*****************************************************************");
            Console.Write("Enter your choice: ");
        }

        static void MakePayment()
        {
            var payment = new Payment();

            Console.Write("Enter Student ID: ");
            string studentIdInput = Console.ReadLine();
            if (!int.TryParse(studentIdInput, out int studentId))
            {
                Console.WriteLine("Invalid ID!");
                return;
            }
            payment.StudentId = studentId;

            Console.Write("Enter Payment Amount: RM");
            string amountInput = Console.ReadLine();
            if (!int.TryParse(amountInput, out int amount))
            {
                Console.WriteLine("Invalid amount!");
                return;
            }
            payment.Amount = amount;

            File.AppendAllText(FilePath, payment + Environment.NewLine);
            Console.WriteLine("\nPayment successfully processed.\n");
        }

        static void DeletePayment(int studentId)
        {
            var lines = File.ReadAllLines(FilePath);
            var newLines = new List<string>();
            bool found = false;

            foreach (var line in lines)
            {
                var parts = line.Split(',');
                if (parts.Length == 2 && int.Parse(parts[0]) != studentId)
                    newLines.Add(line);
                else
                    found = true;
            }

            File.WriteAllLines(FilePath, newLines);
            Console.WriteLine(found ? "Payment deleted successfully!" : "Payment not found!");
        }

        static void EditPayment(int studentId)
        {
            var lines = File.ReadAllLines(FilePath);
            bool found = false;

            for (int i = 0; i < lines.Length; i++)
            {
                var parts = lines[i].Split(',');
                if (parts.Length == 2 && int.Parse(parts[0]) == studentId)
                {
                    Console.Write($"Enter new amount for {studentId}: RM");
                    if (int.TryParse(Console.ReadLine(), out int newAmount))
                    {
                        lines[i] = $"{studentId},{newAmount}";
                        found = true;
                    }
                    else
                    {
                        Console.WriteLine("Invalid amount!");
                    }
                }
            }

            File.WriteAllLines(FilePath, lines);
            Console.WriteLine(found ? "Payment updated successfully!" : "Payment not found!");
        }

        static void SearchPayment(int studentId)
        {
            var lines = File.ReadAllLines(FilePath);
            bool found = false;

            foreach (var line in lines)
            {
                var parts = line.Split(',');
                if (parts.Length == 2 && int.Parse(parts[0]) == studentId)
                {
                    Console.WriteLine(line);
                    found = true;
                    break;
                }
            }

            if (!found)
                Console.WriteLine("Payment not found!");
        }

        static void PrintPayments()
        {
            var lines = File.ReadAllLines(FilePath);
            int totalAmount = 0;
            int numPayments = 0;

            Console.WriteLine("\nAll Payments:");
            foreach (var line in lines)
            {
                Console.WriteLine(line);
                var parts = line.Split(',');
                if (parts.Length == 2)
                {
                    totalAmount += int.Parse(parts[1]);
                    numPayments++;
                }
            }

            double avgPayment = numPayments > 0 ? (double)totalAmount / numPayments : 0;
            var now = DateTime.Now;

            Console.WriteLine("\n*****************************************************************");
            Console.WriteLine("*               Payment Overview                                *");
            Console.WriteLine("*****************************************************************");
            Console.WriteLine("*                                                               *");
            Console.WriteLine($"*        Total amount paid: RM{totalAmount}                    *");
            Console.WriteLine($"*        Number of payments: {numPayments}                     *");
            Console.WriteLine($"*        Average payment: RM{avgPayment:F2}                    *");
            Console.WriteLine("*                                                               *");
            Console.WriteLine($"*        Time/Date: {now:hh:mm:ss tt MM/dd/yyyy}               *");
            Console.WriteLine("*****************************************************************");
            Console.WriteLine("*        THANK YOU FOR USING THE SERVICE                        *");
            Console.WriteLine("*****************************************************************\n");
        }
    }
}