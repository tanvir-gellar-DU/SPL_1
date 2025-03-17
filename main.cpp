#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ANSI escape codes for colors and styles
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"

void displayMenu() {
    cout << BOLD << CYAN << "====================================" << RESET << endl;
    cout << BOLD << MAGENTA << "          AST Builder: C edition    " << RESET << endl;
    cout << BOLD << CYAN << "====================================" << RESET << endl;
    cout << BOLD << GREEN << "1. Tokenize C Source Code" << RESET << endl;
    cout << BOLD << YELLOW << "2. Generate Abstract Syntax Tree (AST)" << RESET << endl;
    cout << BOLD << RED << "3. Exit" << RESET << endl;
    cout << BOLD << CYAN << "====================================" << RESET << endl;
}

// Function to display the contents of TOKENS.txt
void displayTokens() {
    ifstream tokensFile("TOKENS.txt");
    if (!tokensFile.is_open()) {
        cout << BOLD << RED << "Error: Unable to open TOKENS.txt!" << RESET << endl;
        return;
    }

    cout << BOLD << BLUE << "Contents of TOKENS.txt:" << RESET << endl;
    cout << BOLD << CYAN << "-----------------------" << RESET << endl;

    string line;
    while (getline(tokensFile, line)) {
        cout << line << endl;
    }

    tokensFile.close();
    cout << BOLD << CYAN << "-----------------------" << RESET << endl;
}

void handleUserInput(int choice) {
    switch (choice) {
        case 1:
            cout << BOLD << BLUE << "Running Tokenization..." << RESET << endl;
            system("./tokenizer");
            cout << BOLD << GREEN << "Tokenization completed successfully!" << RESET << endl;
            displayTokens(); // Display the contents of TOKENS.txt
            break;
        case 2:
            cout << BOLD << BLUE << "Generating AST..." << RESET << endl;
            system("./ast");
            break;
        case 3:
            cout << BOLD << RED << "Exiting the program. Goodbye!" << RESET << endl;
            break;
        default:
            cout << BOLD << RED << "Invalid choice. Please try again." << RESET << endl;
            break;
    }
}

int main() {
    int choice;
    do {
        displayMenu();
        cout << BOLD << CYAN << "Enter your choice: " << RESET;
        cin >> choice;
        handleUserInput(choice);
    } while (choice != 3);

    return 0;
}
