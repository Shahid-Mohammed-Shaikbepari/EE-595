#include <iostream>
#include "time.h" //gfg

int findMax(int arr[], int size){
    int max = arr[0];
    for(int i = 0; i< size ; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}
void printArr(int arr[], int size){
    for(int i = 0; i< size ; i++){
        std::cout << i << ": " << arr[i] << std::endl;
    }
}

int main() {
    int arr[999];
    srand(time(0)); //gfg
    int upper = 100, lower = 1;
    for(int i = 0; i < 999 ; i++){
        arr[i] = (rand() % (upper - lower + 1))  + lower; //to print random number in range[lower, upper]
    }
    printArr(arr, 999);
    std:: cout << "Maximum value is: "<< findMax(arr, 999) << std::endl;
    return 0;
}
