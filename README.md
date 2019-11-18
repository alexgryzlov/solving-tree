# solving-tree
## About
This is akinator-like program that have a lot of different functions.

## Functionality
With this program you can build solving trees and create your own akinator.
There are several functions that you can use. The main one is "Guess". If you choose it then the program will try to guess what you are thinking about and if it fails you can expand the guessing tree. After you done playing you can save current tree with function "Save" and it will save the current configuration in a human-readable format (see example.txt). If you want to see the picture of your tree you can call "Print" and the program will create .svg image using graphviz. Also you can get full definition of your object according to the current tree and get the difference of the common qualities of the two given objects. If you don't want to create a new tree after every run, you can "Export" an already existing solving tree using .txt config file that must be written in the same format as example.txt.

## Run
To run example you need:
```
$ git clone https://github.com/alexgryzlov/solving-tree/
$ ./build.sh
$ ./solve_tree.o
$ E
$ example.txt

