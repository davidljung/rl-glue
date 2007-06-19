#ifndef LeahAgent_h
#define LeahAgent_h

#include <RL_common.h>

void agent_init(Task_specification task_spec);
Action agent_start(Observation o);
Action agent_step(Reward r, Observation o);
void agent_end(Reward r);
void agent_cleanup();
int egreedy(Observation o);

#endif