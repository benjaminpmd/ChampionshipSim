# TournamentSimulator
Projet réalisé dans le carde de la license informatique de Cergy paris Université

commande pour installer gtk :

```bash
sudo apt-get install libgtk-3-dev
```


Commande de compilation temporaire : 

```bash
gcc `pkg-config --cflags gtk+-3.0` -o ./output/main ./src/main.c `pkg-config --libs gtk+-3.0`
```
