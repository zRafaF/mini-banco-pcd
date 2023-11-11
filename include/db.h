#ifndef DB_H
#define DB_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "trie.h"

typedef struct
{
    char id[MAX_ID_SIZE];               // Obrigatoriamente uma string de letras minusculas
    char fullName[MAX_FULL_NAME_SIZE];  // Nome completo da Pessoa
    int age;                            // Idade da pessoa
} PersonRecord;

typedef struct
{
    TrieNode* trie;
} DataBase;

/*
Instancia um novo banco de dados

ATENÇÃO: É necessário deletar esse Nodo. Com a função `deleteDataBase()`
*/
DataBase* createDataBase();

// Insere um novo PersonRecord ao banco de dados (Volátil)
DataBase* insertNewRecord(DataBase* db, PersonRecord newRecord);

// Helper para criar um novo PersonRecord
PersonRecord createPersonRecord(char id[MAX_ID_SIZE], char fullName[MAX_FULL_NAME_SIZE], int age);

// Imprime os dados contidos em um PersonRecord
PersonRecord* printPersonRecord(PersonRecord* record);

// Imprime todos os elementos do banco de dados (Volátil)
DataBase* printEntireDB(DataBase* db);

// Função privada: Recursão para imprimir os elementos
void _displayDBElement(TrieNode* node, int level);

/*
    Libera a memória alocada ao banco de dados.

    Ao deletar o Banco de dados as estruturas de dados relacionadas também serão excluídas
*/
void deleteDataBase(DataBase* db);

#endif