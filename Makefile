LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj

CC=gcc

FLAGS=  -g -O0
CFLAGS=''

all: libdev OPFknn OPFcluster OPFpruning DBN TensorDBN DropoutDBN DropconnectDBN DBM TensorDBM DropoutDBM DropconnectDBM CombinatorialOPF FeatureSelectionOPF FeatureSelectionHamming RBM TensorRBM DropoutRBM DropconnectRBM DRBM DropoutDRBM GaussianDRBM DropoutGaussianDRBM EPNN GaussianRBM DropoutGaussianRBM LinearRegression LogisticRegression

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
