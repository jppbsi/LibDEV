LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj

OPF_DIR=../LibOPF
OPT_DIR=../LibOPT
LIBDEEP_DIR=../LibDEEP

CC=gcc

FLAGS=  -g -O0
CFLAGS=''

all: libdev OPFknn OPFcluster OPFpruning DBN DropoutDBN DropconnectDBN DBM DropoutDBM DropconnectDBM CombinatorialOPF FeatureSelectionOPF FeatureSelectionOPF_ABC FeatureSelectionOPF_AIWPSO FeatureSelectionOPF_BA FeatureSelectionOPF_BHA FeatureSelectionOPF_BSO FeatureSelectionOPF_CS FeatureSelectionOPF_FA FeatureSelectionOPF_FPA FeatureSelectionOPF_GP FeatureSelectionOPF_GSGP FeatureSelectionOPF_HS FeatureSelectionOPF_IHS FeatureSelectionOPF_MBO FeatureSelectionOPF_PSFHS FeatureSelectionOPF_WCA FeatureSelectionHamming RBM DropoutRBM DropconnectRBM DRBM DropoutDRBM GaussianDRBM DropoutGaussianDRBM EPNN GaussianRBM DropoutGaussianRBM LinearRegression LogisticRegression

#TensorDBN TensorDBM TensorRBM

libdev: $(LIB)/libdev.a
	echo "libdev.a built..."

$(LIB)/libdev.a: \
$(OBJ)/dev.o \
$(OBJ)/_opf_.o \
$(OBJ)/_dbn_.o \
$(OBJ)/_dbm_.o \
$(OBJ)/_epnn_.o \
$(OBJ)/_featureselection_.o \
$(OBJ)/_rbm_.o \
$(OBJ)/_regression_.o \

	ar csr $(LIB)/libdev.a \
$(OBJ)/dev.o \
$(OBJ)/_opf_.o \
$(OBJ)/_dbn_.o \
$(OBJ)/_dbm_.o \
$(OBJ)/_epnn_.o \
$(OBJ)/_featureselection_.o \
$(OBJ)/_rbm_.o \
$(OBJ)/_regression_.o \

$(OBJ)/dev.o: $(SRC)/dev.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -c $(SRC)/dev.c -o $(OBJ)/dev.o

$(OBJ)/_opf_.o: $(SRC)/_opf_.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -c $(SRC)/_opf_.c -o $(OBJ)/_opf_.o

$(OBJ)/_dbn_.o: $(SRC)/_dbn_.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -c $(SRC)/_dbn_.c -o $(OBJ)/_dbn_.o

$(OBJ)/_dbm_.o: $(SRC)/_dbm_.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -c $(SRC)/_dbm_.c -o $(OBJ)/_dbm_.o

$(OBJ)/_epnn_.o: $(SRC)/_epnn_.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -c $(SRC)/_epnn_.c -o $(OBJ)/_epnn_.o

$(OBJ)/_featureselection_.o: $(SRC)/_featureselection_.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -c $(SRC)/_featureselection_.c -o $(OBJ)/_featureselection_.o

$(OBJ)/_rbm_.o: $(SRC)/_rbm_.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -c $(SRC)/_rbm_.c -o $(OBJ)/_rbm_.o

$(OBJ)/_regression_.o: $(SRC)/_regression_.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -c $(SRC)/_regression_.c -o $(OBJ)/_regression_.o

OPFknn: examples/OPF/OPFknn.c
	$(CC) $(FLAGS) examples/OPF/OPFknn.c -o examples/bin/OPFknn -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I $(INCLUDE) -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lOPF -lDeep -lopt -lm;

OPFcluster: examples/OPF/OPFcluster.c
	$(CC) $(FLAGS) examples/OPF/OPFcluster.c -o examples/bin/OPFcluster -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I $(INCLUDE) -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lOPF -lDeep -lopt -lm;

OPFpruning: examples/OPF/OPFpruning.c
	$(CC) $(FLAGS) examples/OPF/OPFpruning.c -o examples/bin/OPFpruning -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I $(INCLUDE) -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lOPF -lDeep -lopt -lm;

DBN: examples/DBN/DBN.c
	$(CC) $(FLAGS) examples/DBN/DBN.c -o examples/bin/DBN -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

TensorDBN: examples/DBN/TensorDBN.c
	$(CC) $(FLAGS) examples/DBN/TensorDBN.c -o examples/bin/TensorDBN -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

DropoutDBN: examples/DBN/DropoutDBN.c
	$(CC) $(FLAGS) examples/DBN/DropoutDBN.c -o examples/bin/DropoutDBN -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
-I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

DropconnectDBN: examples/DBN/DropconnectDBN.c
	$(CC) $(FLAGS) examples/DBN/DropconnectDBN.c -o examples/bin/DropconnectDBN -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
-I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

DBM: examples/DBM/DBM.c
	$(CC) $(FLAGS) examples/DBM/DBM.c -o examples/bin/DBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

TensorDBM: examples/DBM/TensorDBM.c
	$(CC) $(FLAGS) examples/DBM/TensorDBM.c -o examples/bin/TensorDBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

DropoutDBM: examples/DBM/DropoutDBM.c
	$(CC) $(FLAGS) examples/DBM/DropoutDBM.c -o examples/bin/DropoutDBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

DropconnectDBM: examples/DBM/DropconnectDBM.c
	$(CC) $(FLAGS) examples/DBM/DropconnectDBM.c -o examples/bin/DropconnectDBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

