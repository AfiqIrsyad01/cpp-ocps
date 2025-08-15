package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"strconv"
)

const filePath = "payments.txt"

func printMenu() {
	fmt.Println(`
*********************************
*  Online College Payment System *
*********************************
1. Process Payment
2. Delete Payment
3. Edit Payment
4. Search Payment
5. Print All Payments
6. Exit`)
}

func makePayment(scanner *bufio.Scanner) {
	fmt.Print("Enter Student ID: ")
	scanner.Scan()
	id := scanner.Text()

	fmt.Print("Enter Amount: RM")
	scanner.Scan()
	amount := scanner.Text()

	file, _ := os.OpenFile(filePath, os.O_APPEND|os.O_WRONLY|os.O_CREATE, 0644)
	defer file.Close()
	fmt.Fprintf(file, "%s,%s\n", id, amount)
	fmt.Println("Payment saved!")
}

func deletePayment(scanner *bufio.Scanner) {
	fmt.Print("Enter Student ID to delete: ")
	scanner.Scan()
	targetID := scanner.Text()

	file, _ := os.Open(filePath)
	defer file.Close()

	var lines []string
	scannerFile := bufio.NewScanner(file)
	for scannerFile.Scan() {
		line := scannerFile.Text()
		if !strings.HasPrefix(line, targetID+",") {
			lines = append(lines, line)
		}
	}

	file, _ = os.Create(filePath)
	defer file.Close()
	for _, line := range lines {
		fmt.Fprintln(file, line)
	}
	fmt.Println("Payment deleted!")
}

func editPayment(scanner *bufio.Scanner) {
	fmt.Print("Enter Student ID to edit: ")
	scanner.Scan()
	targetID := scanner.Text()

	file, _ := os.Open(filePath)
	defer file.Close()

	var lines []string
	scannerFile := bufio.NewScanner(file)
	found := false

	for scannerFile.Scan() {
		line := scannerFile.Text()
		parts := strings.Split(line, ",")
		if parts[0] == targetID {
			fmt.Printf("Current amount: RM%s\n", parts[1])
			fmt.Print("Enter new amount: RM")
			scanner.Scan()
			newAmount := scanner.Text()
			lines = append(lines, fmt.Sprintf("%s,%s", targetID, newAmount))
			found = true
		} else {
			lines = append(lines, line)
		}
	}

	if !found {
		fmt.Println("Payment not found!")
		return
	}

	file, _ = os.Create(filePath)
	defer file.Close()
	for _, line := range lines {
		fmt.Fprintln(file, line)
	}
	fmt.Println("Payment updated!")
}

func searchPayment(scanner *bufio.Scanner) {
	fmt.Print("Enter Student ID to search: ")
	scanner.Scan()
	targetID := scanner.Text()

	file, _ := os.Open(filePath)
	defer file.Close()

	scannerFile := bufio.NewScanner(file)
	found := false

	for scannerFile.Scan() {
		line := scannerFile.Text()
		if strings.HasPrefix(line, targetID+",") {
			fmt.Println("Payment found:", line)
			found = true
			break
		}
	}

	if !found {
		fmt.Println("Payment not found!")
	}
}

func printPayments() {
	file, _ := os.Open(filePath)
	defer file.Close()

	scanner := bufio.NewScanner(file)
	total := 0
	count := 0

	fmt.Println("\nAll Payments:")
	for scanner.Scan() {
		line := scanner.Text()
		fmt.Println(line)
		parts := strings.Split(line, ",")
		if len(parts) == 2 {
			total += func() int { i, _ := strconv.Atoi(parts[1]); return i }()
			count++
		}
	}

	fmt.Printf("\nTotal payments: %d\n", count)
	fmt.Printf("Total amount: RM%d\n", total)
	if count > 0 {
		fmt.Printf("Average payment: RM%.2f\n", float64(total)/float64(count))
	}
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	for {
		printMenu()
		scanner.Scan()
		choice := scanner.Text()
		switch choice {
		case "1":
			makePayment(scanner)
		case "2":
			deletePayment(scanner)
		case "3":
			editPayment(scanner)
		case "4":
			searchPayment(scanner)
		case "5":
			printPayments()
		case "6":
			os.Exit(0)
		default:
			fmt.Println("Invalid choice!")
		}
	}
}