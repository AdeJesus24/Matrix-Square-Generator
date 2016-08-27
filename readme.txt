HOW TO USE DENSEMULT

Compile using: g++ -Wall -std=c++11 densemult.cpp -o densemult
Argument is a string in the format:
A={input file};C={output file}
The input file must have text in a dense matrix format, i.e.:
0 1
1 0
with values all being real numbers and one space apart. The matrix
must be square, i.e. m = n. Comments can be entered anywhere, with a # 
preceding them. The matrix can be no larger than 20x20.

Example: ./densemult "A=input.txt;C=output.txt"
