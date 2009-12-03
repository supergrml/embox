/**
 * @file etherdevice.h
 *
 * @brief Definitions for the Ethernet handlers.
 * @date 5.03.2009
 * @author Anton Bondarev
 */
#ifndef ETHERDEVICE_H_
#define ETHERDEVICE_H_

#define NET_TYPE_ALL_PROTOCOL 0

#include <net/netdevice.h>
#include <net/if_ether.h>

typedef void (*ETH_LISTEN_CALLBACK)(void * pack);

struct sk_buff;

/**
 * Functions provided by eth.c
 */

/**
 * Init ethernet.
 */
extern int eth_init();

/**
 * Create the Ethernet header
 * @param pack buffer to alter
 * @param dev source device
 * @param type Ethernet type field
 * @param daddr destination address (NULL leave destination address)
 * @param saddr source address (NULL use device source address)
 * @paramlen packet length (<= pack->len)
 */
extern int eth_header(struct sk_buff *pack, struct net_device *dev,
                    unsigned short type, void *daddr, void *saddr, unsigned len);

/**
 * Rebuild the Ethernet MAC header.
 * @param pack socket buffer to update
 */
extern int eth_rebuild_header(struct sk_buff *pack);

/**
 * Setup Ethernet network device
 * @param dev network device
 * Fill in the fields of the device structure with Ethernet-generic values.
 */
extern void ether_setup(net_device_t *dev);

/**
 * Allocates and sets up an Ethernet device
 */
extern net_device_t *alloc_etherdev(int num);

/**
 * Send Ethernet packet.
 * send packet into define eth interface
 * @param pack network packet which want send
 * @return on success, returns 0, on error, -1 is returned
 */
extern int dev_queue_xmit (struct sk_buff *pack);

#endif /* ETHERDEVICE_H_ */
