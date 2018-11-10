#include "Network.h"

#ifndef SAVEANDLOAD_H
#define SAVEANDLOAD_H

typedef enum DataType {Weights, Bias}DataType;

void SaveData(DataType type, StoreMatrix data);
void SaveNetwork(Network net);
StoreMatrix LoadData(DataType type);
Network LoadNetwork();

#endif