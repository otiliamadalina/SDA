//
// Created by ASUS on 31.05.2024.
//

#include "fib_algs.h"

int fibbonacci(int n) {
    if(n == 0){
        return 0;
    } else if(n == 1) {
        return 1;
    } else {
        return (fibbonacci(n-1) + fibbonacci(n-2));
    }
}