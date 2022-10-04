#ifndef _music_H
#define _music_H
#define TAMMAX 200

typedef struct artista {
 int id;
 char nome[200];
 char genero[200];
} artista;

typedef struct artista_no {
 artista *artista;
 struct artista_no *prox;
} artista_no;

typedef struct musica {
 int id;
 char titulo[200];
 int id_artista;
 int duracao; //segundos
} musica;

typedef struct musica_no {
 musica *musica;
 struct musica_no *prox;
} musica_no;

typedef struct playlist_no {
 musica *musica;
 struct playlist_no *prox;
} playlist_no;

typedef struct lplaylists_no {
 int id;
 char nome[200];
 playlist_no *musicas;
 struct lplaylists_no *prox;
} lplaylists_no;

//----------------OK--------------//

//cria lista artista
artista_no *criaListaArtista();
//cria lista musica
musica_no *criaListaMusica();
//cria playlist
playlist_no *criaPlaylist();
//cria lista playlist
lplaylists_no *criaListaPlaylist();

//Cadastra artista
void insereArtista(artista_no *ini, artista *Artista);
//Insere artista na lista
void cadastraArtista(int *lastIdArtista, artista_no *ini);
// imprime  todos artistas 
void imprimeArtista(artista_no *ini);
//cadastra musica
void cadastraMusica(int *lastIdMusica, artista_no *listaArtista, musica_no *ini);
//insere musica na laylist
void insereMusica( musica_no *ini, musica *novaMusica);


// imprime todas musicas existentes
void imprimeMusica(musica_no *ini, artista_no *listaArtistas);
// converte a duração da musica em minutos para impressão-
void converteTempoMinutos(int segundos);
//escolha do id de um artista
int escolheArtista(artista_no *ini);
// busca artista pelo id
artista_no *buscaArtista(artista_no *ini, int k);
// imprime todas musicas de um dado artista 
void imprimeMusicaPorArtista(musica_no *ini,  artista_no *listaArtistas);
//insere musicas na playlist
void adicionaMusicaPlaylist(playlist_no *ini, musica_no *listaMusicas, int k);
// busca musica 
musica_no *buscaMusica(musica_no *ini, int k);
// imprime playlist
void imprimePlaylist(lplaylists_no *ini, artista_no *listaArtistas, int k);
//insere playlist na lista de playlist
void adicionaPlaylist(int *lastIdPlaylist, lplaylists_no *ini, playlist_no *playlist, musica_no *lista);
//deleta artistas e todas suas musicas
void removeMusica(artista_no listaArtistas, musica_no listaMusicas, lplaylists_no listaPlaylist, int id);

//---------------NOK-----------------//

// troca as musicas aleatoriamente 
void shufflePlaylist(playlist_no *ini);



#endif