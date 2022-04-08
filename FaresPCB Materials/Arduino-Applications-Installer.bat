@ECHO OFF

REM "This Batch File Requires Administrative Permissions"
REM "This Batch File Links Project Libraries Into User Arduino Libraries"
REM "Reference(s)"
REM "- https://en.wikibooks.org/wiki/Windows_Batch_Scripting"
REM "- https://stackoverflow.com/questions/4051883/batch-script-how-to-check-for-admin-rights"

REM "Makes Variables Local To Script, And Assignable"
SETLOCAL ENABLEDELAYEDEXPANSION

REM "Checks Administrative Permissions"
NET SESSION >NUL 2>&1

IF NOT %ERRORLEVEL% == 0 (
    ECHO Requires Administrative Permissions
    PAUSE
    EXIT /B 1
)

REM "Switches/Navigates To Script's Location"
%~d0 & CD "%~dp0"

REM "Prompts For User Directory"
SET /P USER_DIR = "User Directory (default: C:\Users\%USERNAME%): "

REM "Uses Current Logged-In User Directory If Not Provided"
IF "%USER_DIR%"=="" (
    SET USER_DIR=C:\Users\%USERNAME%
)

REM "Displaying User Directory"
ECHO Using User Directory '%USER_DIR%'

REM "Removes Existing Applications From User Directory"
FOR /D %%f IN ("%CD%\Application(s)\FaresPCB_*") DO (
    IF EXIST "%USER_DIR%\Documents\Arduino\libraries\%%~nf" (
        ECHO Remove Detected %USER_DIR%\Documents\Arduino\libraries\%%~nf
        RMDIR /S /Q "%USER_DIR%\Documents\Arduino\libraries\%%~nf"
    )
)

REM "Links Libraries From Project Folders Into User Directory"
FOR /D %%f IN ("%CD%\Application(s)\FaresPCB_*") DO (
    SET PROJECT_APPLICATION=%%~nf
    IF "%%~nf"=="!PROJECT_APPLICATION:Template=!" (
        ECHO Linking %%~nf From %%f To %USER_DIR%\Documents\Arduino\libraries\%%~nf
        MKLINK /D "%USER_DIR%\Documents\Arduino\libraries\%%~nf" "%%f"
    )
)

ENDLOCAL
PAUSE