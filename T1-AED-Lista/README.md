# Sistema de Gerenciamento Acadêmico

Este repositório contém funções para gerenciar cursos, disciplinas, professores e distribuições de disciplinas em uma instituição de ensino. Abaixo estão descritas as principais funções disponíveis no sistema.

## Funções Disponíveis

### Cadastro

- **cadastrarCurso()**: Permite ao usuário cadastrar um novo curso de graduação.
  - Parâmetros: código do curso, nome do curso, área do curso (Exatas, Humanas, Biológicas).

- **cadastrarDisciplina()**: Permite ao usuário cadastrar uma nova disciplina.
  - Parâmetros: código da disciplina, nome da disciplina, código do curso ao qual a disciplina pertence, série da disciplina.

- **cadastrarProfessor()**: Permite ao usuário cadastrar um novo professor.
  - Parâmetros: código do professor, nome do professor.

- **cadastrarDistDisc()**: Permite ao usuário cadastrar uma distribuição de disciplina, associando uma disciplina a um professor e a um ano letivo.
  - Parâmetros: código da disciplina, ano letivo, código do professor.

### Remoção

- **removerDistDisc()**: Permite ao usuário remover uma distribuição de disciplina existente.
  - Parâmetros: código da disciplina, ano letivo da distribuição a ser removida.

### Impressão

- **imprimirListCurso()**: Permite ao usuário visualizar a lista de cursos de graduação cadastrados.
  - Informações exibidas: código do curso, nome do curso, área do curso.

- **imprimirListDisc()**: Permite ao usuário visualizar a lista de disciplinas cadastradas.
  - Informações exibidas: código da disciplina, nome da disciplina, código do curso ao qual pertence, série.

- **imprimirListProf()**: Permite ao usuário visualizar a lista de professores cadastrados.
  - Informações exibidas: código do professor, nome do professor.

- **imprimirDistDisc()**: Permite ao usuário visualizar a lista de distribuições de disciplina.
  - Informações exibidas: código da disciplina, ano letivo, código do professor.

### Carregamento em Lote

- **carregarLote()**: Permite ao usuário carregar informações em lote a partir de um arquivo de texto.
  - Utilidade: inicializar o sistema com um conjunto de dados existentes.

## Instruções de Uso

1. Clone o repositório:
    ```sh
    git clone https://github.com/julietRigoti/Algoritmo-e-Estrutura-de-Dados.git
    ```
2. Navegue até o diretório do projeto:
    ```sh
    cd Algoritmo-e-Estrutura-de-Dados/T1-AED-Lista
    ```
3. Compile e execute.
