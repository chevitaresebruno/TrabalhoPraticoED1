gcc -o lib\bin\mainfile.o main.c -c -W -Wall -ansi -pedantic

gcc -o mainFile.exe lib\bin\mainfile.o lib\bin\cJSON.o lib\bin\ai.o lib\bin\patient.o lib\bin\patientQueue.o lib\bin\exam.o lib\bin\examQueue.o lib\bin\condition.o lib\bin\xrmm.o lib\bin\db.o lib\bin\simulation.o

del /Q lib\bin\mainfile.o
