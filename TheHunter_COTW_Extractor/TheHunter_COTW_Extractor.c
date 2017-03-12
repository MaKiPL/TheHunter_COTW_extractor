// TheHunter_COTW_Extractor.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>


int main()
{
	const char * tabc = "tab";
	char * filename = malloc(256);
	char * mydir = malloc(256);
	while (1)
	{
		printf("Type path to your .ARC file: ");
		char * c = malloc(512);
		scanf("%s", c);
		FILE *arc = fopen(c, "rb");
		if (arc == NULL)
		{
			printf(".ARC file not found/cannot be opened!\n");
			system("pause");
			return -1;
		}
		char * p = malloc(strlen(c));
		strcpy(p, c);
		strncpy(p + (strlen(c) - 3), tabc, 3);
		FILE *tab = fopen(p, "rb");
		if (tab == NULL)
		{
			printf(".TAB file not found/cannot be opened. It has to be in the same folder as ARC!\n");
			system("pause");
			return -1;
		}
		char * dir = malloc(strlen(c));
		strcpy(dir, c);
		strncpy(dir+(strlen(dir)-4), "ext\\", 4);
		_mkdir(dir);

		fseek(tab, 0xC, SEEK_SET);
		fseek(arc, 0x10, SEEK_SET);

		while (1)
		{
			unsigned int Flags = 0;
			unsigned int Offset = 0;
			unsigned int Size = 0;
			fread(&Flags, sizeof(unsigned int), 1, tab);
			fread(&Offset, sizeof(unsigned int), 1, tab);
			fread(&Size, sizeof(unsigned int), 1, tab);
			fseek(arc, Offset + 0x10, SEEK_SET);
			sprintf(mydir,"%08X.bin", Flags);
			/*sprintf(mydir, "%s%s", dir, filename);
			strcpy(mydir, dir);
			filename = strcat(mydir, filename);*/
			sprintf(filename, "%s%s", dir, mydir);
			FILE * fwrr = fopen(filename, "ab");
			for (unsigned int i = 0; i < Size-16; i++)
			{
				unsigned char b;
				fread(&b, sizeof(char), 1, arc);
				fwrite(&b, sizeof(char), 1, fwrr);
			}
			printf("\nSaved: %s", filename);
			fclose(fwrr);
			if (fgetc(tab) == EOF)
				break;
			else fseek(tab, -1, SEEK_CUR);
		}
		printf("\n");
	}
	
    return 0;
}

