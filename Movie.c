/*****************************************************
 * @file   Movie.c                                   *
 * @author Paterakis Giorgos <geopat@csd.uoc.gr>     *
 *                                                   *
 * @brief Implementation for Movie.h 	      	     *
 * Project: Winter 2023				     *
 *****************************************************/
#include "Movie.h"

/**
 * @brief Creates a new user.
 * Creates a new user with userID as its identification.
 *
 * @param userID The new user's identification
 *
 * @return 1 on success
 *         0 on failure
 */

 int register_user(int userID){

	user_t* nextNode = (user_t *)malloc(sizeof(user_t));
	if(nextNode == NULL){
		return 0;
	}
	nextNode->userID = userID;
	nextNode->next = NULL;
	nextNode->history = NULL;
	
	printf("eimai gkei");

	/* Calculate index */
	int index = userID % hashtable_size;

	nextNode->next = user_hashtable_p[index]->next;
	user_hashtable_p[index]->next = nextNode;
	
	printf("Chain <%d> of Users:\n", index);
	user_t *temp = user_hashtable_p[index]->next;
	while (temp != NULL){
		printf("\t<%d>\n", temp->userID);
		temp = temp->next;
	}
	printf("DONE\n");
	return 1;
 }
 
/**
 * @brief Deletes a user.
 * Deletes a user with userID from the system, along with users' history tree.
 *
 * @param userID The new user's identification
 *
 * @return 1 on success
 *         0 on failure
 */

 int unregister_user(int userID){
	user_t* usr = searchUser(userID);
	if(usr == NULL){
		printf("User not found");
		return 0;
	}
	
	deleteTree(usr->history);

	 int index = userID % hashtable_size;
	 user_t* chain = user_hashtable_p[index]->next;

	 if(chain != usr){
		while(chain->next != usr && chain->next != NULL){
			chain = chain->next;
		}
	 	chain->next = chain->next->next;

		free(usr);
	 } else {
		user_hashtable_p[index]->next = chain->next;
		free(chain);
	 }

	printf("Chain <%d> of Users:\n", index);
	user_t *temp = user_hashtable_p[index]->next;
	while (temp != NULL){
		printf("\t<%d>\n", temp->userID);	
		temp = temp->next;
	}

	return 1;
 }
 
 /**
 * @brief Add new movie to new release binary tree.
 * Create a node movie and insert it in 'new release' binary tree.
 *
 * @param movieID The new movie identifier
 * @param category The category of the movie
 * @param year The year movie released
 *
 * @return 1 on success
 *         0 on failure
 */

 int add_new_movie(int movieID, int category, int year){
	
	new_movie_t* newNode = (new_movie_t *)malloc(sizeof(struct new_movie));
	if(newNode == NULL){
		return 0;
	}
	newNode->category = category;
	newNode->movieID = movieID;
	newNode->year = year;
	newNode->sumScore = 0;
	newNode->watchedCounter = 0;
	newNode->lc = NULL;
	newNode->rc = NULL;
	
	if(new_releases == NULL){
		new_releases = newNode;
		printf("New releases Tree:\n\t<new_releases>: ");
		printInOrderTree(new_releases);
		printf("\nDONE\n");
		return 1;
	}

	new_movie_t* curr = new_releases;
	new_movie_t* parent = NULL;
	while(curr != NULL){
		parent = curr;
		if(movieID < curr->movieID){
			curr = curr->lc;
		} else if( movieID > curr->movieID){
			curr = curr->rc;
		} else {
			printf("Movie already added");
			free(newNode);
		}
	}

	if(movieID < parent->movieID){
		parent->lc = newNode;
	} else {
		parent->rc = newNode;
	}
	
	printf("New releases Tree:\n\t<new_releases>: ");
	printInOrderTree(new_releases);
	printf("\nDONE\n");
	return 1;
 }
 
 /**
 * @brief Distribute the movies from new release binary tree to the array of categories.
 *
 * @return 0 on success
 *         1 on failure
 */

 int distribute_movies(void){

	struct new_movie *movieArr = (new_movie_t *)malloc(countNodesTree(new_releases) * sizeof(new_movie_t));
	if(movieArr == NULL){
		return 1;
	}

	fill_array(new_releases, movieArr, 0);

	int countCat[6] = {0};

	for(int i = 0; i < countNodesTree(new_releases); i++){
		countCat[movieArr[i].category]++;
	}

	struct movie *cat1 = (movie_t *)malloc(countCat[0] * sizeof(movie_t));
	struct movie *cat2 = (movie_t *)malloc(countCat[1] * sizeof(movie_t));
	struct movie *cat3 = (movie_t *)malloc(countCat[2] * sizeof(movie_t));
	struct movie *cat4 = (movie_t *)malloc(countCat[3] * sizeof(movie_t));
	struct movie *cat5 = (movie_t *)malloc(countCat[4] * sizeof(movie_t));
	struct movie *cat6 = (movie_t *)malloc(countCat[5] * sizeof(movie_t));

	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	int count4 = 0;
	int count5 = 0;
	int count6 = 0;

	for(int i = 0; i < countNodesTree(new_releases); i++){
		switch (movieArr[i].category)
		{
		case 0:
			cat1[count1].movieID = movieArr[i].movieID;
			cat1[count1].year = movieArr[i].year;
			cat1[count1].watchedCounter = movieArr[i].watchedCounter;
			cat1[count1].sumScore = movieArr[i].sumScore;
			count1++;
			break;
		case 1:
			cat2[count2].movieID = movieArr[i].movieID;
			cat2[count2].year = movieArr[i].year;
			cat2[count2].watchedCounter = movieArr[i].watchedCounter;
			cat2[count2].sumScore = movieArr[i].sumScore;
			count2++;
			break;
		case 2:
			cat3[count3].movieID = movieArr[i].movieID;
			cat3[count3].year = movieArr[i].year;
			cat3[count3].watchedCounter = movieArr[i].watchedCounter;
			cat3[count3].sumScore = movieArr[i].sumScore;
			count3++;
			break;
		case 3:
			cat4[count4].movieID = movieArr[i].movieID;
			cat4[count4].year = movieArr[i].year;
			cat4[count4].watchedCounter = movieArr[i].watchedCounter;
			cat4[count4].sumScore = movieArr[i].sumScore;
			count4++;
			break;
		case 4:
			cat5[count5].movieID = movieArr[i].movieID;
			cat5[count5].year = movieArr[i].year;
			cat5[count5].watchedCounter = movieArr[i].watchedCounter;
			cat5[count5].sumScore = movieArr[i].sumScore;
			count5++;
			break;
		default:
			cat6[count6].movieID = movieArr[i].movieID;
			cat6[count6].year = movieArr[i].year;
			cat6[count6].watchedCounter = movieArr[i].watchedCounter;
			cat6[count6].sumScore = movieArr[i].sumScore;
			count6++;
			break;
		}
	}

	categoryArray[0]->movie = arrayToTree(cat1, 0, countCat[0] - 1, categoryArray[0]->sentinel);
	categoryArray[1]->movie = arrayToTree(cat2, 0, countCat[1] - 1, categoryArray[1]->sentinel);
	categoryArray[2]->movie = arrayToTree(cat3, 0, countCat[2] - 1, categoryArray[2]->sentinel);
	categoryArray[3]->movie = arrayToTree(cat4, 0, countCat[3] - 1, categoryArray[3]->sentinel);
	categoryArray[4]->movie = arrayToTree(cat5, 0, countCat[4] - 1, categoryArray[4]->sentinel);
	categoryArray[5]->movie = arrayToTree(cat6, 0, countCat[5] - 1, categoryArray[5]->sentinel);

	/* free */

	free(cat1);
	free(cat2);
	free(cat3);
	free(cat4);
	free(cat5);
	free(cat6);
	free(movieArr);
	freeTree(new_releases);
	new_releases = NULL;

	print_movies();

	printf("\nDONE\n");

	return 1;
 }
 
 /**
 * @brief User rates the movie with identification movieID with score
 *
 * @param userID The identifier of the user
 * @param category The Category of the movie
 * @param movieID The identifier of the movie
 * @param score The score that user rates the movie with id movieID
 *
 * @return 1 on success
 *         0 on failure
 */

 int watch_movie(int userID,int category, int movieID, int score){

	 user_t *currUser = searchUser(userID);

	 if(currUser == NULL){
		printf("User not found.\n");
		return 0;
	 }

	 movie_t* node = searchNode(categoryArray[category]->movie, movieID);
	 if(node == NULL){
		printf("Movie not found.\n");
		return 0;
	 }

	 node->watchedCounter += 1;
	 node->sumScore += score;
	 userMovie_t *userMovieNode = (userMovie_t *)malloc(sizeof(userMovie_t));
	 userMovieNode->movieID = movieID;
	 userMovieNode->category = category;
	 userMovieNode->score = score;
	 userMovieNode->lc = NULL;
	 userMovieNode->parent = NULL;
	 userMovieNode->rc = NULL;

	  /* insert from ask 4 */

	 userMovie_t* currUserHistory = currUser->history;
	
	 currUserHistory = addToLeafOriented(currUserHistory, movieID, userMovieNode);

	 currUser->history = currUserHistory;

	 printUserMovie(currUser->history);

	 printf("\nDONE\n");
	 return 1;
 }
 
