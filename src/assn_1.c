/*
 ============================================================================
 Name        : assn_1.c
 Author      : Arjun Sharma
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int binarySearchInMemory(int *K, int seek, int low, int high);
int *linearSearchInMemory(int *S, int *K, int seekLength, int keyLength);
int *linearSearchOnDisk(FILE *keyInputFile, int keyInputFileLength, int *S, int seekInputFileLength);
int binarySearchOnDisk(FILE *keyInputFile, int seek, int low, int high);


//Main Method

int main(int argc, char* argv[]) {

    if(argc != 4) {
    	printf("Illegal Number of Arguments");
    	exit(0);
    }
    else {
    	 struct timeval start_time, end_time;

    	 FILE *keyInputFile = fopen("key.db", "rb");
    	 fseek(keyInputFile, 0, SEEK_END); //2 * sizeof( int ), SEEK_SET
    	 int keyInputFileLength = ftell(keyInputFile);
    	 fclose(keyInputFile);

    	 keyInputFile = fopen("key.db", "rb");
    	 int *K = (int*)malloc(keyInputFileLength);
    	 int i = 0;
    	 while(!feof(keyInputFile))
    	 	{
    	 		fread((K + i), sizeof(int), 1, keyInputFile);
    	 		i++;
    	 	}
    	 fclose(keyInputFile);


    	 //printf("%d", keyInputFileLength);
    	 FILE *seekInputFile = fopen("seek.db", "rb");
    	 fseek(seekInputFile, 0, SEEK_END);
    	 int seekInputFileLength = ftell(seekInputFile);
    	 fclose(seekInputFile);

    	 seekInputFile = fopen("seek.db", "rb");
    	 int *S = (int*)malloc(seekInputFileLength);
    	 i = 0;
    	 while(!feof(keyInputFile))
    	    {
    	       fread((S + i), sizeof(int), 1, seekInputFile);
    	       i++;
     	 	}
    	 fclose(seekInputFile);

    	 int *hit = (int *)malloc(seekInputFileLength);

    	 //start time
    	 gettimeofday( &start_time, NULL );

    	 if(strcmp(argv[1], "--mem-bin") == 0) {
    		 int i = 0;
    		 while(i < seekInputFileLength/(sizeof (int))) {
    			 hit[i] = binarySearchInMemory(K, S[i], 0, keyInputFileLength/(sizeof (int)));
    			 i++;
    		 }
    	 }
    	 else if(strcmp(argv[1], "--mem-lin") == 0) {
    		 hit = linearSearchInMemory(S, K, seekInputFileLength/(sizeof (int)), keyInputFileLength/(sizeof (int)));
    	 }
    	 else if(strcmp(argv[1], "--disk-lin") == 0) {
    		 keyInputFile = fopen("key.db", "rb");
    		 hit = linearSearchOnDisk(keyInputFile, keyInputFileLength/(sizeof (int)), S, seekInputFileLength/(sizeof (int)));
    		 fclose(keyInputFile);
    	 }
    	 else if(strcmp(argv[1], "--disk-bin") == 0) {
    		 keyInputFile = fopen("key.db", "rb");
    		 int i = 0;
    		 while(i < seekInputFileLength/(sizeof (int))) {
    			 hit[i] = binarySearchOnDisk(keyInputFile, S[i], 0, keyInputFileLength/(sizeof (int)));
    			 i++;
    		 }
    		 fclose(keyInputFile);
    	 }
    	 else {
    		 printf("Error");
    	 }

    	 gettimeofday( &end_time, NULL );

    	 i = 0;
    	 while(i < seekInputFileLength/(sizeof (int))) {
    	    if(hit[i])
    	    	printf("%12d: Yes\n", S[i]);
    	    else
    	    	printf("%12d: No\n", S[i]);
    	    i++;
    	 }

    	 printf( "Time: %lf\n", (end_time.tv_sec - start_time.tv_sec ) + ( end_time.tv_usec - start_time.tv_usec) *1.0e-6);
    }
}

int binarySearchInMemory(int *K, int seek, int low, int high) {
	int mid = (low + high)/2;
	if(low > high)
		return 0;
	else if(K[mid] == seek)
		return 1;
	else if(K[mid] < seek)
		return binarySearchInMemory(K, seek, mid + 1, high);
	else
		return binarySearchInMemory(K, seek, low, mid - 1);
}

int binarySearchOnDisk(FILE *keyInputFile, int seek, int low, int high) {
	int mid = (low + high)/2;
	int keyValue;

	fseek(keyInputFile, mid * (sizeof (int)), SEEK_SET);
	fread(&keyValue, sizeof (int), 1, keyInputFile);

	if(low > high)
		return 0;
	else if(keyValue == seek)
		return 1;
	else if(keyValue < seek)
		return binarySearchOnDisk(keyInputFile, seek, mid + 1, high);
	else
		return binarySearchOnDisk(keyInputFile, seek, low, mid - 1);
}

int *linearSearchOnDisk(FILE *keyInputFile, int keyInputFileLength, int *S, int seekInputFileLength) {
	int *hit = (int *)malloc(seekInputFileLength * (sizeof (int)));
	int keyValue;
	for(int i = 0; i < seekInputFileLength; i++) {
		for(int j = 0; j < keyInputFileLength; j++) {
			fseek(keyInputFile, j * (sizeof (int)), SEEK_SET);
			fread(&keyValue, sizeof(int), 1, keyInputFile);
			if(keyValue == S[i]) {
				hit[i] = 1;
				break;
			} else {
				hit[i] = 0;
			}
		}
	}
	return hit;
}

int *linearSearchInMemory(int *S, int *K, int seekInputFileLength, int keyInputFileLength) {
	int *hit = (int *)malloc(seekInputFileLength * (sizeof (int)));
    for(int i = 0; i < seekInputFileLength; i++) {
    	for(int j = 0; j < keyInputFileLength; j++) {
    		if(S[i] == K[j]) {
    			hit[i] = 1;
    			break;
    		}
    		hit[i] = 0;
    	}
    }
    return hit;
}
