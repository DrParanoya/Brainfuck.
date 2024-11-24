# Complete BrainFuckByteCode instruction set
Features 7 different instructions:
- chg x
- mov y
- out
- inp
- lps
- lpe
##
### chg
`chg` **ch**an**g**es the current cell by x.  
> ### Example:
> chg -13  
> Decreases the cell value by 13.
> ##
### mov
`mov` **mov**es the pointer y steps.
> ### Example:
> mov 4  
> Moves the pointer 4 steps.
##
### out
`out` **out**puts the ASCII character with the value of the current cell to the terminal.
> ### Example (Value of the current cell is 41.):
> Outputs the character ) to the terminal.
##
### inp
`inp` awaits and reads 1 character of user **inp**ut and stores its ASCII value in the current cell.
##
### lps
`lps` defines the start of a loop. If no mathing `lpe` instrution is found, it will throw an error.
  
### lpe
`lpe` defines the end of a loop. If no matching `lps` instruction is found, it will throw an error.
##
> ### Example program ( **,[-.]>+++++.** ):
> ```
> inp
> lps
> chg +1
> out
> lpe
> mov 1
> chg -5
> out
> ```
> This program will first await user input and store it in the current cell (cell 0).  
> Then in will enter a loop.
> This loop will decrease the current cell by 1 and then output it until the cell reaches a value of 0.  
> The value the current cell will eventually overflow.
> The loop will then be exited.  
> After the loop, the pointer is moved one step.  
> The cell value will be increased by 5.
> Lastly, it will output the ASCII character `{`.
