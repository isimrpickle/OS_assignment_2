#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/param.h"
#include "kernel/spinlock.h"
#include "kernel/riscv.h"
#include "kernel/proc.h"



int main() { 
   if(setpriority(14)<0)
        printf("something is wrong with setpriority");
    struct pstat statuses;
    if (getpinfo(&statuses) < 0) {
        
        printf( "Error: Unable to get process information\n");
        exit(-1);
    }

    // Εκτύπωση επικεφαλίδας
    printf( "PID\tNAME\tPRIORITY\tSTATE\t\tSIZE\n");
    
    // array with the enum variables as indexes so i can print them as strings in the next print. https://stackoverflow.com/questions/9907160/how-to-convert-enum-names-to-string-in-c
    const char * const state_str[] =
{
    [USED] = "used     ",
    [ZOMBIE] = "zombie   ",
    [RUNNABLE]  = "runnable",
    [RUNNING]  = "running  ",
    [SLEEPING]= "sleeping" 
};
    // Print process information
    for (int i = 0; i < statuses.summary_of_active_processes; i++) {
        if (statuses.pid[i] != 0) {
            printf( "%d\t%s\t%d\t\t%s\t%d\n", statuses.pid[i], statuses.name[i], statuses.priority[i],state_str[statuses.state[i]], statuses.sz[i] );
        }
    }

    exit(0);
}
