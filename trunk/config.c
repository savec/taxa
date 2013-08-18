#include "TCPIP Stack/TCPIP.h"
#include "config.h"
#include <stdlib.h>
#include <string.h>
#include "m_lcd.h"
#include "version.h"
#include "m_logger.h"
#include "net.h"
//#include "helpers.h"

static int cvrt_ip_in(char *from, char *to);
static int cvrt_mac_in(char *from, char *to);

static BYTE string_buf[60];

/*================================ GENERAL CONFIG ==============================================*/

//static ROM const menu_prm_t prm00 = { TYPE_STRING, "string parameter 1",
//		(void *) str1, { { 256, 0 } } };
//static ROM const menu_prm_t prm01 = { TYPE_CHAR, "char parameter 1",
//		(void *) &char_prm1, { { 0, 10 } } };

//static ROM const menu_section_t general_cfg_s = { "GENERAL CONFIG", {
//		(ROM menu_prm_t *) 0 } };

/*================================ COMMUNICATIONS ==============================================*/
//BYTE station_id = 1;
static ROM const menu_prm_t station_id_p = { TYPE_CHAR, "Station ID",
		(void *) &AppConfig.comm_station_id, { { 0, 255 } } };

//BYTE mac_addr[6] = { 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01 };
static ROM const menu_prm_t mac_addr_p = { TYPE_VECTOR, "MAC address",
		(void *) AppConfig.MyMACAddr.v, { { (ROM DWORD) cvrt_mac_in,
				(ROM DWORD) cvrt_mac_out, sizeof(AppConfig.MyMACAddr.v) } } };

//IP_ADDR ip_addr = (192l << 24) | (168l << 16) | (10l << 8) | 100;
static ROM const menu_prm_t ip_addr_p = { TYPE_VECTOR, "IP address",
		(void *) &AppConfig.MyIPAddr, { { (ROM DWORD) cvrt_ip_in, (ROM DWORD) cvrt_ip_out,
				sizeof(AppConfig.MyIPAddr) } } };

//WORD port = 50;
static ROM const menu_prm_t port_p = { TYPE_SHORT, "Port", (void *) &AppConfig.comm_port, { {
		0, 65535 } } };

static ROM const menu_section_t communications_s =
		{ "COMMUNICATIONS", { &station_id_p, &mac_addr_p, &ip_addr_p, &port_p,
				(ROM menu_prm_t *) 0 } };

/*================================ RS-232 SETTINGS =============================================*/

//DWORD baud_rate = 9600;
static ROM const menu_prm_t baud_rate_p = { TYPE_LONG, "Baud rate",
		(void *) &AppConfig.rs232_baudrate, { { 9600, 115200 } } };

//BYTE parity = 1;
static ROM const menu_prm_t parity_p = { TYPE_CHAR, "Parity", (void *) &AppConfig.rs232_parity,
		{ { 0, 1 } } };

//BYTE data_bits = 8;
static ROM const menu_prm_t data_bits_p = { TYPE_CHAR, "Data bits",
		(void *) &AppConfig.rs232_databits, { { 5, 9 } } };

//BYTE stop_bits = 2;
static ROM const menu_prm_t stop_bits_p = { TYPE_CHAR, "Stop bits",
		(void *) &AppConfig.rs232_stopbits, { { 0, 2 } } };

//BYTE handshake = 0;
static ROM const menu_prm_t handshake_p = { TYPE_CHAR, "Handshake",
		(void *) &AppConfig.rs232_handshake, { { 0, 1 } } };

static ROM const menu_section_t rs232_settings_s = { "RS-232 SETTINGS", {
		&baud_rate_p, &parity_p, &data_bits_p, &stop_bits_p, &handshake_p,
		(ROM menu_prm_t *) 0 } };

/*==================================== READER 1 ================================================*/

//BYTE r1_activity = 1;
static ROM const menu_prm_t r1_activity_p = { TYPE_CHAR, "Activity",
		(void *) &AppConfig.r1_activity, { { 0, 1 } } };

//BYTE r1_wiegand_framelen = 34;
static ROM const menu_prm_t r1_wiegand_framelen_p =
		{ TYPE_CHAR, "Wiegand frame length", (void *) &AppConfig.r1_framelen, { {
				26, 128 } } };

