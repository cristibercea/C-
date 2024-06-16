// Lab6-7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_DBG_MAP_ALLOC
#include "ui.h"
#include "tests.h"
#include <crtdbg.h>
#include <iostream>

int main() {
    Tests test_app; 
    test_app.run_all();
    try{  
        FileRepository repo("data.txt");  
        //InMemoryRepository repo;  
        Validator valid;    
        Service serv(repo, valid);   
        UI ui(serv);   
        ui.run_app();   
    }  
    catch (RepoException& re) { std::cout << re.get_message(); }  ///repo file could not be opened
    _CrtDumpMemoryLeaks();
    return 0;
}