# Trabalho Prático 1 (Parte 2)
O presente repositório contém todos os aquivos necessários para a execução do trabalho prático 1, parte 2, da disciplina de estrutura de Dados. Nos tópicos subsequentes, informações como requisitos, como executar o programa e contexto sobre a implementação serão abordados. Caso queira ler as especificações do trabalho, leia o arquivo "TrabalhoPratico2_Especificacoes.pdf".

## Requisitos
O projeto foi desenvolvido e testado em duas plataformas específica. Quanto aos sistemas operacionais (SO), testou-se:
    
    • Ubuntu 22.04; e
    • Windows 11.

Quanto aos compiladores, os testados foram:

    GCC 11 (Linux Version); e
    GCC 11 (Windows Version).

Assegura-se que o projeto é capaz de ser compilado e executado nesses dois sistemas operacionais e compiladores. No entanto, é possível que outros sistemas e compiladores executem corretamente o programa.

Em particular, o módulo `db.c` pode ser problemático, pois, ele utiliza bibliotecas de criação de arquivos e pastas. Portanto, caso seu SO ou compilador tenha diferenças em relação aos comandos de criação e modificação de arquivos e pastas, é fortemente recomendável edi
tá-los para funcionamento correto.

Ademais, caso você seja usuário Linux, recomenda-se fortemente a instalação do "make", para a execução mais fácil da do código.

Por fim, para que o código seja compilado corretamente, assegure que em seu computador existem as bibliotecas:

    • stdlib;
    • string;
    • stdio;
    • time;

    Para uusuários Windows:
        • direct;

    Para usuários unix:
        • sys/stat;
        • sys/types; e
        • unistd.


## Instalação e Execução
Para baixar e executar corretamente o projeto, siga as instruções abaixo.

### Preparando as dependências
O primeiro passo é instalar todas as dependências necessárias para a execução do projeto.

#### Sistema Windows 11
Caso você seja usuário Windows, instale o programa mingw32 (https://sourceforge.net/projects/mingw-w64/). Após, com o programa aberto, marque a opção "Basic Setup" na barra lateral esquerda, e escolha os pacotes na seção central, "Package", "mingw-devolper-toolkit" e "mingw32-base". Depois, na barra horizontal superior, escolha a opção "Instalation" e "Aplly Changes". Por fim, adicione a pasta do mingw nas variáveis Path do "Windows". Na caixa de pesquisa, busque por "Editar as variáveis de ambiente do sistema", clique na caixa "Variáveis de Ambiente...", duplo clique na variável "Path" e então clique em novo. Na caixa de escrita, excreva o nome do caminho onde o mingw foi instalado (comumente ` C:\\MinGW\\bin `).
    

#### Ubuntu
Caso você seja usuário ubuntu, comece atualizando seus arquivos com o comando ` sudo apt-get update `. Depois, instale o ` gcc ` com o comando ` sudo apt install gcc`. Por fim, recomenda-se instalar o `make` com o comando ` sudo apt install make `.

### Clone o Repositório
Com as dependências preparadas, clone o repositório para a sua máquina local. É possível fazer isso baixando os arquivos e descompatando-os, ou utilizando o comando abaixo:

    git clone https://github.com/chevitaresebruno/TrabalhoPraticoED1

Atenção usuários Windows: o comando acima apenas funcionará se você tiver os comandos git instalados no seu computador. Recomendamos o GitBash: https://git-scm.com/downloads.

### Compile o Código:
O próximo passo é compilar o código. A estrutura do projto é bastante complexa, portanto recomenda-se FORTEMENTE o uso das receitas pré-prontas no arquivo "makefile". O mesmo contém duas receitas, `all`, a qual irá compilar todo o projeto e gerará um arquivo executável na pasta "root" do projeto, e `clean`, o qual pode ser utilizado para limpar os arquivos criados pela receita `all`. No arquivo "makefile", também é possível configurar o compilador e as suas flags. Dicas de comandos para executar as receitas abaixo:

    Usuário Linux:
        make all
        make clean
    
    Usuário Windows
        mingw32-make all
        mingw32-make clean

### Execute o Programa:
Após a compilação do projeto, um arquivo, definido por padrão como `main.exe`, executável será gerado na root. Então, basta executá-lo e verificar os prompts de saída.

    Usuário Windows:
        main.exe
    
    Usuário Linux:
        ./main.exe


## Compreendendo a Estrutura do Projeto
### xrMachineManager

Gerencia as máquinas de exame disponíveis no hospital. Responsável por alocar e liberar máquinas de raio-x para os exames.

### patient
Representa um paciente no sistema. Armazena as informações de ID e nome, como uma lista simplesmente encadeada.

### patientQueue
Gerencia a fila de pacientes. Optou-se pela estrutura de Fila, pois seu funcionamento FIFO (Firs in, First Out) é o exigido no contexto do hospital.

### examQueue
Assim como patientQueue, essa lista armazena informações de exames (dentro do cógico ficou como Report, mas para lógica dele exames e reports são a mesma coisa, a diferença é o momento onde ele é utilizado). No entanto, esse lista está ordenada mediante uma priorirade, estabelecida pela condição do paciente. A estrutura de examQueue contém como atributos "firts", que salva o primeiro paciente da fila, e "last_per_p", que salva o último elemento de pioridade em um vetor de Reports. Assim fizemos, pois, ao considerarmos uma estrutura de lista simplesmente encadeada, definir a posição de um novo elemento exige percorrer elemento a elemento e verificar a sua gravidade. Da forma como foi implementada, no entanto, basta acessar o último elemento da prioridade desejada e substituir o valor.

### medicManager

Essa estrutura é usada para gerenciar o médico. No caso, se ele ainda está, ou não, avaliando um exame.

