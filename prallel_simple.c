#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#define PARALLEL 1


int main() {


    //exemple simple parallel ::


    printf("\n\nThis is a simple example of omp Parallel :\n");
#pragma omp parallel
    {
        printf("Hello World !! \n");
    };



    //exemple avec la directive If ::

    printf("\n\nThis is an example of the IF directive : \n");
#pragma omp parallel if (PARALLEL)
    {
        printf(" The variable PARALLEL is equal to 1\n");

    }

    //exemple avec la directive num_threads() ::

    printf("\n\nthis is an example with the directive num_threads(n)\n"
                   "in this example we used n = 3 \n");

#pragma omp parallel num_threads(3)
    {
        printf("Hello World  !! the number of the thread is : %d\n", omp_get_thread_num());
    }


