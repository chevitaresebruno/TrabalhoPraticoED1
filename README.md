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
O projeto está bastante fragmentado. Isso decorre da necessidade de organizar os mais de 16 arquivos totais que o projeto tem em seu final. Assim, toda uma estrutura de divisões e subdiviões foram criadas para organizar o projeto.

### Pasta root
A pasta principal do projeto possui alguns arquivos importantes. O principal é o `main.c`, o qual contém o loop principal da simulação. Além dele, ao executar arquivo executável será gerada uma pasta `output`, a aqual contém o banco de dados gerado pelo programa. Por fim, há a pasta lib, a qual separa todos os módulos criados pelo projeto.


### Pasta lib
A pasta `lib` armazena todos os códigos do projeto. A pasta `bin` é responsável por manter todos os arquivos .o gerados pela receita `all`. A pasta `include`, por sua vez, armazena os arquivos .h dos módulos .c, os quais são armazenados na pasta `src`.

### Divisão dos Módulos
A pasta `src` e `include` são idênticas no quesito de estrutura. Elas determinam as categorias de `scripts` que o projeto possui. No total, pode-se dividir a estrutura em 4 categorias: objects (pasta `obj`), `handlers`, coisas que eu não sei o nome (pasta `adt`, Abstract Data Type) e módulos úteis (pastas `ai` e `db`).

As pastas `ai` e `db` guardam os scripts ai.c e db.c, respectivamente. Eles estão em pastas separadas, pois, possuem funcionamento específico dentro da simulação mas não tinhamos uma pasta com um bom nome para eles, então os jogamos em pastas próprias separadas.

Entende-se por objeto, tudo no sistema que será armazenado no banco de dados. Assim, pacientes, exames e laudos são entendidos como scripts específicos, com recuros específicos e atributos que o representem no banco de dados. Por sua vez, handlers são scripts que manipulam outras estruturas, sejam objetos ou outros TAD's.

Por fim, a pasta de adt possui TAD que são úteis, mas não são descritos dentro do contexto das especificações. No entanto, fazem sentido serem estruturas e tornam todo o processo mais simples e também mais intuitivo.

A nível de implementação, é importante destacar que os arquivos na pasta adt são independentes. Isto é, não dependem de nada mais do que sua própria estrutura. Já objetos tendem a não depender de mais nada, mas podem depender de algum arquivo da pasta adt. Por fim, os objetos não dependem de handlers, mas estes comumente dependem de um objeto ou arquivo da pasta adt.

### Arquivo shared.h
A pasta `include` possui um arquivo chamado shared.h. Nele, são definidos algumas coisas úteis em todos os módulos. Não é um arquivo fundamental, serve somente para deixar as estruturas mais elegantes dentro do contexto dos códigos. Por exemplo, um tipo `ID` é um inteiro de valor somente positivo, logo unsigned int. Para não ficar escrevendo isso sempre, nomeamos esse conjunto de ID, tornando o código mais legível.

### Sobre a Documentação e Padrões
Toda a documentação dos módulos foi feita nos arquivos .h. Os arquivos .c só vão possuir "docs strings" caso as funções, ou estruturas, sejam privadas (não estejam mencionadas nos arquivos .h).

Por padrão, todo arquivo contém um nome em letras minúsculas. Os arquivos .c iniciam, após as importações, com a estrutura definida com letras minúsculas. Na sequência, seguem as funções associadas à estrutura, seguindo o padrão `nomeDaEstrutura_verbo_complemento`, onde um verbo é uma ação a ser executada e o complemento é opcional. Os arquivos .h, por sua vez, iniciam definindo a estrutura do arquivo como a mesma estrutura, mas letras separadas entre palavras em maiúsculo, iniciando em maiúsculu (exemplo, o termo `xrmm` é uma abreviação para X-Ray Machine Manager, então no arquivo xrmm.c tem-se `struct xrmm` e no arquivo xrmm.h tem-se `typedef struct xrmm XRMachineManager`).

Ainda nos arquivos .h, tem-se as docstrings das estruturas e funções. Cada uma possui um padrão, conforme evidênciado abaixo:

**Estrturas**

    Feature:
        Explicação da estrutura.
    
    Attributes:
        Definição e explicação dos atributos públicos da estrutura, ou seja àqueles que possuem função de "Get".
    
    Verbs:
        Conjunto de verbos associados à estrutura e suas respectivas funções.

    typedef struct estrutura Estrutura;


