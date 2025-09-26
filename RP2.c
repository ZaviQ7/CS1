#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Question 1
int zeroes (int n){
    int res = 0;
    
    if (n == 0){
        return 0
    }
    else {
        return n/5 + zeroes(n/5); 
    }
    
}

// Q2
int sumEven(int vals[], int low, int high){
    // Base Case
    if (low > high){
        return 0; 
    }
    else{
        if(vals[low]%2 == 0){

            return vals[low] + sumEven(vals, int low + 1, int high);
        }
        else{
            return sumEven(vals, int low + 1, int high);

        }

    }
}
// Q3
int minMovesToWin(int n){
    if n <= 0{
        return 0;
    }
    else {

        int moves_if_subtract = 1 + minMovesToWin(n - 10);

        int moves_if_divide = 1 + minMovesToWin(n / 3);

        return fmin(moves_if_subtract, moves_if_divide);
    }
 }



