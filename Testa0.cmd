ECHO T1 %date% - %time%
ECHO Otimo
Otimo.exe -f trace1.txt %1
ECHO LRU
LRUPilha.exe -f trace1.txt %1

ECHO T2 %date% - %time%
ECHO Otimo
Otimo.exe -f teste2.txt %1
ECHO LRU
LRUPilha.exe -f teste2.txt %1

ECHO T3 %date% - %time%
ECHO Otimo
Otimo.exe -f teste3.txt %1
ECHO LRU
LRUPilha.exe -f teste3.txt %1

ECHO T4 %date% - %time%
ECHO Otimo
Otimo.exe -f teste4.txt %1
ECHO LRU
LRUPilha.exe -f teste4.txt %1

ECHO T5 %date% - %time%
ECHO Otimo
Otimo.exe -f teste5.txt %1
ECHO LRU
LRUPilha.exe -f teste5.txt %1
