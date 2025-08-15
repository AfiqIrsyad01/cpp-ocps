const fs = require('fs');
const readline = require('readline');

// File operations
const FILE_PATH = 'payments.txt';

// Create file if missing
if (!fs.existsSync(FILE_PATH)) {
    fs.writeFileSync(FILE_PATH, '');
}

// Main menu
function displayMenu() {
    console.log(`
*****************************************************************
*             Online College Payment System                     *
*****************************************************************
*                                                               *
*        1 - Process a Payment                                  *
*        2 - Delete Payment                                     *
*        3 - Edit Payment                                       *
*        4 - Search Payment                                     *
*        5 - Print Payments                                     *
*        6 - Exit                                               *
*                                                               *
*****************************************************************`);
}

// Input helper
async function askQuestion(question) {
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout
    });
    return new Promise(resolve => {
        rl.question(question, answer => {
            rl.close();
            resolve(answer);
        });
    });
}

// CRUD operations
async function makePayment() {
    const studentId = await askQuestion('Enter Student ID: ');
    const amount = await askQuestion('Enter Payment Amount: RM');
    fs.appendFileSync(FILE_PATH, `${studentId},${amount}\n`);
    console.log('\nPayment processed successfully!\n');
}

function deletePayment(studentId) {
    const payments = fs.readFileSync(FILE_PATH, 'utf-8').split('\n');
    const newPayments = payments.filter(line => {
        const [id] = line.split(',');
        return id !== studentId;
    });
    fs.writeFileSync(FILE_PATH, newPayments.join('\n'));
    console.log('Payment deleted!');
}

// (Other functions: edit, search, print similar to above)

// Main loop
async function main() {
    while (true) {
        displayMenu();
        const choice = await askQuestion('Enter your choice: ');

        switch (choice) {
            case '1': await makePayment(); break;
            case '2': {
                const id = await askQuestion('Enter Student ID to delete: ');
                deletePayment(id);
                break;
            }
            // Add cases 3-6 similarly
            case '6': process.exit(0);
            default: console.log('Invalid choice!');
        }
    }
}

main();