#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#define PARALLEL 1


int main() {
	//un autre exemple avec la directive master

    printf("\n\n\n");

    int thread_num;
#pragma omp parallel private (thread_num)
    {
        thread_num = omp_get_thread_num();
        printf("Bonjour je suis le thread n° %d\n", thread_num);

#pragma omp master
        {
            printf("Bonjour je suis le thread maitre avec le numero : %d\n", omp_get_thread_num());
        };

    }

    //exemple de l'utilisation de la directive single
    //single : le code est exécuté par le premier thread arrivé ::

    printf("\n\n\nThis is an example of using the directive Single\n");

    int a, rang;

#pragma omp parallel private(a, rang)
    {
        rang = omp_get_thread_num();
        a = 1;
#pragma omp single
        {
            a = 2;
            printf("je suis le premier thread (%d) arrivé  et j'ai modifié la variable a = %d\n", rang, a);
        };

        printf("je suis le thread %d, avec a = %d\n", rang, a);
    }

    // exemple avec la directive single et la clause copyprivate()

    /*
     * Cette clause n'est utilisable qu'à la fin de la directive single.
     * Elle permet de transmettre à tous les threads la nouvelle valeur d'une variable
     * privée affectée par le thread arrivé en premier (le thread qui a executé le bloc single).
     *
     * */
    printf("\n\nThis is an example of the directive single and the clause copyprivate() \n");


#pragma omp parallel private (rang, a)
    {
        rang = omp_get_thread_num();
        a =1;
#pragma single copyprivate()
        {
            a =2;
        }
        printf("thread n°%d \t a = %d\n", rang, a);

    }



}

