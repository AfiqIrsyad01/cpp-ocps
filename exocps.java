import java.io.*;
import java.util.*;

public class Main {
    private static final String FILE_PATH = "payments.txt";

    private static void printMenu() {
        System.out.println("""
            *********************************
            *  Online College Payment System *
            *********************************
            1. Process Payment
            2. Delete Payment
            3. Edit Payment
            4. Search Payment
            5. Print All Payments
            6. Exit
            """);
    }

    private static void makePayment(Scanner sc) throws IOException {
        System.out.print("Enter Student ID: ");
        String id = sc.nextLine();
        System.out.print("Enter Amount: RM");
        String amount = sc.nextLine();
        
        try (FileWriter fw = new FileWriter(FILE_PATH, true)) {
            fw.write(id + "," + amount + "\n");
            System.out.println("Payment saved!");
        }
    }

    private static void deletePayment(Scanner sc) throws IOException {
        System.out.print("Enter Student ID to delete: ");
        String targetId = sc.nextLine();
        
        List<String> lines = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(FILE_PATH))) {
            String line;
            while ((line = br.readLine()) != null) {
                if (!line.startsWith(targetId + ",")) {
                    lines.add(line);
                }
            }
        }
        
        try (FileWriter fw = new FileWriter(FILE_PATH)) {
            for (String line : lines) {
                fw.write(line + "\n");
            }
        }
        System.out.println("Payment deleted!");
    }

    public static void main(String[] args) throws IOException {
        new File(FILE_PATH).createNewFile(); // Create if not exists
        Scanner sc = new Scanner(System.in);
        
        while (true) {
            printMenu();
            String choice = sc.nextLine();
            switch (choice) {
                case "1" -> makePayment(sc);
                case "2" -> deletePayment(sc);
                case "6" -> System.exit(0);
                default -> System.out.println("Invalid choice!");
            }
        }
    }
}