$ErrorActionPreference = "Stop"

function Test-Command($Name) {
    return [bool](Get-Command $Name -ErrorAction SilentlyContinue)
}

$localToolchain = Join-Path $PSScriptRoot "tools\w64devkit\bin"
if (Test-Path (Join-Path $localToolchain "g++.exe")) {
    $env:PATH = "$localToolchain;$env:PATH"
}

if (-not (Test-Command "g++")) {
    Write-Error "g++ was not found. Install MinGW-w64/MSYS2 and add g++ to PATH."
}

$make = $null
$localMake = Join-Path $localToolchain "mingw32-make.exe"
if (Test-Path $localMake) {
    $make = $localMake
} elseif (Test-Command "mingw32-make") {
    $make = "mingw32-make"
} elseif (Test-Command "make") {
    $make = "make"
}

if (-not $make) {
    Write-Error "make was not found. On Windows, install MinGW/MSYS2 or run: g++ -Wall -std=c++17 -Isrc -o build\program.exe src\*.cpp src\data_structures\*.cpp -lraylib"
}

& $make run

if ($LASTEXITCODE -ne 0) {
    Write-Host ""
    Write-Host "Build failed. If the error mentions raylib.h or -lraylib, install Raylib for the same MinGW-w64 compiler that provides g++." -ForegroundColor Yellow
    exit $LASTEXITCODE
}
