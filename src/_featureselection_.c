#include "_featureselection_.h"

/* Feature Selection */

/* It creates a subgraph only with the selected features*/
Subgraph *CreateSubgraphFromSelectedFeatures(Subgraph *sg, double *feat){
    Subgraph *newsg = CreateSubgraph(sg->nnodes);
    int i, j, k;

    newsg->nlabels = sg->nlabels;
    newsg->nfeats = 0;

    for (i = 0; i < sg->nfeats; i++){
        if(feat[i])
            newsg->nfeats++;
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
Subgraph *S1TransferFunction(Subgraph *sg, double *feat){
    Subgraph *newsg = CreateSubgraph(sg->nnodes);
    int i, j, k, nfeats = 0;
    double r;
                    
    for(j = 0; j < sg->nfeats; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < 1.0/(1.0+exp(-2*feat[j]))){
            feat[j] = 1;
            nfeats++;
        }else{
            feat[j] = 0;
        }
    }

    newsg->nlabels = sg->nlabels;
    newsg->nfeats = nfeats;

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

Subgraph *S2TransferFunction(Subgraph *sg, double *feat){
    Subgraph *newsg = CreateSubgraph(sg->nnodes);
    int i, j, k, nfeats = 0;
    double r;

    for(j = 0; j < sg->nfeats; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < 1.0/(1.0+exp(-1*feat[j]))){
            feat[j] = 1;
            nfeats++;
        }else{
            feat[j] = 0;
        }
    }
    newsg->nlabels = sg->nlabels;
    newsg->nfeats = nfeats;

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

Subgraph *S3TransferFunction(Subgraph *sg, double *feat){
    Subgraph *newsg = CreateSubgraph(sg->nnodes);
    int i, j, k, nfeats = 0;
    double r;

    for(j = 0; j < sg->nfeats; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < 1.0/(1.0+exp(-1*feat[j]/2))){
            feat[j] = 1;
            nfeats++;
        }else{
            feat[j] = 0;
        }
    }
    newsg->nlabels = sg->nlabels;
    newsg->nfeats = nfeats;

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

Subgraph *S4TransferFunction(Subgraph *sg, double *feat){
    Subgraph *newsg = CreateSubgraph(sg->nnodes);
    int i, j, k, nfeats = 0;
    double r;

    for(j = 0; j < sg->nfeats; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < 1.0/(1.0+exp(-1*feat[j]/3))){
            feat[j] = 1;
            nfeats++;
        }else{
            feat[j] = 0;
        }
    }
    newsg->nlabels = sg->nlabels;
    newsg->nfeats = nfeats;

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

Subgraph *V1TransferFunction(Subgraph *sg, double *feat){
    Subgraph *newsg = CreateSubgraph(sg->nnodes);
    int i, j, k, nfeats = 0;
    double r;

    for(j = 0; j < sg->nfeats; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < fabs(erf(sqrt(3.1415926535)/2*(-1*feat[j])))){
            feat[j] = 1;
            nfeats++;
        }else{
            feat[j] = 0;
        }
    }
    newsg->nlabels = sg->nlabels;
    newsg->nfeats = nfeats;

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

Subgraph *V2TransferFunction(Subgraph *sg, double *feat){
    Subgraph *newsg = CreateSubgraph(sg->nnodes);
    int i, j, k, nfeats = 0;
    double r;

    for(j = 0; j < sg->nfeats; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < fabs(tanhf(-1*feat[j]))){
            feat[j] = 1;
            nfeats++;
        }else{
            feat[j] = 0;
        }
    }
    newsg->nlabels = sg->nlabels;
    newsg->nfeats = nfeats;

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

Subgraph *V3TransferFunction(Subgraph *sg, double *feat){
    Subgraph *newsg = CreateSubgraph(sg->nnodes);
    int i, j, k, nfeats = 0;
    double r;

    for(j = 0; j < sg->nfeats; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < fabs(-1*feat[j]/sqrt(1 + (-1*(feat[j]*feat[j]))))){
            feat[j] = 1;
            nfeats++;
        }else{
            feat[j] = 0;
        }
    }
    newsg->nlabels = sg->nlabels;
    newsg->nfeats = nfeats;

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

Subgraph *V4TransferFunction(Subgraph *sg, double *feat){
    Subgraph *newsg = CreateSubgraph(sg->nnodes);
    int i, j, k, nfeats = 0;
    double r;

    for(j = 0; j < sg->nfeats; j++){
        r = GenerateUniformRandomNumber(0, 1);
        if(r < fabs(2/3.1415926535  * atan(3.1415926535/2 * (-1*feat[j])))){
            feat[j] = 1;
            nfeats++;
        }else{
            feat[j] = 0;
        }
    }
    newsg->nlabels = sg->nlabels;
    newsg->nfeats = nfeats;

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

/* It executes Feature Selection with OPF evaluation
Parameters: [Train, Test, feats, optTransfer]
Train: training set
Test: testing set
feats: feature vector
optTransfer: Transfer function pointer */
double FeatureSelection(Agent *a, va_list arg){
    double classification_error;
    TransferFunc optTransfer = NULL;
    Subgraph *Train = NULL, *Test = NULL;
    Subgraph *sgTrain = NULL, *sgTest = NULL;
        
    Train = va_arg(arg, Subgraph *);
    Test = va_arg(arg, Subgraph *);
    optTransfer = va_arg(arg, TransferFunc);
    
    sgTrain = optTransfer(Train,a->x);
    sgTest = optTransfer(Test,a->x);
    opf_OPFTraining(sgTrain);
    opf_OPFClassifying(sgTrain, sgTest);
    classification_error = opf_Accuracy(sgTest);
        
    DestroySubgraph(&sgTrain);
    DestroySubgraph(&sgTest);

    return 1/classification_error;
}
/***********************************************/