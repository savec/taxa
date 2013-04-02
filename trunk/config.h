/*
 * config.h
 *
 *  Created on: 24.03.2013
 *      Author: admin
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define MAX_PRMS	20

typedef enum {
	TYPE_STRING, TYPE_CHAR, TYPE_SHORT, TYPE_LONG, TYPE_VECTOR, TYPE_ACTION
} type_e;

typedef enum {
	SHOW_SECTIONS,
	SHOW_SECTION,
	SHOW_PARAM
} menu_state_e;

typedef int (* ROM convert_prm_cb)(char *, char *);

typedef struct {
	ROM const type_e type;
	ROM const BYTE *caption;
	void *prm;
	union {
		ROM DWORD ROM raw[3];
		struct {
			ROM DWORD min;
			ROM DWORD max;
		} d;
		struct {
			ROM DWORD maxlen;
		} s;
		struct {
			ROM DWORD cvrt_in;
			ROM DWORD cvrt_out;
			ROM DWORD len;
		} v;
	} lim;
} menu_prm_t;

typedef struct {
	ROM const BYTE *caption;
	ROM const menu_prm_t * ROM prms[MAX_PRMS];
} menu_section_t;

void config(void);

#endif /* CONFIG_H_ */