/**
 * @brief Identify the best rating score movie and cluster all the movies of a category.
 *
 * @param userID The identifier of the user
 * @param score The minimum score of a movie
 *
 * @return 1 on success
 *         0 on failure
 */

 int filter_movies(int userID, int score){
	 int numMovies = 0;
	 for(int i = 0; i < 6; i++){
		numMovies += countGreaterEq(categoryArray[i]->movie, score);
	 }
	 
	 movie_t** tempArr = (movie_t**)malloc(numMovies * sizeof(movie_t*));
	 if(tempArr == NULL){
		return 0;
	 }

	  elementIntoArray(tempArr, score, numMovies);

	  HeapShort(tempArr, numMovies);

	 for(int i = 0; i < numMovies; i++){

		printf("\t<%d>", tempArr[i]->movieID);
		if(tempArr[i]->watchedCounter != 0){
			printf("<%d>", tempArr[i]->sumScore/tempArr[i]->watchedCounter);
		} else {

			printf("<0>");
		}
		printf("\n");
	 }

	 printf("\nDONE\n");
	 return 1;
 }
 
/**
 * @brief Find movies from categories withn median_score >= score t
 *
 * @param userID The identifier of the user
 * @param category Array with the categories to search.
 * @param score The minimum score the movies we want to have
 *
 * @return 1 on success
 *         0 on failure
 */

 int user_stats(int userID){
	 userMovie_t* nextId = mostLeftNode(searchUser(userID)->history);
	 int prev = -1;
	 int count = 1;
	 int ScoreSum = nextId->score;
	 while(nextId != NULL && prev < nextId->movieID){
		prev = nextId->movieID;
		if(FindNextLeaf(searchUser(userID)->history, nextId->movieID)->movieID > prev){
			nextId = FindNextLeaf(searchUser(userID)->history, nextId->movieID);
			count++;
			ScoreSum += nextId->score;
		}
	 }
	 int mscore = ScoreSum / count;
	 printf("<%d>", mscore);
	 printf("\nDONE\n");
	 return 1;
 }
 
