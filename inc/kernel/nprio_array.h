/*
 * This file is part of nKernel.
 *
 * Copyright (C) 2010 - 2013 Nenad Radulovic
 *
 * nKernel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * nKernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with nKernel.  If not, see <http://www.gnu.org/licenses/>.
 *
 * web site:    http://github.com/nradulovic
 * e-mail  :    nenad.b.radulovic@gmail.com
 *//***************************************************************************************************************//**
 * @file
 * @author  	Nenad Radulovic
 * @brief       Priority array header
 * @defgroup    priority_array Priority array
 * @brief       Priority array
 *************************************************************************************************************//** @{ */
/**@defgroup    priority_array_intf Interface
 * @brief       Public interface
 * @{ *//*------------------------------------------------------------------------------------------------------------*/

#ifndef NPRIO_ARRAY_H_
#define NPRIO_ARRAY_H_

/*=================================================================================================  INCLUDE FILES  ==*/

#include <stdint.h>

#include "plat/compiler.h"
#include "arch/cpu.h"

#include "kernel/nkernel_config.h"
#include "kernel/nbitop.h"

/*=======================================================================================================  MACRO's  ==*/
/*----------------------------------------------------------------------------------------------  C++ extern begin  --*/
#ifdef __cplusplus
extern "C" {
#endif

/*====================================================================================================  DATA TYPES  ==*/

/**@brief       Priority Bit Map structure
 * @notapi
 */
struct nprio_bitmap
{
#if   (CONFIG_PRIORITY_BUCKETS > NCPU_DATA_WIDTH) || defined(__DOXYGEN__)
    natomic                     bitGroup;                                       /**<@brief Bit list indicator         */
#endif
    /**@brief       Bit priority indicator
     */
    natomic                     bit[NDIVISION_ROUNDUP(CONFIG_PRIORITY_BUCKETS, NCPU_DATA_WIDTH)];
};

/**@brief       Thread doubly linked list
 * @api
 */
struct nthread_list
{
    struct nthread *            next;
    struct nthread *            prev;
};

/**@brief       Priority array entry
 * @notapi
 */
struct nprio_array_entry
{
    struct nthread_list         list;
};

/**@brief       Priority array structure
 * @details     An priority array consists of an array of sub-queues. There is one sub-queue per priority level. Each
 *              sub-queue contains the runnable threads at the corresponding priority level. There is also a bitmap
 *              corresponding to the array that is used to determine effectively the highest-priority task on the queue.
 * @api
 */
struct nprio_array
{
#if (CONFIG_PRIORITY_BUCKETS != 1)
    struct nprio_bitmap         bitmap;                                         /**<@brief Priority bitmap            */
#endif
    struct nthread *            sentinel[CONFIG_PRIORITY_BUCKETS];
};

/**@brief       Priority queue type
 * @api
 */
typedef struct nprio_array nprio_array;

/*==============================================================================================  GLOBAL VARIABLES  ==*/
/*===========================================================================================  FUNCTION PROTOTYPES  ==*/

void nprio_array_init(
    struct nprio_array *        array);

void nprio_array_insert(
    struct nprio_array *        array,
    struct nthread *            thread);

void nprio_array_remove(
    struct nprio_array *        array,
    struct nthread *            thread);

struct nthread * nprio_array_peek(
    const struct nprio_array * array);

struct nthread * nprio_array_rotate_thread(
    struct nprio_array *        array,
    struct nthread *            thread);

void nprio_array_init_entry(
    struct nthread *            thread);

/*------------------------------------------------------------------------------------------------  C++ extern end  --*/
#ifdef __cplusplus
}
#endif

/*========================================================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//** @} *//*************************************************************************************
 * END of nprio_array.h
 **********************************************************************************************************************/
#endif /* NPRIO_ARRAY_H_ */
