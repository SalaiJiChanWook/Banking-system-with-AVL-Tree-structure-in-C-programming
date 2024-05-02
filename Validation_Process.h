//
// Created by uchia on 4/27/2024.
//

#ifndef FINAL_ASS_VALIDATION_PROCESS_H
#define FINAL_ASS_VALIDATION_PROCESS_H
#include "Chinland_Banking_System.h"
#include "stdlib.h"
#include "stdio.h"

//Function Declares
int phone_validation(char phoneNumber[]);
//int Email_exit_or_not(struct Node* root, char Email[]);


 //Checking the user's E-mail which does not exit or exits.
// Function to search for an email in the AVL tree
Database* searchEmail(Database* root, const char* mail) {
    if (root == NULL) return NULL;
    if (strcmp(root->email, mail) == 0) return root;

    Database* leftSearch = searchEmail(root->left, mail);
    if (leftSearch != NULL) return leftSearch;

    return searchEmail(root->right, mail);
}

//checking the strong password  from user's data
int isStrongPassword(char *R_password) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    int length = strlen(R_password);
    for (int i = 0; i < length; i++) {
        if (isupper(R_password[i])) {
            hasUpper = 1;
        } else if (islower(R_password[i])) {
            hasLower = 1;
        } else if (isdigit(R_password[i])) {
            hasDigit = 1;
        } else {
            hasSpecial = 1;
        }
    }
    return (hasUpper && hasLower && hasDigit && hasSpecial);
}



// Phone Validation from users
int phone_validation(char phoneNumber[]){

    // Check if the phone number is 11 digits and follows the specified format
    if (strlen(phoneNumber) == 13 && phoneNumber[0] == '+' && phoneNumber[1] == '9' && phoneNumber[2] == '5') {
        // Check if all the characters are digits
        int i, valid = 1;
        for (i = 0; i < strlen(phoneNumber); i++) {
            if(i == 0 || i == 1) {
                continue;
            }
            if (!isdigit(phoneNumber[i])) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            return 1; // Phone number is valid
        } else {
            return -1; // Phone number contains non-digit characters
        }
    } else {
        return -1; // Phone number does not meet the specified format
    }
}
#endif //FINAL_ASS_VALIDATION_PROCESS_H
