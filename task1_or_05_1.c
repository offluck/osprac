#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
  int     fd;
  size_t  line_length;
  char    string[14];

  // Trying to open file.
  if ((fd = open("myfile.txt", O_RDONLY, 0666)) < 0) {
    printf("Can\'t open file\n");
    exit(-1);
  }
  line_length = read(fd, string, 14);
  // Debug log.
  // printf("%zu\n", line_length);

  // Checking if line is read correctly.
  if (line_length != 13) {
    printf("Can\'t read all string\n");
    exit(-1);
  }
  printf("%s\n", string);

  // Trying to close file.
  if (close(fd) < 0) {
    printf("Can\'t close file\n");
  }
  return 0;
}
