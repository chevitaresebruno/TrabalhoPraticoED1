gcc -o lib\bin\mainfile.o main.c -c -W -Wall -ansi -pedantic

gcc -o mainFile.exe lib\bin\mainfile.o lib\bin\patient.o lib\bin\patientQueue.o lib\bin\db.o

del /Q lib\bin\mainfile.o
