#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#define PARALLEL 1


int main() {


 //exemple avec les directives : private et shared  ::

    printf("\n\nThis is an example with the two directives Private and Shared\n");

    int x =1, y=10;
    int num_threads;
    printf("Dans la partie sequentielle : \n x = %d \t y = %d\n", x, y);

#pragma omp parallel private(x, num_threads) shared(y)
    {
        num_threads = omp_get_thread_num();
        x = 2+ num_threads;
        y = 2+num_threads;
        printf("Dans la partie parallele du  thread %d : x = %d , y = %d\n",num_threads,  x, y);
    }

    printf("Apres la parrtie parallele :  : \n x = %d \t y = %d\n", x, y);


    //exemple avec la directive firstprivate ::
    //(first private pour garder la valeur de la variable déclaré juste avant la partie parallele)

    printf("\n\nThis is an example of the directive firstprivate");
    int x2 = 10;
    printf("la valeur de x avant la partie parallele  x = %d", x2);
#pragma omp parallel private(x2)
    {
        printf("la valeur de x en utilisant private (La valeur n'est pas reconnu)  x = %d\n", x2);

    }

    printf("\n\n");

#pragma omp parallel firstprivate(x2)
    {
        printf("La valeur de x  en utilisant firstprivate  (la valeur est reconnu) x = %d\n", x2);
    }

}
