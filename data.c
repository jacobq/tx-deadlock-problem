//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdint.h>
//#include <inttypes.h>
//#include <sys/types.h>
//#include <sys/queue.h>
//#include <netinet/in.h>
//#include <setjmp.h>
//#include <stdarg.h>
//#include <ctype.h>
//#include <errno.h>
//#include <getopt.h>
//#include <signal.h>
//#include <stdbool.h>
//
#include <rte_common.h>
#include <rte_log.h>
//#include <rte_malloc.h>
//#include <rte_memory.h>
//#include <rte_memcpy.h>
//#include <rte_eal.h>
//#include <rte_launch.h>
//#include <rte_atomic.h>
//#include <rte_cycles.h>
//#include <rte_prefetch.h>
//#include <rte_lcore.h>
//#include <rte_per_lcore.h>
//#include <rte_branch_prediction.h>
//#include <rte_interrupts.h>
//#include <rte_random.h>
//#include <rte_debug.h>
#include <rte_ether.h>
#include <rte_ethdev.h>
//#include <rte_mempool.h>
#include <rte_mbuf.h>

#include "common.h"
#include "data.h"

static void
app_main_loop(void)
{
    struct rte_mbuf *pkts_burst[MAX_PKT_BURST];
    unsigned int lcore_id;
    unsigned int nb_rx, nb_tx;
    unsigned int loop_counter = 0;
    struct rte_eth_dev_tx_buffer *buffer;

    lcore_id = rte_lcore_id();
    RTE_LOG(INFO, DATA, "entering main loop on lcore %u\n", lcore_id);

    while (!force_quit) {
        /*
         * Send back all the packets we get
         */
        for (i = 0; i < qconf->n_rx_port; i++) {
            nb_rx = rte_eth_rx_burst(PORT_ID, QUEUE_ID, pkts_burst, MAX_PKT_BURST);
            for (unsigned int i=0, j=0; i<nb_rx; j++) {
                nb_tx = rte_eth_tx_burst(PORT_ID, 0, &pkts_burst[i], nb_rx-i);
                if (nb_tx == 0 && j % 1024 == 0) {
                    RTE_LOG(INFO, DATA, "Failed to send packets\n");
                }
                i += sent;
            }
        }
        if (loop_counter % 8192 == 0) {
            // TODO: Send message to "control actor" on other core
        }
        loop_counter++;
    }
}

int
app_launch_one_lcore(__attribute__((unused)) void *dummy)
{
    app_main_loop();
    return 0;
}
