# Prototype

Proof-of-concept code for 〈Constrained Hardware/ECS architecture Game Engine〉.

## Installing Dependencies
```bash
# IF on Linux
cd prototype
chmod +x setup.sh
./setup.sh

#IF on Windows
cd prototype
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope Process
.\setup.ps1
```

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
pip install pytest              # once
python -m pytest tests -q       # 4 tests
```

CI runs exactly these tests on every pull request (job **Prototype build &
tests**). If you use Node instead of Python, put a `package.json` here with a
`test` script and CI will detect and run that instead.

## What it proves

That credentials can be checked and a session token issued, with unknown-user
and wrong-password failures indistinguishable to the caller — the riskiest
assumption in 〈the epic this belongs to〉.

## Status

| Sprint | Increment |
|---|---|
| v0 (Sep 27) | login check + 4 tests (this example) |
| Sprint 1 | 〈what you added〉 |