# Lem-IPC

- ![alt text](https://img.shields.io/badge/Note-121%2F100-lightgreen)
- ![alt text](https://img.shields.io/badge/Dur%C3%A9e%20du%20projet-1%20semaine-orange)
- ![alt text](https://img.shields.io/badge/XP-9450-red)

### Projet

Le projet Lem-IPC consiste a creer un petit jeu par le biais de processus.
En lancant plusieurs fois le meme binaire, plusieurs joueurs rejoignent alors un jeu ou seul la derniere team en vie remporte la victoire !

### Compilation

```bash
$ make
$ make visualizer
$ make processus
```

Vous obtenez alors 3 binaires.
- lemipc : le binaire principal pour lancer le jeu
- lemipc-visualizer : le binaire pour visualiser le jeu en temps reel créé avec la MLX
- lemipc-processus : créer plusieurs processus pour le jeu

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

#### Usage classique:

```bash
./lemipc 1 --pts:4
./lemipc-processus 3 2
```

#### Usage avec le visualizer:

```bash
./lemipc 1 --pts:4
./lemipc-visualizer -m
./lemipc-processus 3 2
```

#### Usage avec plein de processus:

```bash
./lemipc 1 --pts:200
./lemipc-visualizer -m
./lemipc-processus 200 2
```
### Visualizer

![image](https://user-images.githubusercontent.com/66129673/177877518-87a63e85-a439-499c-aa92-0083b3b7fbd8.png)


![image](https://user-images.githubusercontent.com/66129673/177877571-0b97e70e-83f1-4c1a-8d53-2a641daae655.png)
