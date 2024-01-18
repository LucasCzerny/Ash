@echo off

pushd ..
git submodule update --remote
popd

echo(
echo -----------
echo ^| Done :^) ^|
echo -----------

pause