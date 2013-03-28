#include "TCPIP Stack/TCPIP.h"
#include "config.h"
#include <stdlib.h>
#include <string.h>

static int cvrt_ip_in(char *from, char *to);
static int cvrt_mac_in(char *from, char *to);
static int cvrt_ip_out(char *from, char *to);
static int cvrt_mac_out(char *from, char *to);

/*================================ GENERAL CONFIG ==============================================*/

//static ROM const menu_prm_t prm00 = { TYPE_STRING, "string parameter 1",
//		(void *) str1, { { 256, 0 } } };
//static ROM const menu_prm_t prm01 = { TYPE_CHAR, "char parameter 1",
//		(void *) &char_prm1, { { 0, 10 } } };

static ROM const menu_section_t general_cfg_s = { "GENERAL CONFIG", {
		(ROM menu_prm_t *) 0 } };

/*================================ COMMUNICATIONS ==============================================*/
BYTE station_id = 1;
static ROM const menu_prm_t station_id_p = { TYPE_CHAR, "Station ID",
		(void *) &station_id, { { 255, 0 } } };

BYTE mac_addr[6] = { 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01 };
static ROM const menu_prm_t mac_addr_p = { TYPE_VECTOR, "MAC address",
		(void *) mac_addr, { { (ROM DWORD)cvrt_mac_in, (ROM DWORD)cvrt_mac_out,
				sizeof(mac_addr) } } };

BYTE ip_addr[4] = { 192, 168, 10, 100 };
static ROM const menu_prm_t ip_addr_p = { TYPE_VECTOR, "IP address",
		(void *) ip_addr, { { (ROM DWORD)cvrt_ip_in, (ROM DWORD)cvrt_ip_out,
				sizeof(ip_addr) } } };

WORD port = 50;
static ROM const menu_prm_t port_p = { TYPE_SHORT, "Port", (void *) &port, { {
		0, 65535 } } };

static ROM const menu_section_t communications_s =
		{ "COMMUNICATIONS", { &station_id_p, &mac_addr_p, &ip_addr_p, &port_p,
				(ROM menu_prm_t *) 0 } };

/*================================ RS-232 SETTINGS =============================================*/

DWORD baud_rate = 9600;
static ROM const menu_prm_t baud_rate_p = { TYPE_LONG, "Baud rate",
		(void *) &baud_rate, { { 9600, 115200 } } };

BYTE parity = 1;
static ROM const menu_prm_t parity_p = { TYPE_CHAR, "Parity", (void *) &parity,
		{ { 0, 1 } } };

BYTE data_bits = 8;
static ROM const menu_prm_t data_bits_p = { TYPE_CHAR, "Data bits",
		(void *) &data_bits, { { 5, 9 } } };

BYTE stop_bits = 2;
static ROM const menu_prm_t stop_bits_p = { TYPE_CHAR, "Stop bits",
		(void *) &stop_bits, { { 0, 2 } } };

BYTE handshake = 0;
static ROM const menu_prm_t handshake_p = { TYPE_CHAR, "Handshake",
		(void *) &handshake, { { 0, 1 } } };

static ROM const menu_section_t rs232_settings_s = { "RS-232 SETTINGS", {
		&baud_rate_p, &parity_p, &data_bits_p, &stop_bits_p, &handshake_p,
		(ROM menu_prm_t *) 0 } };

/*==================================== READER 1 ================================================*/

BYTE r1_activity = 1;
static ROM const menu_prm_t r1_activity_p = { TYPE_CHAR, "Activity",
		(void *) &r1_activity, { { 0, 1 } } };

BYTE r1_wiegand_framelen = 34;
static ROM const menu_prm_t r1_wiegand_framelen_p =
		{ TYPE_CHAR, "Wiegand frame length", (void *) &r1_wiegand_framelen, { {
				26, 128 } } };

BYTE r1_wg_parity[16] = "Classic e/o";
static ROM const menu_prm_t r1_wg_parity_p = { TYPE_STRING,
		"Wiegand parity control", (void *) r1_wg_parity, { { 16 /*, 0*/} } };

static ROM const menu_section_t reader1_settings_s = { "READER 1 SETTINGS", {
		&r1_activity_p, &r1_wiegand_framelen_p, &r1_wg_parity_p,
		(ROM menu_prm_t *) 0 } };

/*==================================== READER 2 ================================================*/

BYTE r2_activity = 1;
static ROM const menu_prm_t r2_activity_p = { TYPE_CHAR, "Activity",
		(void *) &r2_activity, { { 0, 1 } } };

BYTE r2_convert2hex = 1;
static ROM const menu_prm_t r2_convert2hex_p = { TYPE_CHAR, "Convert to hex",
		(void *) &r2_convert2hex, { { 0, 1 } } };

