#ifndef TX_DEADLOCK_PROBLEM_COMMON_H
#define TX_DEADLOCK_PROBLEM_COMMON_H

#define RTE_LOGTYPE_MAIN RTE_LOGTYPE_USER1
#define RTE_LOGTYPE_DATA RTE_LOGTYPE_USER2
#define RTE_LOGTYPE_CONTROL RTE_LOGTYPE_USER3

#define PORT_ID 0
#define QUEUE_ID 0

struct message {
  int foo;
};

#endif //TX_DEADLOCK_PROBLEM_COMMON_H
