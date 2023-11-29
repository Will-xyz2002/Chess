# Chess
CS246 project
## Command
```
game or g (human or computer[1-4]) (human or computer[1-4])
```
```
resign or r
```
```
move or m:
    regular move: move starting_coord ending_coord (example : m e2 e4)
    castling: regular move of two steps for king (example : m e1 g1)
    pawn promotion: regular move add the type that promoted (example: m e7 e8 Q)
    computer move : regular move with no argument
```
```
setup or s
    add piece: place a type of piece to the given coordinate (example: + K e1)
    remove piece : remove a piece in the given coordinates (example: - e1)
    make it colour's turn to got next (example: = white)
    leave the setup mode : done
```
