CFLAGS = -Wall -Iheader
# Remove this -lm flag on Mac
LDLIBS = -lm

SRC = src
HEADER = header

# Object files
OBJS = global.o bt.o bst.o avl.o main.o ui.o

# Target executable
tree: $(OBJS)
		gcc $(CFLAGS) -o tree $(addprefix $(SRC)/, $(OBJS)) $(LDLIBS)

# Object file dependencies
global.o: $(SRC)/global.c $(HEADER)/global.h
		gcc $(CFLAGS) -c $(SRC)/global.c -o $(SRC)/global.o

main.o: $(SRC)/main.c $(HEADER)/ui.h $(HEADER)/global.h
		gcc $(CFLAGS) -c $(SRC)/main.c -o $(SRC)/main.o

ui.o: $(SRC)/ui.c $(HEADER)/ui.h $(HEADER)/global.h
		gcc $(CFLAGS) -c $(SRC)/ui.c -o $(SRC)/ui.o

bt.o: $(SRC)/bt.c $(HEADER)/bt.h
		gcc $(CFLAGS) -c $(SRC)/bt.c -o $(SRC)/bt.o

bst.o: $(SRC)/bst.c $(HEADER)/bt.h $(HEADER)/bst.h $(HEADER)/global.h
		gcc $(CFLAGS) -c $(SRC)/bst.c -o $(SRC)/bst.o

avl.o: $(SRC)/avl.c $(HEADER)/bt.h $(HEADER)/bst.h $(HEADER)/avl.h $(HEADER)/global.h
		gcc $(CFLAGS) -c $(SRC)/avl.c -o $(SRC)/avl.o

# Clean up
clean:
		rm -f $(SRC)/*.o
		rm -f tree