//BYTE r1_wg_parity[16] = "Classic e/o";
static ROM const menu_prm_t r1_wg_parity_p = { TYPE_STRING,
		"Wiegand parity control", (void *) AppConfig.r1_parity, { { 16 /*, 0*/} } };

static ROM const menu_section_t reader1_settings_s = { "READER 1 SETTINGS", {
		&r1_activity_p, &r1_wiegand_framelen_p, &r1_wg_parity_p,
		(ROM menu_prm_t *) 0 } };

/*==================================== READER 2 ================================================*/

//BYTE r2_activity = 1;
static ROM const menu_prm_t r2_activity_p = { TYPE_CHAR, "Activity",
		(void *) &AppConfig.r2_activity, { { 0, 1 } } };

//BYTE r2_convert2hex = 1;
static ROM const menu_prm_t r2_convert2hex_p = { TYPE_CHAR, "Convert to hex",
		(void *) &AppConfig.r2_convert2hex, { { 0, 1 } } };

//BYTE r2_framelen = 1;
static ROM const menu_prm_t r2_framelen_p = { TYPE_CHAR, "Frame length",
		(void *) &AppConfig.r2_framelen, { { 0, 255 } } };

//BYTE r2_stop_byte = 0x0D;
static ROM const menu_prm_t r2_stop_byte_p = { TYPE_CHAR, "Stop byte",
		(void *) &AppConfig.r2_stop_byte, { { 0, 255 } } };

//BYTE r2_code_begin = 0;
static ROM const menu_prm_t r2_code_begin_p = { TYPE_CHAR, "Code begin",
		(void *) &AppConfig.r2_code_begin, { { 0, 255 } } };

//BYTE r2_code_len = 0;
static ROM const menu_prm_t r2_code_len_p = { TYPE_CHAR, "Code length",
		(void *) &AppConfig.r2_code_len, { { 0, 255 } } };

//BYTE r2_max_delay = 10;
static ROM const menu_prm_t r2_max_delay_p = { TYPE_CHAR,
		"Max symbol delay x10ms", (void *) &AppConfig.r2_max_delay, { { 1, 100 } } };

static ROM const menu_section_t reader2_settings_s = { "READER 2 SETTINGS",
		{ &r2_activity_p, &r2_convert2hex_p, &r2_framelen_p, &r2_stop_byte_p,
				&r2_code_begin_p, &r2_code_len_p, &r2_max_delay_p,
				(ROM menu_prm_t *) 0 } };

/*=================================== ACCESSOR =================================================*/

//BYTE host_tout = 10;
static ROM const menu_prm_t host_tout_p = { TYPE_CHAR, "Host timeout x10ms",
		(void *) &AppConfig.acc_host_tout, { { 10, 100 } } };

//BYTE retry_cnt = 2;
static ROM const menu_prm_t retry_cnt_p = { TYPE_CHAR, "Max retries",
		(void *) &AppConfig.acc_retry_cnt, { { 1, 10 } } };

//BYTE local_access = 3;
static ROM const menu_prm_t local_access_p = { TYPE_CHAR, "Local access mode",
		(void *) &AppConfig.acc_local_access, { { 0, 3 } } };

//BYTE local_msg[32] = "Проходите пожалуйста";
static ROM const menu_prm_t local_msg_p = { TYPE_STRING,
		"Local customer message", (void *) AppConfig.acc_local_msg, { { 32 /*, 0*/} } };

//BYTE busy_msg[32] = "Извините, временно не работаю";
static ROM const menu_prm_t busy_msg_p = { TYPE_STRING,
		"Busy customer message", (void *) AppConfig.acc_busy_msg, { { 32 /*, 0*/} } };

//BYTE failure_msg[32] = "Извините, временно не работаю";
static ROM const menu_prm_t failure_msg_p = { TYPE_STRING,
		"Failure customer message", (void *) AppConfig.acc_failure_msg, { { 32 /*, 0*/} } };

//BYTE prompt_msg[32] = "Предъявите карту";
static ROM const menu_prm_t prompt_msg_p = { TYPE_STRING, "Prompt message",
		(void *) AppConfig.acc_prompt_msg, { { 32 /*, 0*/} } };

static ROM const menu_section_t accessor_settings_s = { "ACCESSOR SETTINGS", {
		&host_tout_p, &retry_cnt_p, &local_access_p, &local_msg_p, &busy_msg_p,
		&failure_msg_p, &prompt_msg_p, (ROM menu_prm_t *) 0 } };

