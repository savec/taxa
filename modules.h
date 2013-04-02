/*
 * modules.h
 *
 *  Created on: 03.04.2013
 *      Author: admin
 */

#ifndef MODULES_H_
#define MODULES_H_
typedef enum {
	MODULE_BCP = 0,
	MODULE_READERS,
	MODULE_ACCESSOR,
	MODULE_SRVMACHINE,
	MODULE_LOGGER,
	MODULE_LCD,
	MODULES_NUM,
	MODULE_UNKNOWN = MODULES_NUM
} modules_e;
#endif /* MODULES_H_ */
