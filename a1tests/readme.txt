Some tests for assignment 1
---------------------------
There are 3 input files: input, input2 & input3.

The following are the commands used to generate the output files
under Linux.  (It assumes that the program can be invoked as ./a1.)

# translations:
# both sets of the same size (-t should have no effect)
./a1 abc xyz < input > my-out1
./a1 ab bc < input > my-out2
./a1 abaca vwxyz < input > my-out3
./a1 -t abaca vwxyz < input > my-out4

# 2nd set is larger (-t should have no effect)
./a1 aei vwxyz < input > my-out5
./a1 -t aei vwxyz < input > my-out6

# 1st set is larger
./a1 abcdef xyz < input > my-out7
./a1 abacaba vwxyz < input > my-out8
./a1 -t abcdef xyz < input > my-out9
./a1 -t abacaba vwxyz < input > my-out10

# deletion:
./a1 -d a < input > my-out11
./a1 -d aeiou < input > my-out12

# with escape characters:
./a1 '\n' x < input > my-out13
./a1 'a\nc' xyz < input > my-out14
./a1 'a\t\nc' wxyz < input > my-out15
./a1 '\\n' ab < input2 > my-out16
./a1 ei 'x\n' < input2 > my-out17
./a1 '\tu' 'x\n' < input2 > my-out18

./a1 -d 'a\n' < input > my-out19
./a1 -d '\\n' < input2 > my-out20
./a1 -d '\n\t' < input2 > my-out21

# with ranges:
./a1 -d a-c < input3 > my-out22
./a1 a-z A-Z < input > my-out23
./a1 A-Z a-z < input > my-out24
./a1 a-e xyz < input > my-out25
./a1 -t a-e xyz < input > my-out26

Notes:
- All input & output files are in Unix format
- The single quotes around arguments that use escape characters may or may
  not be necessary in cygwin
- The given tests are not exhaustive.  In particular, there are no tests
  that use both escape characters & ranges.
- You may be able to use the runtests script to run the tests.  This has
  only been tested on Linux but may work in the cygwin bash shell as well.
  You need to name your executable a1.exe (in cygwin) or a1 (in Linux) & put
  it is in the same directory as the runtests script & the input & output 
  files.

aw
