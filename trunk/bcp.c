/*
 * bcp.c
 *
 *  Created on: 16.02.2013
 *      Author: admin
 */

#include "net.h"
#include "bcp.h"

BOOL bcp_process_packet(BYTE *pkt)
{
	bcp_header_t * hdr = (bcp_header_t *)pkt;

	if(hdr->hdr_u.type != BCP_SYNC) {
		net_disconnect();
		return FALSE;
	}









}
