//
// Created by uchia on 4/29/2024.
//

#ifndef FINAL_ASS_DATABASE_H
#define FINAL_ASS_DATABASE_H
#include <string.h>
#include "Chinland_Banking_System.h"




// Function to record account data to a file
void record_data(Database* root, FILE* fptr) {
    if (root == NULL) {
        return;
    }

    record_data(root->left, fptr);

    fprintf(fptr, "%d %s %s %s %s %s %d %lf %d", root->accountNumber, root->name, root->email,
            root->phone, root->password, root->address, root->postal_code,
            root->balance, root->trans_counter);

    for (int a = 0; a < root->trans_counter; a++) {
        fprintf(fptr, " %s", root->trans[a].trans_record);
    }
    fprintf(fptr, "\n");
    record_data(root->right, fptr);
}

// Function to record account data to a data-base
void record_data_to_file(Database* root) {
    FILE* fptr = fopen("Bank_DataBase.txt", "a");

    if (!fptr) {
        perror("Recording Data Error:\n");
        return;
    }

    printf("Recording Account's Data to File.....\n");
    record_data(root, fptr);

    fclose(fptr);
    printf("Account Data Recorded Successfully!\n");
}

//// Function to reload account data from database.txt into AVL Tree


//To load the data from the file when Program is restart

void loading_data_from_file(Database* root) {
    FILE *fptr = fopen("Bank_DataBase.txt", "r");
    if (!fptr) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (!feof(fptr)) {
        Database temp;
        if (fscanf(fptr, "%d %s %s %s %s %s %d %lf %d", &temp.accountNumber, temp.name, temp.email,
                   temp.phone, temp.password, temp.address, &temp.postal_code, &temp.balance, &temp.trans_counter) == 9) {
            root = insertAccount(root, temp.accountNumber, temp.name, temp.email,
                                 temp.phone, temp.password, temp.address, temp.postal_code, temp.balance, temp.trans_counter);
        }
    }
    fclose(fptr);
    printf("Data from Database are successfully reloaded! \n");

    displayAccount(searchAccount(root, 1));
}


#endif //FINAL_ASS_DATABASE_H
