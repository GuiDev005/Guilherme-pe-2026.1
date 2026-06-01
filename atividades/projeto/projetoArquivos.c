#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX_FAV 30
 
typedef struct {
    int id;
    char nome[50];
    int favoritos[MAX_FAV];
    int quant_favoritos;
} usuarios;
 
typedef struct {
    int id;
    char nome[50];
    char genero[20];
    int duracao;
} videos;
 
void barra() {
    printf("======================================================\n");
}
 
void limparBuffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}
 
int geradorIDVideos() {
    FILE *f = fopen("videos.bin", "rb");
    if (f == NULL) return 1;
    videos v;
    int ultimo_id = 0;
    while (fread(&v, sizeof(videos), 1, f) == 1)
        ultimo_id = v.id;
    fclose(f);
    return ultimo_id + 1;
}
 
int geradorIDUsuarios() {
    FILE *f = fopen("usuarios.bin", "rb");
    if (f == NULL) return 1;
    usuarios u;
    int ultimo_id = 0;
    while (fread(&u, sizeof(usuarios), 1, f) == 1)
        ultimo_id = u.id;
    fclose(f);
    return ultimo_id + 1;
}
 
void cadastrarVideo() {
    videos v;
    FILE *f = fopen("videos.bin", "ab");
 
    v.id = geradorIDVideos();
    barra();
    printf("Cadastro de video\n");
    barra();
    printf("Nome: ");
    scanf(" %[^\n]", v.nome);
    printf("Genero: ");
    scanf(" %[^\n]", v.genero);
    printf("Duracao (minutos): ");
    scanf("%d", &v.duracao);
 
    fwrite(&v, sizeof(videos), 1, f);
    fclose(f);
    printf("Video cadastrado com ID %d!\n", v.id);
}
 
void listarVideos() {
    FILE *f = fopen("videos.bin", "rb");
    if (f == NULL) {
        printf("Nenhum video cadastrado.\n");
        return;
    }
    videos v;
    barra();
    printf("Lista de videos\n");
    barra();
    while (fread(&v, sizeof(videos), 1, f) == 1) {
        printf("ID: %d\n", v.id);
        printf("Nome: %s\n", v.nome);
        printf("Genero: %s\n", v.genero);
        printf("Duracao: %d minutos\n", v.duracao);
        barra();
    }
    fclose(f);
}
 
void buscarVideoPorNome() {
    char nome[50];
    videos v;
    int encontrado = 0;
 
    printf("Nome do video: ");
    scanf(" %[^\n]", nome);
 
    FILE *f = fopen("videos.bin", "rb");
    if (f == NULL) {
        printf("Nenhum video cadastrado.\n");
        return;
    }
 
    while (fread(&v, sizeof(videos), 1, f) == 1) {
        if (strcmp(v.nome, nome) == 0) {
            barra();
            printf("ID: %d\n", v.id);
            printf("Nome: %s\n", v.nome);
            printf("Genero: %s\n", v.genero);
            printf("Duracao: %d minutos\n", v.duracao);
            barra();
            encontrado = 1;
            break;
        }
    }
    fclose(f);
 
    if (!encontrado)
        printf("Video nao encontrado.\n");
}
 
void atualizarVideo() {
    int id;
    printf("ID do video a atualizar: ");
    scanf("%d", &id);
    limparBuffer();
 
    FILE *f = fopen("videos.bin", "r+b");
    if (f == NULL) {
        printf("Nenhum video cadastrado.\n");
        return;
    }
 
    videos v;
    int encontrado = 0;
    while (fread(&v, sizeof(videos), 1, f) == 1) {
        if (v.id == id) {
            printf("Novo nome: ");
            scanf(" %[^\n]", v.nome);
            printf("Novo genero: ");
            scanf(" %[^\n]", v.genero);
            printf("Nova duracao: ");
            scanf("%d", &v.duracao);
            limparBuffer();
 
            fseek(f, -(long)sizeof(videos), SEEK_CUR);
            fwrite(&v, sizeof(videos), 1, f);
            encontrado = 1;
            printf("Video atualizado!\n");
            break;
        }
    }
    fclose(f);
 
    if (!encontrado) printf("Video nao encontrado.\n");
}
 
void removerVideo() {
    int id;
    printf("ID do video a remover: ");
    scanf("%d", &id);
    limparBuffer();
 
    FILE *f   = fopen("videos.bin",     "rb");
    FILE *tmp = fopen("videos_tmp.bin", "wb");
 
    videos v;
    int removido = 0;
    while (fread(&v, sizeof(videos), 1, f) == 1) {
        if (v.id == id)
            removido = 1;
        else
            fwrite(&v, sizeof(videos), 1, tmp);
    }
    fclose(f);
    fclose(tmp);
 
    remove("videos.bin");
    rename("videos_tmp.bin", "videos.bin");
 
    if (removido) printf("Video removido!\n");
    else          printf("Video nao encontrado.\n");
}
 
void cadastrarUsuario() {
    usuarios u;
    FILE *f = fopen("usuarios.bin", "ab");
 
    u.id = geradorIDUsuarios();
    u.quant_favoritos = 0;
 
    barra();
    printf("Cadastro de usuario\n");
    barra();
    printf("Nome: ");
    scanf(" %[^\n]", u.nome);
 
    fwrite(&u, sizeof(usuarios), 1, f);
    fclose(f);
    printf("Usuario cadastrado com ID %d!\n", u.id);
}
 
