# Sistema de Gerenciamento Acadêmico

Este repositório contém funções para gerenciar cursos, disciplinas, professores e distribuições de disciplinas em uma instituição de ensino. Abaixo estão descritas as principais funções disponíveis no sistema.

## Funções Disponíveis

### Cadastro

- **cadastrarCurso()**: Esta função permite ao usuário cadastrar um novo curso de graduação. O usuário deve fornecer o código do curso, o nome do curso e a área do curso (Exatas, Humanas, Biológicas).

- **cadastrarDisciplina()**: Com esta função, o usuário pode cadastrar uma nova disciplina. São necessários o código da disciplina, o nome da disciplina, o código do curso ao qual a disciplina pertence e a série da disciplina.

- **cadastrarProfessor()**: Esta função permite ao usuário cadastrar um novo professor. São necessários o código do professor e o nome do professor.

- **cadastrarDistDisc()**: O usuário pode usar esta função para cadastrar uma distribuição de disciplina, associando uma disciplina a um professor e a um ano letivo. São necessários o código da disciplina, o ano letivo e o código do professor.

### Remoção

- **removerDistDisc()**: Esta função permite ao usuário remover uma distribuição de disciplina existente. O usuário precisa fornecer o código da disciplina e o ano letivo da distribuição a ser removida.

### Impressão

- **imprimirListCurso()**: Com esta função, o usuário pode visualizar a lista de cursos de graduação cadastrados, incluindo o código do curso, o nome e a área.

- **imprimirListDisc()**: Esta função permite ao usuário visualizar a lista de disciplinas cadastradas, incluindo o código da disciplina, o nome da disciplina, o código do curso ao qual pertence e a série.

- **imprimirListProf()**: O usuário pode usar esta função para ver a lista de professores cadastrados, incluindo o código do professor e o nome.

- **imprimirDistDisc()**: Com esta função, o usuário pode visualizar a lista de distribuições de disciplina, incluindo informações sobre a disciplina, o ano letivo e o professor associado.

- **imprimelivre()**: Com esta função, o usuário pode visualizar os nós que foram removidos.

- **imprimirpornivel()**: Com esta função, o usuário pode visualizar o arquivo binário em árvore via prompt.

### Carregamento em Lote

- **carregarLote()**: Esta função permite ao usuário carregar informações em lote a partir de um arquivo de texto. Isso é útil para inicializar o sistema com um conjunto de dados existentes.

## Instruções de Uso

1. Clone o repositório:
    ```sh
    git clone https://github.com/julietRigoti/Algoritmo-e-Estrutura-de-Dados.git
    ```
2. Navegue até o diretório do projeto:
    ```sh
    cd Algoritmo-e-Estrutura-de-Dados/T2-AED-ArvoreBinaria
    ```
3. Siga as instruções específicas de cada função para cadastrar, remover ou visualizar informações no sistema.
