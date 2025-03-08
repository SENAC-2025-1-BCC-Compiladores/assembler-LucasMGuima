[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/FLG6_3H5)
# Assembler para o Neander
Lucas da Mata Guimarães

## Observações
>O Lexer não possue a capacidade de intepretar a palavra reservada ```.ORG```, logo o código sempre inícia no endereço ```0```da memória.

### Para testar
O assembler vem com um cósigo de texte, ```./codigo.txt```, sendo uma soma simples de 2 elementos e o resultado é armazenado em outra váriavel.

- **Compilar**:
    Para compilar basta rodar o comando ``make assembler`` na pasta raiz do projeto.
    Deve aparecer um arquivo ``assembler.exe`` na pasta raiz do projeto.

- **Testar**:
    Para testar basta rodar o comando ``make teste`` na pasta raiz do projeto.
    Será criado um arquivo ```.mem```com o mesmo nome do arquivo ```.txt```passado como parametro, neste caso, código.
    Esse arquivo gerado pode ser tanto lido pelo Neander, como pela VM criada anteriormente.

### Usando
Desdeque se siga o padrão de nomenclatura dos minemonimos do Neander, e da escrita contida no arquivo ```codigo.txt```, pode ser passar qualquer código para o assembler, que o arquivo ```.mem```será gerado.
```
    ./assembler.exe [nome do seu arquivo].txt
```

> [!IMPORTANT]
> Os arquivos gerados tem no máximo 255 espaços de memósria, qualquer parte do código que fique a mais, podera acarretar em erros e possivelmente fazer o assembler falhar.