/**
 * @brief Search for a movie with identification movieID in a specific category.
 *
 * @param movieID The identifier of the movie
 * @param category The category of the movie
 *
 * @return 1 on success
 *         0 on failure
 */

 int search_movie(int movieID, int category){
	 
	 movie_t *root = categoryArray[category]->movie;

	 int res = searchRecursive(root, movieID);
	 
	 if(res == 0){
		printf("Movie not found.\n");
		return 0;
	 } else {
		printf("<%d>\nDONE\n", res);
	 }
	 return 1;
 }
 
 /**
 * @brief Prints the movies in movies categories array.
 * @return 1 on success
 *         0 on failure
 */

 int print_movies(void){

printf("Movie Category Array:\n");
	
	for(int i = 0; i < 6; i++){
		switch (i)
        {
        case 0:
            printf("\tHorror: ");
            break;
        case 1:
            printf("\tSci-fi: ");
            break;
        case 2:
            printf("\tDrama: ");
            break;
        case 3:
            printf("\tRomance: ");
            break;
        case 4:
            printf("\tDocumentary: ");
            break;
        default:
            printf("\tComedy: ");
            break;
        }
		printTreeWithSent(categoryArray[i]->movie, categoryArray[i]->sentinel);
		printf("\n");
	}	
	 return 1;
 }
 
  /**
 * @brief Prints the users hashtable.
 * @return 1 on success
 *         0 on failure
 */

 int print_users(void){
	for(int i = 0; i < hashtable_size; i++){
		printf("Chain <%d> of Users:\n", i);
		user_t *temp = user_hashtable_p[i]->next;
		while (temp != NULL){
			printf("\t<%d>\n", temp->userID);
			printf("\t History Tree:\n");
			printUserMovie2(temp->history);
			printf("\n");	
			temp = temp->next;
		}
	}
	 return 1;
 }
 

 ////////////////////////////// helper functions ///////////////////////////////////


 void printInOrderTree(new_movie_t * root){
	if(root == NULL){
		return;
	}
	printInOrderTree(root->lc);
	printf("<%d> ", root->movieID);
	printInOrderTree(root->rc);
 }

 void printTreeWithSent(movie_t* root, movie_t* sent){
	if(root == sent){
		return;
	}
	printTreeWithSent(root->lc, sent);
	printf("<%d> ", root->movieID);
	printTreeWithSent(root->rc, sent);	
 }


 int countNodesTree(new_movie_t * root){
	if(root == NULL){
		return 0;
	}
	int left = countNodesTree(root->lc);
	int right = countNodesTree(root->rc);

	return left + right + 1;
 }

  int fill_array(new_movie_t* root, struct new_movie * arr, int pos){
	if(root->lc != NULL){
		pos = fill_array(root->lc, arr, pos);
	}

	arr[pos].movieID = root->movieID;
	arr[pos].sumScore = root->sumScore;
	arr[pos].watchedCounter = root->sumScore;
	arr[pos].category = root->category;
	arr[pos].year = root->year;
	pos++;

	if(root->rc != NULL){
		pos = fill_array(root->rc, arr, pos);
	}

	return pos;
  }


  struct movie* arrayToTree(struct movie * arr, int start, int end, struct movie *sent){
	if(start > end){
		return sent;
	}
	int mid = start + (end - start)/2;

	struct movie* root = (struct movie*)malloc(sizeof(struct movie));
	root->movieID = arr[mid].movieID;
	root->year = arr[mid].year;
	root->sumScore = arr[mid].sumScore;
	root->watchedCounter = arr[mid].watchedCounter;

	root->lc = arrayToTree(arr, start, mid - 1, sent);
	root->rc = arrayToTree(arr, mid + 1, end, sent);

	return root;
  }

 void printArr(movie_t *arr, int k){
	for(int i = 0; i < k; i++){
		printf("%d ", arr[i].movieID);
	}
 }

 void freeTree(new_movie_t* root){
	if(root == NULL){
		return;
	}
	freeTree(root->lc);
	freeTree(root->rc);

	free(root);
 }

 int searchRecursive(movie_t* root, int k){
	if(root == NULL){
		return 0;
	}

	if(root->movieID == k){
		return root->year;
	}

	if(root->movieID > k){
		return searchRecursive(root->lc, k);
	} else {
		return searchRecursive(root->rc, k);
	}

 }


  movie_t *searchNode(movie_t* root, int k){
  	if(root == NULL){
		return NULL;
	}

	if(root->movieID == k){
		return root;
	}

	if(root->movieID > k){
		return searchNode(root->lc, k);
	} else {
		return searchNode(root->rc, k);
	}
 }

 user_t* searchUser(int k){
	int index = k % hashtable_size;
	user_t* chain = user_hashtable_p[index]->next;
	while(chain != NULL){
		if(chain->userID == k){
			return chain;
		}
		chain = chain->next;
	}
	return NULL;
 }

  userMovie_t* addToLeafOriented(userMovie_t* root, int k, userMovie_t* newNode){
		if(root != NULL){
			userMovie_t *tr = root;
			while(tr->lc != NULL){
				if(k <= tr->movieID){
					tr = tr->lc;
				} else {
					tr = tr->rc;
				}
			}

			if(tr->movieID == k){
				tr->score = newNode->score;
				return root;
			}


			if(tr->movieID > k){
				userMovie_t* rc = (userMovie_t*)malloc(sizeof(userMovie_t));
				rc->movieID = tr->movieID;
				rc->category = tr->category;
				rc->score = tr->score;
				rc->parent = tr;
				newNode->parent = tr;
				rc->lc = NULL;
				rc->rc = NULL;
				tr->movieID = newNode->movieID;
				tr->category = newNode->category;
				tr->score = newNode->score;
				tr->lc = newNode;
				tr->rc = rc;
			} else {
				userMovie_t* lc = (userMovie_t*)malloc(sizeof(userMovie_t));
				lc->movieID = tr->movieID;
				lc->category = tr->category;
				lc->score = tr->score;
				lc->parent = tr;
				newNode->parent = tr;
				lc->lc = NULL;
				lc->rc = NULL;
				tr->lc = lc;
				tr->rc = newNode;
			}

		} else {
			root = newNode;
		}

	return root;
  }

 void printUserMovie(userMovie_t* root){
	if(root == NULL){
		return;
	}
	printUserMovie(root->lc);
	printf("< %d, %d >\n", root->movieID, root->score);
	printUserMovie(root->rc);	
 } 
 
 
 void printUserMovie2(userMovie_t* root){
	if(root == NULL){
		return;
	}
	printUserMovie2(root->lc);
	printf("\t\t<%d>, <%d>\n", root->movieID, root->score);
	printUserMovie2(root->rc);	
 }

 userMovie_t* FindNextLeaf(userMovie_t* root, int k){
	if(root == NULL){
		return NULL;
	}
	userMovie_t* tr = root;
	while(tr->lc != NULL){
		if(tr->movieID >= k){
			tr = tr->lc;
		} else {
			tr = tr->rc;
		}
	}

	if(tr->parent->lc->movieID == k){
		return tr->parent->rc;
	} else {
		if(tr->parent->parent->rc->lc != NULL){
			return tr->parent->parent->rc->lc;
		} else {
			return tr->parent->parent->rc;
		}
	}
 }
 
  userMovie_t* mostLeftNode(userMovie_t* root){
	if(root == NULL){
		return NULL;
	}
	userMovie_t* tr = root;
	while(tr->lc != NULL){
		tr = tr->lc;
	}
	return tr;
  }

 int countGreaterEq(movie_t* root, int k){

	if(root->movieID == -1){
		return 0;
	}

	int avgscore = 0;
	if(root->watchedCounter != 0){
		avgscore = root->sumScore / root->watchedCounter;
	}

	int l = 0;
	if(root->lc->movieID != -1){
		l = countGreaterEq(root->lc, k);
	}
	int r = 0;
	if(root->rc->movieID != -1){
		r = countGreaterEq(root->rc, k);
	}

	if(avgscore >= k){
		return 1 + l + r;
	} else {
		return l + r;
	}
 }

  void elementIntoArray(movie_t** arr, int k, int size){
	int c = 0;
	for(int i = 0; i < 6; i++){
		addToArray(arr, categoryArray[i]->movie, k, size, c);
		c+= countGreaterEq(categoryArray[i]->movie, k);
	}
  }


  int addToArray(movie_t** arr, movie_t* root, int k, int size, int c){
		if(root->movieID == -1){
			return c;
		}

		c = addToArray(arr, root->lc, k, size, c);

		int avgscore = 0;
		if(root->watchedCounter != 0){
			avgscore = root->sumScore/ root->watchedCounter;
		}

		if(avgscore >= k){
			arr[c] = root;
			c++;
		}

		c = addToArray(arr, root->rc, k, size, c);

  } 




