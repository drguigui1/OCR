#include "Network.h"

#ifndef SAVEANDLOAD_H
#define SAVEANDLOAD_H

typedef enum DataType {Weights, Bias}DataType;

void SaveData(DataType type, StoreMatrix data);
StoreMatrix LoadData(DataType type);

#endif