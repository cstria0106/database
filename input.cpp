#include "input.h"
#include "database.h"
#include <iostream>
#include <string>

std::string readKey() {
  std::cout << "key: ";
  std::string key;
  std::cin >> key;
  return key;
}

bool readType(Type &type) {
  std::cout << "type (int, double, string, array): ";
  std::string typeString;
  std::cin >> typeString;

  if (typeString == "int") {
    type = Type::INT;
  } else if (typeString == "double") {
    type = Type::DOUBLE;
  } else if (typeString == "string") {
    type = Type::STRING;
  } else if (typeString == "array") {
    type = Type::ARRAY;
  } else {
    return false;
  }

  return true;
}

int *readInt() {
  int *value = new int;
  std::cin >> *value;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore();
    std::cerr << "invalid int" << std::endl;
    return nullptr;
  }
  return value;
}

double *readDouble() {
  double *value = new double;
  std::cin >> *value;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore();
    std::cerr << "invalid double" << std::endl;
    return nullptr;
  }
  return value;
}

std::string *readString() {
  std::string *value = new std::string;
  std::getline(std::cin, *value);
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore();
    std::cerr << "invalid string" << std::endl;
    return nullptr;
  }
  return value;
}

Array *readArray() {
  Type type;
  if (!readType(type)) {
    std::cerr << "invalid type" << std::endl;
    return nullptr;
  }

  std::cout << "size: ";
  int size;
  std::cin >> size;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore();
    std::cerr << "invalid size" << std::endl;
    return nullptr;
  }

  if (type == Type::STRING) {
    std::cin.ignore();
  }

  void **items = new void *[size];
  for (int i = 0; i < size; i++) {
    std::cout << "item[" << i << "]: ";
    items[i] = readValue(type);
    if (items[i] == nullptr) {
      for (int j = 0; j < i; j++) {
        destroyValue(type, items[j]);
      }
      delete[] items;
      return nullptr;
    }
  }

  Array *value = new Array;
  value->type = type;
  value->size = size;

  value->items = items;
  return value;
}

void *readValue(Type type) {
  switch (type) {
  case Type::INT:
    return readInt();
  case Type::DOUBLE:
    return readDouble();
  case Type::STRING:
    return readString();
  case Type::ARRAY:
    return readArray();
  }
  return nullptr;
}

Entry *readEntry() {
  std::cout << "key: ";
  std::string key;
  std::cin >> key;

  Type type;
  if (!readType(type)) {
    std::cerr << "invalid type" << std::endl;
    return nullptr;
  }

  if (type == Type::STRING) {
    std::cin.ignore();
  }

  std::cout << "value: ";
  void *value = readValue(type);
  if (value == nullptr)
    return nullptr;

  return create(type, key, value);
}
