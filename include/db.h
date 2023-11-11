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
    char staticPath[PATH_STRING_SIZE];
} DataBase;

/*
Instancia um novo banco de dados

ATENÇÃO: É necessário deletar esse Nodo. Com a função `deleteDataBase()`
*/
DataBase* createDataBase(char staticPath[PATH_STRING_SIZE]);

// Checa se um ID já existe e insere um novo PersonRecord ao banco de dados (Volátil)
PersonRecord* insertNewRecord(DataBase* db, PersonRecord newRecord);

PersonRecord* findRecordById(DataBase* db, char id[MAX_ID_SIZE]);

// Remove um PersonRecord por seu ID
bool removeRecordById(DataBase* db, char id[MAX_ID_SIZE]);

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

// Faz o parsing do input do usuário para um novo PersonRecord
PersonRecord parseData(char data[MAX_DATA_SIZE], size_t dataSize);

// Inverte uma string
void _invertString(char* str);

// Carrega dados do disco a partir Path do db
bool loadRecordsFromDisk(DataBase* db);

// Salva dados ao disco, procura o arquivo explicito no path e caso não o encontre cria um novo arquivo
bool saveRecordsToDisk(DataBase* db);

// Função privada: Recursão para imprimir os elementos ao disco
void _printToDiskRecursive(TrieNode* node, int level, FILE* fp);

// Conta o número de Recordes no banco
unsigned int countNumOfRecords(DataBase* db);

#endif