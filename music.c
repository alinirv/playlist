#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "music.h"

artista_no *criaListaArtista()
{
    artista_no *cabeca = malloc(sizeof(artista_no));
    cabeca->prox = NULL;
    return cabeca;
}
musica_no *criaListaMusica()
{
    musica_no *cabeca = malloc(sizeof(musica_no));
    cabeca->prox = NULL;
    return cabeca;
}
playlist_no *criaPlaylist()
{
    playlist_no *cabeca = malloc(sizeof(playlist_no));
    cabeca->prox = cabeca;
    return cabeca;
}
lplaylists_no *criaListaPlaylist()
{
    lplaylists_no *cabeca = malloc(sizeof(lplaylists_no));
    cabeca->prox = NULL;
    return cabeca;
}

void insereArtista(artista_no *ini, artista *Artista)
{
    artista_no *novo;
    novo = malloc(sizeof(artista_no));
    novo->artista = Artista;
    novo->prox = ini->prox;
    ini->prox = novo;
}
void cadastraArtista(int *lastIdArtista, artista_no *ini)
{
    artista *novoArtista;
    novoArtista = malloc(sizeof(artista));
    novoArtista->id = ++(*lastIdArtista);

    printf("Digite o nome do artista: ");    
    fgets(novoArtista->nome, TAMMAX - 1, stdin); 
    getchar(); 
    novoArtista->nome[strlen(novoArtista->nome) - 1] = 0;
    
    printf("Digite o genero do Artista");    
    scanf("%s", novoArtista->genero);
    getchar();
    insereArtista(ini, novoArtista);
    printf("Artista cadastrado!");
}

void imprimeArtista(artista_no *ini)
{
    if (ini->prox != ini)
    {
        printf("Lista vazia! \n");
    }
    else
    {
        for (artista_no *p = ini->prox; p != NULL; p = p->prox)
        {
            printf("Id: %d \n", p->artista->id);
            printf("Nome: %s\n", p->artista->nome);
            printf("Genero:  %s \n", p->artista->genero);
            printf("--------------------------\n");
        }
    }
}

int escolheArtista(artista_no *ini)
{
    artista_no *p;
    int k;
    printf("Escolha o Id do artista:\n");
    for (p = ini->prox; p != NULL; p = p->prox)
        printf(" %d - %s \n", p->artista->id, p->artista->nome);
    scanf("%d", &k);
    return k;
}

artista_no *buscaArtista(artista_no *ini, int k)
{
    artista_no *p;

    p = ini->prox;
    while (p && p->artista->id != k)
        p = p->prox;
    return p;
}

void insereMusica( musica_no *ini, musica *novaMusica)
{
    musica_no *novo;

    novo = malloc(sizeof(musica_no));    
    novo->musica = novaMusica;
    novo->prox = ini->prox;
    ini->prox = novo;
}

void cadastraMusica(int *lastIdMusica, artista_no *listaArtista, musica_no *ini)
{
    musica *novaMusica;
    artista_no *escolhido;
    int k;

    novaMusica = malloc(sizeof(musica));  
    novaMusica->id = ++(*lastIdMusica);
    printf("Digite o nome da musica: ");
    fgets(novaMusica->titulo, TAMMAX - 1, stdin);
    getchar();
    novaMusica->titulo[strlen(novaMusica->titulo) -1] = 0;
    k = escolheArtista(listaArtista);
    escolhido = buscaArtista(listaArtista, k);
    novaMusica->id_artista = escolhido->artista->id;
    printf("Digite a duração da musica em segundos: ");
    getchar();
    scanf("%d", &novaMusica->duracao);
    insereMusica(ini, novaMusica);

}

void converteTempoMinutos(int segundos)
{
    int h, m, s, resto;
    h = segundos / 3600;
    resto = segundos % 3600;
    m = resto / 60;
    s = resto % 60;
    printf("Duração: %d:%d:%d\n", h, m, s);
}

void imprimeMusica(musica_no *ini, artista_no *listaArtistas)
{
    artista_no *escolhido;
    for (musica_no *p = ini->prox; p != NULL; p = p->prox)
    {
        printf("Id: %d \n", p->musica->id);
        printf("Titulo: %s \n", p->musica->titulo);
        escolhido = buscaArtista(listaArtistas, p->musica->id_artista);
        printf("Artista: %s \n", escolhido->artista->nome);
        converteTempoMinutos(p->musica->duracao);
        printf("--------------------------\n");
    }
}

void imprimeMusicaPorArtista(musica_no *ini, artista_no *listaArtistas)
{
    musica_no *p;
    artista_no *escolhido;
    int k;
    k = escolheArtista(listaArtistas);
    for (p = ini->prox; p != NULL; p = p->prox)
    {
        if (p->musica->id_artista == k)
        {
            printf("Id: %d \n", p->musica->id);
            printf("Titulo: %s \n", p->musica->titulo);
            escolhido = buscaArtista(listaArtistas, p->musica->id_artista);
            printf("Artista: %s \n", escolhido->artista->nome);
            converteTempoMinutos(p->musica->duracao);
            printf("--------------------------\n");
        }
    }
}

