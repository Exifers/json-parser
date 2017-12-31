#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <fcntl.h>

int analyse_args(int argc, char **argv)
{
  if (argc < 2)
    errx(1, "Usage ./main <filename.json>");
  
  int f = open(argv[1], O_RDONLY);
  if (f == -1)
    perror(NULL);

  return f;  
}

int main(int argc, char **argv)
{
  int f = analyse_args(argc, argv);

  
  close(f);
  return 0;
}
