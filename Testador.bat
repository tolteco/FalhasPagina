@ECHO OFF
COLOR 0F

::Chama
CALL Testa0.cmd 5
CALL Testa0.cmd 10
CALL Testa0.cmd 20
CALL Testa0.cmd 50
CALL Testa0.cmd 70

::Desliga
SHUTDOWN /s /f /t 30
