#include <iostream>
#include <chrono>
#include <fstream>
#include "../inc/bellmanFord.hpp"



int main()
{
    constexpr int vSize = 10;
    // constexpr int vSize = 50;
    // constexpr int vSize = 100;
    // constexpr int vSize = 500;
    // constexpr int vSize = 1000;
    constexpr int eSize = ((2 * 25 * vSize * (vSize - 1))/ 200);  // density = 25%
    //constexpr int eSize = ((2 * 50 * vSize * (vSize - 1))/ 200);  // density = 50%
    //constexpr int eSize = ((2 * 75 * vSize * (vSize - 1))/ 200);  // density = 75%
    //constexpr int eSize = ((2 * 100 * vSize * (vSize - 1))/ 200);  // density = 100%
    
    double execution_time_list = 0;
    double execution_time_matrix = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_list;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop_time_list;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_matrix;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop_time_matrix;

    

    for (size_t i = 0; i < 100; i++)
    {
        graphList<vSize, eSize> test_list;
        graphMatrix<vSize, eSize> test_matrix;
        for (size_t i = 0; i < vSize; i++)
        {
            test_list.addVertex(i);
            test_matrix.addVertex(i);
        }
        std::srand(time(NULL));
        for (size_t i = 0; i < eSize; i++)
        {
        int first;
        first = std::rand() % (vSize-1);
        int second;
        second = std::rand() % (vSize-1);
        if (first == second)
        {
            second++;
        }
        
        int value;
        value = (std::rand() % 1000) - 100;
        test_list.addEdge(value, first, second);
        test_matrix.addEdge(value, first, second);
        
        }

        std::ofstream bellmanFordResults("BellmanFord.txt", std::ofstream::app);
        
            start_time_list = std::chrono::high_resolution_clock::now();
            auto b = bellmanFord(test_list, 1);
            stop_time_list = std::chrono::high_resolution_clock::now();
            execution_time_list += std::chrono::duration<double, std::milli>(stop_time_list - start_time_list).count();
            delete[] b;
            start_time_matrix = std::chrono::high_resolution_clock::now();
            auto a = bellmanFord(test_matrix, 1);
            stop_time_matrix = std::chrono::high_resolution_clock::now();
            execution_time_matrix += std::chrono::duration<double, std::milli>(stop_time_matrix - start_time_matrix).count();
            //displaying bellman-ford results
            for (int i = 0; i < vSize; ++i)      
                {
                    bellmanFordResults << a[i].id << " -" << a[i].value << "- " << a[i].parent->id << std::endl;
                    bellmanFordResults << std::endl;
                }

                bellmanFordResults << std::endl;
            delete[] a;
            bellmanFordResults.close();
        }
   
    std::ofstream results("results.txt", std::ofstream::app);
    std::cout << "List representation " << execution_time_list/100 << std::endl;
    std::cout << "Matrix representation " << execution_time_matrix/100 << std::endl;
    results << "List representation " << execution_time_list/100 << std::endl;
    results << "Matrix representation " << execution_time_matrix/100 << std::endl;
    results.close();
}