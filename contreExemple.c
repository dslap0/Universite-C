#include <stdio.h>
#define LENGTH 1000

int main(){
    int x[LENGTH]; 

    // assignation of the values
    int i = 0;
    while(i < LENGTH){
        x[i] = i + 1;
        i++;
    }

    for (int i = 1; i < LENGTH; i++){
        for(int j = 0; j < LENGTH; i++){
            if(i*i % 59 == x[j]*x[j] % 59){
                if(i % 59 != x[j] % 59){
                    printf("x = %d, y = %d\n", x[j], i);
                    goto label;
                }
            }
        }
    }
    label:
    return 0;
}