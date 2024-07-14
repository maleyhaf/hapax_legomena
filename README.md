# Hapax Legomena

Program written by Maleyha Fatima for CIS2520 (Data Structures).

## About

Hapax Legomena are words in a text that occur only once.
This is a data processing tool where it tallies the amount of words in a data files in order to list the hapax Legomena. To produce results it does the following:
* keep track of all words
* keep track of counter to track how many times a word occurs

## Usuage

To run, simply run the following commands:
    make
    ./hapax [<options>] <datafile> [ <datafile> ...]
    

It takes information from the user through the command line:
	Usage:
	    hapax [<options>] <datafile> [ <datafile> ...]

	Options:
	-d     : print out all data loaded before printing hapax legomena.
	-h     : this help.  You are looking at it.
	-l <N> : only print hapax legomena of length <N>.
	       : If no -l option is given, all hapax legomena are printed.

### Examples

Let us say the file "`smalldata.txt`" has this content:

	hello where, hello there
	this is a test
	line three



If we run our "`hapax`" program on this file, this is the output we should see:

	$ ./hapax smalldata.txt 
	Total word count 10
	Tally loaded
	Hapax legomena from file 'smalldata.txt':
		a
		is
		line
		test
		this
		three
		there
		where
	$ ./hapax -l 3 smalldata.txt 
	Total word count 10
	Tally loaded
	Hapax legomena from file 'smalldata.txt':
	$ ./hapax -l 4 smalldata.txt 
	Total word count 10
	Tally loaded
	Hapax legomena from file 'smalldata.txt':
		line
		test
		this


* Note that the second run above is expected to print out no hapax legomena as there are no words of length 3 in the file whatsoever, so there can't be any that occur only once!

