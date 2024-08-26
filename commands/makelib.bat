copy lib\src\patient\patient.c patient.c
copy lib\src\patient\patientQueue.c patientQueue.c
copy lib\src\exam\exam.c exam.c
copy lib\src\exam\condition.c condition.c
copy lib\src\xray\xrmm.c xrmm.c
copy lib\src\exam\examQueue.c examQueue.c
copy lib\src\ai\ai.c ai.c
copy lib\src\db\db.c db.c
copy lib\src\simulation\simulation.c simulation.c
copy lib\src\.extern\cjson\cJSON.c cJSON.c

gcc -o lib\bin\cJSON.o cJson.c -c -W -Wall -ansi -pedantic
gcc -o lib\bin\xrmm.o xrmm.c -c -W -Wall -ansi -pedantic
gcc -o lib\bin\patient.o patient.c -c -W -Wall -ansi -pedantic
gcc -o lib\bin\patientQueue.o patientQueue.c -c -W -Wall -ansi -pedantic
gcc -o lib\bin\exam.o exam.c -c -W -Wall -ansi -pedantic
gcc -o lib\bin\condition.o condition.c -c -W -Wall -ansi -pedantic
gcc -o lib\bin\examQueue.o examQueue.c -c -W -Wall -ansi -pedantic
gcc -o lib\bin\ai.o ai.c -c -W -Wall -ansi -pedantic
gcc -o lib\bin\db.o db.c -c -W -Wall -ansi -pedantic
gcc -o lib\bin\simulation.o simulation.c -c -W -Wall -ansi -pedantic

del /Q patientQueue.c
del /Q patient.c
del /Q db.c
del /Q simulation.c
del /Q exam.c
del /Q examQueue.c
del /Q condition.c
del /Q xrmm.c 
del /Q ai.c 
del /Q cJSON.c