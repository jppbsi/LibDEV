#include "dev.h"

int main(int argc, char **argv){
    if(argc != 4){
        fprintf(stderr,"\nUsage: OPFknn <training set> <validating set> <kmax>.\n");
        exit(-1);
    }
    
    SearchSpace *s = NULL;
    
    s = CreateSearchSpace(100, 1, _PSO_);
    s->w = 1.4;
    s->c1 = 1.4;
    s->c2 = 0.6;
    s->iterations = 10;
    
    
    DestroySearchSpace(&s);
    
    return 0;
}