@ECHO OFF

REM "This Batch File Requires Administrative Permissions"
REM "This Batch File Links Arduino Core Into Specified Folder"
REM "       Default Eclipse Arduino Packages Folder 'ECLIPSE_HOME\arduinoPlugin\packages'"
REM "       Default Arduino Packages Folder 'C:\Users\%USERNAME%\AppData\Local\Arduino15\packages'"

REM "Switch To Script Drive"
%~d0

REM "Navigate To Script Location"
CD "%~dp0"

REM "Get Packages Directory"
SET PACKAGES_DIR="%~1"

REM "If Not Provided, Prompt For Packages Directory"
IF %PACKAGES_DIR% == "" (
    SET /p PACKAGES_DIR="Packages Directory (Arduino Packages Directory Path (ex: ECLIPSE_HOME\arduinoPlugin\packages): "
)

ECHO "Arduino Packages Directory Path: %PACKAGES_DIR%"

IF NOT %PACKAGES_DIR% == "" (
    RMDIR /S /Q "%PACKAGES_DIR%\adafruit\hardware\nrf52\0.21.0"
    REM ECHO "Creating direcory %PACKAGES_DIR%\adafruit\hardware\nrf52\"
    REM setlocal enableextensions
    REM MD "%PACKAGES_DIR%\adafruit\hardware\nrf52\"
    ECHO "Creating Link Into %PACKAGES_DIR%\adafruit\hardware\nrf52\0.21.0 To %cd%\..\waveshare setup materials\adafruit\hardware\nrf52\0.21.0"
    MKLINK /D "%PACKAGES_DIR%\adafruit\hardware\nrf52\0.21.0" "%cd%\..\waveshare setup materials\adafruit\hardware\nrf52\0.21.0"
) ELSE (
    ECHO "Please Specify The Arduino Packages Directory Path (ex: ECLIPSE_HOME\arduinoPlugin\packages)"
)

PAUSE