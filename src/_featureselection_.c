#include "_featureselection_.h"

/* Feature Selection */

/* It creates a subgraph only with the selected features*/
Subgraph *CreateSubgraphFromSelectedFeatures(Subgraph *sg, double *feat, int transfer_id){
    Subgraph *newsg = CreateSubgraph(sg->nnodes);
    int i, j, k, nfeats = 0;
    double r;
    
    newsg->nlabels = sg->nlabels;
    newsg->nfeats = 0;

    switch(transfer_id){
        case _S1_:
            feat = S1TransferFunction(feat, sg->nfeats, &nfeats);
            newsg->nfeats = nfeats;
        break;
        case _S2_:
            feat = S2TransferFunction(feat, sg->nfeats, &nfeats);
            newsg->nfeats = nfeats;
        break;
        case _S3_:
            feat = S3TransferFunction(feat, sg->nfeats, &nfeats);
            newsg->nfeats = nfeats;
        break;
        case _S4_:
            feat = S4TransferFunction(feat, sg->nfeats, &nfeats);
            newsg->nfeats = nfeats;
        break;
        case _V1_:
            feat = V1TransferFunction(feat, sg->nfeats, &nfeats);
            newsg->nfeats = nfeats;
        break;
        case _V2_:
            feat = V2TransferFunction(feat, sg->nfeats, &nfeats);
            newsg->nfeats = nfeats;
        break;
        case _V3_:
            feat = V3TransferFunction(feat, sg->nfeats, &nfeats);
            newsg->nfeats = nfeats;
        break;
        case _V4_:
            feat = V4TransferFunction(feat, sg->nfeats, &nfeats);
            newsg->nfeats = nfeats;
        break;
        default:
            for(i = 0; i < sg->nfeats; i++)
                if(feat[i])
                    newsg->nfeats++;
        break;
    }
    
    for (i = 0; i < newsg->nnodes; i++){
        newsg->node[i].feat = AllocFloatArray(newsg->nfeats);
        newsg->node[i].truelabel = sg->node[i].truelabel;
        newsg->node[i].position = sg->node[i].position;
        k = 0;
        for (j = 0; j < sg->nfeats; j++){
            if(feat[j])
                newsg->node[i].feat[k++] = sg->node[i].feat[j];
        }
    }

    return newsg;
}

/* Transfer functions used for feature selection */
double *S1TransferFunction(double *x, int n, int *nfeats){
    int j;
    double r;
                    
    for(j = 0; j < n; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < 1.0/(1.0+exp(-2*x[j]))){
            x[j] = 1;
            (*nfeats)++;
        }else{
            x[j] = 0;
        }
    }
    return x;
}

double *S2TransferFunction(double *x, int n, int *nfeats){
    int j;
    double r;

    for(j = 0; j < n; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < 1.0/(1.0+exp(-1*x[j]))){
            x[j] = 1;
            (*nfeats)++;
        }else{
            x[j] = 0;
        }
    }
    return x;
}

double *S3TransferFunction(double *x, int n, int *nfeats){
    int j;
    double r;

    for(j = 0; j < n; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < 1.0/(1.0+exp(-1*x[j]/2))){
            x[j] = 1;
            (*nfeats)++;
        }else{
            x[j] = 0;
        }
    }
    return x;
}

double *S4TransferFunction(double *x, int n, int *nfeats){
    int j;
    double r;

    for(j = 0; j < n; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < 1.0/(1.0+exp(-1*x[j]/3))){
            x[j] = 1;
            (*nfeats)++;
        }else{
            x[j] = 0;
        }
    }
    return x;
}

double *V1TransferFunction(double *x, int n, int *nfeats){
    int j;
    double r;

    for(j = 0; j < n; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < fabs(erf(sqrt(3.1415926535)/2*(-1*x[j])))){
            x[j] = 1;
            (*nfeats)++;
        }else{
            x[j] = 0;
        }
    }
    return x;
}

double *V2TransferFunction(double *x, int n, int *nfeats){
    int j;
    double r;

    for(j = 0; j < n; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < fabs(tanhf(-1*x[j]))){
            x[j] = 1;
            (*nfeats)++;
        }else{
            x[j] = 0;
        }
    }
    return x;
}

double *V3TransferFunction(double *x, int n, int *nfeats){
    int j;
    double r;

    for(j = 0; j < n; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < fabs(-1*x[j]/sqrt(1 + (-1*(x[j]*x[j]))))){
            x[j] = 1;
            (*nfeats)++;
        }else{
            x[j] = 0;
        }
    }
    return x;
}

double *V4TransferFunction(double *x, int n, int *nfeats){
    int j;
    double r;

    for(j = 0; j < n; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < fabs(2/3.1415926535  * atan(3.1415926535/2 * (-1*x[j])))){
            x[j] = 1;
            (*nfeats)++;
        }else{
            x[j] = 0;
        }
    }
    return x;
}

/* It executes Feature Selection with OPF evaluation
Parameters: [Train, Test, feats, transfer_id]
Train: training set
Test: testing set
feats: feature vector
transfer_id: Transfer function identifier */
double FeatureSelection(Agent *a, va_list arg){
    int transfer_id;
    double classification_error;
    Subgraph *Train = NULL, *Test = NULL;
    Subgraph *sgTrain = NULL, *sgTest = NULL;
        
    Train = va_arg(arg, Subgraph *);
    Test = va_arg(arg, Subgraph *);
    transfer_id = va_arg(arg, int);
            
    sgTrain = CreateSubgraphFromSelectedFeatures(Train, a->x, transfer_id);    
    sgTest = CreateSubgraphFromSelectedFeatures(Test, a->x, transfer_id);
    opf_OPFTraining(sgTrain);
    opf_OPFClassifying(sgTrain, sgTest);
    classification_error = opf_Accuracy(sgTest);
            
    DestroySubgraph(&sgTrain);
    DestroySubgraph(&sgTest);

    return 1-classification_error;
}
/***********************************************/
