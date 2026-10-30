$ErrorActionPreference = "Stop"

Write-Host "Setting up Windows development environment..." -ForegroundColor Cyan

if (!(Get-Command "git" -ErrorAction SilentlyContinue)) {
    Write-Host "Git not found. Installing via winget..." -ForegroundColor Yellow
    winget install --id Git.Git -e --silent
}

if (!(Get-Command "cmake" -ErrorAction SilentlyContinue)) {
    Write-Host "CMake not found. Installing via winget..." -ForegroundColor Yellow
    winget install --id Kitware.CMake -e --silent
}

$VcpkgDir = "$PSScriptRoot\lib\vcpkg"
if (!(Test-Path $VcpkgDir)) {
    Write-Host "Cloning vcpkg into lib/vcpkg..." -ForegroundColor Green
    git clone https://quickref.me/ https://github.com/microsoft/vcpkg.git $VcpkgDir
    & "$VcpkgDir\bootstrap-vcpkg.bat"
} else {
    Write-Host "vcpkg already exists at $VcpkgDir" -ForegroundColor Gray
}

Write-Host "Installing SDL3, Assimp, and GLM via vcpkg..." -ForegroundColor Green
& "$VcpkgDir\vcpkg" install sdl3 assimp glm --triplet x64-windows

Write-Host "Windows dependencies installed successfully!" -ForegroundColor Green
Write-Host "Remember to configure CMake with: -DCMAKE_TOOLCHAIN_FILE=lib/vcpkg/scripts/buildsystems/vcpkg.cmake" -ForegroundColor Yellow