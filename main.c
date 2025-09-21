#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void encrypt(char* filePath, char cKey)
{
	char buffer[256];
	FILE* inFile = fopen(filePath, "r+");
	if (!inFile)
	{
		printf("Failed to open %s\n", filePath);
		exit(-1);
	}

	int i, n;
	int oldPos = 0;
	while (fgets(buffer, 256, inFile) != 0)
	{
		n = strlen(buffer);
		for (i = 0; i < n; i++)
		{
			buffer[i] += cKey;
		}

		
		int newPos = ftell(inFile);

		printf("%d\n", n);

		fseek(inFile, oldPos, SEEK_SET);
		fputs(buffer, inFile);
		fseek(inFile, newPos, SEEK_SET);

		oldPos = ftell(inFile);
	} 

	fclose(inFile);

}

void decrypt(char* filePath, char cKey)
{
	char buffer[256];
	FILE* inFile = fopen(filePath, "r+");
	if (!inFile)
	{
		printf("Failed to open %s\n", filePath);
		exit(-1);
	}

	int i, n;
	int oldPos = 0;
	while (fgets(buffer, 256, inFile) != 0)
	{
		n = strlen(buffer);
		for (int i = 0; i < n; i++)
		{
			buffer[i] -= cKey;
		}

		int newPos = ftell(inFile);

		fseek(inFile, oldPos, SEEK_SET);
		fputs(buffer, inFile);
		fseek(inFile, newPos, SEEK_SET);

		oldPos = ftell(inFile);
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("This program needs 2 arguments\n");
		return -1;
	}

	char c;

	printf("Type a Key to Encrypt/Decrypt\n");
	scanf("%c", &c);

	if (strcmp(argv[1], "encrypt") == 0)
	{
		encrypt(argv[2], c);
	}
	else if (strcmp(argv[1], "decrypt") == 0)
	{
		decrypt(argv[2], c);
	}

	return 0;

}