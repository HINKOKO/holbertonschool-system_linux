#include <unistd.h>
#include <signal.h>

/**
 * pid_exist - tests if a process exists
 * From man 2 kill => if sig is 0, no signal is sent,
 * but existence and permission checks are still performed
 * => trick with 'kill' to check existence
 * => revert it since we want 1 for exists and 0 otherwise
 * @pid: the PID to check the existence
 * Return: 1 if pid exists, 0 otherwise
 * we negate because kill(pid, 0) returns 0 if pid exists
 * and we want it to 1
 * and logical negation of any negatives one result in 0, switch operated.
 */

int pid_exist(pid_t pid)
{
	return (!kill(pid, 0));
}
