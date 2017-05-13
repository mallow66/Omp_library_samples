#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#define PARALLEL 1


int main() {

	//exemple de parallelisation des boucles avec la directive for


    int t0, t1, M=1000, N=1000 ;

    double A[M][N];

    t0 = omp_get_wtime();
    for (int i = 0; i <M ; ++i)
        for (int j = 0; j <N ; ++j)
            A[i][j] = 0.0;

    t1 = omp_get_wtime();

    printf("time sans paralellisation  : %f\n",  t1-t0);


    t0 = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i <M ; ++i)
        for (int j = 0; j <N ; ++j)
            A[i][j] = 0.0;

    t1 = omp_get_wtime();

    printf("time avec paralellisation  : %f\n",  t1-t0);


    /*  exemple avec la directive shedule()  ::
        Schedule(type, N)
        type : static | dynamic | guided | runtime
        N : entier qui determine le nombre des paquets dans un thread.(Prend la valeur 1 s'il n'est pas specifié)

        schedule(static) : les itérations sont réparties sur chaque thread par paquets en proportion égale, sans
        accorder de priorité aux threads.

        schedule(dynamic) : les paquets d'itérations sont distribués sur les threads les plus rapides.
        A chaque fois qu'un thread termine un paquet d'itérations, il reçoit un autre paquet.

        guided : la taille des paquets d'itérations attribués à chaque thread décroit
        exponentiellement, chaque paquet est attribué au thread le plus rapide.

        runtime : permet de chosir le mode de répartition des itérations avec la variable
        d'environnement OMP_SCHEDULE.

        Exemple : OMP_SCHEDULE="static,4" */


    printf("\n\nExemple avec la directive Schedule()\n");

    M = 12;
    N = 12;
    long double B[N][M];
    int num_du_thread;
    int i, j;
#pragma omp parallel for ordered schedule(runtime) private(i, j, num_du_thread)
    for(i=0; i<M; i++){
        for(j=0; j<N; j++)
            B[i][j] = 0.0;
        num_du_thread = omp_get_thread_num();

        printf("i = %d :: thread n° %d \n", i, num_du_thread);
    }



    /*exemple avec la directive barrier
     * barriere implicite  :: parallel, for, ordered, section
     * critical, single.
     *
     * barriere explicite syntaxe :: directive barrier
     * Remarque ; il n'est pas necessaire de mettre "barrier" apres single
     * car cette derniere contient une barriere de synchronisation implicite
     * */




    printf("\n\nExemple avec la directive barrier \n");

#pragma omp parallel
    {
      thread_num = omp_get_thread_num();
#pragma omp single
        {
            printf("Single : je suis le 1er thread a entrer, mon numero de thread est %d\n", thread_num);
        };
        printf("region parralele : Bonjour je suis le thread n° %d\n, ",thread_num);

#pragma omp barrier // lorsqu'on utiliste cette directive, la section de master attend tout les threads precedents a terminer pour s'executer
#pragma omp master
        {
            printf("Bonjour je suis le thread principale : mon numero est: %d ", thread_num);
        };
    }


    /*
     * exemple avec la directive nowait()
     * Dans certaines cas, imposer une barriere implicite peut s'averer inutile
     * et ralentit un peu l'execution du code
     * Pour eviter cette attente, il faut utiliser la clause nowait qui vient
     * direcctement apres la fin d'une directive contenant une barriere de synchronisation
     * implicite (à part la directive parallel qui contient un barriere explicite qui ne peut
     * etre levée)
     * #pragram omp for nowait
     *
     */

    printf("\n\nExemple avec la directive nowait \n");


#pragma omp parallel
    {
        thread_num = omp_get_thread_num();
#pragma omp single nowait
        {
            printf("Single : hello depuis le thread n° %d\n", thread_num);

        };

        printf("region parallel : hello depuis le thread numero %d\n", thread_num);
#pragma omp master
        {
            printf("master: hello depuis le thread n° %d\n", thread_num) ;
        };

    };

    /*
     * exemple de la clause :: reduction() :
     * Cette clause est ulilisée pour calculer une somme, un produit
     * un maximul etc..
     *
     *
     * Syntaxe :: #pragma omp for reduction(operation:variable)
     * operation : + | - | *
     */


    /*
     * pecifies that one or more variables that are private to each thread are the subject
     * of a reduction operation at the end of the parallel region.
     */

    printf("\n\nExemple avec la directive reduction \n");

    M = 10;
    a =2;
#pragma omp parallel
    {
        thread_num = omp_get_thread_num();
#pragma omp for reduction(+:a)
        for( i=0; i<M; i++){
            a = a+1;
        }
    };
    printf("a final = %d\n", a);


    /*
     * Exemple avec la directrive atomic
     *
     * La directive atomic() permet la mise a jour atomique d'un
     * emplacement memoire.
     *
     * Cette directive ne prend en charge aucune clause et
     * s'applique sur l'instruction qui vient just apres
     *
     * l'atomicité designe une operation ou un ensemble d'operation qui
     * s'executent entierement sans pouvoir etre interrompues avant
     * la fin de leur deroulement
     */


    printf("\n\nExemple avec la directive atomic\n");
    M=  10;
    a = 2;

#pragma omp parallel
    {

        thread_num  = omp_get_thread_num();
#pragma omp for
        for (i=0; i<M; i++){
#pragma omp atomic
            a+=1;
            printf("Thread numero %d \t a = %d\n", thread_num, a);
        }
    };

    printf("a final = %d\n",a);



    /*
     * Exemple avec la directive critical()
     * La directive critical(): s'applique sur un bloc de code, qui sera exécuté par un
       seul thread à la fois,
       Une fois qu'un thread a terminé un autre thread peut donc avoir accès à cette région
       critique.
     */

    M =10, a = 2;
#pragma omp parallel
    {
        thread_num = omp_get_thread_num();
#pragma omp for
        for(i=0; i<M; i++){
#pragma omp critical
            a+=1;
            printf("Thread %d \t, a = %d\n", thread_num, a);
        }
    };
    printf("a final = %d\n", a);


    /*
     *
     * Exemple avec la directive sections
     * une section parallele n'est executée que par un seul et
     * unique thread (tout comme single)
     * Cette directive peut  prendre les clauses lastprivate et
     * reduction
     *
     * Syntaxe ::
     * #pragma omp secions{
     *
     *      #pragma omp section
     *          X();
     *      #pragma omp section
     *          Y();
     * }
     * Comme la directive parallel, la barriere implicite de omp secions ne peut
     * pas etre levée par la clause nowait
     */

    printf("\n\nExemple avec la directive sections \n");


#pragma omp parallel sections num_threads(4)
    {
        printf("Hello from thread %d\n", omp_get_thread_num());

#pragma omp section
        printf("Hello from thread %d\n", omp_get_thread_num());
    }


    printf("\n\nUn ature exemple avec la directive section\n\n");


#pragma omp parallel sections
    {
#pragma omp section
        {
            printf("Section 1 id = %d\n", omp_get_thread_num());
        }

#pragma omp section
        {
            printf("Section 2 id = %d\n", omp_get_thread_num());
        }

#pragma omp section
        {
            printf("Section 3 id = %d\n", omp_get_thread_num());
        }
    };



    /*
     * Le nombre de coeur de votre machine
     *
     */

    int n = omp_get_num_procs();
#pragma omp parallel
    {
        printf("Hello World !! \n");
    };
    printf("le nombre de coeur est %d, ",n);





}

