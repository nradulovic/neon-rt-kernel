/*
 * This file is part of eSolid - RT Kernel
 *
 * Copyright (C) 2011, 2012, 2013 - Nenad Radulovic
 *
 * eSolid - RT Kernel is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option) any
 * later version.
 *
 * eSolid - RT Kernel is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * eSolid - RT Kernel; if not, write to the Free Software Foundation, Inc., 51
 * Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * web site:    http://github.com/nradulovic
 * e-mail  :    nenad.b.radulovic@gmail.com
 *//***********************************************************************//**
 * @file
 * @author  	Nenad Radulovic
 * @brief   	Configuration of CPU port - Template.
 * @addtogroup  template_cpu_cfg
 * @details     Each configuration option or setting has its own default value
 *              when not defined by the application. When application needs to
 *              change a setting it just needs to define a configuration macro
 *              with another value and the default configuration macro will be
 *              overridden.
 *********************************************************************//** @{ */

#ifndef CPU_CFG_H_
#define CPU_CFG_H_

/*=========================================================  INCLUDE FILES  ==*/
/*===============================================================  DEFINES  ==*/
/** @cond */

/** @endcond */
/*==============================================================  SETTINGS  ==*/

/*------------------------------------------------------------------------*//**
 * @name        Port General configuration
 * @brief       Configuration options and settings which are available for every
 *              port.
 * @note        1) All port General configuration macros are prefixed with
 *              @c CFG_ string.
 * @note        2) All port specific options and constants are prefixed with
 *              @c CPU_ string.
 * @{ *//*--------------------------------------------------------------------*/

/**@brief       Priority of critical sections in kernel
 * @details     This option varies with the MCU used. In the simplest case when
 *              the MCU does not support interrupt priorities than only one
 *              priority level is available. In that case critical section will
 *              simply disable interrupts on entry and enable them at exit.
 */
#if !defined(PORT_CFG_MAX_ISR_PRIO)
# define PORT_CFG_MAX_ISR_PRIO          1u
#endif

/**@brief       The frequency of clock which is used for the system timer
 * @details     Specify here the clock value so the kernel can properly manage
 *              system tick event generation. Usually system timer will use the
 *              clock of the processor. A hardware timer is configured to
 *              generate an interrupt at a rate between 10 and 1000 Hz which
 *              provides the system tick. The rate of interrupt is application
 *              specific and depends on the desired resolution system tick time
 *              source. However, the faster the tick rate, the higher the
 *              overhead will be imposed on the system.
 */
#if !defined(PORT_CFG_SYSTMR_CLOCK_FREQ)
# define PORT_CFG_SYSTMR_CLOCK_FREQ     1000000ul
#endif

/** @} *//*-------------------------------------------------------------------*/
/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//******************************************************
 * END of cpu_cfg.h
 ******************************************************************************/
#endif /* CPU_CFG_H_ */