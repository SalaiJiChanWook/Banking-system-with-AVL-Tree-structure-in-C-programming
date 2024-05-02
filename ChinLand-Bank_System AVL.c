//
// Created by uchia on 4/24/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "processenv.h"
#include "Chinland_Banking_System.h"
#include "Menu_&_Options.h"

int main() {
//
//    Database* root = NULL;
//
//  Insert some accounts
    root = insertAccount(root, 1001, "SalaiLunLyanPon", "test1@gmail.com","+959797604809","Vpjtqwv23@","Soul-korea", 5000.0,21,1);
    root = insertAccount(root, 1002, "SalaiJiChnagWook", "test1@gmail.com","+959797604809","Vpjtqwv23@","Soul-korea", 5000.0,21,1);
    root = insertAccount(root, 1003, "SalaiLunThihaminzin", "test1@gmail.com","+959797604809","Vpjtqwv23@","Soul-korea", 5000.0,21,1);
//    record_data_to_file(root);
//    root = insertAccount(root, 1002, "Ma Ma Hsu","test1@gmail.com","+959797604809","Vpjtqwv23@","Soul-korea", 3000.0,22);
//    root = insertAccount(root, 1003, "Ma Ma Hsu ko chit thaw kg ly","test1@gmail.com","+959797604809","Vpjtqwv23@","Soul-korea", 8000.0,23);
//
//
//
//    // Deposit money
//    printf("\n Testing the Deposit function!\n");
//    depositMoney(root, 1001, 1000.0);
//
//    // Withdraw money
//    printf("\n Testing the Withdraw function!\n");
//    withdrawMoney(root, 1002, 2000.0);
//
//    // Display account details
//    printf("\n Testing the Display account function!\n");

    loading_data_from_file(root);
    displayAccount(searchAccount(root, 1001));
    menu();



    return 0;
}