BYTE r2_framelen = 1;
static ROM const menu_prm_t r2_framelen_p = { TYPE_CHAR, "Frame length",
		(void *) &r2_framelen, { { 0, 255 } } };

BYTE r2_stop_byte = 0x0D;
static ROM const menu_prm_t r2_stop_byte_p = { TYPE_CHAR, "Stop byte",
		(void *) &r2_stop_byte, { { 0, 255 } } };

BYTE r2_code_begin = 0;
static ROM const menu_prm_t r2_code_begin_p = { TYPE_CHAR, "Code begin",
		(void *) &r2_code_begin, { { 0, 255 } } };

BYTE r2_code_len = 0;
static ROM const menu_prm_t r2_code_len_p = { TYPE_CHAR, "Code length",
		(void *) &r2_code_len, { { 0, 255 } } };

BYTE r2_max_delay = 10;
static ROM const menu_prm_t r2_max_delay_p = { TYPE_CHAR,
		"Max symbol delay x10ms", (void *) &r2_max_delay, { { 1, 100 } } };

static ROM const menu_section_t reader2_settings_s = { "READER 2 SETTINGS",
		{ &r2_activity_p, &r2_convert2hex_p, &r2_framelen_p, &r2_stop_byte_p,
				&r2_code_begin_p, &r2_code_len_p, &r2_max_delay_p,
				(ROM menu_prm_t *) 0 } };

/*=================================== ACCESSOR =================================================*/

BYTE host_tout = 10;
static ROM const menu_prm_t host_tout_p = { TYPE_CHAR, "Host timeout x10ms",
		(void *) &host_tout, { { 10, 100 } } };

BYTE retry_cnt = 2;
static ROM const menu_prm_t retry_cnt_p = { TYPE_CHAR, "Max retries",
		(void *) &retry_cnt, { { 1, 10 } } };

BYTE local_access = 3;
static ROM const menu_prm_t local_access_p = { TYPE_CHAR, "Local access mode",
		(void *) &local_access, { { 0, 3 } } };

BYTE local_msg[32] = "Проходите пожалуйста";
static ROM const menu_prm_t local_msg_p = { TYPE_STRING,
		"Local customer message", (void *) local_msg, { { 32 /*, 0*/} } };

BYTE busy_msg[32] = "Извините, временно не работаю";
static ROM const menu_prm_t busy_msg_p = { TYPE_STRING,
		"Busy customer message", (void *) busy_msg, { { 32 /*, 0*/} } };

BYTE failure_msg[32] = "Извините, временно не работаю";
static ROM const menu_prm_t failure_msg_p = { TYPE_STRING,
		"Failure customer message", (void *) failure_msg, { { 32 /*, 0*/} } };

BYTE prompt_msg[32] = "Предъявите карту";
static ROM const menu_prm_t prompt_msg_p = { TYPE_STRING, "Prompt message",
		(void *) prompt_msg, { { 32 /*, 0*/} } };

static ROM const menu_section_t accessor_settings_s = { "ACCESSOR SETTINGS", {
		&host_tout_p, &retry_cnt_p, &local_access_p, &local_msg_p, &busy_msg_p,
		&failure_msg_p, &prompt_msg_p, (ROM menu_prm_t *) 0 } };

/*================================ SERVICE MACHINE =============================================*/

DWORD service_time = 1000;
static ROM const menu_prm_t service_time_p = { TYPE_LONG, "Service time x10ms",
		(void *) &service_time, { { 500, 100000 } } };

BYTE sig_control_en = 1;
static ROM const menu_prm_t sig_control_en_p = { TYPE_CHAR,
		"Signal <CONTROL> enabled", (void *) &sig_control_en, { { 0, 1 } } };
BYTE sig_control_relay = 0;
static ROM const menu_prm_t sig_control_relay_p = { TYPE_CHAR,
		"Signal <CONTROL> relay number", (void *) &sig_control_relay, {
				{ 0, 1 } } };
BYTE sig_control_inverse = 0;
static ROM const menu_prm_t sig_control_inverse_p =
		{ TYPE_CHAR, "Signal <CONTROL> inverse", (void *) &sig_control_inverse,
				{ { 0, 1 } } };
WORD sig_control_duration = 10;
static ROM const menu_prm_t sig_control_duration_p = { TYPE_CHAR,
		"Signal <CONTROL> duration", (void *) &sig_control_duration, { { 0,
				1000 } } };

BYTE sig_indicator_en = 1;
static ROM const menu_prm_t sig_indicator_en_p =
		{ TYPE_CHAR, "Signal <INDICATOR> enabled", (void *) &sig_indicator_en,
				{ { 0, 1 } } };
BYTE sig_indicator_relay = 0;
static ROM const menu_prm_t sig_indicator_relay_p = { TYPE_CHAR,
		"Signal <INDICATOR> relay number", (void *) &sig_indicator_relay, { {
				0, 1 } } };
