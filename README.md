![**Brainfuck**](Brainfuck.png?raw=true "Brainfuck")
# **Brainfuck.**
### Brainfuck interpreter/optimizing transpiler written in C++.
### This implementation has 65 536 memory cells (uint16_t limit).
##### Future plans: ([Roadmap](https://github.com/DrParanoya/Brainfuck/blob/main/ROADMAP.md))
##### Version 1.1.0
##
When running this, a terminal will open.  
Enter the filepath to your brainfuck file (file extension doesn't matter).  
###### A regex search will be performed to read the flags, anything behind the flags will be appended to the file path!
The following flags are allowed:  

- `-i` will just interpret the code (default, will be used if no mode is specified).
- `-a` will transpile brainfuck code into C++ and store it in a `.cpp` file.
- `-l` will perform a check if all brainfuck loops open and close correctly. Runs with ```-a``` and ```-i``` to prevent errors.
- `-c ` will run a cleanup (removes every non-brainfuck character). Can improve performance on heavily commented programs.
- `-?` will enable randomness (every `?` inside your brainfuck code will randomize the value of the current cell).

Important: `-?`  should only be placed after the mode flag!
 
##
### Examples:  
> ##
> `C:\brainfuck_code.txt`  
> This will interpret the file `brainfuck_code.txt` without support for randomness.
> ##
> `C:\Users\User\Images\Screenshot22.png -a -?`
> This will transpile the file `Screenshot22.png` to C++ with support for randomness.
### Bugs / Contributing:
If you encounter any bugs feel free to open an issue. Please describe it as accurately as possible.  
If possible, add the steps to reproduce it.  
To contribute, just open a pull request.  
###### *Do not ask questions about how brainfuck works!*  
##  
###### This project is licensed under the GNU GENERAL PUBLIC LICENSE Version 3
