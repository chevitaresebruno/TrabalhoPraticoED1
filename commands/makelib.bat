copy lib\src\patient\patient.c patient.c
copy lib\src\patient\patientQueue.c patientQueue.c
copy lib\src\db\db.c db.c

gcc -o lib\bin\patient.o patient.c -c -W -Wall -ansi -pedantic
gcc -o lib\bin\patientQueue.o patientQueue.c -c -W -Wall -ansi -pedantic
gcc -o lib\bin\db.o db.c -c -W -Wall -ansi -pedantic


del /Q patientQueue.c
del /Q patient.c
del /Q db.c