/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*																											 *
*		Name		:	Ryan Dozier																			 *
*		Assignment	:	Exam 4																				 *
*		Due Date	:	December 4, 2016																	 *
*																											 *
*		Description	:	This program creates a linked list of music albums either inputted					 *
*						manually through the interface, or by scanning a formatted text file.				 *
*						The list is sorted, and can be viewed, in a number of ways.							 *
*																											 *
*																											 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/*******************************************************************************************************
To Do List	:
1)	Comments for Data Structure				Status	:	DONE
2)	Comments for Function Declarations		Status	:	DONE
3)	Create Header File						Status	:	DONE
4)	Error Checking							Status	:	Incomplete
5)	Remake the testAlphabedical function	Status	:	DONE (Needs Testing)
This appears to be working as intended.
6)	Create an independant sorting function	Status	:	INCOMPLETE
for when the strings are equal. send
the "head" of this new "list as well
as the "tail" adress. then sort,
and return the head and tail.
********************************************************************************************************/

#include "musicHeader.h"
//	Start Functions
//	Menu Functions
char runMenu();
void printMenu();
void printSearchMenu();								//	This function prints the Search Menu
void printAddToCollectionMenu();					//	This function controls the Input Menu
void viewCollection(COLLECTION* c);					//	This function controls the View Collection Menu
void addToCollection(COLLECTION* c);				//	This function controls the Input Menu
void searchTheCollection(COLLECTION* c);			//	This function controls the Search Menu

//	Output to Screen Functions
void textFileFormat();								//	This function outputs the text file format to the user
void printSingleCd(CDNODE* c);						//	This function prints a single album to the user
void printCdSongs(CD* x);							//	This function prints the SONG array to the user
void printByYear(COLLECTION* c);					//	This function outputs the Collection by Year Released
void printByAlbum(COLLECTION* c);					//	This function outputs the Collection by Album Name
void printByArtist(COLLECTION* c);					//	This function outputs the Collection by Artist Name
void printCollectionEntered(COLLECTION* c);			//	This function outputs the Collection by Date Entered
void collectionStatistics(COLLECTION* c);			//	This function collects data on the Collection and outputs to the user

//	Text File Output
void writeTxtFile(COLLECTION* c);

//	Sorting Functions
void sortByEntered(CDNODE* head, CDNODE* compare);	//	This function sorts the list for the byEntered chain
void sortByArtist(CDNODE* head, CDNODE* compare);	//	This function sorts the list for the byArtist chain
void sortByAlbum(CDNODE* head, CDNODE* compare);	//	This function sorts the list for the byAlbum chain
void sortByYear(CDNODE* head, CDNODE* compare);		//	This function sorts the list for the byYear chain

//	Searching Functions
void searchByAlbum(COLLECTION* c);			//	This function allows the user to search teh list for a specific Album
void searchByArtist(COLLECTION* c);			//	This function allows the user to search teh list for a specific Artist

//	Data Entry Functions
COLLECTION* buildCollection();				//	Creates the dynamic memory for the initial collection.
void enterNewCd(COLLECTION* c);				//	This function allows the user to manually input an album into the list
void enterSongs(CD* cd);					//	This function allows the user to manually input type SONGS to an album
void readTxtFile(COLLECTION* c);			//	This function allows the user to input data from a text file into the list
void saveToBinFile(COLLECTION* c);			//	This function saves the current list to a .bin file
void readFromBinFile(COLLECTION* c);		//	This function reads, and repopulates, the list from a .bin file
void initializeNextToNull(CDNODE* c);		//	This function initializes the nextBy values to NULL in a new node

//	Data Deletion Functions
void deleteCdNode(COLLECTION* head);
void deleteByArtist(COLLECTION* head, char search[]);		//	This function re-organizes the byArtist list so a node can be deleted
void deleteByAlbum(COLLECTION* head, char search[]);		//	This function re-organizes the byAlbum list so a node can be deleted
void deleteByYear(COLLECTION* head, char search[]);			//	This function re-organizes the byYear list so a node can be deleted
void deleteByEntered(COLLECTION* head, char search[]);		//	This function re-organizes the byEntered list so a node can be deleted

//	Dynamic Memory Free Functions
void freeMemory(COLLECTION* head);						//	This function Frees the memory of the list
void freeSongArray(SONG** songArray, int numSongs);		//	This function releases memory of the dynamic SONG array
// END Functions

int main(void)
{
	char menuChoice;
	COLLECTION* myCollection;

	myCollection = buildCollection();

	readFromBinFile(myCollection);

	do
	{
		menuChoice = runMenu();
		switch (menuChoice)
		{
		case '1':	// Modify Collection
			addToCollection(myCollection);
			break;
		case '2':	//	View the Collection
			viewCollection(myCollection);
			break;
		case '3':	//	Search Collection
			searchTheCollection(myCollection);
			break;
		case '4' :	//	Print to text file 
			writeTxtFile(myCollection);
			break;
		case 'X':	//	Exit
			CLS;
			saveToBinFile(myCollection);
			freeMemory(myCollection);
			printf("\n\n\tThank You For Using the Program!\n\n\t");
			PAUSE;
			return 0;
			break;
		default:
			printf("\n\tEnter a Valid Option\n\t");
			PAUSE;
		}
	} while (menuChoice != 'X');
}	//	END Main


/*******************************************************************************************************
Function		:
Data Required	:
Data Returned	:
Purpose			:
********************************************************************************************************/


