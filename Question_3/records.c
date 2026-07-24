#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// define what an employee looks like
struct Employee {
    int id;
    char name[20];
};

int main() {
    // open file. O_CREAT makes it if it doesn't exist
    int fd = open("employees.dat", O_CREAT | O_RDWR, 0644);
    if (fd < 0) { 
        perror("failed to open file"); 
        return 1; 
    }

    struct Employee emp1 = {1, "Alice"};
    struct Employee emp2 = {2, "Bob"};

    // write the initial records to the file
    write(fd, &emp1, sizeof(struct Employee));
    write(fd, &emp2, sizeof(struct Employee));

    // change bob to charlie
    struct Employee updated_emp = {2, "Charlie"};

    // use lseek to jump exactly to the second record's position
    lseek(fd, sizeof(struct Employee), SEEK_SET); 
    write(fd, &updated_emp, sizeof(struct Employee));

    // retrieve record from location to verify it worked
    struct Employee retrieved;

    // jump back to read it
    lseek(fd, sizeof(struct Employee), SEEK_SET); 
    read(fd, &retrieved, sizeof(struct Employee));

    printf("Retrieved Updated Record: ID=%d, Name=%s\n", retrieved.id, retrieved.name);

    // always remember to close it
    close(fd);
    return 0;
}
