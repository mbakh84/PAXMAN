<b>PAXMAN</b> is a simplified Sample of "pacman" game. no graphical libraries are used in this program and every graphical shape is a handmade shape which made from symbol characters. there is pacman, ghost, coin and Pill characters in this game.<br><br> <b>the rule is simple</b>; pacman should collect all coins to win the game and must not touch ghosts. if pacman collet a pill character, ghosts will run from pacman and they cant kill it (for 7 moves).<br><br><b>how does ghosts choose their way?</b> at first, the ghost checks the row and column in which it stands. if pacman is in the diraction of ghost's move, if pacman has not collect a pill character at the time, ghost will chase pacman. else if pacman has collect a pill, ghost will escape from pacman. but if pacman is not in the coulmn or row, ghost will move in a constant diracrtion. after every 2 moves and if there is no sign of pacman in the raw and coulmn, ghost will choose a new way to move(randomly).<br><br>I apply a semi backend-frontend system on the game. i save and work with datas as some symbol characters(@,P,G,|&...), but for show the datas on the screen, i translate those symbols to some beautiful and semi graphical shapes (for more performance)<br><br>i consider some items of game (such as pacman,ghosts and game field) as objects and use struct to define them.<br><br><b>note :</b> beacuse of some access limits on C drive, i use D drive to collect users information and save some files. if you don't have D drive on your system, you should change code and make it usable for your system.<br><br><br><b>*What does extension folder include?<b> there is a convertor in this file, that convertes specific .txt type files to .bin format. by this convertor, any bode can design a map for this game and use convertor to make designed usable for program.
