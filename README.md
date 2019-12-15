# Game of Life

![Example][0]

A command line simultion program for [Conway's Game of Life][1] with virtually
no restriction on cell growth.

## Table of Contents
+ [Installation](#installation)
+ [Usage](#usage)
+ [Tips and Tricks](#tips-and-tricks)

## Installation <a name = "installation"></a>

0. Install make and g++

1. Clone this repository

2. Run `make` to build the project

## Usage <a name = "usage"></a>

Building this project provides two separate programs, driver.exe and timer.exe.

### Driver

The driver program is the one shown in the example GIF at the top. Its usage is
as follows:

```
Usage: driver.exe PATTERN_FILENAME
```

It takes the filename of a pattern in [RLE format][2] as its only argument,
initializes the grid to that pattern, prints it out, and waits for user input.

The program reacts to user input in the following ways:

1. If a blank line is entered, the generation is incremented by one and the new
grid configuration is printed

2. If a positive integer x is entered, the generation is incremented by x and
the new grid configuration is printed

3. All other input is ignored

To end the program, send the EOF signal (Ctrl+D on Linux and MacOS, Ctrl+Z on
Windows).

### Timer

The timer program is used to measure the execution time of going from generation
0 to generation x for a given starting grid configuration and a given positive
integer x. Its usage is as follows:

```
Usage: timer.exe PATTERN_FILENAME NUM_ITERATIONS [--stats]
```

Like the driver program, the timer program takes the filename for a pattern file
in RLE format as its first argument. In addition to that, it takes the number of
iterations as its second argument, and an optional third argument "--stats".

By default the timer program only prints the execution time. If the optional
argument is provided, it will also print statistics about the initial and final
grid configurations, in that order, before printing the execution time. The
statistics printed are as follows:

+ `size` - the number of living cells in the grid
+ `dims` - the dimensions of the smallest bounding box containing all living
cells in the grid, format: width by height
+ `span` - the positions of the upper-left-most and bottom-right-most living
cells in the grid, format: min_pos to max_pos

### Examples

Let's try using driver.exe on glider.rle. The outupt, with extra newlines
removed, is shown below.

```
[mokhan@aspire life]$ ./driver.exe glider.rle
Generation 0
.O.
..O
OOO

Generation 1
O.O
.OO
.O.

Generation 2
..O
O.O
.OO

Generation 3
O..
.OO
OO.

Generation 4
.O.
..O
OOO
```

Okay, so this pattern seems to oscillate back to its original configuration.
What's going on? To see, we run timer.exe with its optional argument.

```
[mokhan@aspire life]$ ./timer.exe glider.rle 100 --stats
size    5
dims    3 by 3
span    (0,0) to (2,2)

size    5
dims    3 by 3
span    (25,25) to (27,27)

time    0m0.000s
```

From the initial and final spans, it's now apparent that our pattern seems to
be moving across the grid! Seems like the output of the driver program doesn't
do the "motion" of our pattern justice.

## Tips and Tricks <a name = "tips-and-tricks"></a>

Here are some tips and tricks for this project.

### Provided Pattern Files

From the repository, you might have noticed that there are several pattern
files provided, namely

+ glider.rle
+ gosperglidergun.rle
+ glidertrain.rle
+ rpentominio.rle
+ breeder1.rle

I suggest trying out the first four with the driver program, they have really
interesting and different outputs!

The last file, breeder1.rle does not fit in a normal terminal window in its
initial configuration, so I don't recommend using the driver program with it.
It was included because it has the interesting property that the number of
cells grows quadratically with the number of generations. It may be interesting
to test that out for yourself.

Finally, can you guess the growth functions for the other patterns without
running tests with the timer program? How about with running tests with the
timer program? Try it out!

### Getting More Pattern Files

All the pattern files included were taken from [LifeWiki][3]. If you want, you
can browse for more patterns on this website, download the RLE pattern file, and
use it with one of the programs! One thing to look out for though, if you're
searching for a pattern to use with the driver program, make sure the dimensions
the pattern are small enough to see in you terminal.

[0]: https://i.imgur.com/tyxv8WX.gif
[1]: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
[2]: https://www.conwaylife.com/wiki/Run_Length_Encoded
[3]: https://www.conwaylife.com/wiki/Main_Page