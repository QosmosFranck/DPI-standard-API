/*
 * Copyright  Qosmos 2014 - Franck Baudin <franck.baudin@qosmos.com>
 */

/* TODO: add newBSD & GPLv2 license headers */


#ifndef DPI_ENGINE_H
#define DPI_ENGINE_H

/*
 * To be called once, before any other dpi_* call
 */
int dpi_engine_init_once(int argc, char **argv);

/*
 * Once called, any dpi_* functions call are prohibited
 * exept dpi_engine_init_once()
 */
void dpi_engine_exit_once(void);


/* Return value: per thread opaque value, mandatory for the following calls
 *  dpi_engine_exit_perthread()
 *  dpi_engine_inject_packet()
 */
void *dpi_engine_init_perthread(void);

/* To be called only once per thread, with the proper opaque value,
 * returned by dpi_engine_init_perthread()
 */
void dpi_engine_exit_perthread(void *opaque);

/*
 * This function requires linear packets:
 * scatter/gather, chained packets are not supported
 *
 * return code:
 *  !0 if more packets are required for a proper classification
 *  0 when no more packets required, classification is final
 *
 * opaque: opaque per thread value, returned by dpi_engine_init_perthread()
 * packet: pointer to the first byte of the packet Ethernet header
 * len: len of the payload (bytes)
 * tv: has to be not NULL. Time of arrival of the packet.
 * classif: array of 32 bits values. for instance:
 *   classif[0]: application ID 
 *   classif[1]: protocol tags/family 
 *   classif[2..]: TBD
 */
int dpi_engine_inject_packet(void *opaque,
                    char *packet, size_t len, struct timeval *tv,
                    void* classif, size_t classif_len);
#endif /* DPI_ENGINE_H */
