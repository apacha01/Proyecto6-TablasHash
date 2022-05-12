/*
Implement with array using linear probing
	hash(k, m) - m is size of hash table
	add(key, value) - if key already exists, update value
	exists(key)
	get(key)
	remove(key)
*/
///////////////////////////////////////////////////////BIBLIOTECAS///////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/////////////////////////////////////////////////////////DEFINES/////////////////////////////////////////////////////////
#define SMALL_PRIME_NUM		103
#define MEDIUM_PRIME_NUM	100003
#define BIG_PRIME_NUM		1000000003
#define DELETED_ITEM		2147483647
#define NON_EXISTANT_ITEM	-2147483648
////////////////////////////////////////////////////////VARIABLES////////////////////////////////////////////////////////

///////////////////////////////////////////////////////ESTRUCTURAS///////////////////////////////////////////////////////
typedef struct
{
	char *key;
	int value;
}Item;

typedef struct
{
	Item *i;
	int m;
}HashTable;
/////////////////////////////////////////////////PROTOTIPOS DE FUNCIONES/////////////////////////////////////////////////
unsigned int hash(char* /*key*/);
void addToTable(HashTable*, char* /*key*/,int /*value*/);
bool existsInTable(HashTable*, char* /*key*/);
int getFromTable(HashTable*, char* /*key*/);
void removeFromTable(HashTable*, char* /*key*/);

//AUX FUNC.
void initHashTable(HashTable*);
void finishHashTable(HashTable*);
void printTable(HashTable*);
////////////////////////////////////////////////////////FUNCIONES////////////////////////////////////////////////////////
//AUX FUNC.
void initHashTable(HashTable *ht, int m){
	ht->i = (Item*)calloc(sizeof(Item),m);
	ht->m = m;
}

void finishHashTable(HashTable *ht){
	free(ht->i);
	ht->m = NULL;
}

void printTable(HashTable *ht){
	printf("----------------------INICIO TABLA HASH----------------------\n");
	for (int i = 0; i < ht->m; ++i){
		printf("%d. Key: %3s", i+1, (ht->i + i)->key);
		printf("\t\tValue: %d\n", (ht->i + i)->value);
	}
	printf("------------------------FIN TABLA HASH-----------------------\n");
}

//CONSIGNA
unsigned int hash(HashTable *ht, char *key){
	int length = strlen(key);
	unsigned int hash = 0;

	for (int i = 0; i < length; i++){
		hash += *(key + i) * *key;
		hash *= BIG_PRIME_NUM;
	}

	hash %= ht->m;

	return hash;
}

void addToTable(HashTable *ht, char *key, int value){
	if(ht == NULL) return;
	unsigned int hashValue = hash(ht,key);
	for (int i = 0; i < ht->m; i++) {
		int hashTrys = (hashValue + i) % ht->m;
		if ((ht->i + hashTrys)->key == NULL && (ht->i + hashTrys)->value == 0) {
			(ht->i + hashTrys)->key = key;
			(ht->i + hashTrys)->value = value;
			return;
		}
	}
}

bool existsInTable(HashTable *ht, char *key){
	//UNA TABLA VACIA O INEXISTENTE
	if(ht == NULL) return false;

	unsigned int hashValue = hash(ht,key);

	for (int i = 0; i < ht->m; i++) {
		int hashTrys = (hashValue + i) % ht->m;
		if ((ht->i + hashTrys)->key != NULL && strcmp((ht->i + hashTrys)->key, key) == 0) {
			return true;
		}
	}

	//SI RECORRIO TODA LA TABLA Y NO ENCONTRO ENTONCES NO EXISTE
	return false;
}

int getFromTable(HashTable *ht, char *key){
	if(ht == NULL) return 0;
	unsigned int hashValue = hash(ht,key);
	if ((ht->i + hashValue)->key == NULL) return 0;
	if (!strcmp((ht->i + hashValue)->key, key)) return (ht->i + hashValue)->value;	//return ht->i (Item) ??
	return 0;
}

void removeFromTable(HashTable *ht, char *key){
	if(ht == NULL) return;
	unsigned int hashValue = hash(ht,key);
	if ((ht->i + hashValue)->key == NULL) return;
	//NO ES LA KEY
	if (strcmp((ht->i + hashValue)->key, key)) return;

	(ht->i + hashValue)->key = NULL;
	(ht->i + hashValue)->value = DELETED_ITEM;
}
///////////////////////////////////////////////////////////FIN///////////////////////////////////////////////////////////