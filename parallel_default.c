#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#define PARALLEL 1


int main() {
//exemple en utilisant la classe default()
    //default(none) permet à l'utilisateur de specifier le statut de tous les variables utilisés dans la région parallele ::

    printf("\n\n This is an example of using the directive default()");

    /*
     * shared, which is in effect if the default clause is not specified,
     * means that any variable in a parallel region will be treated as if it were specified with the shared clause.
     * none means that any variables used in a parallel region that are not scoped
     * with the private, shared, reduction, firstprivate, or lastprivate clause will cause a compiler error.
     *
     * */

    x=1, y=10;

#pragma omp parallel default(none) firstprivate (x, y)
    {
        printf("La valeur de x = %d\t La valeur de y = %d\n",  x, y);


    }


    printf("\n\nthis is two examples of using the directive master \n");
    //exemple de l'éxecution exclusive avec les directives : master et single


    printf("\n\nExécution avec le thread principale (le thread 0 : Master)\n");

#pragma omp master
    {
        printf("Ce code est executé juste avec le thread principale ; le thread %d\n", omp_get_thread_num());
    };




}

