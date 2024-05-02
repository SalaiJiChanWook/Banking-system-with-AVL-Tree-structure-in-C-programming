//
// Created by uchia on 4/23/2024.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define USERSIZE 10



// Structure to store transaction records
typedef struct TransactionRecord {
    double amount;
    time_t date_time;
    struct TransactionRecord *next;
} TransactionRecord;

// Structure to store user data
typedef struct User {
    int user_id;
    char user_name[30];
    char user_email[30];
    char user_pass[20];
    char phone_number[20];
    char address[50];
    int postal_code;
    double balance;
    TransactionRecord *transactions;
} User;

// AVL tree node
typedef struct AVLNode {
    User data;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// Function declarations
AVLNode* insertUser(AVLNode* node, User user);
AVLNode* deleteUser(AVLNode* node, int user_id);
AVLNode* findUser(AVLNode* node, int user_id);
void inOrderTraversal(AVLNode* node);
void preOrderTraversal(AVLNode* node);
void postOrderTraversal(AVLNode* node);
int height(AVLNode* N);
int max(int a, int b);
AVLNode* newNode(User user);
AVLNode* rightRotate(AVLNode* y);
AVLNode* leftRotate(AVLNode* x);
int getBalance(AVLNode* N);
AVLNode* minValueNode(AVLNode* node);
void recordTransaction(User *user, double amount, time_t date_time);
void transferMoney(AVLNode* root, int sender_id, int receiver_id, double amount);
void withdrawMoney(AVLNode* root, int user_id, double amount);
void depositMoney(AVLNode* root, int user_id, double amount);
void printUserTransactions(User user);
void saveDatabaseToFile(AVLNode* root, const char* filename);
void loadDatabaseFromFile(AVLNode** root, const char* filename);

// Implement the AVL tree functions and other utility functions here

int main() {
    AVLNode *root = NULL;
    // Load the database from file
    loadDatabaseFromFile(&root, "database.txt");

    // User interface and operations go here


    // Save the database to file
    saveDatabaseToFile(root, "database.txt");

    return 0;
}

// Implement the rest of the functions here