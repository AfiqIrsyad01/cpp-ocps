import java.io.File
import kotlin.system.exitProcess

const val FILE_PATH = "payments.txt"

fun printMenu() {
    println(
        """
        *********************************
        *  Online College Payment System *
        *********************************
        1. Process Payment
        2. Delete Payment
        3. Edit Payment
        4. Search Payment
        5. Print All Payments
        6. Exit
    """.trimIndent()
    )
}

fun makePayment() {
    print("Enter Student ID: ")
    val id = readLine()!!
    print("Enter Amount: RM")
    val amount = readLine()!!
    
    File(FILE_PATH).appendText("$id,$amount\n")
    println("Payment saved!")
}

fun deletePayment() {
    print("Enter Student ID to delete: ")
    val targetId = readLine()!!
    
    val lines = File(FILE_PATH).readLines()
        .filterNot { it.startsWith("$targetId,") }
    
    File(FILE_PATH).writeText(lines.joinToString("\n"))
    println("Payment deleted!")
}

fun main() {
    File(FILE_PATH).apply { if (!exists()) createNewFile() }
    
    while (true) {
        printMenu()
        when (readLine()) {
            "1" -> makePayment()
            "2" -> deletePayment()
            "6" -> exitProcess(0)
            else -> println("Invalid choice!")
        }
    }
}