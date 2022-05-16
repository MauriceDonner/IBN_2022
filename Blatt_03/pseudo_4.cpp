// init semaphore on creation
int semaphore.guard = 0;
int semaphore.value = 0;
list semaphore.queue = <empty>;

void wait(semaphore) {
    while (TesetAndSet(&semaphore.guard) == 0); //spinning wait
    // now we have lock (i.e. semaphore.guard set to 1 by us)
    semaphore.value--;

    if (semaphore.value < 0) {
	//Atomically add current process P (executing this) to a queue of
	//processes waiting for the semaphore (i.e. to semaphore.queue);
	//-Set the process state (Prozesszustand) of P to "blocked",
	//effectively putting P to sleep
    }

    //Since wait() is a sys-call, next line is still executed, even if P blocked
    
    semaphore.guard = 0;
}

void signal(semaphore) {
    while (TestAndSet(&semaphore.guard) == 0); //spinning wait
    //Alternative: if (semaphore.value <= 0 && there is an entry in semaphore.queue)
    
    if (semaphore.value < 0){
	//Wake up the first/any process P referenced in semaphore.queue
	//(i.e. set process state of P to "ready"
	}
    else{
	semaphore.value++;
    }

    semaphore.guard = 0;
}
