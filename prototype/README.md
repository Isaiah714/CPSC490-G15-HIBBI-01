# Prototype

Proof-of-concept code for 〈Constrained Hardware/ECS architecture Game Engine〉.

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