/*================================ SERVICE MACHINE =============================================*/

//DWORD service_time = 1000;
static ROM const menu_prm_t service_time_p = { TYPE_LONG, "Service time x10ms",
		(void *) &AppConfig.sm_service_time, { { 500, 100000 } } };

//BYTE sig_control_en = 1;
static ROM const menu_prm_t sig_control_en_p = { TYPE_CHAR,
		"Signal <CONTROL> enabled", (void *) &AppConfig.sm_sig_control_en, { { 0, 1 } } };
//BYTE sig_control_relay = 0;
static ROM const menu_prm_t sig_control_relay_p = { TYPE_CHAR,
		"Signal <CONTROL> relay number", (void *) &AppConfig.sm_sig_control_relay, {
				{ 0, 1 } } };
//BYTE sig_control_inverse = 0;
static ROM const menu_prm_t sig_control_inverse_p =
		{ TYPE_CHAR, "Signal <CONTROL> inverse", (void *) &AppConfig.sm_sig_control_inverse,
				{ { 0, 1 } } };
//WORD sig_control_duration = 10;
static ROM const menu_prm_t sig_control_duration_p = { TYPE_SHORT,
		"Signal <CONTROL> duration x10ms", (void *) &AppConfig.sm_sig_control_duration, { { 0,
				1000 } } };

//BYTE sig_indicator_en = 1;
static ROM const menu_prm_t sig_indicator_en_p =
		{ TYPE_CHAR, "Signal <INDICATOR> enabled", (void *) &AppConfig.sm_sig_indicator_en,
				{ { 0, 1 } } };
//BYTE sig_indicator_relay = 0;
static ROM const menu_prm_t sig_indicator_relay_p = { TYPE_CHAR,
		"Signal <INDICATOR> relay number", (void *) &AppConfig.sm_sig_indicator_relay, { {
				0, 1 } } };
//BYTE sig_indicator_inverse = 0;
static ROM const menu_prm_t sig_indicator_inverse_p = { TYPE_CHAR,
		"Signal <INDICATOR> inverse", (void *) &AppConfig.sm_sig_indicator_inverse, {
				{ 0, 1 } } };
//WORD sig_indicator_duration = 10;
static ROM const menu_prm_t sig_indicator_duration_p = { TYPE_SHORT,
		"Signal <INDICATOR> duration x10ms", (void *) &AppConfig.sm_sig_indicator_duration, { { 0,
				1000 } } };

//BYTE sig_done_en = 1;
static ROM const menu_prm_t sig_done_en_p = { TYPE_CHAR,
		"Signal <DONE> enabled", (void *) &AppConfig.sm_sig_done_en, { { 0, 1 } } };
//BYTE sig_done_sensor = 0;
static ROM const menu_prm_t sig_done_sensor_p =
		{ TYPE_CHAR, "Signal <DONE> sensor number", (void *) &AppConfig.sm_sig_done_sensor,
				{ { 0, 1 } } };
//BYTE sig_done_inverse = 0;
static ROM const menu_prm_t sig_done_inverse_p = { TYPE_CHAR,
		"Signal <DONE> inverse", (void *) &AppConfig.sm_sig_done_inverse, { { 0, 1 } } };

//BYTE sig_failure_en = 1;
static ROM const menu_prm_t sig_failure_en_p = { TYPE_CHAR,
		"Signal <FAILURE> enabled", (void *) &AppConfig.sm_sig_failure_en, { { 0, 1 } } };
//BYTE sig_failure_sensor = 0;
static ROM const menu_prm_t sig_failure_sensor_p = { TYPE_CHAR,
		"Signal <FAILURE> sensor number", (void *) &AppConfig.sm_sig_failure_sensor, { { 0,
				1 } } };
