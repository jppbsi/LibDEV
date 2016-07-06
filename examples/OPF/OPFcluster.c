#include "dev.h"

int main(int argc, char **argv){
    if(argc != 4){
        fprintf(stderr,"\nUsage: OPFcluster <training set> <validating set> <kmax>.\n");
        exit(-1);
    }
    
    SearchSpace *s = NULL;
    int kmax = atoi(argv[3]);
    Subgraph *Train = NULL, *Val = NULL;
    
    Train = ReadSubgraph(argv[1]);
    Val = ReadSubgraph(argv[2]);
    
    s = CreateSearchSpace(100, 1, _PSO_);
    s->w = 1.4;
    s->c1 = 1.4;
    s->c2 = 0.6;
    s->iterations = 10;
    s->LB[0] = 1;
    s->UB[0] = kmax;
    
    InitializeSearchSpace(s, _PSO_);
    runPSO(s, OPFcluster_Optimization, Train, Val);
    
    DestroySearchSpace(&s, _PSO_);
    DestroySubgraph(&Train);
    DestroySubgraph(&Val);
    
    return 0;
}