void HeapShort(movie_t** arr, int size){
	for(int i = size/2 - 1;i >= 0; i--){
		Heapify(arr, size, i);
	}

	for(int i = size - 1;i >= 0; i--){
		movie_t* temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		Heapify(arr, i, 0);
	}
}

void Heapify(movie_t** arr, int size,int k){
	int big = k;
	int l = 2*k+1;
	int r = 2*k+2;

	if(l < size){
		if(arr[l]->watchedCounter != 0 && arr[big]->watchedCounter != 0){
			if(arr[l]->sumScore/arr[l]->watchedCounter > arr[big]->sumScore/arr[big]->watchedCounter){
				big = l;
			}
		} else if(arr[l]->watchedCounter != 0){
			big = l;
		}
	}

	if(r < size){
		if(arr[r]->watchedCounter != 0 && arr[big]->watchedCounter != 0){
			if(arr[r]->sumScore/arr[r]->watchedCounter > arr[big]->sumScore/arr[big]->watchedCounter){
				big = r;
			}
		} else if(arr[r]->watchedCounter != 0){
			big = r;
		}
	}

	if(big != k){
		movie_t* temp = arr[k];
		arr[k] = arr[big];
		arr[big] = temp;

		Heapify(arr, size, big);
	}
}

 void deleteTree(userMovie_t* root){
	if(root == NULL){
		return;
	}

	deleteTree(root->lc);
	deleteTree(root->rc);

	free(root);
 }


