#ifndef MENU_H
#define MENU_H

#include "arqB.h"
#include "cursos.h"
#include "professores.h"
#include "disciplinas.h"
#include "distribuicoes.h"

// Função para registrar informações de um arquivo de texto em uma estrutura de dados
// Pré-condição: O arquivo passado como argumento está aberto para leitura
// Pós-condição: As informações do arquivo de texto são registradas na estrutura de dados
void registroArqTXT(FILE *f);

// Função para verificar se o arquivo foi carregado com sucesso
// Pré-condição: O arquivo é passado como argumento
// Pós-condição: Retorna 0 se o arquivo foi carregado com sucesso, 1 caso contrário
int loadFile(FILE* file);

// Função para carregar informações de um arquivo em lote
// Pré-condição: Nenhuma
// Pós-condição: As informações do arquivo em lote são registradas na estrutura de dados
void carregarLote();

// Função que exibe o menu e permite ao usuário escolher uma opção
// Pré-condição: Nenhuma
// Pós-condição: Dependendo da escolha do usuário, as funções correspondentes são chamadas
void menu();

#endif
