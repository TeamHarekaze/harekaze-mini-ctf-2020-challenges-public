#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

unsigned char command1[11] = {77, 40, 70, 79, 101, 21, 23, 13, 19, 16, 0};

int main(void)
{
  unsigned char buffer[25];
  unsigned char prefix[15] = "HarekazeCTF{ID";
  unsigned char suffix[3] = "X}";
  unsigned char hash[SHA_DIGEST_LENGTH];
  unsigned char ans[SHA_DIGEST_LENGTH] = {0x1f, 0xcc, 0xe7, 0xec, 0x44, 0xbe, 0xb7, 0x2c, 0x99, 0x4e, 0x2c, 0xd6, 0x9c, 0x46, 0x29, 0x16, 0xca, 0x8e, 0xc8, 0x10};
  unsigned char command2[11] = {38, 68, 31, 22, 11, 11, 28, 33, 29, 32, 0};
  unsigned char command_verify[SHA_DIGEST_LENGTH] = {0x5c, 0x75, 0xca, 0x57, 0x85, 0x49, 0xf6, 0xa2, 0xc8, 0x3d, 0x14, 0xd1, 0xef, 0xce, 0x56, 0x55, 0xa5, 0x00, 0xaa, 0x67};

  printf("Input flag ( HINT: ^HarekazeCTF\\{ID[A-Z]{4}X\\}$ )\n");
  scanf("%20s", buffer);

  for(int i = 0; i < 14; i++)
  {
    if(prefix[i] != buffer[i])
    {
      printf("Wrong flag\n");
      return 0;
    }
  }
  for(int i = 14; i < 18; i++)
  {
    if(!('A' <= buffer[i] && buffer[i] <= 'Z'))
    {
      printf("Wrong flag\n");
      return 0;
    }
  }
  if(suffix[0] != buffer[18] || suffix[1] != buffer[19])
  {
    printf("Wrong flag\n");
    return 0;
  }

  buffer[20] = 'S';
  buffer[21] = 'A';
  buffer[22] = 'L';
  buffer[23] = 'T';
  buffer[24] = '\0';

  printf("Verifying... \n");


  for(int i = 0; i < 11; i++)
  {
    command2[i] += command1[i];
  }

  SHA1(command2, 11, hash);

  #ifdef DEBUG
  printf("\nCommand: %s", command2);
  printf("\nCommand Hash: {");
  for(int i = 0; i < SHA_DIGEST_LENGTH - 1; i++)
  {
    printf("0x%02x, ", hash[i]);
  }
  printf("0x%02x}\n", hash[SHA_DIGEST_LENGTH - 1]);

  printf("Verify  Hash: {");
  for(int i = 0; i < SHA_DIGEST_LENGTH - 1; i++)
  {
    printf("0x%02x, ", command_verify[i]);
  }
  printf("0x%02x}\n", command_verify[SHA_DIGEST_LENGTH - 1]);
  #endif

  for(int i = 0; i < 11; i++)
  {
    if(hash[i] != command_verify[i])
    {
      printf("Be patient\n");
      return 0;
    }
  }

  if(system((char*)command2) != 0)
  {
    printf("Be patient\n");
    return 0;
  }

  SHA1(buffer, 25, hash);

  #ifdef DEBUG
  printf("\nFlag   Hash: {");
  for(int i = 0; i < SHA_DIGEST_LENGTH - 1; i++)
  {
    printf("0x%02x, ", hash[i]);
  }
  printf("0x%02x}\n", hash[SHA_DIGEST_LENGTH - 1]);

  printf("Answer Hash: {");
  for(int i = 0; i < SHA_DIGEST_LENGTH - 1; i++)
  {
    printf("0x%02x, ", ans[i]);
  }
  printf("0x%02x}\n", ans[SHA_DIGEST_LENGTH - 1]);
  #endif

  for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
  {
    if(hash[i] != ans[i])
    {
      printf("Wrong flag\n");
      return 0;
    }
  }

  printf("Correct flag\n");
  return 0;
}
