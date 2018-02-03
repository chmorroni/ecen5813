/**
 * @file arch_arm32.h
 * @brief 
 *
 * @author Christopher Morroni
 * @date 01/30/2018
 */
#ifndef __ARCH_ARM32_H__
#define __ARCH_ARM32_H__

/**
 * @brief Get the endianness configuration of an ARM processor
 *
 * Checks the AIRCR register to determine endianness.
 *
 * @return The endianness of the ARM processer
 */
__attribute__((always_inline)) uint32_t ARM32_AIRCR_get_endianness_setting();

#endif /* __ARCH_ARM32_H__ */
