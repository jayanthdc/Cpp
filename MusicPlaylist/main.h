/*
 * main.h
 *
 *  Created on: Aug 9, 2020
 *      Author: JAYANTH
 */

#ifndef MAIN_H_
#define MAIN_H_

typedef enum
{
	VALID,
	QUIT
}status_t;

//Function Declaration
void display(const list<CSong> &Playlist);
void addSong(list<CSong> &Playlist , const CSong &Newsong);
void printMenu();
status_t getUserInput( char &Input);
void defaultPlaylist(  list<CSong> &Playlist);



#endif /* MAIN_H_ */
