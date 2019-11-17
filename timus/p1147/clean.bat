@echo off
FOR /d /r . %%d IN (x64) DO @if EXIST "%%d" RD /s/q "%%d"
IF EXIST Apps (
	RD /s/q Apps
)
IF EXIST ".vs" (
	RD /s/q ".vs"
)
DEL /S /Q *.user >>nul 2>>nul