/*******************************************************************************************************
Function		:	printMenu
Data Required	:	NONE
Data Returned	:	NONE
Purpose			:	Outputs the menu to the user
********************************************************************************************************/
void printMenu()
{
	CLS;
	printf("\n\n\t*********************************************************"
		"\n\t*							*"
		"\n\t*		  My Music Collection			*"
		"\n\t*							*"
		"\n\t*	'1'	:	Modify Collection		*"
		"\n\t*							*"
		"\n\t*	'2'	:	View Collection			*"
		"\n\t*							*"
		"\n\t*	'3'	:	Search Collection		*"
		"\n\t*							*"
		"\n\t*	'4'	:	Print Text File			*"
		"\n\t*							*"
		"\n\t*	'X'	:	Exit				*"
		"\n\t*							*"
		"\n\t*********************************************************"
		"\n\tEntry	:   ");
	return;
}	//	END printMenu


/*******************************************************************************************************
Function		:	printSearchMenu
Data Required	:	NONE
Data Returned	:	NONE
Purpose			:	Outputs the search menu to the user
********************************************************************************************************/
void printSearchMenu()
{
	CLS;
	printf("\n\n\t*********************************************************"
		"\n\t*							*"
		"\n\t*	'1'	:	Search for Album		*"
		"\n\t*							*"
		"\n\t*	'2'	:	Search for Artist		*"
		"\n\t*							*"
		"\n\t*	'R'	:	Return to Main Menu		*"
		"\n\t*							*"
		"\n\t*********************************************************"
		"\n\tEntry	:   ");
	return;
}	//	END printSearchMenu


/*******************************************************************************************************
Function		:	addToCollection
Data Required	:	pointer to the head of the collection
Data Returned	:	NONE
Purpose			:	Controls the menu which is used to input data into the list
********************************************************************************************************/
void searchTheCollection(COLLECTION* c)
{
	char result;
	printSearchMenu();
	result = scanCHAR();
	if (islower(result))
		result = toupper(result);
	switch (result)
	{
	case '1':	// Search for an Album
		searchByAlbum(c);
		break;
	case '2':	//	Search by Artist
		searchByArtist(c);
		break;
	case 'R':	//	Return to Main Menu
		break;
	default:
		printf("\n\tInvalid Entry\n\n\t");
		PAUSE;
		break;
	}
	return;
}	//	END	searchTheCollection

/*******************************************************************************************************
Function		:	viewCollectionMenu
Data Required	:	NONE
Data Returned	:	NONE
Purpose			:	Outputs the
********************************************************************************************************/
void viewCollectionMenu()
{
	CLS;
	printf("\n\n\t*********************************************************"\
		"\n\t*							*"
		"\n\t*	'1'	:	View by Date Entered		*"
		"\n\t*							*"
		"\n\t*	'2'	:	View by Artist			*"
		"\n\t*							*"
		"\n\t*	'3'	:	View by Album			*"
		"\n\t*							*"
		"\n\t*	'4'	:	View by Year			*"
		"\n\t*							*"
		"\n\t*	'5'	:	Collection Statistics		*"
		"\n\t*							*"
		"\n\t*	'R'	:	Return to Main Menu		*"
		"\n\t*							*"
		"\n\t*********************************************************"
		"\n\tEntry	:   ");
	return;
}	// END viewCollectionMenu


/**************************************************************************
Function		:	runMenu
Data Needed		:	NONE
Data Returned	:	char : represents the users menu choice
Purpose			:	To run the menu, and allow the user to make different
choices in the menu.
***************************************************************************/
char runMenu()
{
	char result;
	printMenu();
	result = scanCHAR();
	if (islower(result))
		result = toupper(result);
	return result;
} // END runMenu


/*******************************************************************************************************
Function		:	addToCollection
Data Required	:	pointer to the head of the collection
Data Returned	:	NONE
Purpose			:	Controls the menu which is used to input data into the list
********************************************************************************************************/
void addToCollection(COLLECTION* c)
{
	char result;
	printAddToCollectionMenu();
	result = scanCHAR();
	if (islower(result))
		result = toupper(result);
	switch (result)
	{
	case '1':	//	Enter a New CD
		enterNewCd(c);
		break;
	case '2':	//	Enter a New File
		readTxtFile(c);
		break;
	case '3':	//	Displays the format for the text file to the user
		textFileFormat();
		break;
	case '4':	//	Delete An Album
		deleteCdNode(c);
		break;
	case 'R':
		break;
	default:
		printf("\n\tInvalid Entry\n\n\t");
		PAUSE;
		break;
	}
	return;
}	//	END	addToCollection


/*******************************************************************************************************
Function		:	addMenu
Data Required	:	NONE
Data Returned	:	NONE
Purpose			:	Displays the menu used to input data into the list
********************************************************************************************************/
void printAddToCollectionMenu()
{
	CLS;
	printf("\n\n\t*********************************************************"
		"\n\t*							*"
		"\n\t*	'1'	:	Enter an Album			*"
		"\n\t*							*"
		"\n\t*	'2'	:	Scan a Text File		*"
		"\n\t*							*"
		"\n\t*	'3'	:	View Text File Format		*"
		"\n\t*							*"
		"\n\t*	'4'	:	Delete an Album			*"
		"\n\t*							*"
		"\n\t*	'R'	:	Return to Main Menu		*"
		"\n\t*							*"
		"\n\t*********************************************************"
		"\n\tEntry	:	");
	return;
}	//	END	addMenu


