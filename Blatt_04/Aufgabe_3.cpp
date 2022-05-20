#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

    int i, shmID, *shared_mem, count=0, total=0, rnd;
    shmID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0644);
    shared_mem = (int*)shmat(shmID,0,0);
    *shared_mem = 0;
    if (fork())
	for (i=0; i<500; i++){
	    *shared_mem += 1;
	    printf("\nElternprozess: %i", *shared_mem);
	    sleep(2);
	}
    else
	for (i=0; i<500; i++){
	    *shared_mem += 1;
	    printf("\nKindprozess: %i", *shared_mem);
	    rnd=rand();
	    sleep(rnd%3);
	}
    shmdt(shared_mem);
    shmctl(shmID, IPC_RMID, 0);
    return 0;

}

/* Das gemeinsame Hochzählen funktioniert nicht verlässlich. Beide Prozesse
 * kommen sich in die Quere, da se die geteilte Variable shared_mem haben
 * (typische race conditions sind möglich) */
