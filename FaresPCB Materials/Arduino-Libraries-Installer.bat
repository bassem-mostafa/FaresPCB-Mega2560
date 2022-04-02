@ECHO OFF

REM "This Batch File Requires Administrative Permissions"
REM "This Batch File Links Project Libraries Into User Arduino Libraries"

REM "Switch To Script Drive"
%~d0

REM "Navigate To Script Location"
CD "%~dp0"

REM "Prompt For User Directory"
SET /p USER_DIR="User Directory (ex: C:\Users\<USER_DIR>): "

REM "If Not Provided, Use Current Logged-In Username"
IF "%USER_DIR%"=="" (
    SET USER_DIR=%USERNAME%
)

REM "Remove Libraries From Destination Folder If Exists"
FOR /D %%f in ("C:\Users\%USER_DIR%\Documents\Arduino\libraries\FaresPCB_"*) DO (
    RMDIR /S /Q "%%f"
)

REM "Make Libraries Links From Project Folders Into Destination Folder"
FOR /D %%f in ("%CD%\Driver(s)\FaresPCB_"*) DO (
    ECHO "Creating Link For %%~nf From %%f To C:\Users\%USER_DIR%\Documents\Arduino\libraries\%%~nf"
    MKLINK /D "C:\Users\%USER_DIR%\Documents\Arduino\libraries\%%~nf" "%%f"
)

REM "Remove Template Libraries Links From Destination Folder"
FOR /D %%f in ("C:\Users\%USER_DIR%\Documents\Arduino\libraries\*Template"*) DO (
    RMDIR /S /Q "%%f"
)
PAUSE