#ifndef SAVE_AND_LOAD_H
#define SAVE_AND_LOAD_H

typedef enum DataType {Weights, Bias}DataType;

void SaveData(DataType type, StoreMatrix data);
StoreMatrix LoadData(DataType type);

#endif