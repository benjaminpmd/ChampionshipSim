# ChampionshipSim

## Introduction

This project is realized as part as the Cergy Paris University IT licence. It simulate match between teams. The team number must be a power of two. Those teams can be the default ones or they can be fetch from a file as well as other config for the simulation. The result is stored in a file, and this one can be setup when calling the program.

## Usage

> This program needs a compiler for C in order to work properly

### Compilation

> The compilation of the documentation require doxygen and graphviz, to install them, use the command:
> `sudo apt-get install graphviz doxygen`

The compilation can be done using the makefile provided. It includes several commands to perform various actions listed below:

- `make` Compiles the program
- `make doxygen` Compiles the documentation
- `make run` Runs the program without any parameters (run the program with all default values)
- `make run-manual` Runs the program with default values with manual score input mode
- `make run-input` Runs the program with input file
- `make run-output` Runs the program with output file
- `make clean` Removes build and output directories as well as their contents

### Input

An input file can be provided, it needs to adopt a specific format in order to be correctly read by the application: `team1;team2;...;time=X` where `X` is the duration of a match in seconds.

### Options

Some options can be provided when calling the program, their are listed below:

- `-i/--input <path>` to pass an input file to the program.
- `-o/--output <path>` to pass an output file to the program.
- `-m/--manual-input` to use the score manual input for the simulation.
