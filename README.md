# TESTE

# Trabalho Prático 1 (Parte 2)
Este trabalho tem por objetivo implementar duas estruturas simples, exam e patient, e uma série de funções a elas associadas.

## Estruturas
O código conta com dois tipos abstratos de dados (TAD). Elas são implementadas com o objetivo de modelar um paciente e um exame. Ambas as estruturas foram criadas em arquivos separados por uma questão de organização do código.

### struct patient
A estrutura patient modela um paciente em um banco de dados de um suposto hospital. O paciente em questão possui três atributos: id, nome e data de aniversário. O id é um identificador único para cada paciente (ele poderia ser unseigned, mas nas especificações foi declarado como inteiro normal). Seu nome é um ponteiro, natural ao esperar uma string, vetor de caracteres. Por fim, ele possui uma data de aniversário, que é na verdade sua data de nascimento, que é uma estrutura tm da biblioteca time.

#### Funções associadas
É uma boa prática que uma estrutura tenha funções a ela associada. Isso é particurlamente útil para que outras pessoas mexam nos parâmetros internos em abiente controlado. Assim, é mais seguro que não ocorra erros no código. Aqui, apenas funções para get, creation e delete foram desenvolvidas. Cada um dos parâmetros tem função get; além disso, existe uma função de criação da estrutura e uma outra função para liberar a memória por ela utilizada.
Todas as funções possuem tratamento de erros e a alocação de memória é feita de forma dinâmica.

### struct exam
A estrutura exam modela um exame em um banco de dados de um suposto hospital. O exame em questão possui quatro atributos: id, paciete_id, rx_id e time. O id é um identificador único para cada exame (ele poderia ser unseigned, mas nas especificações foi declarado como inteiro normal). Também possui um campo para armazenar o id de um paciente (em uma possível associação de chave estrangeira em um banco de dados). Tal qual o id do paciente, também há um campo para o id da máquina de raio-x utilizada no exame. Por fim, ele possui uma data de realização do exame (com horário exato incluso) que é uma estrutura tm da biblioteca time.

#### Funções associadas
É uma boa prática que uma estrutura tenha funções a ela associada. Isso é particurlamente útil para que outras pessoas mexam nos parâmetros internos em abiente controlado. Assim, é mais seguro que não ocorra erros no código. Aqui, apenas funções para get, creation, delete e read foram desenvolvidas. Cada um dos parâmetros tem função get; além disso, existe uma função de criação da estrutura e uma outra função para liberar a memória por ela utilizada. Todas as funções possuem tratamento de erros e a alocação de memória é feita de forma dinâmica.

Como um extra, há a função print_exam que não foi solicitada. Ela imprime todos os atributos da estrutura com os devidos indicadores, caso a estrutura não seja nula.

## Usando o Código
Para usar o código primeiro você deve fazer algo chato. Acesse a pasta "makefilef", ela contém diversos arquivos para a criação do código. Por questões de diferenças entre os comandos de execução dos comandos entre sistemas operacionais, criamos dois arquivos, um w_makefile e um l_makefile. O primeiro é destinado para usuários Windows, o outro para usuários linux. Após identificar o arquivo certo, mova-o para a pasta principal do projeto. Após, basta executar o makefile. Caso queira praticidade, deixamos preparado um arquivo .bat (Windows) e um arquivo .sh (Linux) para executar o comando e limpar os arquivos .o gerados.