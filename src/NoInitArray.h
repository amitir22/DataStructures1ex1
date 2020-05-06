#ifndef DEEZEL_NOINITARRAY_H
#define DEEZEL_NOINITARRAY_H

#include <exception>

// TODO: make a non-integer data structure
// TODO: more methods needed like getSize() etc...
class NoInitArray {
private:
    int          *A;    // the data
    unsigned int *C;    // initialized indexes map
    unsigned int *B;    // reverse map of C
    int numOfUsedIndexes;
    unsigned int capacity;
public:
    NoInitArray(); // Improper usage

    NoInitArray(int size);

    int get(unsigned int index);

    void put(unsigned int index, int value);

    // TODO: maybe put this method static inline
    bool isIndexValid(unsigned int index);

    // TODO: maybe put this method static inline
    bool isIndexInitialized(unsigned int index);

    class NoInitArrayException : public std::exception {
        const char *what() const noexcept override {
            return "Improper usage of Non-Initialized Array";
        }
    };

    class UnInitializedIndexException : public std::exception {
        const char *what() const noexcept override {
            return "Attempted to retrieve data from uninitialized index";
        }
    };

    class IndexOutOfBoundsException : public std::exception {
        const char *what() const noexcept override {
            return "Attempted to store data out of the bounds of the array";
        }
    };
};


#endif //DEEZEL_NOINITARRAY_H
