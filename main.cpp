#include "database.h"
#include "input.h"
#include <iostream>
#include <string>

void printValue(Type type, void *value) {
  switch (type) {
  case Type::INT:
    std::cout << *((int *)value);
    break;
  case Type::DOUBLE:
    std::cout << *((double *)value);
    break;
  case Type::STRING:
    std::cout << "\"" << *((std::string *)value) << "\"";
    break;
  case Type::ARRAY:
    Array *array = (Array *)value;
    std::cout << "[";
    for (int i = 0; i < array->size; i++) {
      printValue(array->type, ((void **)array->items)[i]);
      if (i < array->size - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "]";
    break;
  }
}

void printEntry(Entry *entry) {
  std::cout << entry->key << ": ";
  printValue(entry->type, entry->value);
  std::cout << std::endl;
}

std::string &readCommand() {
  static std::string command;
  std::cout << "command (list, add, get, del, exit): ";
  std::cin >> command;
  if (std::cin.fail()) {
    exit(1);
  }
  return command;
}

void listCommand(Database &database) {
  for (int i = 0; i < database.size; i++) {
    printEntry(database.entries[i]);
  }
}

void addCommand(Database &database) {
  Entry *entry = readEntry();
  if (entry == nullptr) {
    return;
  }
  add(database, entry);
}

void getCommand(Database &database) {
  std::string key = readKey();
  Entry *entry = get(database, key);
  if (entry != nullptr) {
    printEntry(entry);
  } else {
    std::cerr << "not found" << std::endl;
  }
}

void delCommand(Database &database) {
  std::string key = readKey();
  remove(database, key);
}

int main() {
  Database database;
  init(database);

  while (true) {
    std::string &command = readCommand();

    if (command == "list") {
      listCommand(database);
    }

    else if (command == "add") {
      addCommand(database);
    }

    else if (command == "get") {
      getCommand(database);
    }

    else if (command == "del") {
      delCommand(database);
    }

    else if (command == "exit") {
      break;
    }

    else {
      std::cerr << "invalid command" << std::endl;
    }

    std::cout << std::endl;
  }

  destroy(database);
}