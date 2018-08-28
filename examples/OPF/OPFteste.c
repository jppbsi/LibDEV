#include "dev.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "\nUsage: OPFteste <training set> .\n");
        exit(-1);
    }

    float perc = 0.25;
    int m = 15;
    int i, j;

    Subgraph *Train = ReadSubgraph(argv[1]);

    SearchSpace *s = CreateInitializeSearchSpaceOPF(Train, perc, _PSO_, m);

    for (i = 0; i < s->m; i++){
       printf("Agent %d:\n", i);
       for (j = 0; j < s->n; j++)
          printf("%f ", s->a[i]->x[j]);
       printf("\n");
    }

    DestroySearchSpace(&s, _PSO_);
    DestroySubgraph(&Train);

    return 0;
}
