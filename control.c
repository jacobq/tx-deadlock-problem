#include "control.h"

#define RTE_LOGTYPE_CONTROL RTE_LOGTYPE_USER2

void
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
         * TX burst queue drain
         */
        diff_tsc = cur_tsc - prev_tsc;
        if (unlikely(diff_tsc > drain_tsc)) {

            for (i = 0; i < qconf->n_rx_port; i++) {

                portid = l2fwd_dst_ports[qconf->rx_port_list[i]];
                buffer = tx_buffer[portid];

                sent = rte_eth_tx_buffer_flush(portid, 0, buffer);
                if (sent)
                    port_statistics[portid].tx += sent;

            }

            /* if timer is enabled */
            if (timer_period > 0) {

                /* advance the timer */
                timer_tsc += diff_tsc;

                /* if timer has reached its timeout */
                if (unlikely(timer_tsc >= timer_period)) {

                    /* do this only on master core */
                    if (lcore_id == rte_get_master_lcore()) {
                        print_stats();
                        /* reset the timer */
                        timer_tsc = 0;
                    }
                }
            }

            prev_tsc = cur_tsc;
        }

        /*
         * Read packet from RX queues
         */
        for (i = 0; i < qconf->n_rx_port; i++) {

            portid = qconf->rx_port_list[i];
            nb_rx = rte_eth_rx_burst(portid, 0,
                    pkts_burst, MAX_PKT_BURST);

            port_statistics[portid].rx += nb_rx;

            for (j = 0; j < nb_rx; j++) {
                m = pkts_burst[j];
                rte_prefetch0(rte_pktmbuf_mtod(m, void *));
                l2fwd_simple_forward(m, portid);
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