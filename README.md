# Lem-IPC

The Lem-IPC project consists in creating a small game through processes.<br>
By launching the same binary several times, several players then join a game and only the last team left wins !<br>

## Usage

- Clone Repository
```bash
git clone https://github.com/vvaucoul/Lem-IPC && cd Lem-IPC
```

- Compilation
```bash
make
make processus
make visualize
```

Then, you get 3 binaries.
- lemipc: the main binary to launch the game
- lemipc-visualizer: the binary to visualize the real-time game created with the MLX
- lemipc-processu: creating multiple processes for the game

### Usage

```C
Usage: ./lemipc [TEAM] [OPTIONS]...
  Lemipc is a simple IPC game with multiple processus.
  First execution: [HOST]
  Second execution and more: [CLIENT]

  [TEAM]: team number (1 to 32)
  [OPTIONS]:
    -h: display this help
    -s: display shared memory segment
    -c: display communications between processus.
    --pts:<n>: set the number of players to start the game. (Default: 4)
    --tts:<n>: set the number of teams to start the game. (Default: 2)

  Examples:
    ./lemipc 1
    ./lemipc 1 --tts:8
    ./lemipc 1 --tts:8 --pts:4
```

#### Basic usage

```bash
./lemipc 1 --pts:4
./lemipc-processus 3 2
```

#### Visualizer usage

```bash
./lemipc 1 --pts:4
./lemipc-visualizer -m
./lemipc-processus 3 2
```

#### Multiple processus usage

```bash
./lemipc 1 --pts:200
./lemipc-visualizer -m
./lemipc-processus 200 2
```
### Visualizer

![Animation](https://user-images.githubusercontent.com/66129673/198732940-f11bcf33-b76b-4905-9ef5-323bc33d71be.gif)

