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
#include <stdbool.h>

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
#include <rte_lcore.h>
//#include <rte_per_lcore.h>
//#include <rte_branch_prediction.h>
//#include <rte_interrupts.h>
//#include <rte_random.h>
//#include <rte_debug.h>
//#include <rte_ether.h>
//#include <rte_ethdev.h>
//#include <rte_mempool.h>
//#include <rte_mbuf.h>

#include "common.h"
#include "control.h"


static void
control_main_loop(struct control_args *args)
{
    unsigned lcore_id;
    unsigned i, j, portid, nb_rx;
    struct lcore_queue_conf *qconf;

    lcore_id = rte_lcore_id();
    qconf = &lcore_que

    RTE_LOG(INFO, L2FWD, "control: entering main loop on lcore %u\n", lcore_id);

    for (i = 0; i < qconf->n_rx_port; i++) {

        portid = qconf->rx_port_list[i];
        RTE_LOG(INFO, CONTROL, " -- lcoreid=%u portid=%u\n", lcore_id,
                portid);

    }

    while (!*args->force_quit) {
        /*
         * Read messages from ring
         */

        for (i = 0; i < qconf->n_rx_port; i++) {

            portid = qconf->rx_port_list[i];
            nb_rx = rte_eth_rx_burst(portid, 0,
                    pkts_burst, MAX_PKT_BURST);

            port_statistics[portid].rx += nb_rx;

            for (j = 0; j < nb_rx; j++) {
                m = pkts_burst[j];
                rte_prefetch0(rte_pktmbuf_mtod(m, void *));
                app_simple_forward(m, portid);
            }
        }
    }
}

int
control_launch_one_lcore(struct control_args *args)
{
    control_main_loop(args);
    return 0;
}