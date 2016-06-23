#include "dev.h"

int main(int argc, char **argv){
    if(argc != 4){
        fprintf(stderr,"\nUsage: OPFknn <training set> <validating set> <kmax>.\n");
        exit(-1);
    }
    
    return 0;
}