**Funções**
    
    Feature:
        Explicação breve do funcionamento da função. Só existe caso a função não tenha verbo associado.

    Verb:
        Verbo que aquela função utiliza. Não existe caso Feature seja descrita.

    Feature Complement:
        Explicação adicional sobre o funcionamento da função (opcional).
    
    Args:
        Explicação de cada argumento função (opcional).
    
    Return:
        Informa o valor retornado (Opcional).


## Principais Tipos Abstratos de Dados
Dentro do contexto da simulação, diversos tipos abstratos de dados foram implementados. Como anteriormente explicado, os TAD's possuem 4 categorias, mas as mais importantes são os objetos e os handlers. E são neles que vamos focar.

### Objetos
Os objetos são estruturas com presentação no Banco de Dados. Dentro desse contexto, temos os objetos Patient, Exam e Laudo. Todos os objetos possuem os seguintes verbos:

        Create -> Cira um novo elemento daquele tipo;
        Get -> Pega um atributo do elemento;
        Set -> Coloca um valor específico em um atributo; e
        Free -> Libera memória alocada dinâmicamente para a estrutura.

Abaixo, segue uma pequena descrição de cada estrutura:

    Patient
    
        Representa um Paciente no banco de dados como uma lista simplesmente encadeada. A decisão de implementar a estrutura como lista simplesmente encadeada é para reduzir a generalidade do código e tornar a implementação mais simples (o mais correto a nível de arquitetura é ter uma estrutura lista cujos elementos internos são nós, mas preferimos evitar um pouco de trabalho).

        Verbos Definidos: Create, Get, Set e Free.

    Exam

        Representa um Exame no banco de dados como uma lista simplesmente encadeada. A decisão de implementar a estrutura como lista simplesmente encadeada é para reduzir a generalidade do código e tornar a implementação mais simples (o mais correto a nível de arquitetura é ter uma estrutura lista cujos elementos internos são nós, mas preferimos evitar um pouco de trabalho).

        Verbos Definidos: Create, Get, Set e Free.

    Report

        Representa um Laudo no banco de dados.

        Verbos Definidos: Create, Get e Free.
    

### Handlers
Handlers são estruturas que manipulam outras estruturas ou processos. No caso do sistema, os dois principais Handlers são: Patient Queue e Exam Queue. O primeiro, controla a lista de chegada de pacientes no hospital, enquanto o segundo gerencia o total de exames em aguardo para receber um laudo, considerando a sua prioridade após sair da IA. Os Hadnlers, possuem os eguintes verbos associados:

        Create -> Cria uma nova estrutura;
        Get -> Pega um atributo de um elemento;
        Insert -> Insere uma estrutura em uma lista;
        Remove -> Remove uma estrutura de uma lista;
        Alloc -> Aloca uma estrutura em um processo;
        Dealloc -> Desaloca uma estrutura ao final de um processo.
        Check -> Verifica uma condição.

Abaixo, segue uma explicação sobre o Handler patientQueue:

    PatientQueue
        
        Feature:
            Estrutura reponsável por ordenar a lista de pacientes aguardando um exame na lista. Os pacitentes novos são inseridos ao final da lista e os primeiros a erem removidos são os mais antigos. A estrutura comporta-se como uma fila, seguinte o princípio FIFO (First in, Firts out).
        
        Verbos Associados: Create, Get, Insert e Remove.


#### Exam Queue
A seguinte estrutura merece um tópico só para ela por ser consideravelmente mais complexa do que a anterior. Essa lista também é uma fila simplesmente encadeada, no entanto os elementos são inseridos de acordo com uma prioriade. Por consequência, os elementos saem de acordo com uma prioriade.

A solução óbivia é tratar a fila como uma lista simplesmente encadeada e onde ao inserir um valor nela, o códgo busca pelo último elemento daquela condição e então insere um novo exame ao final. O problema dessa abordagem é o consumo de processamento em uma fila superlotada.

Para corrigir esse problema e ganhar mais performance, definiu-se que a lista armazena cada último elemento de uma prioridade específica. Assim, ao inserir um novo elemento na lista, basta acessar aquele elemento em particurlar. 

    ExamQueue

        Feature:
            Estrutura reponsável por ordenar a lista de exames aguardando um laudo, seguindo uma ordem de prioridade.
        
        Verbos Associados: Create, Get, Insert e Remove.