//BYTE sig_failure_inverse = 0;
static ROM const menu_prm_t sig_failure_inverse_p =
		{ TYPE_CHAR, "Signal <FAILURE> inverse", (void *) &AppConfig.sm_sig_failure_inverse,
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

///*================================ ACTION: slog_flush ==========================================*/
//
//static ROM const menu_prm_t data_bits_p = { TYPE_CHAR, "Data bits",
//		(void *) &data_bits, { { 5, 9 } } };
//
///*================================ ACTION: exit ================================================*/
//
//BYTE stop_bits = 2;
//static ROM const menu_prm_t stop_bits_p = { TYPE_CHAR, "Stop bits",
//		(void *) &stop_bits, { { 0, 2 } } };
//
///*================================ ACTION: save & exit =========================================*/
//
//BYTE handshake = 0;
//static ROM const menu_prm_t handshake_p = { TYPE_CHAR, "Handshake",
//		(void *) &handshake, { { 0, 1 } } };


/*==============================================================================================*/

static ROM const menu_section_t * ROM sections[] =
		{ /*&general_cfg_s,*/&communications_s, &rs232_settings_s,
				&reader1_settings_s, &reader2_settings_s, &accessor_settings_s,
				&serv_machine_settings_s, 0 };

#define n_elements(x) (sizeof(x)/sizeof(x[0]))

void config_show_sections(void)
{
	BYTE i;
//	BYTE a[6];
	static BYTE buf[40];

	put_string("\n\r");
	for (i = 0; sections[i]; i++) {
		strcpypgm2ram(buf, sections[i]->caption);
		put_string("%d. %s\n\r", i + 1,  buf);
//		uitoa((WORD) (i + 1), a);
//		put_string(a);
//		put_rom_string(". ");
//		put_rom_string(sections[i]->caption);
//		put_rom_string("\n\r");
	}
	put_string("\n\r");
}

int config_show_section(ROM const menu_section_t * section)
{

	BYTE i;
	static BYTE buf[40];
	BYTE a[33];

	if (section == NULL)
		return -1;

	put_string("\r\n");

	for (i = 0; section->prms[i]; i++) {

//		uitoa((WORD) (i + 1), a);
//		put_string(a);
//		put_rom_string(". ");
//		put_rom_string(section->prms[i]->caption);
//		put_rom_string(" [");
		switch (section->prms[i]->type) {
		case TYPE_CHAR:
			uitoa(*(BYTE *) section->prms[i]->prm, a);
//			put_string(a);
			break;
		case TYPE_SHORT:
			uitoa(*(WORD *) section->prms[i]->prm, a);
//			put_string(a);
			break;
		case TYPE_LONG:
			ultoa(*(DWORD *) section->prms[i]->prm, a);
//			put_string(a);
			break;
		case TYPE_STRING:
//			put_string((BYTE *) section->prms[i]->prm);
			strcpy(a, (BYTE *) section->prms[i]->prm);
			break;
		case TYPE_VECTOR:
			(*(convert_prm_cb) (section->prms[i]->lim.v.cvrt_out))(
					(BYTE *) section->prms[i]->prm, a);
//			put_string(buf);
		}

		strcpypgm2ram(buf, section->prms[i]->caption);
		put_string("%d. %s [%s]\n\r", i + 1, buf, a);
	}

	return 0;
}

int config_show_param(ROM const menu_prm_t * prm)
{
	static BYTE buf[40];

	if (prm == NULL)
		return -1;

	strcpypgm2ram(buf, prm->caption);
	put_string("\r\n< %s >\n\r", buf);

	switch (prm->type) {
	case TYPE_CHAR:
		ultoa(prm->lim.d.min, buf);
		put_string("Min = %s", buf);
		ultoa(prm->lim.d.max, buf);
		put_string("; Max = %s", buf);
		put_string("; Val = %d\n\r", *(BYTE *) prm->prm);
		break;

	case TYPE_SHORT:

		ultoa(prm->lim.d.min, buf);
		put_string("Min = %s", buf);
		ultoa(prm->lim.d.max, buf);
		put_string("; Max = %s", buf);
		put_string("; Val = %d\n\r", *(WORD *) prm->prm);

		break;

	case TYPE_LONG:

		ultoa(prm->lim.d.min, buf);
		put_string("Min = %s", buf);
		ultoa(prm->lim.d.max, buf);
		put_string("; Max = %s", buf);
		ultoa(*(DWORD *) prm->prm, buf);
		put_string("; Val = %s\n\r", buf);

		break;

	case TYPE_STRING:

		put_string("Val = %s\n\r", (BYTE *) prm->prm);
		break;

	case TYPE_VECTOR:
		(*(convert_prm_cb) (prm->lim.v.cvrt_out))((BYTE *) prm->prm, buf);
		put_string("Val = %s\n\r", buf);
		break;
	}

	return 0;
}

#define isdigit(ch) ((ch) >= '0' && (ch) <= '9')
#define isdot(ch)   ((ch) == '.')

int cvrt_ip_out(char *from, char *to)
{
	BYTE i;
	BYTE sbyte[4];
	BYTE dot[] = ".";

	*to = '\0';
	itoa((int) from[0], sbyte);
	strcat(to, sbyte);
	strcat(to, dot);
	itoa((int) from[1], sbyte);
	strcat(to, sbyte);
	strcat(to, dot);
	itoa((int) from[2], sbyte);
	strcat(to, sbyte);
	strcat(to, dot);
	itoa((int) from[3], sbyte);
	strcat(to, sbyte);
	return 1;
}

int cvrt_mac_out(char *from, char *to)
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
	char tmp[4], *p_tmp = tmp;
	char *_to = p_tmp + 3;
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
			if (_to < p_tmp)
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

	*p_tmp = (char) i;

	if (_to != p_tmp)
		return 0;

	*(DWORD *)tmp = swapl(*(DWORD *)tmp);
	memcpy(to, tmp, sizeof(tmp));

	return 1;
}

