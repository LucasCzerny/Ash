@echo off

setlocal enabledelayedexpansion

set BATCH_DIR="%~dp0"

pushd %BATCH_DIR%
pushd ..\SpinningCube\Resources\Shaders

if not exist compiled mkdir compiled

for /r %%f in (*.*) do (
	set compile=0
	
	if "%%~xf" == ".vert" set compile=1
	if "%%~xf" == ".frag" set compile=1
	if "%%~xf" == ".comp" set compile=1

	if !compile! == 1 (		
		echo Compiling %%~nxf ...
		%VULKAN_SDK%\Bin\glslc.exe "%%~nxf" -o "compiled/%%~nxf.spv"
		echo(
	)
)

echo -----------
echo ^| Done :^) ^|
echo -----------

popd
popd

pause