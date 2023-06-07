#ifndef __SIGNALISTICS__
#define __SIGNALISTICS__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int handle_signal(void);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);

#endif /* __SIGNALISTICS__*/
