/*
 File Name: data_read_thread.h
 Author:
 Email: @croot.com
 Created: 2023-07-30
 Last Modified: 2023-07-30
*/
#pragma once
#include <rte_debug.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_ether.h>
#include <stdio.h>

#include <iostream>
#include <memory>

#define RX_RING_SIZE 4 
#define TX_RING_SIZE 4 
#define NUM_MBUFS 8191
#define MBUF_CACHE_SIZE 250
#define BURST_SIZE 32
namespace croot {
namespace lltg {
class Channel;

static const struct rte_eth_conf port_conf_default = {
    .rxmode =
        {
            .max_lro_pkt_size = RTE_ETHER_MAX_LEN,
        },
};

class DevReader {
 public:
  uint16_t port_id;
  int32_t Start(int argc, char *argv[]) {
    int ret;
    unsigned nb_ports;
    struct rte_mempool *mbuf_pool;
    struct rte_eth_dev_info dev_info;

    //txconf.offloads = 0x2e;
    /*txconf.offloads = RTE_ETH_TX_OFFLOAD_IPV4_CKSUM |
                      RTE_ETH_TX_OFFLOAD_UDP_CKSUM |
                      RTE_ETH_TX_OFFLOAD_TCP_CKSUM;*/

    ret = rte_eal_init(argc, argv);
    if (ret < 0) {
      rte_exit(EXIT_FAILURE, "Error initializing EAL\n");
    }

    nb_ports = rte_eth_dev_count_avail();
    if (nb_ports == 0) {
      rte_exit(EXIT_FAILURE, "No Ethernet ports found\n");
    }
    std::cout << "Total available ports " << nb_ports << std::endl;

    for (int p = 0; p < nb_ports; p++) {
      rte_eth_dev_info_get(p, &dev_info);
      std::cout << "Port " << p << std::endl
                << "Driver " << dev_info.driver_name << std::endl;
    }
    struct rte_eth_rxconf rxconf = dev_info.default_rxconf;
    struct rte_eth_txconf txconf = dev_info.default_txconf;

    port_id = 0;  // Assuming we have at least one Ethernet port

    // Create a memory pool for mbufs
    mbuf_pool =
        rte_pktmbuf_pool_create("MBUF_POOL", NUM_MBUFS, MBUF_CACHE_SIZE, 0,
                                RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());
    if (mbuf_pool == NULL) {
      rte_exit(EXIT_FAILURE, "Cannot create mbuf pool\n");
    }

    // Initialize the Ethernet port
    ret = rte_eth_dev_configure(port_id, 1, 16, &port_conf_default);
    if (ret < 0) {
      rte_exit(EXIT_FAILURE, "Cannot configure Ethernet port\n");
    }

    // Set up the TX queue
    ret = rte_eth_tx_queue_setup(port_id, 0, 16,
                                 rte_eth_dev_socket_id(port_id), &txconf);
    std::cout << rte_eth_dev_socket_id(port_id) <<"   aaa";
    if (ret < 0) {
      std::cout << "Message :" << rte_strerror(-ret) << std::endl;
      std::cout << "error code " << ret <<std::endl;
      rte_exit(EXIT_FAILURE, "Cannot set up TX queue\n");
    }

    // Set up the RX queue
    ret = rte_eth_rx_queue_setup(port_id, 0, 16,
                                 rte_eth_dev_socket_id(port_id), &rxconf,
                                 mbuf_pool);
    if (ret < 0) {
      rte_exit(EXIT_FAILURE, "Cannot set up RX queue\n");
    }
    // Start the Ethernet port
    ret = rte_eth_dev_start(port_id);
    if (ret < 0) {
      rte_exit(EXIT_FAILURE, "Cannot start Ethernet port\n");
    }
    return ret;
  };

  int32_t ReadBuffer() {
    // Receive and process packets
    struct rte_mbuf *pkts_burst[BURST_SIZE];
    while (1) {
      // Receive a burst of packets
      const uint16_t nb_rx =
          rte_eth_rx_burst(port_id, 0, pkts_burst, BURST_SIZE);

      // Process each received packet
      for (uint16_t i = 0; i < nb_rx; i++) {
        struct rte_mbuf *pkt = pkts_burst[i];
        // Process the TCP packet here
        // ...

        // Free the mbuf after processing
        std::cout << "read message 1" << std::endl;
        rte_pktmbuf_free(pkt);
      }
    }
    return 0;
  }
};

}  // namespace lltg
}  // namespace croot