#define ishex(ch) 			(((ch) >= '0' && (ch) <= '9') || ((ch) >= 'a' && (ch) <= 'f') || ((ch) >= 'A' && (ch) <= 'F'))
#define isseparator(ch)		(((ch) == '-') || ((ch) == ':') || ((ch) == '\n') || ((ch) == ' ') || ((ch) == '\0'))

static int cvrt_mac_in(char *from, char *to)
{
	char tmp[6], *p_tmp = tmp, swp_byte;
	char sbyte[3];
	char *pbyte = sbyte;
	char *_from;
	int i;

	if (strlen(from) != 17)
		return 0;

	for (_from = from; _from < from + 3 * 6; _from += 3, p_tmp ++) {
		if (ishex(_from[0]) && ishex(_from[1]) && isseparator(_from[2])) {
			swp_byte = hexatob(*(WORD_VAL *) _from);
			*p_tmp = (swp_byte << 4) | (swp_byte >> 4);
		} else
			return 0;
	}

	memcpy(to, tmp, sizeof(tmp));
	return 1;
}

//static int escape_there(BYTE *s)
//{
//	while (*s)
//		if (*s++ == '\x1b')
//			return 1;
//
//	return 0;
//}



static void config_save_reboot(void) {

	config_save();
	Reset();
}


static void console_caption(void) {
	put_string("\r\nSkiPIC Configuration menu. System built " SVN_DATETIME " (revision " SVN_REVISION ")\n\r");
	put_string("type:\t\'s\' to save;\r\n");
	put_string("\t\'e\' to exit without saving;\r\n");
	put_string("\t\'l\' to show syslog;\r\n");
	put_string("\t\'f\' to format syslog;\r\n");
	put_string("\t\'c\' to clean syslog;\r\n");
	put_string("\t\'r\' to restore defaults;\r\n");
	put_string("\t\'t\' to print last event;\r\n");
	put_string("\t\'n\' to print next event;\r\n");
	put_string("\t\'b\' to reboot system;\r\n\r\n");
}

static void reboot(void)
{
	static struct
	{
		BYTE vMACAddress[6];
		DWORD dwIPAddress;
		WORD wChecksum;
	} BootloaderAddress;

	// Get our MAC address, IP address, and compute a checksum of them
	memcpy((void*)&BootloaderAddress.vMACAddress[0], (void*)&AppConfig.MyMACAddr.v[0], sizeof(AppConfig.MyMACAddr));
	BootloaderAddress.dwIPAddress = AppConfig.MyIPAddr.Val;
	BootloaderAddress.wChecksum = CalcIPChecksum((BYTE*)&BootloaderAddress, sizeof(BootloaderAddress) - sizeof(BootloaderAddress.wChecksum));

	// To enter the bootloader, we need to clear the /POR bit in RCON.
	// Otherwise, the bootloader will immediately hand off execution
	// to us.
	#if defined(USE_LCD)
		strcpypgm2ram((char*)LCDText, "Bootloader Reset");
		LCDUpdate();
	#endif
	RCONbits.POR = 0;

	INTCONbits.GIEL = 0;
	INTCONbits.GIEH = 0;

	#if defined(__18CXX)
	{
		WORD_VAL wvPROD;

		wvPROD.Val = ((WORD)&BootloaderAddress);
		PRODH = wvPROD.v[1];
		PRODL = wvPROD.v[0];
	}
	#endif

	Reset();
}


