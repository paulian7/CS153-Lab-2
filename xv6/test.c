//this version removes the parameters for exit() and wait()
#include "types.h"
#include "user.h"

int PScheduler(void);
int test_scheduler_performance();
int test_scheduler_performance_fork();

int main(int argc, char *argv[])
{
    PScheduler();
    test_scheduler_performance();
    test_scheduler_performance_fork();
    exit();
    return 0;
}    

int test_scheduler_performance(void) {
    printf(1, "Process with PID %d\n\n", getpid());
    wait();
    exit();
    return 0;
}

int test_scheduler_performance_fork(void) {
    int pid = fork();
    if (pid == 0) {
        printf(1, "CHILD Process with PID %d\n\n", getpid());
        exit();
    } else {
        wait();
        printf(1, "PARENT Process with PID %d\n\n", getpid());
        exit();
    }
    return 0;
}
      
int PScheduler(void){
		 
    // Use this part to test the priority scheduler. Assuming that the priorities range between range between 0 to 31
    // 0 is the highest priority. All processes have a default priority of 10
    // You can use your own priority range/value setup

    int pid, ret_pid;
    int i,j,k;
  
    printf(1, "Testing the priority scheduler and setpriority system call:\n");
    printf(1, "Assuming that the priorities range between range between 0 to 31\n");
    printf(1, "0 is the highest priority. All processes have a default priority of 10\n");
    printf(1, " - The parent processes will switch to priority 0\n");
    set_prior(0); // Use your own setpriority interface
    for (i = 0; i < 3; i++) {
	pid = fork();
	if (pid > 0) {
            continue;
        } else if ( pid == 0) {
            printf(1, " - Hello! this is child# %d and I will change my priority to %d \n", getpid(), 60 - 20 * i);
            set_prior(30 - 10 * i); // Use your own setpriority interface
            for (j = 0; j < 50000; j++) {
                asm("nop");
                for(k = 0; k < 10000; k++) {
                    asm("nop"); 
                }
            }
            printf(1, " - Child #%d with priority %d has finished! \n", getpid(), 30-10*i);		
            exit();
        } else {
            printf(2," \n Error fork() \n");
            exit();
        }
    }

    if(pid > 0) {
        for (i = 0; i < 3; i++) {
            ret_pid = wait();
            printf(1, " - This is the parent: child with PID# %d has finished with status %d \n", ret_pid);
        }
        printf(1, " - If processes with highest priority finished first then its correct. \n");
    }
			
    return 0;
}