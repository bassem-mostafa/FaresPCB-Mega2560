@ECHO OFF

REM "This Batch File Uploads Firmware"

REM "Switch To Script Drive"
%~d0

REM "Navigate To Script Location"
CD "%~dp0"

SET TOOL_EXE="..\waveshare setup materials\adafruit\hardware\nrf52\0.21.0\tools\adafruit-nrfutil\win32\adafruit-nrfutil.exe"
SET FIRMWARE_ZIP="%~1"

if %FIRMWARE_ZIP% == "" (
    SET /p FIRMWARE_ZIP="Firmware ZIP file (default ..\waveshare setup materials\Firmware(s)\sdardtemphumdityfw-latest.zip): "
)

SET /p CUBE_PORT="PORT (ex: COM1): "


IF %FIRMWARE_ZIP% == "" (
    SET FIRMWARE_ZIP="..\waveshare setup materials\Firmware(s)\sdardtemphumdityfw-latest.zip"
)

ECHO "Executing %TOOL_EXE% dfu serial -pkg %FIRMWARE_ZIP% -p %CUBE_PORT% -b 115200 --singlebank"

%TOOL_EXE% dfu serial -pkg %FIRMWARE_ZIP% -p %CUBE_PORT% -b 115200 --singlebank

PAUSE