/*******************************************************************************************************
Function		:	textFileFormat
Data Required	:	NONE
Data Returned	:	NONE
Purpose			:	Displays how the text files should be formatted to import data into the program

Album Name : Name
Artist : Name
Year Released : Year
Songs :
#Songs
Song1
Song2
********************************************************************************************************/
void textFileFormat()
{
	CLS;
	printf("\n\n\tExample Text File Formating."
		"\n\n\tNOTE: The left column is very important."
		"\n\t\tInclude the ':' when creating a file"
		"\n\t _______________________________________________"
		"\n\t|						|"
		"\n\t|Album List:					|"
		"\n\t|Album Name: Album Name Here			|"
		"\n\t|Artist: Artist Name Here			|"
		"\n\t|Year: 2016 (example numerical year)		|"
		"\n\t|Songs: 3 (example numerical number of songs)	|"
		"\n\t|Song Name 1					|"
		"\n\t|Song Name 2					|"
		"\n\t|Song Name 3					|"
		"\n\t|						|"
		"\n\t|Album Name: Next Name Here			|"
		"\n\t|Artist: Next Artist Name			|"
		"\n\t|Year: 2015					|"
		"\n\t|Songs: 2 					|"
		"\n\t|Song Name 1					|"
		"\n\t|Song Name 2					|"
		"\n\t|						|"
		"\n\t|						|"
		"\n\t|						|"
		"\n\t|_______________________________________________|"
		"\n\n\tNOTE: Make Sure the entered number of names is equal"
		"\n\t\tto the number of Songs listed"
		"\n\n\t");

	PAUSE;
	return;
}

/*******************************************************************************************************
Function		:	searchByAlbum
Data Required	:	pointer to the head of the COLLECTION
Data Returned	:	NONE
Purpose			:	To search, and find and album. Then displaying the tracks
********************************************************************************************************/
void searchByAlbum(COLLECTION* c)
{
	CDNODE* cWalker = c->head->nextByAlbum;
	char albumSearch[50];
	char foundFlag = 'N';

	CLS;
	//printByAlbum(c);
	printf("\n\n\tEnter An Album Name : ");
	scanf(" %[^\n]", albumSearch);

	while (cWalker != NULL)
	{
		if (!strcmp(albumSearch, cWalker->currentCd.albumName))
		{
			CLS;
			printCdSongs(&cWalker->currentCd);
			foundFlag = 'Y';
			break;
		}
		cWalker = cWalker->nextByAlbum;
	}
	if (foundFlag == 'N')
		printf("\n\n\tNO RESULTS FOUND\n\n\t");
	PAUSE;
	return;
}	//	END  searchByAlbum


/*******************************************************************************************************
Function		:	searchByArtist
Data Required	:	pointer to the head of the COLLECTION
Data Returned	:	NONE
Purpose			:	To search, and find and album. Then displaying the tracks
********************************************************************************************************/
void searchByArtist(COLLECTION* c)
{
	CDNODE* cWalker = c->head->nextByArtist;
	char artistSearch[50];
	char foundFlag = 'N';

	CLS;
	printf("\n\n\tEnter An Artist Name : ");
	scanf(" %[^\n]", artistSearch);

	while (cWalker != NULL)
	{
		if (!strcmp(artistSearch, cWalker->currentCd.artist))
		{
			CLS;
			printf("\n\n\tDisplaying Results for : %s", artistSearch);
			printCdSongs(&cWalker->currentCd);
			foundFlag = 'Y';
			break;
		}
		cWalker = cWalker->nextByArtist;
	}
	if (foundFlag == 'N')
		printf("\n\n\tNO RESULTS FOUND\n\n\t");
	PAUSE;
	return;
}	//	END  searchByArtist

/*******************************************************************************************************
Function		:	viewCollection
Data Required	:	pointer to the head of the collection
Data Returned	:	NONE
Purpose			:	This function runs a submenu to allow the user to view the entire collection
using various sorting methods
********************************************************************************************************/
void viewCollection(COLLECTION* c)
{
	char menuChoice;

	do
	{
		viewCollectionMenu();
		menuChoice = scanCHAR();

		if (islower(menuChoice))
			menuChoice = toupper(menuChoice);

		switch (menuChoice)
		{
		case '1':	//	View by Entry Date
			CLS;
			printCollectionEntered(c);
			printf("\n\t");
			PAUSE;
			break;
		case '2':	//	View by Artist
			CLS;
			printByArtist(c);
			printf("\n\t");
			PAUSE;
			break;
		case '3':	//	View by Album
			CLS;
			printByAlbum(c);
			printf("\n\t");
			PAUSE;
			break;
		case '4':	//	View by Date
			CLS;
			printByYear(c);
			printf("\n\t");
			PAUSE;
			break;
		case '5':	//	View Statistics
			collectionStatistics(c);
			break;
		case 'R':	//	Return to Main Menu
			break;
		default:
			printf("\n\tEnter a Valid Option\n\t");
			PAUSE;
		}
	} while (menuChoice != 'R');
	return;
}	//	END viewCollection

/*******************************************************************************************************
Function		:	printCd
Data Required	:	variable of Type CD
Data Returned	:	NONE
Purpose			:	To output induvidual songs stored within the CD array to the user
********************************************************************************************************/
void printCdSongs(CD* x)
{
	int i;
	char result;
	if (x->numSongs)
	{
		printf("\n\n\tAlbum Name	: %s", x->albumName);
		printf("\n\tYear Released	: %d", x->year);
		printf("\n\tDate Added	: ");
		printf(ctime(&x->dateImported));
		printf("\n\tTrack\t\tSong Name");
		for (i = 0; i < x->numSongs; i++)
			printf("\n\t%5d\t\t%s", x->songs[i]->trackNum, x->songs[i]->songName);
		printf("\n\t");
	}
	else
	{
		printf("\n\n\tNo Track Data Avaliable for : %s\n"
			"\n\tWould you like to Add Songs to the Album? (Y/N) : ", x->albumName);
		result = scanCHAR();
		if (islower(result))
			result = toupper(result);
		if (result == 'Y')
		{
			printf("\n\tHow many tracks to add? : ");
			do
			{
				x->numSongs = scanINT();
				if (x->numSongs < 0)
				{
					printf("\n\tNumber of Tracks cannot be Negative\n\t");
					PAUSE;
				}
			} while (x->numSongs < 0);
			enterSongs(x);
		}

	}
	return;
}	//	END printCd


