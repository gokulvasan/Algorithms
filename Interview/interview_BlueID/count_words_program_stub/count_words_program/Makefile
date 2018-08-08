
SRC=./src/main/c
INC=./src/main/include/
FILE= count_word.c

EXEC=count_letters
ELFEXT=elf
MAPEXT=map
BIN=bin

CC=gcc
LINK= -Wl,-Map
OBJ= -c
INCLUDE= -I$(INC)
CFLAGS= $(INCLUDE) $(LINK)=$(EXEC).$(MAPEXT)

posix: CC=gcc
arm: CC=arm-none-eabi-gcc

debug:
	$(CC) $(OBJ) $(INCLUDE) $(SRC)/$(FILE) -o $(EXEC).$(ELFEXT)

posix arm:
	$(CC) $(CFLAGS) $(SRC)/$(FILE) -o $(EXEC).$(BIN)
