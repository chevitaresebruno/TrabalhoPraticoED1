# Trabalho Prático 1 (Parte 2)
Este trabalho tem por objetivo implementar duas estruturas simples, exam e patient, e uma série de funções a elas associadas.

## Requisitos

    Sistema Operacional: Ubuntu 22.04
    Compilador: GCC 11

## Instalação e Execução

Siga os passos abaixo para compilar e executar o projeto:

### Clone o Repositório:
` cgit clone https://github.com/chevitaresebruno/TrabalhoPraticoED1 `


### Compile o Código:
Para compilar o código, basta executar a receita "all", contida no arquivo makefile. O código foi desenvolvido pensando no sistema "Ubuntu 22.04", com o compilador "GCC 11".

### Execute o Programa:
Após a compilação, execute o programa com o comando:

` ./main.exe `


## Tipos Abstratos de Dados (TADs) Implementados
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