void config(void)
{
	static BYTE buffer[40], evt_len;
	BYTE ch_section;
	BYTE ch_param;
	DWORD input;
	menu_state_e state = SHOW_SECTIONS;

	sprintf(LCD_STRING_0, "Configuration");
	sprintf(LCD_STRING_1, "mode");
	LCD_decode(LCD_ALL);
	LCDUpdate();

	console_caption();
	config_show_sections();

	while (1) { // XXX add switch/case
		switch (state) {
		case SHOW_SECTIONS:

			if(!get_string(buffer, sizeof(buffer)))
				break;

			if (buffer[0] == 'l' || buffer[0] == 'L') {
				slog_flush();
				break;
			} else if (buffer[0] == 'f' || buffer[0] == 'F') {
				slog_format();
				break;
			} else if (buffer[0] == 'c' || buffer[0] == 'C') {
				slog_clean();
				break;
			} else if (buffer[0] == 'e' || buffer[0] == 'E') {
				config_restore();
				Reset();
				return;
			} else if (buffer[0] == 's' || buffer[0] == 'S') {
				config_save_reboot();
			} else if (buffer[0] == 'r' || buffer[0] == 'R') {
				config_restore_defaults();
				break;
			} else if (buffer[0] == 't' || buffer[0] == 'T') {

				evt_len = slog_getlast(buffer, sizeof(buffer));
				if(evt_len) {
					buffer[evt_len] = '\0';
					put_string("%s", buffer);
				}
				else
					put_string("System log is empty\r\n");

				break;
			} else if (buffer[0] == 'n' || buffer[0] == 'N') {

				evt_len = slog_getnext(buffer, sizeof(buffer));
				if(evt_len) {
					buffer[evt_len] = '\0';
					put_string("%s", buffer);
				}
				else
					put_string("There are no more events\r\n");

				break;
			} else if (buffer[0] == 'b' || buffer[0] == 'B') {

				reboot();
			}


			if (!isdigit(buffer[0])/* || escape_there(buffer)*/)
				break;
			ch_section = atob(buffer) - 1;
			if (ch_section < n_elements(sections) - 1) {
				config_show_section(sections[ch_section]);
				state = SHOW_SECTION;
			}

			break;
		case SHOW_SECTION:

			if(!get_string(buffer, sizeof(buffer)))
				break;
			if (!isdigit(buffer[0])/* || escape_there(buffer)*/) {
				config_show_sections();
				state = SHOW_SECTIONS;
				break;
			}
			ch_param = atob(buffer) - 1;
			if (ch_param < MAX_PRMS && sections[ch_section]->prms[ch_param]) {
				config_show_param(sections[ch_section]->prms[ch_param]);
				state = SHOW_PARAM;
			}

			break;
		case SHOW_PARAM:

			if(!get_string(buffer, sizeof(buffer)))
				break;

			switch (sections[ch_section]->prms[ch_param]->type) {
			case TYPE_CHAR:
				if (!isdigit(buffer[0])/* || escape_there(buffer)*/) {
					config_show_section(sections[ch_section]);
					state = SHOW_SECTION;
					break;
				}

				input = (DWORD) atoi(buffer);
				if (input >= sections[ch_section]->prms[ch_param]->lim.d.min
						&& input
								<= sections[ch_section]->prms[ch_param]->lim.d.max) {
					*(BYTE *) sections[ch_section]->prms[ch_param]->prm
							= (BYTE) input;
					config_show_section(sections[ch_section]);
					state = SHOW_SECTION;
				} else {
					put_string("\n\rOut of range\n\r");
				}
				break;
			case TYPE_SHORT:
				if (!isdigit(buffer[0])/* || escape_there(buffer)*/) {
					config_show_section(sections[ch_section]);
					state = SHOW_SECTION;
					break;
				}

				input = (DWORD) atoi(buffer);
				if (input >= sections[ch_section]->prms[ch_param]->lim.d.min
						&& input
								<= sections[ch_section]->prms[ch_param]->lim.d.max) {
					*(WORD *) sections[ch_section]->prms[ch_param]->prm
							= (WORD) input;
					config_show_section(sections[ch_section]);
					state = SHOW_SECTION;
				} else {
					put_string("\n\rOut of range\n\r");
				}

				break;
			case TYPE_LONG:
				if (!isdigit(buffer[0])/* || escape_there(buffer)*/) {
					config_show_section(sections[ch_section]);
					state = SHOW_SECTION;
					break;
				}

				input = (DWORD) atol(buffer);
				if (input >= sections[ch_section]->prms[ch_param]->lim.d.min
						&& input
								<= sections[ch_section]->prms[ch_param]->lim.d.max) {
					*(DWORD *) sections[ch_section]->prms[ch_param]->prm
							= (DWORD) input;
					config_show_section(sections[ch_section]);
					state = SHOW_SECTION;
				} else {
					put_string("\n\rOut of range\n\r");
				}
				break;
			case TYPE_STRING:
				if (strlen(buffer)
						> sections[ch_section]->prms[ch_param]->lim.s.maxlen) {
					put_string("\n\rToo long\n\r");
				} else {
					strcpy((BYTE *) sections[ch_section]->prms[ch_param]->prm,
							buffer);
					config_show_section(sections[ch_section]);
					state = SHOW_SECTION;
				}
				break;
			case TYPE_VECTOR:
				if(*buffer == '\0'){
					config_show_section(sections[ch_section]);
					state = SHOW_SECTION;
				} else if ((*(convert_prm_cb) (sections[ch_section]->prms[ch_param]->lim.v.cvrt_in))(
						buffer,
						(BYTE *) sections[ch_section]->prms[ch_param]->prm)) {
					config_show_section(sections[ch_section]);
					state = SHOW_SECTION;
				} else {
					put_string("\n\rWrong format\n\r");
				}

				break;
			default:
				break;
			}
			break;
		}

		StackTask();
	}
}

