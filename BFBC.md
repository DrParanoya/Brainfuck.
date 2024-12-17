# Complete BrainFuckByteCode instruction set
Features 8 different instructions:
- chg x
- mov y
- out
- inp
- rng
- slp
- elp
##
### chg
`chg` changes the current cell by x.  
> ### Example:
> chg-13  
> Decreases the cell value by 13.
> ##
### mov
`mov` moves the pointer y steps.
> ### Example:
> mov+4  
> Moves the pointer 4 steps.
##
### out
`out` outputs the ASCII character with the value of the current cell to the terminal.
> ### Example (Value of the current cell is 41.):
> Outputs the character ) to the terminal.
##
### inp
`inp` awaits and reads 1 character of user input and stores its ASCII value in the current cell.
##
### rng
`rng` changes the current cell value to a random number.
##
### slp
`slp` defines the start of a loop. If no mathing `lpe` instrution is found, it will throw an error.
  
### elp
`elp` defines the end of a loop. If no matching `lps` instruction is found, it will throw an error.
##
> ### Example program ( **,[-.]>+++++.<<<<<<<<<<<<<<<?** ):
> ```
> inp     awaits, reads and stores user input
> slp     starts a loop
> chg-1   adds 1 to the current cells value
> out     ouputs the current cells value as ASCII character
> elp     ends the loop
> mov+1   moves the pointer 1 cell forward
> chg+5   subtracts 5 from the current cells value
> out     outputs the current cells value as ASCII character
> mov-15  moves the pointer 15 cells back
> rng     if randomness is disabled, the ? will be ignored, and this instruction will vanish
> ```