BYTE sig_indicator_inverse = 0;
static ROM const menu_prm_t sig_indicator_inverse_p = { TYPE_CHAR,
		"Signal <INDICATOR> inverse", (void *) &sig_indicator_inverse, {
				{ 0, 1 } } };
WORD sig_indicator_duration = 10;
static ROM const menu_prm_t sig_indicator_duration_p = { TYPE_CHAR,
		"Signal <INDICATOR> duration", (void *) &sig_indicator_duration, { { 0,
				1000 } } };

BYTE sig_done_en = 1;
static ROM const menu_prm_t sig_done_en_p = { TYPE_CHAR,
		"Signal <DONE> enabled", (void *) &sig_done_en, { { 0, 1 } } };
BYTE sig_done_sensor = 0;
static ROM const menu_prm_t sig_done_sensor_p =
		{ TYPE_CHAR, "Signal <DONE> sensor number", (void *) &sig_done_sensor,
				{ { 0, 1 } } };
BYTE sig_done_inverse = 0;
static ROM const menu_prm_t sig_done_inverse_p = { TYPE_CHAR,
		"Signal <DONE> inverse", (void *) &sig_done_inverse, { { 0, 1 } } };

BYTE sig_failure_en = 1;
static ROM const menu_prm_t sig_failure_en_p = { TYPE_CHAR,
		"Signal <FAILURE> enabled", (void *) &sig_failure_en, { { 0, 1 } } };
BYTE sig_failure_sensor = 0;
static ROM const menu_prm_t sig_failure_sensor_p = { TYPE_CHAR,
		"Signal <FAILURE> sensor number", (void *) &sig_failure_sensor, { { 0,
				1 } } };
BYTE sig_failure_inverse = 0;
static ROM const menu_prm_t sig_failure_inverse_p =
		{ TYPE_CHAR, "Signal <FAILURE> inverse", (void *) &sig_failure_inverse,
				{ { 0, 1 } } };

static ROM const menu_section_t serv_machine_settings_s = {
		"SERVICE MACHINE SETTINGS", { &service_time_p, &sig_control_en_p,
				&sig_control_relay_p, &sig_control_inverse_p,
				&sig_control_duration_p, &sig_indicator_en_p,
				&sig_indicator_relay_p, &sig_indicator_inverse_p,
				&sig_indicator_duration_p, &sig_done_en_p, &sig_done_sensor_p,
				&sig_done_inverse_p, &sig_failure_en_p, &sig_failure_sensor_p,
				&sig_failure_inverse_p,

				(ROM menu_prm_t *) 0 } };

/*==============================================================================================*/

static ROM const menu_section_t * ROM sections[] =
		{ &general_cfg_s, &communications_s, &rs232_settings_s,
				&reader1_settings_s, &reader2_settings_s, &accessor_settings_s,
				&serv_machine_settings_s, 0 };

#define n_elements(x) (sizeof(x)/sizeof(x[0]))

void config_show_sections(void)
{
	BYTE i;
	putrsUSART("\n\n\r");
	for (i = 0; sections[i]; i++) {
		BYTE a[6];
		uitoa((WORD) (i + 1), a);
		putsUSART(a);
		putrsUSART(". ");
		putrsUSART(sections[i]->caption);
		putrsUSART("\n\r");
	}

}

int config_show_section(ROM const menu_section_t * section)
{

	BYTE i;
	BYTE buf[40];

	if (section == NULL)
		return -1;

	for (i = 0; section->prms[i]; i++) {
		BYTE a[6];
		uitoa((WORD) (i + 1), a);
		putsUSART(a);
		putrsUSART(". ");
		putrsUSART(section->prms[i]->caption);
		putrsUSART(" [");
		switch (section->prms[i]->type) {
		case TYPE_CHAR:
			uitoa(*(BYTE *) section->prms[i]->prm, a);
			putsUSART(a);
			break;
		case TYPE_SHORT:
			uitoa(*(WORD *) section->prms[i]->prm, a);
			putsUSART(a);
			break;
		case TYPE_LONG:
			ultoa(*(DWORD *) section->prms[i]->prm, a);
			putsUSART(a);
			break;
		case TYPE_STRING:
			putsUSART((BYTE *) section->prms[i]->prm);
			break;
		case TYPE_VECTOR:
			(*(convert_prm_cb)(section->prms[i]->lim.v.cvrt_out))((BYTE *) section->prms[i]->prm, buf);
			putsUSART(buf);
		}

		putrsUSART("]\n\r");
	}

	return 0;
}

