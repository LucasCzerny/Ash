@echo off

pushd ..
.\vendor\premake\premake5.exe vs2022
popd

echo(
echo -----------
echo ^| Done :^) ^|
echo -----------

pause