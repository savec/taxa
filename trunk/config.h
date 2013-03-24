/*
 * config.h
 *
 *  Created on: 24.03.2013
 *      Author: admin
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define MAX_PRMS	7

typedef enum {
	TYPE_STRING, TYPE_CHAR, TYPE_SHORT, TYPE_LONG
} type_e;

typedef struct {
	ROM const type_e type;
	ROM const BYTE *caption;
	void *prm;
	union {
		struct {
			ROM DWORD min;
			ROM DWORD max;
		} d;
		struct {
			ROM DWORD maxlen;
			ROM DWORD dummy;
		} s;
	} lim;
} menu_prm_t;

typedef struct {
	ROM const BYTE *caption;
	ROM const menu_prm_t * ROM const prms[MAX_PRMS];
} menu_section_t;

//void menu_show(void);

#endif /* CONFIG_H_ */
