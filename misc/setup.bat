@echo off
REM This script creates shared directories in the root of the project

REM Function to create directories if they don't exist
:create_directories
for %%i in (%*) do (
    if not exist "%%i" (
        mkdir "%%i" && echo Created directory: %%i
    ) else (
        echo Directory already exists: %%i
    )
)
exit /b

REM Main script
:main
REM List of directories to create
call :create_directories shared shared\dll
exit /b
