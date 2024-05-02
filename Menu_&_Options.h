//
// Created by uchia on 4/26/2024.
//
#include "stdio.h"
#include "stdlib.h"
#include "Chinland_Banking_System.h"
#include "Validation_Process.h"
#include "Database.h"
#ifndef FINAL_ASS_MENU___OPTIONS_H
#define FINAL_ASS_MENU___OPTIONS_H

void menu();
void login();
void Registration();
void find_Acc();
void login_account(Database* db, const char* username, const char* password) ;
// Function prototypes
Database* searchUsername(Database* db, const char* username);
Database* searchPassword(Database* db, const char* password);

void menu(){
    int option;
    printf("\n Welcome-to-our-ChinLand-Banking-system!!\n");
    printf("\n Choose the numbers below..\n Press 1 for Login\n Press 2 for Registration \n Press 3 for exit \n Press 4 for Find account: ");
    scanf("%d",&option);
    if(option == 1){
        login();
    } else if(option == 2){
        Registration();
    } else if(option == 3){
        exit(0);
    } else if(option == 4){
        find_Acc();
    }
    else{
        printf("You entered the wrong option!!!\n Please Enter the correct option below...:3\n");
        menu();
    }
}


void Registration(){

    int R_accountNumber = 1;
    char R_name[30];
    char R_email[30];
    char R_phone[13];
    char R_password[20];
    char R_address[50];
    double R_balance = 5000;
    int R_postal_code;
    int R_trans_counter = 1;
    printf("\n This is __Registration__ Page.\n");
    printf("\n Enter Your Name to register: ");
    scanf(" %[^\n]",&R_name);

  //  E-mail checking
    int i = 0 ;
    while (i == 0) {
        printf("\nEnter your Email to Register: ");
        scanf("%s", R_email);

        Database* account = searchEmail(root, R_email);
        if (account != NULL) {
            printf("\nWarning!!! The email '%s' is already registered in the bank.\n", R_email);
        } else {
            printf("\nThe email '%s' is not registered in the bank. You can proceed with the registration.\n", R_email);
            i = 1;
        }
    }

   // Phone Validation Process and collects the user's phone number
    int valid_Phone = -1;
    while (valid_Phone == -1){
        printf("\nEnter Your Phone Number to Register which is start with +95: ");
        scanf("%s",&R_phone);

        valid_Phone =phone_validation(R_phone);
        if (valid_Phone == -1){
            printf("\nPlease Enter Your Correct Phone Number!!\n");
        }
    }



    //Strong Password Checking and collects the user's Passwords
    do {
        printf("Please Enter a strong password to Register \n (A strong password contains at least one uppercase letter,\n one lowercase letter, one digit,\n and one special character): ");
//        scanf("%s", password);
        scanf(" %s",&R_password);
    } while (!isStrongPassword(R_password));

    //Address collects
    printf("\n Enter Your Address to register: ");
    scanf(" %[^\n]",&R_address);

    //Postal code collects
    printf("\n Enter Your Postal-code to register: ");
    scanf(" %d",&R_postal_code);



    //Adding the data into the AVL-tree Structure

    root = insertAccount(root,R_accountNumber,R_name,R_email,R_phone,R_password,R_address,R_balance,R_postal_code,R_trans_counter);
    R_accountNumber++;
    R_trans_counter++;
    record_data_to_file(root);
    menu();

}


void find_Acc(){
    printf("\n Find __account__ page \n");
    int acc_id = 0;
    printf("\nEnter account-id: ");
    scanf("%d",&acc_id);

    displayAccount(searchAccount(root,acc_id));

    menu();
}


void login(){
    printf("\n This is __login__ Page \n");
    const char* L_name[30];
    const char* L_password[30];

    printf("\n Enter User->name: ");
    scanf(" %s",&L_name);
    printf("\n Enter User->password: ");
    scanf(" %[^\n]",&L_password);
    printf("You login with  Username: %s and password: %s \n",L_name,L_password);
    login_account(root,L_name,L_password);
}


// Function to login account
void login_account(Database* db, const char* username, const char* password) {
    Database* uname = searchUsername(db, username);
    Database* passwd = searchPassword(db, password);

    if (uname != NULL && passwd != NULL && uname == passwd) {
        printf("Your Account id-Number: %d\n", uname->accountNumber);
        printf("Your Name: %s\n", uname->name);
        printf("Your Balance: %.2f\n", uname->balance);
        printf("Your Phone Number: %s\n", uname->phone);
        printf("Your Postal_code: %d\n", uname->postal_code);
        printf("Your Address: %s\n", uname->address);

        menu();
    } else {
        printf("Your Account not found.\n");
        login();
    }
}

// Function to search by username
Database* searchUsername(Database* root, const char* username) {
    if (root == NULL) return NULL;
    if (strcmp(root->name, username) == 0) return root;

    Database* leftSearch = searchUsername(root->left, username);
    if (leftSearch != NULL) return leftSearch;

    return searchUsername(root->right, username);
}

// Function to search by password
Database* searchPassword(Database* root, const char* password) {
    if (root == NULL) return NULL;
    if (strcmp(root->password, password) == 0) return root;

    Database* leftSearch = searchPassword(root->left, password);
    if (leftSearch != NULL) return leftSearch;

    return searchPassword(root->right, password);
}
#endif //FINAL_ASS_MENU___OPTIONS_H
