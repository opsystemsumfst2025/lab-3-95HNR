#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>

#define ROUNDS 10

typedef struct {
    sem_t sem_parent;
    sem_t sem_child;
} SharedSems;

int main() {
    SharedSems *sems = mmap(NULL, sizeof(SharedSems),
                            PROT_READ | PROT_WRITE,
                            MAP_SHARED | MAP_ANONYMOUS,
                            -1, 0);
    
    if (sems == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }
    
    // Szülő indíthat (1), gyerek vár (0)
    sem_init(&sems->sem_parent, 1, 1);
    sem_init(&sems->sem_child, 1, 0);
    
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    
    if (pid == 0) {
        for (int i = 0; i < ROUNDS; i++) {
            sem_wait(&sems->sem_child);  // Várakozás a gyerek szemaforra
            printf("PONG\n");
            sem_post(&sems->sem_parent); // Szülő engedélyezése
        }
        exit(0);
    } else {
        for (int i = 0; i < ROUNDS; i++) {
            sem_wait(&sems->sem_parent); // Várakozás a szülő szemaforra
            printf("PING\n");
            sem_post(&sems->sem_child);  // Gyerek engedélyezése
        }
        wait(NULL);
        
        sem_destroy(&sems->sem_parent);
        sem_destroy(&sems->sem_child);
        munmap(sems, sizeof(SharedSems));
    }
    return 0;
}