EPNN: examples/EPNN/EPNN.c
	$(CC) $(FLAGS) examples/EPNN/EPNN.c -o examples/bin/EPNN -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

CombinatorialOPF: examples/FeatureSelection/CombinatorialOPF.c
	$(CC) $(FLAGS) examples/FeatureSelection/CombinatorialOPF.c -o examples/bin/CombinatorialOPF -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF: examples/FeatureSelection/FeatureSelectionOPF.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF.c -o examples/bin/FeatureSelectionOPF -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_ABC: examples/FeatureSelection/FeatureSelectionOPF_ABC.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_ABC.c -o examples/bin/FeatureSelectionOPF_ABC -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_AIWPSO: examples/FeatureSelection/FeatureSelectionOPF_AIWPSO.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_AIWPSO.c -o examples/bin/FeatureSelectionOPF_AIWPSO -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_BA: examples/FeatureSelection/FeatureSelectionOPF_BA.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_BA.c -o examples/bin/FeatureSelectionOPF_BA -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_BHA: examples/FeatureSelection/FeatureSelectionOPF_BHA.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_BHA.c -o examples/bin/FeatureSelectionOPF_BHA -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_BSO: examples/FeatureSelection/FeatureSelectionOPF_BSO.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_BSO.c -o examples/bin/FeatureSelectionOPF_BSO -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_CS: examples/FeatureSelection/FeatureSelectionOPF_CS.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_CS.c -o examples/bin/FeatureSelectionOPF_CS -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_FA: examples/FeatureSelection/FeatureSelectionOPF_FA.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_FA.c -o examples/bin/FeatureSelectionOPF_FA -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_FPA: examples/FeatureSelection/FeatureSelectionOPF_FPA.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_FPA.c -o examples/bin/FeatureSelectionOPF_FPA -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_GP: examples/FeatureSelection/FeatureSelectionOPF_GP.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_GP.c -o examples/bin/FeatureSelectionOPF_GP -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_GSGP: examples/FeatureSelection/FeatureSelectionOPF_GSGP.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_GSGP.c -o examples/bin/FeatureSelectionOPF_GSGP -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_HS: examples/FeatureSelection/FeatureSelectionOPF_HS.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_HS.c -o examples/bin/FeatureSelectionOPF_HS -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_IHS: examples/FeatureSelection/FeatureSelectionOPF_IHS.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_IHS.c -o examples/bin/FeatureSelectionOPF_IHS -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_MBO: examples/FeatureSelection/FeatureSelectionOPF_MBO.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_MBO.c -o examples/bin/FeatureSelectionOPF_MBO -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_PSFHS: examples/FeatureSelection/FeatureSelectionOPF_PSFHS.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_PSFHS.c -o examples/bin/FeatureSelectionOPF_PSFHS -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionOPF_WCA: examples/FeatureSelection/FeatureSelectionOPF_WCA.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionOPF_WCA.c -o examples/bin/FeatureSelectionOPF_WCA -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

FeatureSelectionHamming: examples/FeatureSelection/FeatureSelectionHamming.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelectionHamming.c -o examples/bin/FeatureSelectionHamming -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

RBM: examples/RBM/RBM.c
	$(CC) $(FLAGS) examples/RBM/RBM.c -o examples/bin/RBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

TensorRBM: examples/RBM/TensorRBM.c
	$(CC) $(FLAGS) examples/RBM/TensorRBM.c -o examples/bin/TensorRBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

DropoutRBM: examples/RBM/DropoutRBM.c
	$(CC) $(FLAGS) examples/RBM/DropoutRBM.c -o examples/bin/DropoutRBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

DropconnectRBM: examples/RBM/DropconnectRBM.c
	$(CC) $(FLAGS) examples/RBM/DropconnectRBM.c -o examples/bin/DropconnectRBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

DRBM: examples/RBM/DRBM.c
	$(CC) $(FLAGS) examples/RBM/DRBM.c -o examples/bin/DRBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

DropoutDRBM: examples/RBM/DropoutDRBM.c
	$(CC) $(FLAGS) examples/RBM/DropoutDRBM.c -o examples/bin/DropoutDRBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

GaussianDRBM: examples/RBM/GaussianDRBM.c
	$(CC) $(FLAGS) examples/RBM/GaussianDRBM.c -o examples/bin/GaussianDRBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

DropoutGaussianDRBM: examples/RBM/DropoutGaussianDRBM.c
	$(CC) $(FLAGS) examples/RBM/DropoutGaussianDRBM.c -o examples/bin/DropoutGaussianDRBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

GaussianRBM: examples/RBM/GaussianRBM.c
	$(CC) $(FLAGS) examples/RBM/GaussianRBM.c -o examples/bin/GaussianRBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

DropoutGaussianRBM: examples/RBM/DropoutGaussianRBM.c
	$(CC) $(FLAGS) examples/RBM/DropoutGaussianRBM.c -o examples/bin/DropoutGaussianRBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

LinearRegression: examples/LinearRegression/LinearRegression.c
	$(CC) $(FLAGS) examples/LinearRegression/LinearRegression.c -o examples/bin/LinearRegression -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;

LogisticRegression: examples/LogisticRegression/LogisticRegression.c
	$(CC) $(FLAGS) examples/LogisticRegression/LogisticRegression.c -o examples/bin/LogisticRegression -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt -lgsl -lgslcblas -lm;


clean:
	rm -f $(LIB)/lib*.a; rm -f $(OBJ)/*.o; rm -rf examples/bin/*