int config_show_param(menu_prm_t * prm)
{

	if (prm == NULL)
		return -1;

	putrsUSART("\n\r< ");
	putrsUSART(prm->caption);
	putrsUSART(" >\n\r");

	switch (prm->type) {
	case TYPE_CHAR:
	case TYPE_SHORT:
	case TYPE_LONG:
	case TYPE_STRING:
	case TYPE_VECTOR:
		break;
	}

	return 0;
}

#define isdigit(ch) ((ch) >= '0' && (ch) <= '9')
#define isdot(ch)   ((ch) == '.')

static int cvrt_ip_out(char *from, char *to)
{
	BYTE i;
	BYTE sbyte[4];
	BYTE dot[] = ".";

	*to = '\0';
	itoa((int)from[0], sbyte);
	strcat(to, sbyte);
	strcat(to, dot);
	itoa((int)from[1], sbyte);
	strcat(to, sbyte);
	strcat(to, dot);
	itoa((int)from[2], sbyte);
	strcat(to, sbyte);
	strcat(to, dot);
	itoa((int)from[3], sbyte);
	strcat(to, sbyte);
	return 1;
}

static int cvrt_mac_out(char *from, char *to)
{
	BYTE i;
	for (i = 0; i < 6; i++, to += 3, from++) {
		*to = btohexa_high(*from);
		*(to + 1) = btohexa_low(*from);
		*(to + 2) = '-';
	}
	*(to - 1) = '\0';
	return 1;
}
static int cvrt_ip_in(char *from, char *to)
{
	char *_to = to + 3;
	char sbyte[4], dg_cnt = 0;
	char *pbyte = sbyte;
	int i;

	while (*from) {
		if (isdigit(*from)) {
			if (++dg_cnt > 3)
				return 0;
			*pbyte++ = *from++;
		} else if (isdot(*from)) {
			*pbyte = '\0';
			if ((i = atoi(sbyte)) > 255)
				return 0;
			*_to-- = (char) i;
			if (_to < to)
				return 0;
			from++;
			pbyte = sbyte;
			dg_cnt = 0;
		} else {
			return 0;
		}
	}

	*pbyte = '\0';
	if ((i = atoi(sbyte)) > 255)
		return 0;

	*to = (char) i;

	if (_to != to)
		return 0;
	else
		return 1;
}

#define ishex(ch) 			(((ch) >= '0' && (ch) <= '9') || ((ch) >= 'a' && (ch) <= 'f') || ((ch) >= 'A' && (ch) <= 'F'))
#define isseparator(ch)		(((ch) == '-') || ((ch) == ':') || ((ch) == '\n'))

static int cvrt_mac_in(char *from, char *to)
{
	char sbyte[3];
	char *pbyte = sbyte;
	char *_from;
	int i;

	if (strlen(from) != 17)
		return 0;

	for (_from = from; _from < from + 3 * 6; _from += 3) {
		if (ishex(_from[0]) && ishex(_from[1]) && isseparator(_from[2]))
			*to = hexatob(*(WORD_VAL *) _from);
		else
			return 0;
	}
	return 1;
}

void config(void)
{
	BYTE buffer[40];
	BYTE ch;

//	while (1) { // XXX add switch/case
//		config_show_sections();
//		ReadStringUART(buffer, sizeof(buffer), TRUE);
//		ch = atob(buffer);
//		if (!ch || ch > n_elements(sections))
//			continue;
//		config_show_section(sections[ch - 1]);
//		ReadStringUART(buffer, sizeof(buffer), TRUE);
//		ch = atob(buffer);
//
//	}

		config_show_section(sections[0]);
		config_show_section(sections[1]);
		config_show_section(sections[2]);
		config_show_section(sections[3]);
		config_show_section(sections[4]);
		config_show_section(sections[5]);
		config_show_section(sections[6]);
	//	config_show_section(1);
	//	config_show_section(2);
}

//void menu_show(void)
//{
//	int i;
//
//	for (i = 0; sections[i]; i++) {
//		printf("%d. %s\n", i, sections[i]->caption);
//
//		int j;
//		for (j = 0; sections[i]->prms[j]; j++) {
//
//			printf("\t%d.%d. %s", i, j, sections[i]->prms[j]->caption);
//
//			switch (sections[i]->prms[j]->type) {
//			case TYPE_CHAR:
//			case TYPE_SHORT:
//			case TYPE_LONG:
//				printf(" (val=%d, min=%d, max=%d)\n",
//						*(int *) (sections[i]->prms[j]->prm),
//						(int) (sections[i]->prms[j]->d.min),
//						(int) (sections[i]->prms[j]->d.max));
//				break;
//
//			case TYPE_STRING:
//				printf(" (val=\"%s\", maxlen=%d)\n",
//						(char *) (sections[i]->prms[j]->prm),
//						(int) (sections[i]->prms[j]->s.maxlen));
//
//				break;
//
//			default:
//				break;
//			}
//		}
//
//	}
//}
