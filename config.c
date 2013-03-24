#include "TCPIP Stack/TCPIP.h"
#include "config.h"

BYTE str1[20] = "строка 1";
BYTE char_prm1 = 42;

BYTE str2[20] = "строка 2";
DWORD int_prm1 = 4242;

static ROM const menu_prm_t prm00 = { TYPE_STRING, "string parameter 1",
		(void *) str1, { { 256, 0 } } };
static ROM const menu_prm_t prm01 = { TYPE_CHAR, "char parameter 1",
		(void *) &char_prm1, { { 0, 10 } } };
//static ROM const menu_prm_t * ROM prms1[] = { &prm00, &prm01, (ROM menu_prm_t *)0 };
static ROM const menu_section_t cat1 = { "category 1", { &prm00, &prm01, (ROM menu_prm_t *)0 } };

static ROM const menu_prm_t prm10 = { TYPE_STRING, "string parameter 2",
		(void *) str2, { { 256, 0 } } };
static ROM const menu_prm_t prm11 = { TYPE_LONG, "int parameter 1",
		(void *) &int_prm1, { { 0, 30000 } } };
//static ROM const menu_prm_t * ROM prms2[] = { &prm10, &prm11, (ROM menu_prm_t *)0 };
static ROM const menu_section_t cat2 = { "category 2", { &prm10, &prm11, (ROM menu_prm_t *)0 } };

static ROM const menu_section_t * ROM sections[] = {
		&cat1,
		&cat2,
		0 };

void config_show_sections(void)
{
	BYTE i;
	for (i = 0; sections[i]; i++) {
		BYTE a[6];
		uitoa((WORD)(i + 1), a);
		putsUSART(a); putrsUSART(". ");
		putrsUSART(sections[i]->caption);
		putrsUSART("\n\r");
	}

}

int config_show_section(ROM const menu_section_t * section) {

	BYTE i;

	if(section == NULL)
		return -1;

	for(i = 0; section->prms[i]; i ++) {
		BYTE a[6];
		uitoa((WORD)(i + 1), a);
		putsUSART(a); putrsUSART(". ");
		putrsUSART(section->prms[i]->caption);
		putrsUSART(" (");
		switch(section->prms[i]->type) {
		case TYPE_CHAR:
			uitoa(*(BYTE *)section->prms[i]->prm, a);
			putsUSART(a);
			break;
		case TYPE_SHORT:
			uitoa(*(WORD *)section->prms[i]->prm, a);
			putsUSART(a);
			break;
		case TYPE_LONG:
			uitoa(*(DWORD *)section->prms[i]->prm, a);
			putsUSART(a);
			break;
		case TYPE_STRING:
			putsUSART((BYTE *)section->prms[i]->prm);
			break;
		}

		putrsUSART(")\n\r");
	}

	return 0;
}

void config(void)
{

	config_show_sections();

	config_show_section(sections[0]);
	config_show_section(sections[1]);
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