/*******************************************************************************************************
Function		:	buildCollection
Data Required	:	NONE
Data Returned	:	A pointer of type COLLECTION
Purpose			:	To create the intital conditions for our COLLECTION variable in main
********************************************************************************************************/
COLLECTION* buildCollection()
{
	COLLECTION* temp;

	temp = malloc(sizeof(COLLECTION));
	temp->head = malloc(sizeof(CDNODE));
	temp->numCds = 0;
	initializeNextToNull(temp->head);

	return temp;
}	//	END buildCollection


/*******************************************************************************************************
Function		:	enterNewCd
Data Required	:	pointer to the head
Data Returned	:	NONE
Purpose			:	To enter a new CD and add it to the list
********************************************************************************************************/
void enterNewCd(COLLECTION* c)
{
	CDNODE* newNode;

	CLS;
	newNode = malloc(sizeof(CDNODE));
	printf("\n\tAlbum Name\t\t:\t");
	scanf(" %[^\n]", newNode->currentCd.albumName);
	printf("\tArtist Name\t\t:\t");
	scanf(" %[^\n]", newNode->currentCd.artist);
	printf("\n\tYear Released\t");
	printf("\n\tEnter 0 for Unknown\t:\t");
	newNode->currentCd.year = scanINT();
	if (newNode->currentCd.year == 0)
		newNode->currentCd.year = UNKNOWNYEAR;
	printf("\n\tNumber of Songs?");
	printf("\n\tEnter 0 for Unknown\t:\t");
	newNode->currentCd.numSongs = scanINT();
	if (newNode->currentCd.numSongs)
	{
		enterSongs(&newNode->currentCd);
	}
	else
		newNode->currentCd.songs = NULL;

	newNode->currentCd.dateImported = time(NULL);

	initializeNextToNull(newNode);

	c->numCds++;
	sortByArtist(c->head, newNode);
	sortByAlbum(c->head, newNode);
	sortByYear(c->head, newNode);
	sortByEntered(c->head, newNode);
	return;
}	//	END enterNewCd

/*******************************************************************************************************
Function		:	enterSongs
Data Required	:	pointer of type CDNODE, points to the NODE we wish to add data to
Data Returned	:	NONE
Purpose			:	To allow the user to add additional information to the album
********************************************************************************************************/
void enterSongs(CD* cd)
{
	int i;

	cd->songs = malloc(sizeof(SONG*)*cd->numSongs);

	printf("\n\tEnter Track\n");
	for (i = 0; i < cd->numSongs; i++)
	{
		cd->songs[i] = malloc(sizeof(SONG)); // allocates the space for each song name
		printf("\t%d\t:\t", i + 1);
		scanf(" %[^\n]", cd->songs[i]->songName); // scans each song name
		cd->songs[i]->trackNum = i + 1;
	}
	return;
}	// END enterSongs


/*******************************************************************************************************
Function		:	readTxtFile
Data Required	:	Pointer to the head of the Collection, A text file
Data Returned	:	NONE
Purpose			:	This function is fairly complex.
Goal			:	This function will read in text files, and populate the data contained to our list
We will then call functions to sort the list in various ways.
the file format is as shown below.

Format for the text file

Album Name: Name
Artist: Name
Year Released: Year
Songs:
#Songs
Song1
Song2

NOTE	:	Long term goal may be to not need an int containing the number of songs
For the moment there is no checking mechanism for if the numSongs is >
the number of inputted strings.
********************************************************************************************************/
void readTxtFile(COLLECTION* c)
{
	CDNODE* cdWalker = c->head;
	CDNODE* temp;
	int albumCount = 0;
	char fileName[50] = "test.txt";
	FILE* txtStream;
	char loopFlag;
	char buffer[50];
	int i;

	CLS;
	do
	{
		loopFlag = 'Y';
		printf("\n\n\tEnter the file location : ");
		scanf(" %[^\n]", fileName);
		txtStream = fopen(fileName, "r");
		if (txtStream == NULL)
		{
			printf("\n\t%s NOT FOUND\n\tTry Again? : (Y/N)\n\t", fileName);
			loopFlag = scanCHAR();
			if (islower(loopFlag))
				loopFlag = toupper(loopFlag);

			if (loopFlag != 'Y')
				return;
		}
	} while (txtStream == NULL);

	fscanf(txtStream, " %[^A-Za-z]", buffer);	//	This deletes the annoying beginning of file character
	while (!feof(txtStream))
	{
		fscanf(txtStream, " %s", buffer);	//	checks for "Album Name:" to determine what data we are importing
		if (!strcmp(buffer, "Album:"))
		{
			temp = malloc(sizeof(CDNODE));
			fscanf(txtStream, " %[^\n]", temp->currentCd.albumName);	//	scans the album name

			fscanf(txtStream, " %s", buffer);	//	checks for "Artist:" to determine what data we are importing
			if (!strcmp(buffer, "Artist:"))
				fscanf(txtStream, " %[^\n]", temp->currentCd.artist);	//	scans the band/artist name
			else
				strcpy(temp->currentCd.albumName, "Unknown");

			fscanf(txtStream, " %s", buffer);	//	checks for "Year Released:" to determine what data we are importing
			if (!strcmp(buffer, "Year:"))
				fscanf(txtStream, "%d", &temp->currentCd.year);		//scaans the year
			else
				temp->currentCd.year = 0;

			fscanf(txtStream, "%s", buffer); 	// checks for "Songs:" to determine what data we are importing
			if (!strcmp(buffer, "Songs:"))
			{
				fscanf(txtStream, "%d", &temp->currentCd.numSongs); // scans the number of songs
				temp->currentCd.songs = malloc(sizeof(SONG*)*temp->currentCd.numSongs); // allocates space for the song pointers
				for (i = 0; i < temp->currentCd.numSongs; i++)
				{
					temp->currentCd.songs[i] = malloc(sizeof(SONG)); // allocates the space for each song name
					fscanf(txtStream, " %[^\n]", temp->currentCd.songs[i]->songName); // scans each song name
					temp->currentCd.songs[i]->trackNum = i + 1;
				}
			}
			else
			{
				temp->currentCd.songs = NULL;
				temp->currentCd.numSongs = 0;
			}
			temp->currentCd.dateImported = time(NULL);

			c->numCds++;
			albumCount++;

			initializeNextToNull(temp);

			sortByArtist(c->head, temp);
			sortByAlbum(c->head, temp);
			sortByYear(c->head, temp);
			sortByEntered(c->head, temp);
		}
	}
	fclose(txtStream);
	printf("\n\n\t**************************************"
		"\n\t* Successfully Imported %4d Records *"
		"\n\t**************************************\n\n\t", albumCount);
	PAUSE;
	return;
}	// END readTxtFile


