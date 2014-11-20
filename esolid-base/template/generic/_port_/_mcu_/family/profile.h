/*
 * This file is part of eSolid.
 *
 * Copyright (C) 2010 - 2013 Nenad Radulovic
 *
 * eSolid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * eSolid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with eSolid.  If not, see <http://www.gnu.org/licenses/>.
 *
 * web site:    http://github.com/nradulovic
 * e-mail  :    nenad.b.radulovic@gmail.com
 *//***********************************************************************//**
 * @file
 * @author  	Nenad Radulovic
 * @brief   	Family port specific defines
 * @addtogroup  template_family
 * @brief       Family port specific defines
 *********************************************************************//** @{ */

#if !defined(PROFILE_H__)
#define PROFILE_H__

/*=========================================================  INCLUDE FILES  ==*/
/*===============================================================  DEFINES  ==*/
/*==============================================================  SETTINGS  ==*/

/*------------------------------------------------------------------------*//**
 * @name        Generic family defaults
 * @{ *//*--------------------------------------------------------------------*/

/**@brief       System timer maximum value
 * @details     This macro specifies maximum value that can be reloaded into
 *              system timer counter. For example, if the system timer is an
 *              8-bit counter than this macro would have the value of 0xffu (255).
 */
#define PORT_DEF_SYSTMR_MAX_VAL         0xfful

/**@} *//*----------------------------------------------------------------*//**
 * @name        Exception handlers used by the port
 * @{ *//*--------------------------------------------------------------------*/

/**@} *//*--------------------------------------------------------------------*/
/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//******************************************************
 * END of profile.h
 ******************************************************************************/
#endif /* PROFILE_H__ */
