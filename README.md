# Shelf-Steam

### About:

Shelf-Steam is a custom shell designed for launching and playing terminal-based games seamlessly.

### Info:

Shelf-Steam is designed for Linux-based systems and may not be compatible with other operating systems.

This project was independently developed for an Operating Systems class. It is published for educational and portfolio purposes only. Please do not use this code for academic coursework.

# How to Use

### Run the Shell:

Shelf-Steam requires the directory of complied games to be included.
```
./shelf-steam /full/path/to/games/bin/
```

### Shell Commands:

The `exit` command is used to terminate the shell session.
```
exit
```

The `path` command is used to change the selected directory of the compiled games.
```
path /full/path/to/compiled-games/
```

The `ls` command lists all files found in the selected directory with a description of each game.<br>
*Game descriptions are obtained by passing the `--help` argument into each compiled game.*
```
ls
```

Games are executed by entering the compiled file name along with any arguments.
```
add --seed 0
```

A game can be "replayed" by using stored inputs from a file to automatically run the game.<br>
*The `<` operator is used to specify the file.*
```
add --seed 0 < /full/path/to/games/replay/add.log
```
  
# How to Build

### Clone the Repo:
```
git clone https://github.com/2-adic/Shelf-Steam.git
```

### Compile Games:

Games need to be compiled before Shelf-Steam can run them.<br>
It is up to the user to ensure their games are compiled.<br>

The following command applies to the example game directory included in the repository: `games`.<br>
*Switches to the `games` directory and compiles all games specified in the makefile.*
```
cd games && make
```

### Compile Shelf-Steam:

Do this while in the `./src` directory.
```
make
```

### Run Shelf-Steam:

The full path of the games directory must be provided.<br>
This directory should only contain the compiled game files.
```
./shelf-steam /full/path/to/games/bin/
```
