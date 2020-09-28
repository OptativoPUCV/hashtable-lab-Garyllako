#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct Pair Pair;
typedef struct HashMap HashMap;
int enlarge_called=0;

struct Pair {
     char * key;
     void * value;
};

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) { //insertar datos
  long posicion = hash(key, map->capacity);
  while(map->buckets[posicion] != NULL) {
    posicion = posicion + 1;
    if(posicion >= map->capacity){
      posicion = posicion - map->capacity;
    }
  }
  map->buckets[posicion] = createPair(key,value);
  map->size = map->size + 1;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap * map = (HashMap *) malloc(sizeof(long));
    map->buckets = (Pair **) calloc (capacity,sizeof(Pair **));
    map->size = 0;
    map->capacity = capacity;
    map->current = -1;
    return map;
}

void eraseMap(HashMap * map,  char * key) {    
    long posicion = hash(key, map->capacity);
    //while(is_equal(map->buckets[posicion]->key,key) != 1){
    //  posicion += 1;
    //  if(posicion >= map->capacity){
    //    posicion = posicion - map->capacity;
    //  }
    //}
    map->buckets[posicion]->key = NULL;
    map->size -= 1;
}

void * searchMap(HashMap * map,  char * key) {   
    long posicion = hash(key, map->capacity);
    while(is_equal(map->buckets[posicion]->key,key) != 1){
      posicion += 1;
      if(posicion >= map->capacity){
        posicion = posicion - map->capacity;
      }
      if(map->buckets[posicion] == NULL){
        return NULL;
      }
    }
    map->current = posicion;
    return map->buckets[posicion]->value;
}

void * firstMap(HashMap * map) {
    long pos = 0;
    if(map->buckets[pos]->key != NULL){
      return map->buckets[pos]->value;
    }
    else{
      while(map->buckets[pos]->key == NULL){
        pos += 1;
        map->current = pos;
        printf("%ld",pos);
      }
    }
    return map->buckets[pos]->value;
}

void * nextMap(HashMap * map) {

    return NULL;
}
