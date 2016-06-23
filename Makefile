LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj

CC=gcc 

FLAGS=  -g -O0
CFLAGS=''

all: libdev

libdev: $(LIB)/libdev.a
	echo "libdev.a built..."

$(LIB)/libdev.a: \
$(OBJ)/dev.o \
$(OBJ)/_opf_.o \

	ar csr $(LIB)/libdev.a \
$(OBJ)/dev.o \
$(OBJ)/_opf_.o \


$(OBJ)/dev.o: $(SRC)/dev.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -c $(SRC)/dev.c -o $(OBJ)/dev.o

$(OBJ)/_opf_.o: $(SRC)/_opf_.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(OPF_DIR)/include -I $(OPF_DIR)/include/util \
    -L $(OPF_DIR)/lib -c $(SRC)/_opf_.c -o $(OBJ)/_opf_.o -lopf

clean:
	rm -f $(LIB)/lib*.a; rm -f $(OBJ)/*.o
