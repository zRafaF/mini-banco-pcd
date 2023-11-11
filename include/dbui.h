#ifndef DBUI_H
#define DBUI_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db.h"
#include "globals.h"

// Processa a UI "no terminal"
bool processUi(DataBase* db);

// Implementa o comando '?', procura um id no banco (volátil)
void _searchDBForId(DataBase* db, char data[MAX_DATA_SIZE], size_t dataSize);

// Implementa o comando '+', realiza o parsing e adiciona a entrada ao banco (volátil)
void _addToDb(DataBase* db, char data[MAX_DATA_SIZE], size_t dataSize);

// Implementa o comando '-', remove um PersonRecord do banco (volátil)
void _removeFromDb(DataBase* db, char data[MAX_DATA_SIZE], size_t dataSize);

// Implementa o comando 'P', imprime todo o banco (volátil)
void _printDb(DataBase* db);

// Faz o parsing do input do usuário para um novo PersonRecord
PersonRecord _parseData(char data[MAX_DATA_SIZE], size_t dataSize);

// Inverte uma string
void _invertString(char* str);

#endif