#include <string.h>
#include <stdio.h>
#define MAX 100
void deleteElement(double nums[], char ops[], int index, int *count) {
    for (int i = index + 1; i < *count; i++) {
        nums[i] = nums[i + 1] ;
    }
    for (int i = index; i < *count - 1; i++) {
        ops[i] = ops[i + 1] ;
    }
    (*count)-- ;
}
void process(double nums[], char ops[], int *count, const char *validOps) {
    int i = 0 ;
    
    while (i < *count - 1) {
        char currentOp = ops[i];

        if (strchr(validOps, currentOp) != NULL) {
            double val1 = nums[i] ;
            double val2 = nums[i+1] ;
            double res = 0 ;

            
            if (currentOp == '*') res = val1 * val2 ;
            else if (currentOp == '/') res = (val2 != 0) ? val1 / val2 : 0 ;
            else if (currentOp == '%') res = (int)val1 % (int)val2 ;
            else if (currentOp == '+') res = val1 + val2 ;
            else if (currentOp == '-') res = val1 - val2 ;

            nums[i] = res ; 
            deleteElement(nums, ops, i, count) ; 
            
        } else {
            i++ ; 
        }
    }
}