void listarUsuarios() {
    FILE *f = fopen("usuarios.bin", "rb");
    if (f == NULL) {
        printf("Nenhum usuario cadastrado.\n");
        return;
    }
    usuarios u;
    barra();
    printf("Lista de usuarios\n");
    barra();
    while (fread(&u, sizeof(usuarios), 1, f) == 1) {
        printf("ID: %d\n", u.id);
        printf("Nome: %s\n", u.nome);
        printf("Favoritos: %d video(s)\n", u.quant_favoritos);
        barra();
    }
    fclose(f);
}
 
void atualizarUsuario() {
    int id;
    printf("ID do usuario a atualizar: ");
    scanf("%d", &id);
    limparBuffer();
 
    FILE *f = fopen("usuarios.bin", "r+b");
    if (f == NULL) {
        printf("Nenhum usuario cadastrado.\n");
        return;
    }
 
    usuarios u;
    int encontrado = 0;
    while (fread(&u, sizeof(usuarios), 1, f) == 1) {
        if (u.id == id) {
            printf("Novo nome: ");
            scanf(" %[^\n]", u.nome);
            limparBuffer();
 
            fseek(f, -(long)sizeof(usuarios), SEEK_CUR);
            fwrite(&u, sizeof(usuarios), 1, f);
            encontrado = 1;
            printf("Usuario atualizado!\n");
            break;
        }
    }
    fclose(f);
 
    if (!encontrado) printf("Usuario nao encontrado.\n");
}
 
void removerUsuario() {
    int id;
    printf("ID do usuario a remover: ");
    scanf("%d", &id);
    limparBuffer();
 
    FILE *f   = fopen("usuarios.bin",     "rb");
    FILE *tmp = fopen("usuarios_tmp.bin", "wb");
 
    usuarios u;
    int removido = 0;
    while (fread(&u, sizeof(usuarios), 1, f) == 1) {
        if (u.id == id)
            removido = 1;
        else
            fwrite(&u, sizeof(usuarios), 1, tmp);
    }
    fclose(f);
    fclose(tmp);
 
    remove("usuarios.bin");
    rename("usuarios_tmp.bin", "usuarios.bin");
 
    if (removido) printf("Usuario removido!\n");
    else          printf("Usuario nao encontrado.\n");
}
 
void favoritarVideo() {
    int id_usuario, id_video;
 
    printf("ID do usuario: ");
    scanf("%d", &id_usuario);
    printf("ID do video: ");
    scanf("%d", &id_video);
    limparBuffer();
 
    FILE *f = fopen("usuarios.bin", "r+b");
    if (f == NULL) {
        printf("Nenhum usuario cadastrado.\n");
        return;
    }
 
    usuarios u;
    int encontrado = 0;
    while (fread(&u, sizeof(usuarios), 1, f) == 1) {
        if (u.id == id_usuario) {
            if (u.quant_favoritos < MAX_FAV) {
                u.favoritos[u.quant_favoritos] = id_video;
                u.quant_favoritos++;
                fseek(f, -(long)sizeof(usuarios), SEEK_CUR);
                fwrite(&u, sizeof(usuarios), 1, f);
                printf("Video favoritado!\n");
            } else {
                printf("Limite de favoritos atingido!\n");
            }
            encontrado = 1;
            break;
        }
    }
    fclose(f);
 
    if (!encontrado) printf("Usuario nao encontrado.\n");
}
 
void relatorioFavoritos() {
    FILE *fu = fopen("usuarios.bin", "rb");
    if (fu == NULL) {
        printf("Nenhum usuario cadastrado.\n");
        return;
    }
 
    usuarios u;
    barra();
    printf("Relatorio: usuarios e seus videos favoritos\n");
    barra();
 
    while (fread(&u, sizeof(usuarios), 1, fu) == 1) {
        printf("Usuario: %s (ID: %d)\n", u.nome, u.id);
 
        if (u.quant_favoritos == 0) {
            printf("  Sem favoritos.\n");
        } else {
            for (int i = 0; i < u.quant_favoritos; i++) {
                /* Abre o arquivo de videos para achar o nome pelo ID */
                FILE *fv = fopen("videos.bin", "rb");
                videos v;
                int achou = 0;
                while (fread(&v, sizeof(videos), 1, fv) == 1) {
                    if (v.id == u.favoritos[i]) {
                        printf("  - %s (%s, %d min)\n", v.nome, v.genero, v.duracao);
                        achou = 1;
                        break;
                    }
                }
                fclose(fv);
                if (!achou)
                    printf("  - Video ID %d nao encontrado\n", u.favoritos[i]);
            }
        }
        barra();
    }
    fclose(fu);
}
 
int main() {
    int opcao;
 
    do {
        barra();
        printf("SISTEMA DE STREAMING DE VIDEOS\n");
        barra();
        printf("1.  Cadastrar video\n");
        printf("2.  Listar videos\n");
        printf("3.  Buscar video por nome\n");
        printf("4.  Atualizar video\n");
        printf("5.  Remover video\n");
        printf("6.  Cadastrar usuario\n");
        printf("7.  Listar usuarios\n");
        printf("8.  Atualizar usuario\n");
        printf("9.  Remover usuario\n");
        printf("10. Favoritar video\n");
        printf("11. Relatorio de favoritos\n");
        printf("0.  Sair\n");
        barra();
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
 
        switch (opcao) {
            case 1:  cadastrarVideo();    break;
            case 2:  listarVideos();      break;
            case 3:  buscarVideoPorNome(); break;
            case 4:  atualizarVideo();    break;
            case 5:  removerVideo();      break;
            case 6:  cadastrarUsuario();  break;
            case 7:  listarUsuarios();    break;
            case 8:  atualizarUsuario();  break;
            case 9:  removerUsuario();    break;
            case 10: favoritarVideo();    break;
            case 11: relatorioFavoritos(); break;
            case 0:  printf("Saindo...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
 
    return 0;
}