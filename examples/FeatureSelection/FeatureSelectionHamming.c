#include "dev.h"

int main(int argc, char **argv){

    if(argc != 3){
        fprintf(stderr,"\nusage FeatureSelectionHamming <input best vector> <search space configuration file>\n");
        exit(-1);
    }
    
    SearchSpace *s = NULL;
    int i, n_feats;
    double *input_vector, time_opt, time_classify, bestHamming;
    timer tic, toc;
    FILE *f = NULL;

    f = fopen(argv[1], "r");
    fscanf(f, "%d", &n_feats);
    input_vector = (double*)calloc(n_feats, sizeof(double));
    for (i = 0; i < n_feats; i++)
    	fscanf(f, "%lf", &input_vector[i]);  
    fclose(f);
 
    s = ReadSearchSpaceFromFile(argv[2], _PSO_);
    
    for (i = 0; i < s->n; i++){
	s->LB[i] = 0;
	s->UB[i] = 1;
    }
    
    fprintf(stderr,"\nInitializing search space ... ");
    InitializeSearchSpace(s, _PSO_);
    fprintf(stderr,"\nOk\n");
    
    fflush(stderr); fprintf(stderr,"\nRunning PSO ... ");
    gettimeofday(&tic,NULL);
    runPSO(s, FeatureSelectionHamming, input_vector);
    gettimeofday(&toc,NULL);
    fflush(stderr); fprintf(stderr,"\nOK\n");
    
    time_opt = ((toc.tv_sec-tic.tv_sec)*1000.0 + (toc.tv_usec-tic.tv_usec)*0.001)/1000.0;
    fprintf(stdout, "\nOptimization time: %f seconds\n", time_opt); fflush(stderr);
        
    fflush(stderr); fprintf(stderr,"\nPerforming Hamming Distance with best agent ...\n");
    gettimeofday(&tic,NULL);
    bestHamming = Hamming_Distance(s->g, input_vector, s->n);
    fflush(stderr); fprintf(stderr,"\nOK\n");
    gettimeofday(&toc,NULL);
    
    time_classify = ((toc.tv_sec-tic.tv_sec)*1000.0 + (toc.tv_usec-tic.tv_usec)*0.001)/1000.0;
    fprintf(stdout, "\nClassification time: %f seconds\n", time_classify); fflush(stderr);
    
    f = fopen("best_feats.txt", "a");
    fprintf(f, "%d %d", s->n, (int)s->g[0]);
    for(i = 1; i < s->n; i++){
	    fprintf(f, " %d", (int)s->g[i]);
    }
    fprintf(f, "\n");
    fclose(f);
    
    fprintf(stderr, "\nHamming Distance: %lf\n", bestHamming);
    f = fopen("final_hamming.txt", "a");
    fprintf(f, "%lf\n", bestHamming);
    fclose(f);
    
    fflush(stderr); fprintf(stderr,"\nDeallocating memory ...");
    fflush(stderr); fprintf(stderr,"\nOK\n");
        
    f = fopen("optimization.time","a");
    fprintf(f,"%f %f\n",time_opt, time_classify);
    fclose(f);
    
    free(input_vector);
    DestroySearchSpace(&s, _PSO_);
    
    return 0;
}