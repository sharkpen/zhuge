/*
 File Name: data_read_thread.h
 Author: 
 Email: @croot.com
 Created: 2023-07-30
 Last Modified: 2023-07-30
*/
#pragma once
#include <stdio.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_ether.h>
#include <memory>

#define RX_RING_SIZE 128
#define TX_RING_SIZE 128
#define NUM_MBUFS 8191
#define MBUF_CACHE_SIZE 250
#define BURST_SIZE 32
namespace croot {
namespace lltg {
class Channel;

static const struct rte_eth_conf port_conf_default = {
    .rxmode = {
        .max_lro_pkt_size = RTE_ETHER_MAX_LEN,
    },
};

class DevReader {
  public:
    int32_t Start(int argc, char* argv[]) {
      int ret;
      unsigned nb_ports;
      uint16_t port_id;
      struct rte_mempool *mbuf_pool;
      struct rte_eth_dev_info dev_info;
      struct rte_eth_txconf txconf;
      struct rte_eth_rxconf rxconf;


      ret = rte_eal_init(argc, argv);
      if (ret < 0) {
          rte_exit(EXIT_FAILURE, "Error initializing EAL\n");
      }

      nb_ports = rte_eth_dev_count_avail();
      if (nb_ports == 0) {
          rte_exit(EXIT_FAILURE, "No Ethernet ports found\n");
      }

      port_id = 0; // Assuming we have at least one Ethernet port

      // Create a memory pool for mbufs
      mbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL", NUM_MBUFS,
          MBUF_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());
      if (mbuf_pool == NULL) {
          rte_exit(EXIT_FAILURE, "Cannot create mbuf pool\n");
      }

      // Initialize the Ethernet port
      ret = rte_eth_dev_configure(port_id, 1, 1, &port_conf_default);
      if (ret < 0) {
          rte_exit(EXIT_FAILURE, "Cannot configure Ethernet port\n");
      }

      // Set up the TX queue
      ret = rte_eth_tx_queue_setup(port_id, 0, TX_RING_SIZE,
          rte_eth_dev_socket_id(port_id), &txconf);
      if (ret < 0) {
          rte_exit(EXIT_FAILURE, "Cannot set up TX queue\n");
      }

      // Set up the RX queue
      ret = rte_eth_rx_queue_setup(port_id, 0, RX_RING_SIZE,
          rte_eth_dev_socket_id(port_id), &rxconf, mbuf_pool);
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

    int32_t ReadBUffer() {
      int32_t port_id;
      // Receive and process packets
      struct rte_mbuf *pkts_burst[BURST_SIZE];
      while (1) {
          // Receive a burst of packets
          const uint16_t nb_rx = rte_eth_rx_burst(port_id, 0,
              pkts_burst, BURST_SIZE);

          // Process each received packet
          for (uint16_t i = 0; i < nb_rx; i++) {
              struct rte_mbuf *pkt = pkts_burst[i];
              // Process the TCP packet here
              // ...

              // Free the mbuf after processing
              rte_pktmbuf_free(pkt);
          }
      }
      return 0;
    }


};

}  // namespace lltg
}  // namespace croot

