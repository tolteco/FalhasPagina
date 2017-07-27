@ECHO OFF
COLOR 0F

::Chama
CALL Testa0.cmd trace1.txt
CALL Testa1.cmd trace1.txt
CALL Testa0.cmd teste2.txt
CALL Testa1.cmd teste2.txt
CALL Testa0.cmd teste3.txt
CALL Testa1.cmd teste3.txt
CALL Testa0.cmd teste4.txt
CALL Testa1.cmd teste4.txt
CALL Testa0.cmd teste5.txt
CALL Testa1.cmd teste5.txt

::Desliga
SHUTDOWN /s /f /t 30