/*******************************************************************************************************
Function		:	writeTxtFile
Data Required	:	Pointer to the head of the Collection
Data Returned	:	A text file
Purpose			:	To export the data we have stored to a text file for the user
********************************************************************************************************/
void writeTxtFile(COLLECTION* c)
{
	CDNODE* cdWalker = c->head->nextByEntered;
	FILE* txtStream;
	char fileName[50] = "musicTextFile.txt";
	char loopFlag;
	int i;

	CLS;
	do
	{
		loopFlag = 'Y';
		printf("\n\n\tEnter the location and name to write the file : ");
		scanf(" %[^\n]", fileName);
		txtStream = fopen(fileName, "w");
		if (txtStream == NULL)
		{
			printf("\n\t%s INVALID FILE LOCATION/NAME\n\tTry Again? : (Y/N)\n\t", fileName);
			loopFlag = scanCHAR();
			if (islower(loopFlag))
				loopFlag = toupper(loopFlag);

			if (loopFlag != 'Y')
				return;
		}
	} while (txtStream == NULL);

	fprintf(txtStream, "CD LIST\n");
	while (cdWalker != NULL)
	{
		fprintf(txtStream, "Album: ");
		fprintf(txtStream,"%s\n", cdWalker->currentCd.albumName);
		fprintf(txtStream, "Artist: ");
		fprintf(txtStream, "%s\n", cdWalker->currentCd.artist);
		fprintf(txtStream, "Year: ");
		fprintf(txtStream, "%d\n", cdWalker->currentCd.year);
		fprintf(txtStream, "Songs: %d\n", cdWalker->currentCd.numSongs);
		for (i = 0; i < cdWalker->currentCd.numSongs; i++)
		{
			fprintf(txtStream, "%s\n", cdWalker->currentCd.songs[i]->songName);
		}
		cdWalker = cdWalker->nextByEntered;
	}

	fclose(txtStream);
	return;
}	//	END writeTextFile


/*******************************************************************************************************
Function		:	printSingleCd
Data Required	:	Pointer to a variable type CDNODE
Data Returned	:	NONE
Purpose			:	To output the data of a single cd (minus songs)
********************************************************************************************************/
void printSingleCd(CDNODE* c)
{
	printf("\n\tAlbum Name\t\t:\t%s", c->currentCd.albumName);
	printf("\n\tArtist\t\t\t:\t%s", c->currentCd.artist);
	if (c->currentCd.year != 9999)
		printf("\n\tYear Released\t\t:\t%d", c->currentCd.year);
	else
		printf("\n\tYear Released\t\t:\tUnknown");
	if (c->currentCd.numSongs)
		printf("\n\tNumber of Songs\t\t:\t%d", c->currentCd.numSongs);
	else
		printf("\n\tNumber of Songs\t\t:\tUnknown");
	printf("\n\tDate Imported\t\t:\t");
	printf(ctime(&c->currentCd.dateImported));
	printf("\t");
	return;
}	//	END printSingleCd


/*******************************************************************************************************
Function		:	sortByEntered
Data Required	:	Pointer to the head of the list, and the pointer to the node to compare
Data Returned	:	NONE
Purpose			:	To insert the node at the end of the list (also where by time entered)
********************************************************************************************************/
void sortByEntered(CDNODE* head, CDNODE* compare)
{
	CDNODE* current = head;

	if (head->nextByEntered == NULL)
	{
		head->nextByEntered = compare;
	}
	else
	{
		while (current->nextByEntered != NULL)
			current = current->nextByEntered;

		current->nextByEntered = compare;
	}
	return;
} // END sortByEntered


