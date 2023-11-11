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
void searchDBForId(DataBase* db, char data[MAX_DATA_SIZE], size_t dataSize);

// Implementa o comando '+', realiza o parsing e adiciona a entrada ao banco (volátil)
void addToDb(DataBase* db, char data[MAX_DATA_SIZE], size_t dataSize);

// Faz o parsing do input do usuário para um novo PersonRecord
PersonRecord _parseData(char data[MAX_DATA_SIZE], size_t dataSize);

// Inverte uma string
void _invertString(char* str);

#endif