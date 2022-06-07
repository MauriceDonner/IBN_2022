#include<stdio.h>
#include<stdlib.h>

// Read Console Input
void read_input(int* pointer){
    scanf("%i",pointer);
}

// Function to test, if a value is in an array, need this later
int valueinarray(int val, int* arr, int buffersize) {
    for (int i = 0; i < buffersize; i++) {
	if (arr[i] == val)
	    return 1;
    }
    return 0;
}

// Function to print the current buffer
void print_buffer(int* buffer, int buffersize){
    // Dont want to print double entries of Working set, so blacklist them
    int blacklist[buffersize];
    // initialize it with -1, so that no unwanted values are blacklisted
    for ( int i = 0; i < buffersize; i++) blacklist[i] = -1;

    // Now check for each value in WS if it has been blacklisted before
    printf("%s\n","Working set:");
    for ( int i = 0; i < buffersize; i++ ){
	if (valueinarray(buffer[i], blacklist, buffersize) == 1) {
	    continue;
	}
	else {
	    blacklist[i] = buffer[i];
	    printf("%i\n", buffer[i]);
	}
    }
}

int main(){

    int WS = 5;
    int* pWS = &WS;
    // Enter how many memory accesses should be used for the working set
    printf("%s\n", "Enter size of working set: ");
    read_input(pWS);

    int ringbuffer[WS];
    // Initialize buffer
    for ( int i = 0 ; i < WS ; i++) ringbuffer[i] = 0;

    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    // Open File ReferenceA.txt or ReferenceB.txt for reading
    fp = fopen("ReferenceA.txt", "r");
    if (fp == NULL) {
	perror("Error opening file");
	return(-1);
    }

    // Read line by line into the buffer. Once its full, overwrite the oldest
    // entry.
    int counter = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
	ringbuffer[counter] = atoi(line);
	counter++;
	if ( counter == WS ) { counter = 0; }
    }

    // Print to console
    print_buffer(ringbuffer,WS);

    // Close the file
    fclose(fp);
    if (line) { free(line); }
    exit(EXIT_SUCCESS);

    return 0;
}
