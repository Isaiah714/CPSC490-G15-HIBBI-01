# Prototype

Proof-of-concept code for 〈Constrained Hardware/ECS architecture Game Engine〉.

## Setting up environment for Windows

To install cmake type this command into powershell
```bash
winget install Kitware.CMake
```
Refresh terminal and type this command to confirm installation
```bash
cmake --version
```    

To install Ninja type this command into powershell
```bash
winget install Ninja-build.Ninja
```
Refresh terminal and type this command to confirm installation
```bash
Ninja --version
```

To install C++26 
    Click this link to install MSYS64 (follow its installation steps) - https://www.msys2.org/  
    Come back here when you successfully installed MSYS64, then continue below

Open up the MSYS2 UCRT64 terminal and type in these commands 
```bash
pacman -Syu
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```

Add compiler path to evnironment variable 
        Press the Windows key and R key   
        Type sysdm.cpl into the box   
        Click on the advanced tab 
        Click on environment variables  
        Under the the little window that says System Variables, double click on Path  
        Click new, then type in the file path of where the file is installed    
          GCC/G++ default path should something like this - C:\msys64\ucrt64\bin
          If your default path is different, use that one   
        After applying the changes, you should be good to build the project   

## How to build

```bash
# IF on Linux
cd prototype
cmake -B build -G 'Unix Makefiles'
cd build
make

# IF on Windows
cd prototype
cmake -B build -G Ninja
cd build
Ninja

# To use the Debugger, write this command when building the project
cmake -B build -G <Write Generator Here> -D CMAKE_BUILD_TYPE=Debug
```

## How to run

```bash
cd prototype/build

# IF on Linux
./run

# IF on windows
./run.exe           
```

## How to test

```bash
cd prototype

# IF the project hasn't been built yet, otherwise skip this step
cmake --build build --target test_engine_components

cd build

# IF on Linux
./test_engine_components

# IF on Windows
./test_engine_components.exe
```

## What it proves

That the basic implementation of ECS system works

## Status

| Sprint | Increment |
|---|---|
| Sprint 3 | Tests that check the basic ECS system |