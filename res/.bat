@echo off
set cnt=0
for %%A in (.sfdb) do set /a cnt+=1
echo File count = %cnt%
pause