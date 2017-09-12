//Lab Code: Blue Man 
//Name: Ian Naeger
//Pawprint: IVNQM2
//Section: B 
//2/23/16

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {
	PaperBack,
	HardBack,
} Type;

typedef struct book {
	char* name;
	char* author;
	int rating;
	Type type;
} Book;

typedef Book* Library;

Library loadLibrary(const char* filename, int* lenPtr);
void sortLibrary(Library library,  int length);
void printLibrary(Library library, int length);
void writeLibrary(Library library, int length, const char* filename);

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Incorrect Usage\n");
		printf("%s <input file> <output file>\n", argv[0]);
		return 0;
	}

	int* length = malloc( sizeof( Book ) );
	Library library = loadLibrary(argv[1], length);
	
	sortLibrary(library, (*length) );
	printLibrary(library, (*length) );
	writeLibrary(library, (*length) , argv[2]);
	
	int i;
	for (i = 0; i < *length; i++) 
	{
		free(library[i].name);
		free(library[i].author);
	}

	free(library); 

	return 0;
}

Library loadLibrary(const char* filename, int* lenPtr) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Failed to open file %s\n", filename);
		*lenPtr = 0;
		return NULL;
	}

	fscanf(fp, "%d", lenPtr);
	Library library = malloc( sizeof(Book) * (*lenPtr) );

	int i;
	for (i = 0; i < *lenPtr; i++)  {
		library[i].name = malloc( 30 * sizeof(char) ); 
		library[i].author = malloc( 30 * sizeof(char) ); 

		fscanf(fp, "%s %s %d %d", (library+i)->name, (library+i)->author, &(library+i)->rating, (int*)&(library+i)->type);

	}

	return library;
	fclose(fp);
}

void sortLibrary(Library library,  int length) {
	int i;

	for (i = 1; i < length; i++) {
		int j = i;
		while (j > 0 && library[j].rating < library[j - 1].rating) {
			Book temp = library[j];
			library[j] = library[j - 1];
			library[j - 1] = temp;
			j--;
		}
	}
}

void printLibrary(Library library, int length) {
	int i;
	Type Paper = 0;
	for (i = 0; i < length; i++) {
		printf("%s %s %d", library[i].name, library[i].author, library[i].rating);
		if (library[i].type == Paper) {
			printf(" PaperBack\n");
		} else {
			printf(" HardBack\n");
		}
	}
}

void writeLibrary(Library library, int length, const char* filename) {
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		return ;
	}

	fprintf(fp, "%d\n", length);

	int i;
	for (i = 0; i < length; i++) {
		fprintf(fp, "%s %s %d %d\n", library[i].name, library[i].author, library[i].rating, library[i].type);
	}

	fclose(fp);
}

