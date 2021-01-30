#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <bits/stdc++.h> /* sort */
using namespace std;
//Function returns a pointer to a static array with 10 numbers randomly generated using rand(), with a range of rngRange beginning at rngStart
int * RNG_array (int rngRange, int rngStart){

    static int rngArray [10];

    srand(time(NULL));

    for (int i = 0; i != 10; i++){
            rngArray[i] = rand() % rngRange + rngStart;
            printf("%d ", rngArray[i]);
        }

    puts ("");
    return rngArray;

}

void factorialCheck ( int factorialNumber) {
    unsigned long long factorialResult = 1;
    for(int i = 1; i <= factorialNumber; i++){
        factorialResult *= i;
    }

    if (factorialResult < 100000000000)
        printf("log: ");
    printf("%llu \n", factorialResult);
}


int main ()
{
    int *rnumber, rint;
    rnumber = RNG_array(20, 1);

    sort(rnumber, rnumber + 10);
    for (int i = 0; i != 10; i++)
        printf("%d ", rnumber[i]);
    puts ("");

    for (int i = 0; i != 10; i++){
        printf("%d: ", rnumber[i]);
        factorialCheck(rnumber[i]);
    }

    puts ("");

    return 0;

}
