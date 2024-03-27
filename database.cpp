#include "database.h"
#include <iostream>

#define INITIAL_CAPACITY 16
#define GROW_FACTOR 2

void destroyEntry(Entry *entry) {
  destroyValue(entry->type, entry->value);
  delete entry;
}

// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value) {
  Entry *entry = new Entry;
  entry->type = type;
  entry->key = key;
  entry->value = value;
  return entry;
}

// 데이터베이스를 초기화한다.
void init(Database &database) {
  database.size = 0;
  database.capacity = INITIAL_CAPACITY;
  database.entries = new Entry *[database.capacity];
}

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry) {
  if (database.size == database.capacity) {
    database.capacity *= GROW_FACTOR;
    Entry **newEntries = new Entry *[database.capacity];
    for (int i = 0; i < database.size; i++) {
      newEntries[i] = database.entries[i];
    }
    delete[] database.entries;
    database.entries = newEntries;
  }
  database.entries[database.size++] = entry;
}

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key) {
  for (int i = 0; i < database.size; i++) {
    if (database.entries[i]->key == key) {
      return database.entries[i];
    }
  }
  return nullptr;
}

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key) {
  for (int i = 0; i < database.size; i++) {
    if (database.entries[i]->key == key) {
      destroyEntry(database.entries[i]);
      for (int j = i; j < database.size - 1; j++) {
        database.entries[j] = database.entries[j + 1];
      }
      database.size--;
      return;
    }
  }

  std::cerr << "not found" << std::endl;
}

// 데이터베이스를 해제한다.
void destroy(Database &database) {
  for (int i = 0; i < database.size; i++) {
    destroyEntry(database.entries[i]);
  }
  delete[] database.entries;
}

void destroyValue(Type type, void *value) {
  switch (type) {
  case Type::INT:
    delete (int *)value;
    break;
  case Type::DOUBLE:
    delete (double *)value;
    break;
  case Type::STRING:
    delete (std::string *)value;
    break;
  case Type::ARRAY:
    Array *array = (Array *)value;
    for (int i = 0; i < array->size; i++) {
      destroyValue(array->type, ((void **)array->items)[i]);
    }
    delete[] (void **)array->items;
    delete array;
    break;
  }
}
