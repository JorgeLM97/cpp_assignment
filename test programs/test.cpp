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


int main ()
{
    int *rnumber, rint;
    rnumber = RNG_array(20, 1);

    for (int i = 0; i != 10; i++)
        printf("%d ", rnumber[i]);
        
    puts ("");

    sort(rnumber, rnumber + 10);

    for (int i = 0; i != 10; i++)
        printf("%d ", rnumber[i]);

    puts ("");
    
    return 0;

}
