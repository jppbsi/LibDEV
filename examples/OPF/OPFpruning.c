#include "dev.h"

int main(int argc, char **argv){
    if(argc != 7){
        fprintf(stderr,"\nUsage: OPFpruning <training set> <validating set> <testing set> <output results file name> \
                <search space configuration file> <output best parameters file name>\n");
        exit(-1);
    }
    
    int i, j, qtd_labels = 0, *poll_label = NULL, DL = 0;
    float accuracy;
    double *psi = NULL, *Psi = NULL, lambda = 0.0, micro = 0.0, SL = 0.0;
    char fileName[256];
    FILE *f = NULL;
    SearchSpace *s = NULL;
    Subgraph *Train = NULL, *Val = NULL, *Test = NULL;
    
    s = ReadSearchSpaceFromFile(argv[5], _PSO_);
    
    for (i = 0; i < s->n; i++){
	s->LB[i] = 0;
	s->UB[i] = 50;
    }
    
    fprintf(stderr,"\nInitializing search space ... ");
    InitializeSearchSpace(s, _PSO_);
    psi = (double *)calloc(s->n,sizeof(double));
    fprintf(stderr,"\nOk\n");
    
    Subgraph **gTrain = (Subgraph **)calloc((s->n),sizeof(Subgraph *));
    float training_p = 1.0-(1.0/s->n);
    Subgraph *gAux = NULL;
    
    fprintf(stderr, "\nReading training set ...");	
    Train = ReadSubgraph(argv[1]);
    fprintf(stderr, "\nOK\n");
    
    /* Splitting training set in n (s->n) subsets */
    fprintf(stderr, "\nCreating ensemble ...");
    for(i = 0; i <= s->n; i++){
        opf_SplitSubgraph(Train, &gAux, &gTrain[i], training_p);
        if(training_p == 0.5){
            gTrain[i+1] = CopySubgraph(gAux);
            DestroySubgraph(&Train);
            DestroySubgraph(&gAux);
            break;
        }else{
            DestroySubgraph(&Train);
            Train = CopySubgraph(gAux);
            DestroySubgraph(&gAux);
            training_p = 1.0-(1.0/(s->n-i-1.0));
        }
    }
    for (i = 0; i< s->n; i++){
        if(gTrain[i]->nlabels > qtd_labels)
            qtd_labels = gTrain[i]->nlabels;
    } 
    fprintf(stderr, "\nOK\n");
    
    /* Training OPF standard approach with complete graph */
    for(i = 0; i < s->n; i++){
        fprintf(stderr, "\nTraining OPF classifier set %d/%d ...",i+1,s->n);
        opf_OPFTraining(gTrain[i]);
        fprintf(stderr, "\nOK\n");
        
        fprintf(stderr, "\nWriting classifier's model file %d/%d ...",i+1,s->n);
        sprintf(fileName,"classifier.ensemble.%i.opf",i+1);
        opf_WriteModelFile(gTrain[i], fileName);
        fprintf(stderr, "\nOK\n");
    }
    
    /* Optimization */
    fprintf(stderr, "\nReading evaluation set ...");
    Val = ReadSubgraph(argv[2]);
    fprintf(stderr, "\nOK\n");
    
    fprintf(stderr, "\nOptimizing OPFpruning using PSO ...");
    runPSO(s, OPFpruning_ensemble, gTrain, Val, s->n);
    fprintf(stderr, "\nOk\n");
        
    for (i = 0; i < s->n; i++){
        micro += s->g[i];
        psi[i] = s->g[i]; /* Setting classifiers to testing phase */
        
    }
    
    micro /= s->n; /* Mean of the weights of the classifiers */
    for (i = 0; i < s->n; i++){
        if(psi[i] < micro){
            DL++; /* DL is the number of classifiers whose weight is less than micro */
	    SL += pow((psi[i] - micro),2); /* Squaring the difference */
	} 
    } 
    SL = sqrt((1/(double)DL)*SL); 
    lambda = micro - SL;
    for(i = 0; i < s->n; i++){
	if(psi[i] > lambda)
            psi[i] = 1;
	else
            psi[i] = 0;
    }
    
    /* Testing step */
    Test = ReadSubgraph(argv[3]);
    int **ensemble_label = (int **)malloc(Test->nnodes*sizeof(int *));
    for(i = 0; i < Test->nnodes; i++)
        ensemble_label[i] = AllocIntArray(s->n+1);
        
    fprintf(stderr, "\nOPFpruning classifying ...");
    for(i = 0; i < s->n; i++ ){
        if((int)psi[i]){
            opf_OPFClassifying(gTrain[i], Test);
	    for(j = 0; j < Test->nnodes; j++ ){
                ensemble_label[j][i]=Test->node[j].label;
		Test->node[j].label = 0;
	    }
	}
    }
    fprintf(stderr, "\nOk\n");
    
    /* Majority voting */
    int k, aux, label = 0;
    poll_label = (int *)calloc((qtd_labels+1),sizeof(int));
    for(i = 0; i < Test->nnodes; i++){
        aux = 0;
	for(j = 0; j < s->n; j++){
            if((int)psi[j])
                poll_label[ensemble_label[i][j]]++;
	}
	for(k = 0; k <= qtd_labels; k++){
            if(poll_label[k] > aux){
                aux = poll_label[k];
		label = k;
	    }
	    poll_label[k] = 0;
	}
	Test->node[i].label = label;
    }
    for(i = 0; i < Test->nnodes; i++)
        free(ensemble_label[i]);
    free(ensemble_label);
    free(poll_label);
    for (i = 0; i < s->n; i++){
        DestroySubgraph(&gTrain[i]);
    }
    free(gTrain);
    free(psi);
    
    /* Accuracy step */
    fprintf(stderr, "\nComputing accuracy ...");
    accuracy = opf_Accuracy(Test);
    fprintf(stderr, "\nAccuracy: %.2f%%", accuracy*100);
    
    fprintf(stderr, "\nSaving outputs ... ");
    sprintf(fileName,"%s.acc",argv[4]);
    f = fopen(fileName,"a");
    fprintf(f,"%f\n",accuracy*100);
    fclose(f);
    f = fopen(argv[6], "a");
    fprintf(f,"%d ", s->n);
    for(i = 0; i < s->n; i++)
        fprintf(f, "%lf(%d) ", s->g[i], (int)psi[i]);
    fprintf(f, "\n");
    fclose(f);
    fprintf(stderr, "Ok!\n");
    
    DestroySearchSpace(&s, _PSO_);
    DestroySubgraph(&Train);
    DestroySubgraph(&Val);
    DestroySubgraph(&Test);
    
    return 0;
}