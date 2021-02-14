# TicTacToe
A long time ago, in a dusty desert somewhere, late at night, I really wanted to play TicTacToe. Drawing out a board in the dust didn't quite cut it. I wanted to play on a large scale. And to make it interesting, I wanted to play anonymously... and over the course of a couple hours. What would be more fun to watch than a 2 hour TicTacToe game.

What if there was a 30'x30' board, with 10'x10' squares, and 2 player kiosks 100' from the board. An *X* kiosk and an *O* kiosk 50' away from each other so you couldn't see your opponent at night. 

![](https://github.com/stoph/tictactoe-ws2812/blob/assets/TTT_setup.png?raw=true)

The idea is the easy part, right?

To that end, I got to designing and coding. The gameplay was simple. The board would light up with the outline of 9 squares - the universal image of TicTacToe (or the [many other names](https://en.wikipedia.org/wiki/Tic-tac-toe#History) it goes by). The X kiosk would light up, while the O Kiosk would stay dim. As an innocent passerby walks past it, they see 9 buttons, all lit up. Curious, they press one. A giant X appears on the board, and the kiosk goes dark. Confused, they walk away. Both kiosks stay dark just long enough for anyone waiting to lose interest. Then the O kiosk lights up. Some time later, the same thing happens to another innocent bystander as their curiosity is piqued by the glowing O. They see 9 buttons, but only 8 are lit up. They press one. A giant O appears on the board, and the kiosk goes dark. Confused, they too walk away. Repeat over the next couple hours until someone one wins.

To test out my gameplay on a smaller scale (that would fit on my desk) I build a mock board out of brass wire and some ws2812 LEDs. 

![](https://github.com/stoph/tictactoe-ws2812/blob/assets/TTT_tester.png?raw=true)

(Work in progress) This is for the board 'controller' to power the display itself and do the TicTacToe logic. The code for the player kiosk devices manage the buttons and their LEDs. The plan is to use LoRa for the communications between the kiosk and the board.


### Board logically set up as:

| 1 | 2 | 3 |
|---|---|---|
| 4 | 5 | 6 |
| 7 | 8 | 9 |

### 8 ways to win
<table>
<tr>
<td>

| 1 | 2 | 3 |
|---|---|---|
| . | . | . |
| . | . | . |
</td>
<td>

| . | . | . |
|---|---|---|
| 4 | 5 | 6 |
| . | . | . |
</td>

<td>

| . | . | . |
|---|---|---|
| . | . | . |
| 7 | 8 | 9 |
</td>
</tr><tr>
<td>

| 1 | . | . |
|---|---|---|
| 4 | . | . |
| 7 | . | . |
</td>
<td>

| . | 2 | . |
|---|---|---|
| . | 5 | . |
| . | 8 | . |
</td>
<td>

| . | . | 3 |
|---|---|---|
| . | . | 6 |
| . | . | 9 |
</td>

</tr>
<tr>
<td>

| . | . | 3 |
|---|---|---|
| . | 5 | . |
| 7 | . | . |
</td>
<td>

| 1 | . | . |
|---|---|---|
| . | 5 | . |
| . | . | 9 |
</td>
</tr></table>.

### Board technically set up as:
(Based to arrangement of LEDs on my board)

| 8 | 3 | 2 |
|---|---|---|
| 7 | 4 | 1 |
| 6 | 5 | 0 |

#### ToDo:
- Decide on a board to use with for the controllers with 18 gpio (or MCP23017). Need 9 for button + 9 for each button's LED.
- Should I use ws2812 for the board, or individual colored strands? Each square would need to represent an X, an O, and the square itself (to draw attention)
- Is LoRa the best protocol?
- Profit?
 