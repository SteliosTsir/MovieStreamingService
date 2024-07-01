/*****************************************************
 * @file   main.c                                    *
 *                                                   *
 * @brief Main Function for Data Structures (CS240b) *
 * Project: Winter 2023		       	             *
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#include "Movie.h"

#define BUFFER_SIZE 1024  /**< Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

int hashtable_size; 	/** The size of the users hashtable (>0) */
int max_users;         /** The maximum number of registrations (users) */
int loginfo = 0;		/** Display log info while initialization */
// This is a very conservative progress on the hashtable. Our purpose
// is to force many rehashes to check the stability of the code.
int primes_g[170] = 		{  5,   7,  11,  13,  17,  19,  23,  29,  31,  37,
                               41,  43,  47,  53,  59,  61,  67,  71,  73,  79,
                               83,  89,  97, 101, 103, 107, 109, 113, 127, 131,
                              137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
                              191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
                              241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
                              307, 311, 313, 317, 331, 337, 347, 349, 353, 359,
                              367, 373, 379, 383, 389, 397, 401, 409, 419, 421,
                              431, 433, 439, 443, 449, 457, 461, 463, 467, 479,
                              487, 491, 499, 503, 509, 521, 523, 541, 547, 557,
                              563, 569, 571, 577, 587, 593, 599, 601, 607, 613,
                              617, 619, 631, 641, 643, 647, 653, 659, 661, 673,
                              677, 683, 691, 701, 709, 719, 727, 733, 739, 743,
                              751, 757, 761, 769, 773, 787, 797, 809, 811, 821,
                              823, 827, 829, 839, 853, 857, 859, 863, 877, 881,
                              883, 887, 907, 911, 919, 929, 937, 941, 947, 953,
                          	  967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021 };

user_t **user_hashtable_p;	/* The users hashtable. This is an array of chains (pinakas katakermatismoy xrhstwn)*/
new_movie_t *new_releases;     /* New releases simply-linked binary tree*/
movieCategory_t *categoryArray[6];  /* The categories array (pinakas kathgoriwn)*/


int main(int argc, char** argv)
{
	char filename[256]; // 255 chars + 1 for '\0'
	int choice;
	char correct;
    char buffer[256];  // Buffer for input

    printf("Welcome to my Movie Streaming Service!\n\n");

    do {
        // Ensure input is a positive number
        do {
            printf("Before we begin please enter a positive number for the maximum amount of users: ");
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                // Try to convert to an integer
                if (sscanf(buffer, "%d", &max_users) != 1 || max_users <= 0) {
                    printf("Invalid input. Please enter a positive number.\n");
                }
            } else {
                // Handle case where fgets fails
                printf("Error reading input. Please try again.\n");
                continue;
            }
        } while (max_users <= 0);

        // Confirm the entered number
        do {
            printf("You entered: %d, is this correct? [Y/N]\n", max_users);
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                // Only read the first character and ignore the rest
                correct = toupper(buffer[0]);
            } else {
                // Handle case where fgets fails
                printf("Error reading input. Please try again.\n");
                correct = 'N';  // Force loop to retry
            }
        } while (correct != 'Y' && correct != 'N');
    } while (correct == 'N');

    printf("Thank you.\n");


//////////////////////////////////////////////////////////////////////////////////////////
	int i = 0;
	while (i < 170){
		if(primes_g[i] > max_users){
			break;
		}
		i++;
	}
	hashtable_size = primes_g[i];
	if(hashtable_size == 0){
		printf("Invalid size");
		return 1;
	}

	user_hashtable_p = (user_t **)malloc(hashtable_size * sizeof(user_t *));

	if(user_hashtable_p == NULL){
		return -1;
	}

	for(i = 0; i < hashtable_size; i++){
		user_hashtable_p[i] = (user_t *)malloc(sizeof(user_t));
		if(user_hashtable_p[i] == NULL){
			return -1;
		}
		user_hashtable_p[i]->next = NULL;
	}


	movie_t* sentinelNode = (movie_t *)malloc(sizeof(movie_t));
	if(sentinelNode == NULL){
		printf("Memory allocation failed");
		return 1;
	}
	sentinelNode->movieID = -1;
	sentinelNode->watchedCounter = 0;
	sentinelNode->sumScore = 0;
	sentinelNode->year = 0;
	sentinelNode->lc = NULL;
	sentinelNode->rc = NULL;

	for(int i = 0; i < 6; i++){
		categoryArray[i] = (movieCategory_t *)malloc(6 * sizeof(movieCategory_t));
		if(categoryArray[i] == NULL){
			return -1;
		}
		categoryArray[i]->movie = sentinelNode;
		categoryArray[i]->sentinel = sentinelNode;
	}

