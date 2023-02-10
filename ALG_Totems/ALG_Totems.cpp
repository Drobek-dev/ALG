// ALG_Totems.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>


using namespace std::chrono;

int main()
{
    auto start = high_resolution_clock::now();

    std::cout << "Hello Totems!\n";
    
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << " Time taken by function: "
        << duration.count() << " ms" << std::endl;
}

