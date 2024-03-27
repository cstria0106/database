#ifndef IO_H
#define IO_H

#include "database.h"

std::string readKey();
bool readType(Type &type);
int *readInt();
double *readDouble();
std::string *readString();
Array *readArray();
void *readValue(Type type);
Entry *readEntry();

#endif