/*******************************************************************************************************
Function		:	printCollectionEntered
Data Required	:	Pointer to the Head of the list
Data Returned	:	NONE
Purpose			:	To output the entire list by Date Entered
********************************************************************************************************/
void printCollectionEntered(COLLECTION* c)
{
	CDNODE* cWalker = c->head->nextByEntered;

	printf("\n\t*************************************************"
		"\n\t*\tPrinting Numerically by Input Date\t*"
		"\n\t*************************************************\n\t");
	while (cWalker != NULL)		//	Will loop until the last pointer is NULL
	{
		printSingleCd(cWalker);
		cWalker = cWalker->nextByEntered;	// Increments the list
	}
	return;
}	// END printCollectionEntered


/*******************************************************************************************************
Function		:	sortByArtist
Data Required	:	Pointer to the head of the list, and the pointer to the node to compare
Data Returned	:	NONE
Purpose			:	To insert the node we are comparing into the list alphabedically by Artist/Band
********************************************************************************************************/
void sortByArtist(CDNODE* head, CDNODE* compare)
{
	CDNODE* current = head;
	CDNODE* previous;

	if (head->nextByArtist == NULL)
	{
		head->nextByArtist = compare;
	}
	else
	{
		previous = current;
		current = current->nextByArtist;
		do
		{
			if (testAlphaOrder(current->currentCd.artist, compare->currentCd.artist) > 0)	// This tests which comes first alphabedically based on the first letter
			{
				//	Places the node in the correct location
				previous->nextByArtist = compare;
				compare->nextByArtist = current;
				return;
			}
			//			if (!strcmp(current->currentCd.artist, compare->currentCd.artist))
			//			{
			//				here i'd like to sort again if the artist is the same by alphabetical ablbum
			//			}

			previous = current;
			current = current->nextByArtist;
		} while (current != NULL);
		if (previous->nextByArtist == NULL)
			previous->nextByArtist = compare;
	}
	return;
}	// END sortByArtist


/*******************************************************************************************************
Function		:	printByArtist
Data Required	:	Pointer to the Head of the list
Data Returned	:	NONE
Purpose			:	To output the entire list alpbabedically by artist
********************************************************************************************************/
void printByArtist(COLLECTION* c)
{
	CDNODE* cWalker = c->head->nextByArtist;

	printf("\n\t*************************************************"
		"\n\t*\tPrinting Alphabedically by Artist Namee\t*"
		"\n\t*************************************************\n\t");
	while (cWalker != NULL)		//	Will loop until the last pointer is NULL
	{
		printSingleCd(cWalker);
		cWalker = cWalker->nextByArtist;	// Increments the list
	}
	return;
}	// END printByArtist


/*******************************************************************************************************
Function		:	sortByAlbum
Data Required	:	Pointer to the head of the list, and the pointer to the node to compare
Data Returned	:	NONE
Purpose			:	To insert the node we are comparing into the list alphabedically by Album
********************************************************************************************************/
void sortByAlbum(CDNODE* head, CDNODE* compare)
{
	CDNODE* current = head;
	CDNODE* previous;

	if (head->nextByAlbum == NULL)
	{
		head->nextByAlbum = compare;
	}
	else
	{
		previous = current;
		current = current->nextByAlbum;
		do
		{
			if (testAlphaOrder(current->currentCd.albumName, compare->currentCd.albumName) > 0)		// This tests which comes first alphabedically based on the first letter
			{
				//	Places the node in the correct location
				previous->nextByAlbum = compare;
				compare->nextByAlbum = current;
				return;
			}
			previous = current;
			current = current->nextByAlbum;
		} while (current != NULL);
		if (previous->nextByAlbum == NULL)
			previous->nextByAlbum = compare;
	}
	return;
}	// END sortByAlbum


/*******************************************************************************************************
Function		:	printByAlbum
Data Required	:	Pointer to the Head of the list
Data Returned	:	NONE
Purpose			:	To output the entire list alphabedically by album name
********************************************************************************************************/
void printByAlbum(COLLECTION* c)
{
	CDNODE* cWalker = c->head->nextByAlbum;

	printf("\n\t*************************************************"
		"\n\t*\tPrinting Alphabedically by Album Name\t*"
		"\n\t*************************************************\n\t");
	while (cWalker != NULL)		//	Will loop until the last pointer is NULL
	{
		printSingleCd(cWalker);
		cWalker = cWalker->nextByAlbum;	// Increments the list
	}
	return;
}	// END printByAlbum


/*******************************************************************************************************
Function		:	sortByYear
Data Required	:	Pointer to the head of the list, and the pointer to the node to compare
Data Returned	:	NONE
Purpose			:	To insert the node we are comparing into the list numerically by Year
********************************************************************************************************/
void sortByYear(CDNODE* head, CDNODE* compare)
{
	CDNODE* current = head;
	CDNODE* previous;

	if (head->nextByYear == NULL)
	{
		head->nextByYear = compare;
	}
	else
	{
		previous = current;
		current = current->nextByYear;
		do
		{
			if (current->currentCd.year > compare->currentCd.year)	// This tests which comes first numerically by year
			{
				//	Places the node in the correct location
				previous->nextByYear = compare;
				compare->nextByYear = current;
				return;
			}
			previous = current;
			current = current->nextByYear;
		} while (current != NULL);
		if (previous->nextByYear == NULL)
			previous->nextByYear = compare;
	}
	return;
}	// END sortByYear


/*******************************************************************************************************
Function		:	printByYear
Data Required	:	Pointer to the Head of the list
Data Returned	:	NONE
Purpose			:	To output the entire list numerically by year
********************************************************************************************************/
void printByYear(COLLECTION* c)
{
	CDNODE* cWalker = c->head->nextByYear;

	printf("\n\t*************************************************"
		"\n\t*\tPrinting Numerically by Release Year\t*"
		"\n\t*************************************************\n\t");
	while (cWalker != NULL)		//	Will loop until the last pointer is NULL
	{
		printSingleCd(cWalker);
		cWalker = cWalker->nextByYear;	// Increments the list
	}
	return;
}	// END printByArtist


