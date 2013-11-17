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
 * @author      Nenad Radulovic
 * @brief       Implementation of Debug module
 * @addtogroup  dbg_impl
 *********************************************************************//** @{ */

/*=========================================================  INCLUDE FILES  ==*/

#include "arch/compiler.h"
#include "arch/cpu.h"
#include "dbg.h"

/*=========================================================  LOCAL MACRO's  ==*/
/*======================================================  LOCAL DATA TYPES  ==*/
/*=============================================  LOCAL FUNCTION PROTOTYPES  ==*/
/*=======================================================  LOCAL VARIABLES  ==*/
/*======================================================  GLOBAL VARIABLES  ==*/
/*============================================  LOCAL FUNCTION DEFINITIONS  ==*/
/*===================================  GLOBAL PRIVATE FUNCTION DEFINITIONS  ==*/
/*====================================  GLOBAL PUBLIC FUNCTION DEFINITIONS  ==*/

/* 1)       This function will disable all interrupts to prevent any new
 *          interrupts to execute which can trigger another assert causing a
 *          very confusing situation of why it failed.
 */
PORT_C_NORETURN void dbgAssert(
    const PORT_C_ROM struct dbgCobj_ * cObj,
    const PORT_C_ROM char * expr,
    enum esDbgMsg       msg) {

    struct esDbgReport  dbgReport;
    const char *        msgText;

    PORT_INT_DISABLE();

    switch (msg) {
        case ES_DBG_OUT_OF_RANGE : {
            msgText = "Value is out of valid range";
            break;
        }
        case ES_DBG_OBJECT_NOT_VALID : {
            msgText = "Object is not valid";
            break;
        }
        case ES_DBG_POINTER_NULL : {
            msgText = "Pointer has NULL value";
            break;
        }
        case ES_DBG_USAGE_FAILURE : {
            msgText = "Object usage failure";
            break;
        }
        case ES_DBG_NOT_ENOUGH_MEM : {
            msgText = "Not enough memory available";
            break;
        }
        default : {
            msgText = "Unknown error has occurred";
            break;
        }
    }
    dbgReport.modName   = cObj->mod->name;
    dbgReport.modDesc   = cObj->mod->desc;
    dbgReport.modAuthor = cObj->mod->auth;
    dbgReport.modFile   = cObj->mod->file;
    dbgReport.fnName    = cObj->fn;
    dbgReport.expr      = expr;
    dbgReport.msgText   = msgText;
    dbgReport.line      = cObj->line;
    dbgReport.msgNum    = msg;
    userAssert(
        &dbgReport);
    PORT_CPU_TERM();

    while (TRUE);
}

/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//******************************************************
 * END of dbg.c
 ******************************************************************************/