void adicionaPlaylist(int *lastIdPlaylist, lplaylists_no *ini, playlist_no *playlist, musica_no *lista)
{
    char idsMusicas[TAMMAX];
    int convertInt[TAMMAX];
    int j = 0, i, k, qtdeMusicas;

    lplaylists_no *listaPlaylist;
    listaPlaylist = malloc(sizeof(lplaylists_no));

    listaPlaylist->id = ++(*lastIdPlaylist);
    printf("\nID da Playlist: %d", listaPlaylist->id);
    printf("\nDigite o nome da playlist: ");
    fgets(listaPlaylist->nome, TAMMAX - 1, stdin);
    getchar();
    listaPlaylist->nome[strlen(listaPlaylist->nome) - 1] = 0;
    printf("Digite os IDs das musicas: ");
    fgets(idsMusicas, TAMMAX - 1, stdin);
    getchar();

    qtdeMusicas = strlen(idsMusicas);
    for (i = 0; idsMusicas[i]; i++)
    {
        if (idsMusicas[i] != ' ')
        {
            idsMusicas[j++] = idsMusicas[i];
            qtdeMusicas--;
        }
    }

    for (k = 0; k <= qtdeMusicas; k++)
    {
        convertInt[k] = idsMusicas[k] - '0';
        // printf("\nid convertido %d", convertInt[k]);
    }

    playlist_no *novoNo;
    novoNo = malloc(sizeof(playlist_no));

    musica_no *p;

    for (k = 0; k <= qtdeMusicas; k++)
    {
        p = lista->prox;

        while (p)
        {
            // printf("\n Lista musica id: %d", p->musica->id);
            // printf("\n id musica %c", idsMusicas[k]);
            if (p->musica->id == convertInt[k])
            {
                novoNo->musica = p->musica;
                novoNo->prox = playlist->prox;
                playlist->prox = novoNo;
            }
            p = p->prox;
        }
    }
    listaPlaylist->musicas = playlist;
    listaPlaylist->prox = ini->prox;
    ini->prox = listaPlaylist;
}

void imprimePlaylist(lplaylists_no *ini, artista_no *listaArtistas, int k)
{
    lplaylists_no *p;
    playlist_no *musicasPlaylist;
    artista_no *escolhido;
    p = ini->prox;
    if (p == NULL)
    {
        printf("\n Playlist vazia!\n");
    }
    else
    {
        while (p)
        {
            if (p->id == k)
            {
                musicasPlaylist = p->musicas;
                printf("\nID da Playlist: %d", p->id);
                printf("\nNome Playlist: %s", p->nome);
                printf("\nMusicas: ");
                if (musicasPlaylist->prox == musicasPlaylist)
                {
                    printf("\n Playlist vazia!\n");
                }
                else
                {
                    do
                    {
                        printf("Id: %d \n", musicasPlaylist->musica->id);
                        printf("Titulo: %s \n", musicasPlaylist->musica->titulo);
                        escolhido = buscaArtista(listaArtistas, musicasPlaylist->musica->id_artista);
                        printf("Artista: %s \n", escolhido->artista->nome);
                        converteTempoMinutos(musicasPlaylist->musica->duracao);
                        printf("--------------------------\n");
                        musicasPlaylist = musicasPlaylist->prox;
                    } while (musicasPlaylist != p->musicas->prox);
                }

                printf("\n");
            }
            p = p->prox;
        }
    }
}
void removeMusica(artista_no listaArtistas, musica_no listaMusicas, lplaylists_no listaPlaylist, int id);

int menuPrincipal()
{
    int op;
    printf("Digite uma das opcoes abaixo:\n");
    printf("1 - Cadastrar artista\n");
    printf("2 - Cadastrar musicas\n");
    printf("3 - Criar playlist\n");
    printf("4 - Exibir Artistas\n");
    printf("5 - Exibir Musicas\n");
    printf("6 - Exibir musicas por artistas\n");
    printf("7 - Exibir playList\n");
    printf("8 - Remover Artista\n");
    printf("0 - Sair\n");
    scanf("%d", &op);
    return op;
}

int main()
{
    int id, k, op, i = 1;
    artista_no *listaArtistas;
    musica_no *listaMusicas;
    playlist_no *playlist;
    lplaylists_no *listaPlaylist;

    listaArtistas = criaListaArtista();
    int lastIdArtista = 0;
    listaMusicas = criaListaMusica();
    int lastIdMusica = 0;
    listaPlaylist = criaListaPlaylist();
    playlist = criaPlaylist();
    int lastIdPlaylist = 0;

    while (i != 0)
    {
        op = menuPrincipal();
        switch (op)
        {
        case 1:
            printf("\n ----  Cadastro da Artista---- \n");
            cadastraArtista(&lastIdArtista, listaArtistas);

            break;
        case 2:
            printf("\n ----  Cadastro de Musicas---- \n");
            cadastraMusica(&lastIdMusica, listaArtistas, listaMusicas);
            break;
        case 3:
            printf("\n ----  Cadastro de Playlist---- \n");

            adicionaPlaylist(&lastIdPlaylist, listaPlaylist, playlist, listaMusicas);
            break;
        case 4:
            printf("\n ---- Exibi Artistas ----\n");
            imprimeArtista(listaArtistas);
            break;
        case 5:
            printf("\n ---- Exibe Musicas ----\n");
            imprimeMusica(listaMusicas, listaArtistas);
            break;
        case 6:
            printf("\n ---- Exibe Musicas por Artistas ----\n");
            imprimeMusicaPorArtista(listaMusicas, listaArtistas);
            break;
        case 7:

            printf("\n ---- Exibe PlayList ----\n");
            printf("\nInforme o ID da playlist que deseja imprimir: ");
            scanf("%d", &k);
            imprimePlaylist(listaPlaylist, listaArtistas, k);
            break;
        case 8:

            printf("\n ---- Remover Musica ----\n");
            printf("\nInforme o ID da musica que deseja remover: ");
            scanf("%d", &id);
            // removeMusica(listaArtistas, listaMusicas, listaPlaylist, id);
            break;
        case 0:
            i = 0, printf("Obrigado por usar nosso programa!!!\n");
            break;
        default:
            printf("Opcao invalida!!! Escolha novamente!\n");
            break;
        }
    }
    getchar();
}