/*******************************************************************************************************
Function		:	initializeNextToNull
Data Required	:	Pointer to a CD Node
Data Returned	:	NONE
Purpose			:	initializes the pointers for our list to NULL
********************************************************************************************************/
void initializeNextToNull(CDNODE* c)
{
	c->nextByAlbum = NULL;
	c->nextByArtist = NULL;
	c->nextByYear = NULL;
	c->nextByEntered = NULL;
	return;
}	//	END initializeNextToNull


/**************************************************************************
Function			:	freeMemory
Data Needed			:	Pointer to the head of the list
Data Returned		:	NONE
Purpose				:	To free dynamically allocated memeory
***************************************************************************/
void freeMemory(COLLECTION* head)
{
	CDNODE* temp;
	CDNODE* cWalker = head->head->nextByEntered;

	while (cWalker->nextByEntered != NULL)
	{
		temp = cWalker;
		cWalker = cWalker->nextByEntered;

		freeSongArray(temp->currentCd.songs, temp->currentCd.numSongs);
		free(temp);
	}

	free(head->head);
	free(head);

	return;
}	//	freeMemory


/**************************************************************************
Function			:	freeSongArray
Data Needed			:	Pointer to the SONG pointer
Data Returned		:	NONE
Purpose				:	To free dynamically allocated memory of a SONG** type
***************************************************************************/
void freeSongArray(SONG** songArray, int numSongs)
{
	int i;
	for (i = 0; i < numSongs; i++)
		free(songArray[i]);

	free(songArray);

	return;
}	//	freeMemory


/**************************************************************************
Function			:	collectionStatistics
Data Needed			:	pointer to the head of the collection
Data Returned		:	NONE
Purpose				:	To output the numerical statistics of what is in the
collection.
1) number albums
2) number artists
3) number songs
***************************************************************************/
void collectionStatistics(COLLECTION* c)
{
	int totalSongs = 0;
	int numArtists = 0;
	CDNODE* cWalker;
	CDNODE* next;

	CLS;
	printf("\n\n\t*********************************"
		"\n\t*        Collection Data        *"
		"\n\t*********************************"
		"\n\t* Number of Albums\t: %5d *", c->numCds);

	cWalker = c->head->nextByArtist;	// sets cWalker to the first adress
	while (cWalker != NULL)
	{
		totalSongs += cWalker->currentCd.numSongs;
		cWalker = cWalker->nextByArtist;
	}
	printf("\n\t* Number of Songs\t: %5d *", totalSongs);

	cWalker = c->head->nextByArtist;	// sets cWalker to the first adress
	if (cWalker != NULL)
	{
		if (strcmp(cWalker->currentCd.artist, "Unknown"))
			numArtists += 1;
		while (cWalker->nextByArtist != NULL)
		{
			next = cWalker->nextByArtist;
			if (strcmp(cWalker->currentCd.artist, next->currentCd.artist))
				numArtists += 1;
			cWalker = cWalker->nextByArtist;
		}
	}
	printf("\n\t* Number of Artists\t: %5d *", numArtists);
	printf("\n\t*********************************");

	printf("\n\n\t");
	PAUSE;

}	//	END	collectionStatistics


/*******************************************************************************************************
Function		:	saveToBinFile
Data Required	:	pointer to the head of the list
Data Returned	:	NONE
Purpose			:	To save the current list in a binary file
********************************************************************************************************/
void saveToBinFile(COLLECTION* c)
{
	CDNODE* pWalker = c->head->nextByEntered;
	FILE* cdPtr;
	int j;

	cdPtr = fopen("cdBinFile.bin", "wb");
	if (cdPtr == NULL)
	{
		CLS;
		printf("\n\t*********************************"
			"\n\t*	ERROR PRINTING TO DISK	*"
			"\n\t*********************************");
		PAUSE;
		return;
	}

	fwrite(&c->numCds, sizeof(int), 1, cdPtr);	// writes the album counter

	while (pWalker != NULL)
	{
		fwrite(&pWalker->currentCd, sizeof(CD), 1, cdPtr);	// writes the album
		for (j = 0; j < pWalker->currentCd.numSongs; j++)
		{
			fwrite(pWalker->currentCd.songs[j], sizeof(SONG), 1, cdPtr);	//	writes the array of songs
		}
		pWalker = pWalker->nextByEntered;
	}
	fclose(cdPtr);
	return;
}	//	END saveToBinFile

