//
// Created by uchia on 4/26/2024.
//

#ifndef FINAL_ASS_CHINLAND_BANKING_SYSTEM_H
#define FINAL_ASS_CHINLAND_BANKING_SYSTEM_H

//Import Header files
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "processenv.h"
#define USERSIZE  1000

//Global variables declares
int g_userCount=0; // how many users
int g_login_check=-1;


struct to_record{
    char trans_record[200];
};



// Structure for an AVL tree node
typedef struct Database {
    int accountNumber;
    char name[30];
    char email[30];
    char phone[13];
    char password[20];
    char address[50];
    double balance;
    int postal_code;
    int trans_counter;
    int height;
    struct Database* left;
    struct Database* right;
    struct to_record trans[100];

} Database;

Database data[USERSIZE];

Database* root ;

// Function to get the height of a node
int getHeight(Database* Database) {
    if (Database == NULL)
        return 0;
    return Database->height;
}

// Function prototypes
Database* insertAccount(Database* Database, int accountNumber, char name[],char email[], char phone[], char password[],char address[] ,double balance, int postal_code,int trans_counter);

// Function to get the height of the tree
int height(Database *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Function to get the maximum of two integers
//int max(int a, int b) {
//    return (a > b) ? a : b;
//}

// Function to create a new node
Database* createNode(int accountNumber, char name[], char email[],char phone[], char password[] ,char address[] ,double balance, int postal_code,int trans_counter) {
    struct Database* newDatabase = (struct Database*)malloc(sizeof(struct Database));
    newDatabase->accountNumber = accountNumber;
    strcpy(newDatabase->name, name);
    strcpy(newDatabase->email, email);
    strcpy(newDatabase->phone, phone);
    strcpy(newDatabase->password, password);
    strcpy(newDatabase->address, address);
    newDatabase->balance = balance;
    newDatabase->postal_code = postal_code;
    newDatabase->trans_counter = trans_counter;
    newDatabase->left = NULL;
    newDatabase->right = NULL;
    newDatabase->height = 1;

    return newDatabase;
}

// Function to rotate the tree left
Database *rotateLeft(Database* Database) {
    struct Database* newRoot = Database->right;
    struct Database* temp = newRoot->left;

    newRoot->left = Database;
    Database->right = temp;

    Database->height = 1 + max(getHeight(Database->left), getHeight(Database->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

// Function to rotate the tree right
Database  *rotateRight(Database* Database) {
    struct Database* newRoot = Database->left;
    struct Database* temp = newRoot->right;

    newRoot->right = Database;
    Database->left = temp;

    Database->height = 1 + max(getHeight(Database->left), getHeight(Database->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

// Function to get the balance factor of a node
int getBalanceFactor(Database* Database) {
    if (Database == NULL)
        return 0;
    return getHeight(Database->left) - getHeight(Database->right);
}

// Function to insert a new account into the AVL tree
Database* insertAccount(Database* Database, int accountNumber, char name[],char email[], char phone[], char password[],char address[] ,double balance, int postal_code,int trans_counter) {
    // Perform normal BST insertion
    if (Database == NULL)
        return createNode(accountNumber, name,email,phone,password,address, balance, postal_code,trans_counter);

    if (accountNumber < Database->accountNumber)
        Database->left = insertAccount(Database->left, accountNumber, name,email,phone,password,address, balance, postal_code,trans_counter);
    else if (accountNumber > Database->accountNumber)
        Database->right = insertAccount(Database->right, accountNumber, name,email,phone,password,address, balance, postal_code,trans_counter);
    else // Account already exists
        return Database;

    // Update the height of the ancestor node
    Database->height = 1 + max(getHeight(Database->left), getHeight(Database->right));

    //  Find the balance factor
    int balanceFactor = getBalanceFactor(Database);

    // Left Left Case
    if (balanceFactor > 1 && accountNumber < Database->left->accountNumber)
        return rotateRight(Database);

    // Right Right Case
    if (balanceFactor < -1 && accountNumber > Database->right->accountNumber)
        return rotateLeft(Database);

    // Left Right Case
    if (balanceFactor > 1 && accountNumber > Database->left->accountNumber) {
        Database->left = rotateLeft(Database->left);
        return rotateRight(Database);
    }

    // Right Left Case
    if (balanceFactor < -1 && accountNumber < Database->right->accountNumber) {
        Database->right = rotateRight(Database->right);
        return rotateLeft(Database);
    }

    return Database;
}

// Function to search for an account in the AVL tree
Database* searchAccount(Database* Database, int accountNumber) {
    if (Database == NULL || Database->accountNumber == accountNumber)
        return Database;

    if (accountNumber < Database->accountNumber)
        return searchAccount(Database->left, accountNumber);
    else
        return searchAccount(Database->right, accountNumber);
}

// Function to deposit money into an account
void depositMoney(Database* Database, int accountNumber, double amount) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    struct Database* account = searchAccount(Database, accountNumber);
    if (account != NULL) {
        account->balance += amount;
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        printf("%s was Deposited successful. New balance: %.2f\n", account->name , account->balance);
    } else {
        printf("Account not found.\n");
    }
}

// Function to withdraw money from an account
void withdrawMoney(Database* Database, int accountNumber, double amount) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    struct Database* account = searchAccount(Database, accountNumber);
    if (account != NULL) {
        if (account->balance >= amount) {
            account->balance -= amount;
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            printf("%s was used Withdrawal successful.\n New balance: %.2f\n",account->name, account->balance);
        } else {
            printf("Insufficient balance.\n");
        }
    } else {
        printf("\n Account not found.\n");
    }
}



// Function to display account details
void displayAccount(Database* account) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (account != NULL) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("Account Number: %d\n", account->accountNumber);
        printf("Name: %s\n", account->name);
        printf("Balance: %.2f\n", account->balance);
        printf("Phone Number: %s\n", account->phone);
        printf("Password: %s\n", account->password);
        printf("Postal_code: %d\n", account->postal_code);
        printf("Address: %s\n", account->address);
    } else {
        printf("Account not found.\n");
    }
}


#endif //FINAL_ASS_CHINLAND_BANKING_SYSTEM_H
