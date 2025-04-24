@echo off
setlocal enabledelayedexpansion

:: Colors for output (Windows 10+)
set "GREEN=[92m"
set "RED=[91m"
set "NC=[0m"

:: Function to print colored messages
call :print_message "Starting build process..."

:: Check if build directory exists, if not create it
if not exist "build" (
    call :print_message "Creating build directory..."
    mkdir build
)

:: Enter build directory
cd build

:: Check if CMake has been run before
if not exist "Makefile" (
    call :print_message "Running CMake..."
    cmake ..
    if errorlevel 1 (
        call :print_error "CMake failed!"
        exit /b 1
    )
)

:: Build the project
call :print_message "Building the project..."
cmake --build .
if errorlevel 1 (
    call :print_error "Build failed!"
    exit /b 1
)

:: Check if the executable exists and run it
if exist "bin\Battleship.exe" (
    call :print_message "Build successful! Running the game..."
    bin\Battleship.exe
) else (
    call :print_error "Executable not found!"
    exit /b 1
)

exit /b 0

:print_message
echo %GREEN%%~1%NC%
exit /b 0

:print_error
echo %RED%%~1%NC%
exit /b 0 