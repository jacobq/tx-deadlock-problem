# Deadlock problem repro

Trying to investigate a problem where [`rte_eth_tx_burst`](https://doc.dpdk.org/api-19.11/rte__ethdev_8h.html#a83e56cabbd31637efd648e3fc010392b) seems to be entering a deadlocked state. 

This repository is based on the [L2 forwarding example](https://doc.dpdk.org/guides-19.11/sample_app_ug/l2_forward_real_virtual.html).

It can be run with CLI arguments similar to what we use for NFlambda:

```
sudo build/deadlock-test -l 3,2,1 --master-lcore=1 -w af:00.0,mprq_en=1,rxqs_min_mprq=1,txq_mpw_en=1,txq_max_inline_len=128 -w af:00.1,mprq_en=1,rxqs_min_mprq=1,txq_mpw_en=1,txq_max_inline_len=128 -n 4 --socket-mem=0,8192
```

See also:

* [This 2017 mailing list discussion](https://mails.dpdk.org/archives/users/2017-January/001474.html)
* [`rte_eth_tx_queue_setup`](https://doc.dpdk.org/api-19.11/rte__ethdev_8h.html#a796c2f20778984c6f41b271e36bae50e)

