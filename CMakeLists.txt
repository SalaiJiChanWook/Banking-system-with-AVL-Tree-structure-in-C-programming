cmake_minimum_required(VERSION 3.27)
project(Final_Ass C)

set(CMAKE_C_STANDARD 11)

add_executable(Final_Ass
        "ChinLand-Bank_System AVL.c"
        Menu_&_Options.h
        Chinland_Banking_System.h
        Validation_Process.h
        Database.h)
