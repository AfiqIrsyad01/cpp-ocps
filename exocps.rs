use std::fs::{File, OpenOptions};
use std::io::{self, BufRead, BufReader, Write};
use std::path::Path;

const FILE_PATH: &str = "payments.txt";

fn print_menu() {
    println!(
        "
*********************************
*  Online College Payment System *
*********************************
1. Process Payment
2. Delete Payment
3. Edit Payment
4. Search Payment
5. Print All Payments
6. Exit"
    );
}

fn make_payment() -> io::Result<()> {
    println!("Enter Student ID:");
    let mut id = String::new();
    io::stdin().read_line(&mut id)?;

    println!("Enter Amount (RM):");
    let mut amount = String::new();
    io::stdin().read_line(&mut amount)?;

    let mut file = OpenOptions::new()
        .append(true)
        .create(true)
        .open(FILE_PATH)?;
    writeln!(file, "{},{}", id.trim(), amount.trim())?;
    println!("Payment saved!");
    Ok(())
}

fn delete_payment() -> io::Result<()> {
    println!("Enter Student ID to delete:");
    let mut target_id = String::new();
    io::stdin().read_line(&mut target_id)?;
    let target_id = target_id.trim();

    let file = File::open(FILE_PATH)?;
    let reader = BufReader::new(file);

    let mut lines = Vec::new();
    let mut found = false;

    for line in reader.lines() {
        let line = line?;
        if !line.starts_with(&format!("{},", target_id)) {
            lines.push(line);
        } else {
            found = true;
        }
    }

    if !found {
        println!("Payment not found!");
        return Ok(());
    }

    let mut file = File::create(FILE_PATH)?;
    for line in lines {
        writeln!(file, "{}", line)?;
    }
    println!("Payment deleted!");
    Ok(())
}

fn main() -> io::Result<()> {
    if !Path::new(FILE_PATH).exists() {
        File::create(FILE_PATH)?;
    }

    loop {
        print_menu();
        let mut choice = String::new();
        io::stdin().read_line(&mut choice)?;
        match choice.trim() {
            "1" => make_payment()?,
            "2" => delete_payment()?,
            "6" => std::process::exit(0),
            _ => println!("Invalid choice!"),
        }
    }
}