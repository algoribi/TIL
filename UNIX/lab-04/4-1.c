#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void) {
	struct stat buf;
	
	stat("password.txt", &buf); // "password.txt"의 성질을 buf에 저장

	printf("Inode = %d\n", (int)buf.st_ino); // buf의 Inode number 출력
	printf("Mode = %o\n", (unsigned int)buf.st_mode); // File type and mode 출력
	printf("Nlink = %o\n", (unsigned int)buf.st_nlink); // Number of hard links 출력
	printf("UID = %d\n", (int)buf.st_uid); // User ID of owner 출력
	printf("GID = %d\n", (int)buf.st_gid); // Group ID of owner 출력
	printf("Size = %d\n", (int)buf.st_size); // Total size, in bytes 출력
	printf("Atime = %d\n", (int)buf.st_atime); // Time of last access 출력
	printf("Ctime = %d\n", (int)buf.st_ctime); // Time of last status change 출력
	printf("Blksize = %d\n", (int)buf.st_blksize); // Block size for filesystem I/O 출력
	printf("Blocks = %d\n", (int)buf.st_blocks); // Number of 512B blocks allocated 출력

	return 0;
}
