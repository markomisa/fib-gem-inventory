#ifndef CONVERTER_H
#define CONVERTER_H

// Forward declarations
class MinFibHeap;
class MaxFibHeap;

MinFibHeap* maxToMinHeap(MaxFibHeap* heap);
MaxFibHeap* minToMaxHeap(MinFibHeap* heap);

#endif // CONVERTER_H