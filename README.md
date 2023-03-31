# ChampionshipSim

## Introduction

This project was undertaken as part of Cergy Paris University's IT bachelor's degree. It simulates a tournament made of several matches bringing together two teams each. The team number must therefore be a power of two. Those teams can be the default ones or they can be fetched from a file as well as other configs for the simulation. The result is stored in a file which can be chosen when calling the program.

## Usage

> This program needs a C compiler in order to work properly.

### Compilation

> Doxygen and graphviz are required in order to compile the documentation. To install them, use this command:
> `sudo apt-get install graphviz doxygen`

You can compile using the provided makefile. It includes several commands to perform various actions listed below:

- `make` Compiles the program
- `make doxygen` Compiles the documentation
- `make run` Runs the program without any parameters (runs the program with all default values)
- `make run-manual` Runs the program with default values and manual score input mode
- `make run-input` Runs the program with input file
- `make run-output` Runs the program with output file
- `make clean` Removes build and output directories as well as their contents

### Input

An input file can be provided. It needs to be written in a specific format in order to be correctly read by the application: `team1;team2;...;time=X` where `X` is the duration of a match in seconds.

### Options

Some options can be provided when calling the program, as listed below:

- `-i/--input <path>` to pass an input file to the program.
- `-o/--output <path>` to pass an output file to the program.
- `-m/--manual-input` to use manual score input for the simulation.
