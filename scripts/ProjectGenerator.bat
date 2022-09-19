@ECHO OFF
PUSHD ..
CALL vendor\bin\premake\premake5.exe vs2022
POPD
PAUSE