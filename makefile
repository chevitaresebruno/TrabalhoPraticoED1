PROJECT_NAME=mainFile
CC=gcc
CC_FLAGS=-c -W -Wall -ansi -pedantic

all: lib $(PROJECT_NAME)

lib: patient.o patientQueue.o db.o simulation.o

patient.o: lib/src/patient/patient.c lib/include/shared.h lib/include/patient/patient.h
	$(CC) -o lib/bin/patient.o lib/src/patient/patient.c $(CC_FLAGS)

patientQueue.o: lib/src/patient/patientQueue.c lib/include/shared.h lib/include/patient/patientQueue.h
	$(CC) -o lib/bin/patientQueue.o lib/src/patient/patientQueue.c $(CC_FLAGS)

db.o: lib/src/db/db.c env.h lib/include/shared.h lib/include/db/db.h
	$(CC) -o lib/bin/db.o lib/src/db/db.c $(CC_FLAGS)

simulation.o: lib/src/simulation/simulation.c env.h lib/include/shared.h lib/include/simulation/simulation.h
	$(CC) -o lib/bin/simulation.o lib/src/simulation/simulation.c $(CC_FLAGS)

$(PROJECT_NAME): mainFile.o
	$(CC) -o $(PROJECT_NAME).exe lib/bin/mainFile.o lib/bin/patient lib/bin/patientQueue lib/bin/db lib/bin/simulation

mainFile.o: main.c env.h lib/include/shared.h
	$(CC) -o lib/bin/mainFile.o main.c $(CC_FLAGS)