/*******************************************************************************************************
Function		:	readFromBinFile
Data Required	:	pointer to the head of the list
Data Returned	:	NONE
Purpose			:	To save the current list in a binary file
********************************************************************************************************/
void readFromBinFile(COLLECTION* c)
{
	CDNODE* pWalker = c->head;
	FILE* cdPtr;
	int i, j;

	cdPtr = fopen("cdBinFile.bin", "rb");
	if (cdPtr == NULL)
	{
		CLS;
		printf("\n\t****************************"
			"\n\t*     NO PRIOR ENTRIES     *"
			"\n\t****************************\n\n\t");
		PAUSE;
		return;
	}

	fread(&c->numCds, sizeof(int), 1, cdPtr);	// writes the cd counter
	for (i = 0; i < c->numCds; i++)
	{
		pWalker->nextByEntered = malloc(sizeof(CDNODE));
		pWalker = pWalker->nextByEntered;

		fread(&pWalker->currentCd, sizeof(CD), 1, cdPtr);	// writes the cd

		pWalker->currentCd.songs = malloc(sizeof(SONG*)*pWalker->currentCd.numSongs); // allocates space for the song pointers
		for (j = 0; j < pWalker->currentCd.numSongs; j++)
		{
			pWalker->currentCd.songs[j] = malloc(sizeof(SONG)); // allocates the space for each song name
			fread(pWalker->currentCd.songs[j], sizeof(SONG), 1, cdPtr);	//	writes the array of songs
		}

		initializeNextToNull(pWalker);

		sortByArtist(c->head, pWalker);
		sortByAlbum(c->head, pWalker);
		sortByYear(c->head, pWalker);
		//sortByEntered(c->head, pWalker);

		//	pWalker = pWalker->nextByEntered;
	}


	fclose(cdPtr);
	printf("\n\n\tSuccessfully Loaded %d Albums into the Collection", c->numCds);
	return;
}	//	END readFromBinFile


/*******************************************************************************************************
Function		:	deleteCdNode
Data Required	:	pointer to the head of the list
Data Returned	:	NONE
Purpose			:	Allows the user to delete an entry
********************************************************************************************************/
void deleteCdNode(COLLECTION* head)
{
	char test[50];
	CLS;
	printf("\n\n\tEnter an Album to Remove from the Collection : ");
	scanf(" %[^\n]", test);


	deleteByArtist(head, test);
	deleteByAlbum(head, test);
	deleteByYear(head, test);
	deleteByEntered(head, test);

	return;
}	// END	deleteCdNode


/*******************************************************************************************************
Function		:	deleteByEntered
Data Required	:	pointer to the head of the list, stringName of the item to delete
Data Returned	:	NONE
Purpose			:	To delete a node , and re-organize the nextByEntered chain in the list
********************************************************************************************************/
void deleteByEntered(COLLECTION* head, char search[])
{
	CDNODE* enterWalker = head->head->nextByEntered;
	CDNODE* previous = head->head;

	do
	{
		if (!strcmp(search, enterWalker->currentCd.albumName))
		{
			if (enterWalker == head->head->nextByEntered)
			{
				previous = head->head->nextByEntered;
				head->head->nextByEntered = enterWalker->nextByEntered;
			}
			else
			{
				previous->nextByEntered = enterWalker->nextByEntered;
			}
			freeSongArray(enterWalker->currentCd.songs, enterWalker->currentCd.numSongs);
			free(enterWalker);
			head->numCds -= 1;
			return;
		}
		previous = enterWalker;
		enterWalker = enterWalker->nextByEntered;
	} while (enterWalker != NULL);

	return;
}	//	END deleteByArtist


/*******************************************************************************************************
Function		:	deleteByArtist
Data Required	:	pointer to the head of the list, stringName of the item to delete
Data Returned	:	NONE
Purpose			:	To delete a node , and re-organize the nextByArtist chain in the list
********************************************************************************************************/
void deleteByArtist(COLLECTION* head, char search[])
{
	CDNODE* artistWalker = head->head;
	CDNODE* previous = head->head;

	do
	{
		if (!strcmp(search, artistWalker->currentCd.albumName))
		{
			if (artistWalker == head->head->nextByArtist)
			{
				previous = head->head->nextByArtist;
				head->head->nextByArtist = artistWalker->nextByArtist;;
			}
			else
			{
				previous->nextByArtist = artistWalker->nextByArtist;
			}
			return;
		}
		previous = artistWalker;
		artistWalker = artistWalker->nextByArtist;
	} while (artistWalker != NULL);

	return;
}	//	END deleteByArtist


/*******************************************************************************************************
Function		:	deleteByAlbum
Data Required	:	pointer to the head of the list, stringName of the item to delete
Data Returned	:	NONE
Purpose			:	To delete a node , and re-organize the nextByAlbum chain in the list
********************************************************************************************************/
void deleteByAlbum(COLLECTION* head, char search[])
{
	CDNODE* albumWalker = head->head;
	CDNODE* previous = head->head;

	do
	{
		if (!strcmp(search, albumWalker->currentCd.albumName))
		{
			if (albumWalker == head->head->nextByAlbum)
			{
				previous = head->head->nextByAlbum;
				head->head->nextByAlbum = albumWalker->nextByAlbum;
			}
			else
			{
				previous->nextByAlbum = albumWalker->nextByAlbum;
			}
			return;
		}
		previous = albumWalker;
		albumWalker = albumWalker->nextByAlbum;
	} while (albumWalker != NULL);

	return;
}	//	END deleteByAlbum


/*******************************************************************************************************
Function		:	deleteByYear
Data Required	:	pointer to the head of the list, stringName of the item to delete
Data Returned	:	NONE
Purpose			:	To delete a node , and re-organize the nextByYear chain in the list
********************************************************************************************************/
void deleteByYear(COLLECTION* head, char search[])
{
	CDNODE* yearWalker = head->head;
	CDNODE* previous = head->head;

	do
	{
		if (!strcmp(search, yearWalker->currentCd.albumName))
		{
			if (yearWalker == head->head->nextByYear)
			{
				previous = head->head->nextByYear;
				head->head->nextByYear = yearWalker->nextByYear;
			}
			else
			{
				previous->nextByYear = yearWalker->nextByYear;
			}
			return;
		}
		previous = yearWalker;
		yearWalker = yearWalker->nextByYear;
	} while (yearWalker != NULL);

	return;
}	//	END deleteByYear