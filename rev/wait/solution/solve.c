#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  char command[] = "echo HarekazeCTF\\{IDAAAAX\\} | ./a.out | grep Correct";

  for(command[20] = 'A'; command[20] <= 'Z'; command[20]++)
  {
    for(command[21] = 'A'; command[21] <= 'Z'; command[21]++)
    {
      printf("Progress: %s\n", command);
      for(command[22] = 'A'; command[22] <= 'Z'; command[22]++)
      {
        for(command[23] = 'A'; command[23] <= 'Z'; command[23]++)
        {
          if(system(command) == 0)
          {
            printf("%s\n", command);
            return 0;
          }
        }
      }
    }
  }
  return 0;
}
