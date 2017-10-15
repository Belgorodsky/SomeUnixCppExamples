#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>


constexpr char sem_name[] = "/file_writing_semaphore";

int main()
{
	sem_t *semaphore = sem_open(sem_name, O_CREAT | O_EXCL, 0777, 1);

	sem_close(semaphore);
	sem_unlink(sem_name);


	return 0;
}

