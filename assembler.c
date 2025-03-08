#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define s 256*2
#define NO_END " "

struct comando
{
    int linha;
    int coluna;
    int minemonico;
    char valor;
};

struct dado
{
    int end;
    int valor;
    char nome;
};


struct comando comandos[s];
struct dado dados[s];
// Posicao atual do array de codigo e data
int pos_codigo = 0;
int pos_dados = 0;

// posicção da memória onde termina o código
int end_codigo = 0;

// Adiciona uma nova operação ao array codigo na posicao i
int add_codigo(int mine, char val, int i){
    comandos[i].minemonico = mine;
    comandos[i].valor = val;
    return i + 1;
}

// Adiciona um novoa dado ao array de dados
int add_data(char nome, int valor,int i){
    dados[i].valor = valor;
    dados[i].nome = nome;
    return i + 1;
}

int assembler(char *file_name){
    char buffer[s+4]; // Cria o buffer para conter o "programa"
    // Confirma que o buffer não contém lixo
    for(int i = 0; i < s+4; i++){
        buffer[i] = 0;
    }
    // Cria o cabeçalho necessário, valores em decimal
    buffer[0] = 3;
    buffer[1] = 78;
    buffer[2] = 68;
    buffer[3] = 82;

    // Passa os dados dos arrays para dentro do buffer
    int pos_mem = 4;
    // Comandos
    for(int i = 0; i < pos_codigo; i++){
        buffer[pos_mem] = (char) comandos[i].minemonico;
        pos_mem += 2;
        if(comandos[i].minemonico != 240 && comandos[i].minemonico != 96){
            buffer[pos_mem] = comandos[i].valor;
            pos_mem += 2;
        }
    }
    // Dados
    for(int i = 0; i < pos_dados; i++){
        buffer[pos_mem] = dados[i].valor;
        pos_mem += 2; 
    }

    char *name = strtok(file_name, ".");
    char *output = strcat(name, ".mem");
    FILE *bin = fopen(("./%s", output), "wb");
    fwrite(&buffer, sizeof(buffer), 1, bin);
    fclose(bin);
};

void lexer(char *file_name){
    FILE *file;
    char *line = NULL;
    size_t len = 0;

    // Linha e coluna atual que se está lendo
    int linha = 0;
    int coluna = 0;

    // Lendo codigo ou data
    int reading_code = 0;
    int reading_data = 0;

    file = fopen(("./%s", file_name), "r");

    while(getline(&line, &len, file) != -1){
        if(line[0] != ';' && line[0] != '\n' && line[0] != ' '){
            //printf("%s", line);
            // Le a linha e remove o comentaio
            char curr_line[len];
            for(int i = 0; i < len; i++){
                if(line[i] != ';' && line[i] != '\n'){
                    curr_line[i] = line[i];
                }else{
                    i = len;
                }
            }
            
            // Checa a área que está lendo, e se mudo
            if(strstr(curr_line, ".CODE")){
                reading_code = 1;
                reading_data = 0;
            }else if(strstr(curr_line, ".DATA")){
                reading_code = 0;
                reading_data = 1;
            }else if(reading_code){
                char *comando = strtok(curr_line, " ");
                char *end = strtok(NULL, " ");
                // Checa qual comando foi usado, e adiciona na lista
                if(strcmp(comando, "STA") == 0){
                    pos_codigo = add_codigo(16, *end, pos_codigo);
                    end_codigo += 2;
                }else if(strcmp(comando, "LDA") == 0){
                    pos_codigo = add_codigo(32, *end, pos_codigo);
                    end_codigo += 2;
                }else if(strcmp(comando, "ADD") == 0){
                    pos_codigo = add_codigo(48, *end, pos_codigo);
                    end_codigo += 2;
                }else if(strcmp(comando, "OR") == 0){
                    pos_codigo = add_codigo(64, *end, pos_codigo);
                    end_codigo += 2;
                }else if(strcmp(comando, "AND") == 0){
                    pos_codigo = add_codigo(80, *end, pos_codigo);
                    end_codigo += 2;
                }else if(strcmp(comando, "NOT") == 0){
                    pos_codigo = add_codigo(96, *NO_END, pos_codigo);
                    end_codigo += 1;
                }else if(strcmp(comando, "JMP") == 0){
                    pos_codigo = add_codigo(128, *end, pos_codigo);
                    end_codigo += 2;
                }else if(strcmp(comando, "JN") == 0){
                    pos_codigo = add_codigo(144, *end, pos_codigo);
                    end_codigo += 2;
                }else if(strcmp(comando, "JZ") == 0){
                    pos_codigo = add_codigo(160, *end, pos_codigo);
                    end_codigo += 2;
                }else if(strcmp(comando, "HLT") == 0){
                    pos_codigo = add_codigo(240, *NO_END, pos_codigo);
                    end_codigo += 1;
                }
            }else if(reading_data){
                // Le os dados e indica espaço da memoria onde salvar
                char *nome = strtok(curr_line, " ");
                char *comando = strtok(NULL, " ");
                int valor = atoi(strtok(NULL, " "));
                if(strcmp(comando, "DB") == 0){
                    pos_dados = add_data(*nome, valor, pos_dados);
                }
            }
        }
        line = NULL;
    }
    fclose(file);
}

// Valida onde o código terminou e da endereço de memoria aos dados
void att_memoria(){
    int end = end_codigo;
    for(int i = 0; i < pos_dados; i++){
        dados[i].end = end;
        end += 1;
    }
    for(int i = 0; i < pos_codigo; i++){
        char valor = comandos[i].valor;
        //printf("%d %c\n", comandos[i].minemonico, valor);
        for(int j = 0; j < pos_dados; j++){
            if(dados[i].nome == valor){
                comandos[i].valor = dados[i].end;
                //printf("%d\n", comandos[i].minemonico);
                j = pos_dados;
            }
        }
    }
}

int main(int argc, char *argv[]){
    char *file_name = argv[1];

    lexer(file_name);
    att_memoria();
    assembler(file_name);

    return 0;
}
