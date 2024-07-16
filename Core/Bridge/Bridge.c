/**
* @author Jakub Bubak
* @date 15.03.2024
*/

#include "Bridge.h"

/**
 * @brief Weak definition of Init function, enables override if necessary
 * */
__attribute__((weak)) void Init() {}

/**
 * @brief Weak definition of Loop function, enables override if necessary
 * */
__attribute__((weak)) void Loop() {}

/**
 * @brief Weak definition of ErrorHandler function, enables override if necessary
 * */
__attribute__((weak)) void ErrorHandler() {}

/**
 * @brief Weak definition of SysTickCallback function, enables override if necessary
 * */
__attribute__((weak)) void SysTickCallback() {}