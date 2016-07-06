LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj

CC=gcc 

FLAGS=  -g -O0
CFLAGS=''

all: libdev OPFknn OPFcluster DBN DropoutDBN DBM FeatureSelection DRBM

libdev: $(LIB)/libdev.a
	echo "libdev.a built..."

$(LIB)/libdev.a: \
$(OBJ)/dev.o \
$(OBJ)/_opf_.o \
$(OBJ)/_dbn_.o \
$(OBJ)/_dbm_.o \
$(OBJ)/_featureselection_.o \
$(OBJ)/_rbm_.o \

	ar csr $(LIB)/libdev.a \
$(OBJ)/dev.o \
$(OBJ)/_opf_.o \
$(OBJ)/_dbn_.o \
$(OBJ)/_dbm_.o \
$(OBJ)/_featureselection_.o \
$(OBJ)/_rbm_.o \

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

$(OBJ)/_featureselection_.o: $(SRC)/_featureselection_.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -c $(SRC)/_featureselection_.c -o $(OBJ)/_featureselection_.o

$(OBJ)/_rbm_.o: $(SRC)/_rbm_.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -c $(SRC)/_rbm_.c -o $(OBJ)/_rbm_.o
    
OPFknn: examples/OPF/OPFknn.c
	$(CC) $(FLAGS) examples/OPF/OPFknn.c -o examples/bin/OPFknn -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I $(INCLUDE) -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lOPF -lDeep -lopt-plus -lm;

OPFcluster: examples/OPF/OPFcluster.c
	$(CC) $(FLAGS) examples/OPF/OPFcluster.c -o examples/bin/OPFcluster -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I $(INCLUDE) -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lOPF -lDeep -lopt-plus -lm;

DBN: examples/DBN/DBN.c
	$(CC) $(FLAGS) examples/DBN/DBN.c -o examples/bin/DBN -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt-plus -lgsl -lgslcblas -lm;

DropoutDBN: examples/DBN/DropoutDBN.c
	$(CC) $(FLAGS) examples/DBN/DropoutDBN.c -o examples/bin/DropoutDBN -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
-I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt-plus -lgsl -lgslcblas -lm;

DBM: examples/DBM/DBM.c
	$(CC) $(FLAGS) examples/DBM/DBM.c -o examples/bin/DBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt-plus -lgsl -lgslcblas -lm;

FeatureSelection: examples/FeatureSelection/FeatureSelection.c
	$(CC) $(FLAGS) examples/FeatureSelection/FeatureSelection.c -o examples/bin/FeatureSelection -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt-plus -lgsl -lgslcblas -lm;

DRBM: examples/RBM/DRBM.c
	$(CC) $(FLAGS) examples/RBM/DRBM.c -o examples/bin/DRBM -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -I $(LIBDEEP_DIR)/include -I $(OPT_DIR)/include -I /usr/local/include -L $(LIB) -L $(LIBDEEP_DIR)/lib -L $(OPT_DIR)/lib -L $(OPF_DIR)/lib -ldev -lDeep -lOPF -lopt-plus -lgsl -lgslcblas -lm;

clean:
	rm -f $(LIB)/lib*.a; rm -f $(OBJ)/*.o; rm -rf examples/bin/*
