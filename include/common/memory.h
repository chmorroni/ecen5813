/**
 * @file memory.h
 * @brief Memory manipulation functions
 *
 * This header file contains the prototypes for functions to manipulate memory.
 *
 * @author Christopher Morroni
 * @date 01/30/2018
 */
#ifndef __MEMORY_H__
#define __MEMORY_H__

/**
 * @brief Copys a block of memory
 *
 * Given a pointer to each source and destination and their size,
 * this function copies the data from the source to the destination.
 * Guaranties no data corruption when source and destination overlap.
 *
 * @param src Pointer to the source data
 * @param dst Pointer to the destination data
 * @param length The length of the memory block to copy
 *
 * @return A pointer to the destination memory
 */
uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length);

/**
 * @brief Copys a block of memory
 *
 * Given a pointer to each source and destination and their size,
 * this function copies the data from the source to the destination.
 *
 * @param src Pointer to the source data
 * @param dst Pointer to the destination data
 * @param length The length of the memory block to copy
 *
 * @return A pointer to the destination memory
 */
uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length);

/**
 * @brief Sets all bytes in a block of data to a given value
 *
 * Given a pointer to a source memory location and its size,
 * sets each byte in the block to the given value.
 *
 * @param src Pointer to the source block
 * @param length The length of the source block
 * @param value The byte that will be copied to each byte of the source block
 *
 * @return A pointer to the source memory block
 */
uint8_t * my_memset(uint8_t * src, size_t length, uint8_t value);

/**
 * @brief Zeros out a block of memory
 *
 * Given a pointer to a source memory location and its size,
 * zeros out the block of memory.
 *
 * @param src Pointer to the source block
 * @param length The length of the memory block
 *
 * @return A pointer to the source memory block
 */
uint8_t * my_memzero(uint8_t * src, size_t length);

/**
 * @brief Reverses a block of memory
 *
 * Given a pointer to a source memory location and its size,
 * reverses the order of the bytes in the block
 *
 * @param src Pointer to the source block
 * @param length The length of the memory block
 *
 * @return A pointer to the source memory block
 */
uint8_t * my_reverse(uint8_t * src, size_t length);

/**
 * @brief Allocates a given number of words in dynamic memory
 *
 * Allocates and reserves a block of memory with a given length in dynamic memory.
 *
 * @param length The number of words to reserve
 *
 * @return A pointer to the reserved memory
 */
int32_t * reserve_words(size_t length);

/**
 * @brief Frees a dynamic memory allocation
 *
 * Frees a block in dynamic memory given its pointer
 *
 * @param src Pointer to the block in dynamic memory
 *
 * @return 0 if successful, 1 if unsuccessful
 */
uint8_t free_words(uint32_t * src);

#endif /* __MEMORY_H__ */