void config_restore(void)
{
	WORD cs;

	memset((void*) &AppConfig, 0x00, sizeof(AppConfig));
	XEEReadArray(0, (BYTE*) &AppConfig, sizeof(AppConfig));

	cs = CalcIPChecksum((BYTE*) &AppConfig,	sizeof(AppConfig) - sizeof(AppConfig.checksum));

	if(cs != AppConfig.checksum)
		config_restore_defaults();
}

void config_save(void)
{
	AppConfig.checksum = CalcIPChecksum((BYTE*) &AppConfig,	sizeof(AppConfig) - sizeof(AppConfig.checksum));
	XEEBeginWrite(0x0000);
	XEEWriteArray((BYTE*) &AppConfig, sizeof(AppConfig));
}

static ROM BYTE SerializedMACAddress[6] = {MY_DEFAULT_MAC_BYTE1, MY_DEFAULT_MAC_BYTE2, MY_DEFAULT_MAC_BYTE3, MY_DEFAULT_MAC_BYTE4, MY_DEFAULT_MAC_BYTE5, MY_DEFAULT_MAC_BYTE6};

void config_restore_defaults(void)
{

	memcpypgm2ram((void*) &AppConfig.MyMACAddr,
			(ROM void*) SerializedMACAddress, sizeof(AppConfig.MyMACAddr));
	AppConfig.MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1
			| MY_DEFAULT_IP_ADDR_BYTE2 << 8ul | MY_DEFAULT_IP_ADDR_BYTE3
			<< 16ul | MY_DEFAULT_IP_ADDR_BYTE4 << 24ul;
	AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2 << 8ul
			| MY_DEFAULT_MASK_BYTE3 << 16ul | MY_DEFAULT_MASK_BYTE4 << 24ul;
	AppConfig.MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2
			<< 8ul | MY_DEFAULT_GATE_BYTE3 << 16ul | MY_DEFAULT_GATE_BYTE4
			<< 24ul;
	AppConfig.PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1
			| MY_DEFAULT_PRIMARY_DNS_BYTE2 << 8ul
			| MY_DEFAULT_PRIMARY_DNS_BYTE3 << 16ul
			| MY_DEFAULT_PRIMARY_DNS_BYTE4 << 24ul;
	AppConfig.SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1
			| MY_DEFAULT_SECONDARY_DNS_BYTE2 << 8ul
			| MY_DEFAULT_SECONDARY_DNS_BYTE3 << 16ul
			| MY_DEFAULT_SECONDARY_DNS_BYTE4 << 24ul;

	memcpypgm2ram(AppConfig.NetBIOSName, (ROM void*)MY_DEFAULT_HOST_NAME, 16);
	FormatNetBIOSName(AppConfig.NetBIOSName);

	AppConfig.comm_station_id = DFLT_COMM_STATION_ID;
	AppConfig.comm_port = DFLT_COMM_PORT;

	AppConfig.rs232_baudrate = DFLT_RS232_BAUDRATE;
	AppConfig.rs232_parity = DFLT_RS232_PARITY;
	AppConfig.rs232_databits = DFLT_RS232_DATABITS;
	AppConfig.rs232_stopbits = DFLT_RS232_STOPBITS;
	AppConfig.rs232_handshake = DFLT_RS232_HANDSHAKE;

	AppConfig.r1_activity = DFLT_R1_ACTIVITY;
	AppConfig.r1_framelen = DFLT_R1_FRAMELEN;

//	AppConfig.r1_parity[16];
	strcpypgm2ram((char*) AppConfig.r1_parity, DFLT_R1_PARITY);

	AppConfig.r2_activity = DFLT_R2_ACTIVITY;
	AppConfig.r2_convert2hex = DFLT_R2_CONVERT2HEX;
	AppConfig.r2_framelen = DFLT_R2_FRAMELEN;
	AppConfig.r2_stop_byte = DFLT_R2_STOPBYTE;
	AppConfig.r2_code_begin = DFLT_R2_CODE_BEGIN;
	AppConfig.r2_code_len = DFLT_R2_CODE_LEN;
	AppConfig.r2_max_delay = DFLT_R2_MAX_DELAY;

	AppConfig.acc_host_tout = DFLT_ACC_HOST_TOUT;
	AppConfig.acc_retry_cnt = DFLT_ACC_RETRY_CNT;
	AppConfig.acc_local_access = DFLT_ACC_LOCAL_ACCESS;

//	AppConfig.acc_local_msg[32];
	strcpypgm2ram((char*) AppConfig.acc_local_msg, DFLT_ACC_LOCAL_MSG);

//	AppConfig.acc_busy_msg[32];
	strcpypgm2ram((char*) AppConfig.acc_busy_msg, DFLT_ACC_BUSY_MSG);

//	AppConfig.acc_failure_msg[32];
	strcpypgm2ram((char*) AppConfig.acc_failure_msg, DFLT_ACC_FAILURE_MSG);

//	AppConfig.acc_prompt_msg[32];
	strcpypgm2ram((char*) AppConfig.acc_prompt_msg, DFLT_ACC_PROMPT_MSG);


	AppConfig.sm_service_time = DFLT_SM_SERVICE_TIME;
	AppConfig.sm_sig_control_en = DFLT_SM_SIG_CONTROL_EN;
	AppConfig.sm_sig_control_relay = DFLT_SM_SIG_CONTROL_RELAY;
	AppConfig.sm_sig_control_inverse = DFLT_SM_SIG_CONTROL_INVERSE;
	AppConfig.sm_sig_control_duration = DFLT_SM_SIG_CONTROL_DURATION;
	AppConfig.sm_sig_indicator_en = DFLT_SM_SIG_INDICATOR_EN;
	AppConfig.sm_sig_indicator_relay = DFLT_SM_SIG_INDICATOR_RELAY;
	AppConfig.sm_sig_indicator_inverse = DFLT_SM_SIG_INDICATOR_INVERSE;
	AppConfig.sm_sig_indicator_duration = DFLT_SM_SIG_INDICATOR_DURATION;
	AppConfig.sm_sig_done_en = DFLT_SM_SIG_DONE_EN;
	AppConfig.sm_sig_done_sensor = DFLT_SM_SIG_DONE_SENSOR;
	AppConfig.sm_sig_done_inverse = DFLT_SM_SIG_DONE_INVERSE;
	AppConfig.sm_sig_failure_en = DFLT_SM_SIG_FAILURE_EN;
	AppConfig.sm_sig_failure_sensor = DFLT_SM_SIG_FAILURE_SENSOR;
	AppConfig.sm_sig_failure_inverse = DFLT_SM_SIG_FAILURE_INVERSE;

	config_save();
}
