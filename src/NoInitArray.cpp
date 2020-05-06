#include "NoInitArray.h"

NoInitArray::NoInitArray() {
    throw NoInitArrayException();
}

NoInitArray::NoInitArray(int size) : numOfUsedIndexes(0), capacity(size) {
    try {
        A = new int[size];
        B = new unsigned int[size];
        C = new unsigned int[size];
    } catch (...) {
        throw NoInitArrayException();
    }
}

int NoInitArray::get(unsigned int index) {
    if (isIndexValid(index)) {
        if (isIndexInitialized(index)) {
            return A[index];
        } else {
            throw UnInitializedIndexException();
        }
    } else {
        throw IndexOutOfBoundsException();
    }
}

void NoInitArray::put(unsigned int index, int value) {
    if (isIndexValid(index)) {
        if (!isIndexInitialized(index)) { // initializing the index
            C[numOfUsedIndexes] = index;
            B[index] = numOfUsedIndexes;
            ++numOfUsedIndexes;
        }

        A[index] = value;
    } else {
        throw IndexOutOfBoundsException();
    }
}

bool NoInitArray::isIndexValid(unsigned int index) {
    return index < this->capacity; // kept "this" keyword for readability
}

bool NoInitArray::isIndexInitialized(unsigned int index) {
    return (B[index] < numOfUsedIndexes && B[index] >= 0 && C[B[index]] == index);
}
