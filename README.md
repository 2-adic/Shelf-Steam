# Shelf-Steam

### About:

Shelf-Steam is a custom shell designed for launching and playing terminal-based games seamlessly.

### Info:

Shelf-Steam is designed for Linux-based systems and may not be compatible with other operating systems.

This project was independently developed for an Operating Systems class. It is published for educational and portfolio purposes only. Do not use this code for academic coursework.

# How to Use

### Run the Shell:

Run the `shelf-stream` binary inside the `src` directory.<br>
*The full path of the game's binary directory must be provided. This directory should only contain compiled game files.*
```
./src/shelf-steam /full/path/to/games/bin/
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
*Game descriptions will not show if a game does not accept the `--help` argument.*
```
ls
```

Games are executed by entering the compiled file's name.
```
add
```

Game descriptions are obtained by passing in the `--help` argument.
```
add --help
```

Additional arguments may be supported, depending on the specific implementation of the game.
```
add --seed 0
```

A game can be "replayed" by using stored inputs from a file to automatically run the game.<br>
*The `<` operator is used to specify the filepath.*
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
Run `make` to compile all games inside the `games` directory.<br>
*Once compiled, the example game binaries are put in the `games/bin` directory.*
```
make -C games
```

### Compile Shelf-Steam:

Run `make` to compile the `shelf-steam` binary inside the `src` directory.
```
make -C src
```
