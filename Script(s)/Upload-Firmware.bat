@ECHO OFF

REM "This Batch File Uploads Firmware"

REM "Switch To Script Drive"
%~d0

REM "Navigate To Script Location"
CD "%~dp0"

SET TOOL_EXE="C:\eclipse\arduinoPlugin\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude"
SET FIRMWARE_HEX="%~1"

if %FIRMWARE_HEX% == "" (
    SET /p FIRMWARE_HEX="Firmware ZIP file (default ../Release/FaresPCB-Mega2560.hex): "
)

SET /p COM_PORT="PORT (ex: COM1): "


IF %FIRMWARE_HEX% == "" (
    SET FIRMWARE_HEX="../Release/FaresPCB-Mega2560.hex"
)

ECHO "Executing %TOOL_EXE% -CC:\eclipse\arduinoPlugin\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf -patmega2560 -cwiring -P%COM_PORT% -b115200 -D -Uflash:w:%FIRMWARE_HEX%:i"

%TOOL_EXE% -CC:\eclipse\arduinoPlugin\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf -patmega2560 -cwiring -P%COM_PORT% -b115200 -D -Uflash:w:%FIRMWARE_HEX%:i

PAUSE