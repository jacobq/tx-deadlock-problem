#ifndef TX_DEADLOCK_PROBLEM_CONTROL_H
#define TX_DEADLOCK_PROBLEM_CONTROL_H

struct control_args {
  static volatile bool *force_quit;
};

int control_launch_one_lcore(struct control_args *);

#endif //TX_DEADLOCK_PROBLEM_CONTROL_H