//////////////////////////////////////////////////////////////////////


	printf("What would you like to do ?\n");
	printf("\t1. Initialize database \n");
	printf("\t2. Print database contents \n");
	do {
            printf("Please enter a number between 1 and 2: ");
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                // Try to convert to an integer
                if (sscanf(buffer, "%d", &choice) != 1 || choice <= 0 || choice >= 3) {
                    printf("Invalid input. Please number between 1 and 2.\n");
                }
            } else {
                // Handle case where fgets fails
                printf("Error reading input. Please try again.\n");
                continue;
            }
    } while (choice != 1 && choice != 2);


	switch (choice){
	case 1:
			do {
				printf("Please enter a filename: ");
				if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
					// Remove newline character from the buffer if present
					buffer[strcspn(buffer, "\n")] = '\0';

					// Validate filename length (in this case 255 chars)
					if (strlen(buffer) > 0 && strlen(buffer) <= 255) { 
						strncpy(filename, buffer, 255);
						filename[255] = '\0'; // Ensure null termination
					} else {
						printf("Filename is either too long or empty. Please try again.\n");
						buffer[0] = '\0'; // Reset buffer to force retry
					}
				} else {
					printf("Error reading input. Please try again.\n");
					clearerr(stdin); // Clear any error flags on stdin
				}
			} while (strlen(buffer) == 0);

			FILE *fin = NULL;
			char buff[BUFFER_SIZE], event;

			do {
				printf("Do you want log info displayed ? [Y/N]\n");
				if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
					// Only read the first character and ignore the rest
					correct = toupper(buffer[0]);
				} else {
					// Handle case where fgets fails
					printf("Error reading input. Please try again.\n");
					correct = 'N';  // Force loop to retry
				}
        	} while (correct != 'Y' && correct != 'N');

			switch (correct)
			{
			case 'Y':
				loginfo = 1;
				break;
			case 'N':
				loginfo = 0;
				break;
			default:
				break;
			}


			if (( fin = fopen(filename, "r") ) == NULL ) {
				fprintf(stderr, "\n Could not open file: %s\n", filename);
				perror("Opening test file\n");
				return EXIT_FAILURE;
			}

			/* Read input file buff-by-buff and handle the events */
			while ( fgets(buff, BUFFER_SIZE, fin) ) {

				DPRINT("Event: %s \n", buff);

				switch(buff[0]) {

				
				/* Event R : R <userID> - Register user. */
				case 'R':
				{
					int userID;
					sscanf(buff, "%c %d", &event, &userID);
					if ( register_user(userID) ) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}
				/* Event U : U <userID> - Unregister user. */
				case 'U':
				{
					int userID;
					sscanf(buff, "%c %d", &event, &userID);
					DPRINT("%c %d\n", event, userID);

					if ( unregister_user(userID) ) {
						DPRINT("%c %d succeeded\n", event, userID);
					} else {
						fprintf(stderr, "%c %d failed\n", event, userID);
					}

					break;
				}
				/* Event A : A <movieID> <category> <year> - Add new movie. */
				case 'A':
				{
					int movieID,category, year;
					sscanf(buff, "%c %d %d %d", &event, &movieID, &category, &year);
					DPRINT("%c %d %d %d\n", event, movieID, category, year);

					if ( add_new_movie(movieID, category, year) ) {
						DPRINT("%c %d %d %d succeeded\n", event, movieID, category, year);
					} else {
						fprintf(stderr, "%c %d %d %d failed\n", event, movieID, category, year);
					}

					break;
				}
				/* Event D : D  - Distribute movies. */
				case 'D':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if ( distribute_movies() ) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}
				/* Event W : W <userID ><category><movieID><score> - Watch movie */
				case 'W':
				{
					int userID, movieID,category,score;

					sscanf(buff, "%c %d %d %d %d", &event,&userID,&category, &movieID, &score);
					DPRINT("%c %d %d %d %d\n", event,userID, category, movieID, score);

					if ( watch_movie(userID,category, movieID, score) ) {
						DPRINT("%c %d %d %d %d succeeded\n", event,userID, category, movieID, score);
					} else {
						fprintf(stderr, "%c %d %d %d %d failed\n", event, userID,category, movieID, score);
					}

					break;
				}
				/* Event –	F  <userID ><category1><category2><score> Filter movies */
				case 'F':
				{
					int userID, score;
					sscanf(buff, "%c %d %d\n", &event, &userID,&score);
					DPRINT("%c %d %d\n", event, userID,score);

					if (filter_movies(userID,score) ) {
						DPRINT("%c %d %d succeeded\n", event, userID,score);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, userID,score);
					}

					break;
				}
				/* Event Q : Q <userID> - User statistics */
				case 'Q':
				{
					int userID;
					sscanf(buff, "%c %d\n", &event, &userID);
					DPRINT("%c %d\n", event, userID);

					if ( user_stats(userID) ) {
						DPRINT("%c %d succeeded\n", event, userID);
					} else {
						fprintf(stderr, "%c %d failed\n", event, userID);
					}

					break;
				}
				/* Event I : I <movieID> <category> - Search movie */
				case 'I':
				{
					int movieID,category;
					sscanf(buff, "%c %d %d\n", &event, &movieID, &category);
					DPRINT("%c %d %d\n", event, movieID, category);

					if ( search_movie(movieID, category) ) {
						DPRINT("%c %d %d succeeded\n", event, movieID, category);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, movieID, category);
					}

					break;
				}

				/* Empty line */
				case '\n':
					break;

				/* Ignore everything else */
				default:
					DPRINT("Ignoring buff: %s \n", buff);
					break;
				}
			}
		break;
	case 2:
		printf("Printing movies and users : \n");
		print_movies();
		print_users();
		break;
	default:
		break;
	}

	return (EXIT_SUCCESS);
}
