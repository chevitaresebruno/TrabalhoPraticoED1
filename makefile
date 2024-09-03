# My second makefile

# Name of the project
PROJ_NAME=main

# Clear Command
ifeq ($(OS),Windows_NT)
	REMOVE=del /Q .\lib\bin\*.o *.exe $(PROJ_NAME)
else
	REMOVE=rm -rf del /Q ./lib/bin/*.o *.exe $(PROJ_NAME) *~
endif


# files
BIN=lib/bin
SRC=lib/src

# Object files
OBJ=$(C_SOURCE:.c=.o)

# Compiler
CC=gcc

# Flags for compiler
CC_FLAGS=-c         \
         -g         \
         -I.        \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic

#
# Compilation and linking
#
all: $(PROJ_NAME)
	$(CC) -o $(PROJ_NAME).exe $(BIN)/condition.o $(BIN)/xrmo.o $(BIN)/ai.o $(BIN)/patient.o $(BIN)/exam.o $(BIN)/report.o $(BIN)/patientQueue.o $(BIN)/xrmm.o $(BIN)/examQueue.o $(BIN)/medic.o $(BIN)/db.o $(BIN)/main.o

$(PROJ_NAME): condition.o xrmo.o ai.o patient.o exam.o report.o patientQueue.o xrmm.o examQueue.o medic.o db.o
	$(CC) -o $(BIN)/main.o main.c $(CC_FLAGS)

condition.o:
	$(CC) -o $(BIN)/condition.o $(SRC)/adt/condition.c $(CC_FLAGS)

xrmo.o:
	$(CC) -o $(BIN)/xrmo.o $(SRC)/adt/xrmo.c $(CC_FLAGS)

ai.o:
	$(CC) -o $(BIN)/ai.o $(SRC)/ai/ai.c $(CC_FLAGS)

patient.o:
	$(CC) -o $(BIN)/patient.o $(SRC)/obj/patient.c $(CC_FLAGS)

exam.o:
	$(CC) -o $(BIN)/exam.o $(SRC)/obj/exam.c $(CC_FLAGS)

report.o:
	$(CC) -o $(BIN)/report.o $(SRC)/obj/report.c $(CC_FLAGS)

patientQueue.o:
	$(CC) -o $(BIN)/patientQueue.o $(SRC)/handlers/patientQueue.c $(CC_FLAGS)

xrmm.o:
	$(CC) -o $(BIN)/xrmm.o $(SRC)/handlers/xrmm.c $(CC_FLAGS)

examQueue.o:
	$(CC) -o $(BIN)/examQueue.o $(SRC)/handlers/examQueue.c $(CC_FLAGS)

medic.o:
	$(CC) -o $(BIN)/medic.o $(SRC)/handlers/medic.c $(CC_FLAGS)

db.o:
	$(CC) -o $(BIN)/db.o $(SRC)/db/db.c $(CC_FLAGS)

clean:
	$(REMOVE)