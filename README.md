# Game of Life

![Example][0]

A command line simulation program for [Conway's Game of Life][1] with virtually
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

Building this project provides two programs, an interactive console program,
which we call the driver program (driver.exe), and a timer program (timer.exe).

### Driver

The driver program is shown in the example GIF at the top. Its usage is
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

As an example, we run the driver program on glider.rle. We input four
consecutive new lines to increment the generation by one, four times. The
output, with the extra new lines removed, is shown below.

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

It seems that this pattern oscillates between four states. To confirm our
suspicions, we run the program again, this time incrementing the generation by
a multiple of four, say, 400.

```
[mokhan@aspire life]$ ./driver.exe glider.rle 
Generation 0
.O.
..O
OOO

400

Generation 400
.O.
..O
OOO
```

Sure enough, we're at the same configuration! So what's going on? Is this
pattern remaining in the same place? To confirm this, we'll (weirdly) run the
timer program with its optional argument --stats.

```
[mokhan@aspire life]$ ./timer.exe glider.rle  400 --stats
size    5
dims    3 by 3
span    (0,0) to (2,2)

size    5
dims    3 by 3
span    (100,100) to (102,102)

time    0m0.000s
```

We now see that the top left corner of the glider started at position (0, 0)
in Generation 0, and ended at position (100, 100) in Generation 400. It seems
that the pattern *moved* across the internal grid data structure. Now the
name "glider" makes sense!

## Tips and Tricks <a name = "tips-and-tricks"></a>

Here are some tips and tricks for this project.

### Watch an "Animation" with Driver

You can create something similar to an animation with the driver program by
simply holding the enter or return key. Of course, all this does is increment
the generation by one repeatedly, but the results are nice to look at (see the
example GIF at the top).

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
the pattern are small enough to see in your terminal.

[0]: https://i.imgur.com/01FLXHe.gif
[1]: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
[2]: https://www.conwaylife.com/wiki/Run_Length_Encoded
[3]: https://www.conwaylife.com/wiki/Main_Page
