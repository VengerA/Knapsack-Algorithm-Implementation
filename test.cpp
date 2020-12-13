#include <iostream>
#include <vector>
#include <iostream>
#include <random>
#include <chrono>     // for pair

using namespace std;

std::ostream &operator<<(std::ostream &output, std::vector<int> vec){
    output << "{" ;
    for(int i = 0; i < vec.size(); i++){
        output << vec[i] << ",";
    }
    output << "\b";
    output << "}";    
    return output;
}


int BuyStocks (int**& market, int n1, int n2, vector<int>& solution)
{
    int i, j;
    int **arr = new int*[n1];

    for (int a = 0; a < n1; a++)
        arr[a] = new int[n2];

    for (int a = 0; a < n1; a++)
        for (int b = 0; b < n2; b++)
            arr[a][b] = 0;

    arr[0][0]= market[0][0]; 
    for( i = 0 ; i < n1; i++){
        for(j = i; j < n2; j++){       
            if(j == 0){
                arr[i][j] = market[i][j]; 
            }else{
                
                if(i == 0){
                    
                    if(market[i][j] > market[i][j-1]){
                        arr[i][j] = market[i][j];
                    }else{
                        arr[i][j] = market[i][j-1];
                    }
                }
                else{ 
                    if(i == j){
                        arr[i][j] = market[i][j] + arr[i-1][j-1];
                    }
                    else if(market[i][j] + arr[i-1][j-1] < arr[i][j-1]){
                        arr[i][j] = arr[i][j-1];
                    }else{
                        arr[i][j] = market[i][j] + arr[i-1][j-1] ;
                    }
                }
            }
        }
    }

    for(i = n1-1; i >= 0; i--){
        for(j = n2 - n1 + i; j >= i ; j --){
            if(arr[i][j] != arr[i][j-1]){
                solution.insert(solution.begin(), j);
                break;
            }
        }
    }

    int num = arr[n1-1][n2-1];

    for(int i = 0; i < n1; ++i) {
        delete[] arr[i];   
    }
    delete[] arr;

    return num;
}

void randomArray(int*& array, int size, int min, int interval) 
{
  
  for (int i = 0; i < size; i++) 
  {
    array[i] = min + (random() % interval);
  }
}



void test_case_random(int n1, int n2){
    std::cout << "*********Test Random*********" << std::endl;

    int **market = new int*[n1];
    for(int i = 0; i < n1; i++){
        market[i] = new int[n2];
    }
    for(int i = 0; i < n1; i++){
        randomArray(market[i], n2, -50, 100);
    }

    /*for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){
            std::cout << market[i][j] << " ";
        }
        std::cout << std::endl;
    }*/

    std::vector<int> solution;

    auto start = std::chrono::steady_clock::now();


    int value = BuyStocks(market, n1, n2, solution);

    auto end = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Elapsed Time\t: " << duration*1e-6 << "s\n";
    std::cout << "Value \t\t: " << value << std::endl;
    std::cout << "Solution \t:" << solution << std::endl;


    for(int i = 0; i < n1; i++){
        delete [] market[i];
    }
    delete [] market;

}


void test_case_1(){
    std::cout << "*********Test1*********" << std::endl;
    std::vector<int> sol;
    std::vector<int> correctSol = {1,3,4};
    int correctVal = 53;
    int n1 = 3, n2 = 5;

    int market[3][5] = { { 7, 23, -5, -24, 16 },

                           { 5, 21, -4, 10, 23 }, 

                           { -21, 5, -4, -20, 20 } };

    int **p = new int*[n1];
    for(int i = 0; i < n1; i++){
        p[i] = new int[n2];
    }
    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){
            p[i][j] = market[i][j];
        }
    }

    int value = BuyStocks(p, n1, n2, sol);

    if(value == correctVal){
        std::cout << "Value \t\t: Correct" << std::endl;
        if(sol == correctSol){
            std::cout << "Solution \t: Correct" << std::endl;
        }
        else{
            std::cout << "Solution \t: Incorrect" << "\tExpected : " << correctSol << "\tFound : " << sol << std::endl;
        }
    }
    else{
        std::cout << "Value \t\t: Incorrect" << "\tExpected : " << correctVal << "\tFound : " <<  value << std::endl;
        if(sol == correctSol){
            std::cout << "Solution \t: Correct" << std::endl;
        }
        else{
            std::cout << "Solution \t: Incorrect" << "\tExpected : " << correctSol << "\tFound : " << sol << std::endl;
        }
    }

    for(int i = 0; i < n1; i++){
        delete [] p[i];
    }
    delete [] p;


}

void test_case_3(){
    std::cout << "*********Test3*********" << std::endl;
    std::vector<int> sol;
    std::vector<int> correctSol = {0, 2};
    int correctValue = 9;
    int n1 = 2, n2 = 3;

    int market[2][3] = { { 10, -2, 5 },
                        { 5, -4, -1} };

    int **p = new int*[n1];
    for(int i = 0; i < n1; i++){
        p[i] = new int[n2];
    }
    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){
            p[i][j] = market[i][j];
        }
    }

    int value = BuyStocks(p, n1, n2, sol);

    if(value == correctValue){
        std::cout << "Value \t\t: Correct" << std::endl;
        if(sol == correctSol){
            std::cout << "Solution \t: Correct" << std::endl;
        }
        else{
            std::cout << "Solution \t: Incorrect" << "\tExpected : " << correctSol << "\tFound : " << sol << std::endl;
        }
    }
    else{
        std::cout << "Value \t\t: Incorrect" << "\tExpected : " << correctValue << "\tFound : " <<  value << std::endl;
        if(sol == correctSol){
            std::cout << "Solution \t: Correct" << std::endl;
        }
        else{
            std::cout << "Solution \t: Incorrect" << "\tExpected : " << correctSol << "\tFound : " << sol << std::endl;
        }
    }

    for(int i = 0; i < n1; i++){
        delete [] p[i];
    }
    delete [] p;
}

void test_case_2(){
    std::cout << "*********Test2*********" << std::endl;
    std::vector<int> sol;
    std::vector<int> correctSol = {0, 1};
    int correctValue = -3;
    int n1 = 2, n2 = 2;

    int market[2][2] = { {-5, 10},
                        {-2, 2} };

    int **p = new int*[n1];
    for(int i = 0; i < n1; i++){
        p[i] = new int[n2];
    }
    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){
            p[i][j] = market[i][j];
        }
    }

    int value = BuyStocks(p, n1, n2, sol);

    if(value == correctValue){
        std::cout << "Value \t\t: Correct" << std::endl;
        if(sol == correctSol){
            std::cout << "Solution \t: Correct" << std::endl;
        }
        else{
            std::cout << "Solution \t: Incorrect" << "\tExpected : " << correctSol << "\tFound : " << sol << std::endl;
        }
    }
    else{
        std::cout << "Value \t\t: Incorrect" << "\tExpected : " << correctValue << "\tFound : " <<  value << std::endl;
        if(sol == correctSol){
            std::cout << "Solution \t: Correct" << std::endl;
        }
        else{
            std::cout << "Solution \t: Incorrect" << "\tExpected : " << correctSol << "\tFound : " << sol << std::endl;
        }
    }

    for(int i = 0; i < n1; i++){
        delete [] p[i];
    }
    delete [] p;
}




int main(){

    test_case_1();
    test_case_2();
    test_case_3();

    test_case_random(10,30);

    return 0;
}