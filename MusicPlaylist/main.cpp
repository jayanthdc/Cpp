/**
 * @section License
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017, Jayanth Chidanand
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

//============================================================================
// File          : main.cpp
// Author        : Jayanth
// Copyright   : Your copyright notice
// Description : MusicPlaylist Implementation using STL Container : List
//============================================================================

#include <iostream>
#include<list>
#include<algorithm>
#include"CSong.h"
#include "main.h"
using namespace std;

/*************************************************************************************************
 * Function      : main()
 * Description : Main Function - Entry point to the program
 * @param      : none
 * @return      : int ( success - 0  )
 *************************************************************************************************/
int main()
{
	cout << "MusicPlaylist Implementation via STL_ LIST" << endl<<endl;

	//local Variables Declaration
	list<CSong> myPlaylist;
	list<CSong>:: iterator songItr;
	char UserInput;
	string title, singer;

	defaultPlaylist( myPlaylist );
	songItr = myPlaylist.begin( );

	display(myPlaylist );
	printMenu();

	while ( VALID == getUserInput(UserInput ) )
	{
		switch (UserInput)
		{
		case 'C' :
			cout<<"********************************"<<endl;
			cout<<"Playing the Current Song"<<endl;
			cout<< *songItr <<endl<<endl;
			cout<<"********************************"<<endl;
			printMenu();
			break;

		case 'A' :
			cout<<"********************************"<<endl;
			cout<<"Adding a new song to the beginning  of the list"<<endl;
			cin.clear();
			cout<<"Enter the Song Title : "<<endl;
			cin>>title;
			cout<<"Enter the Singer : "<<endl;
			cin>>singer;

			myPlaylist.push_front(CSong{title,singer});
			cout<<"********************************"<<endl;
			printMenu();
			break;

		case 'N' :
			cout<<"********************************"<<endl;
			cout<<"Playing the Next Song"<<endl;
			songItr++;
			if ( songItr == myPlaylist.end( ))
			{
				songItr = myPlaylist.begin( );
			}
			cout<<*songItr<<endl<<endl;
			cout<<"********************************"<<endl;
			printMenu();
			break;

		case 'P' :
			cout<<"********************************"<<endl;
			cout<<"Playing the Previous Song"<<endl;
			if ( songItr == myPlaylist.begin( ))
			{
				songItr = myPlaylist.end( );
			}
			songItr--;
			cout<<*songItr<<endl<<endl;
			cout<<"********************************"<<endl;
			printMenu();
			break;

		case 'D' :
			cout<<"MyPlaylist :"<<endl;
			display(myPlaylist );
			printMenu();
			break;
		}
	}

	return 0;
}

/*************************************************************************************************
 * Function      :  void addSong(list<CSong> &Playlist  , const CSong &Newsong)
 * Description : Function to add the new song  to the end of the list
 * @param      :  list<CSong> &Playlist
 * @param      : const CSong &Newsong
 * @return      : void
 *************************************************************************************************/
void addSong(list<CSong> &Playlist  , const CSong &Newsong)
{
	Playlist.push_back(Newsong);
}

/*************************************************************************************************
 * Function      : void display(const list<CSong> &Playlist )
 * Description : Function to display the Songs of the list
 * @param      : const list<CSong> &Playlist
 * @return      : void
 *************************************************************************************************/
void display(const list<CSong> &Playlist )
{
	cout<<"========================"<<endl;
	cout<<"My PlayList: "<<endl;
	cout<<"========================"<<endl;
	for(CSong Element : Playlist)
	{
		cout<<Element<<endl;
	}
	cout<<"========================"<<endl;

}

/*************************************************************************************************
 * Function      : void printMenu()
 * Description : Function to print the default menu
 * @param      : none
 * @return      : void
 *************************************************************************************************/
void printMenu()
{
	cout<<"Press the following Keys to make changes: "<<endl;
	cout<<"C - To play first song "<<endl;
	cout<<"N - To play next subsequent song"<<endl;
	cout<<"P - To play previous song"<<endl;
	cout<<"A - To add a New song to end of Playlist"<<endl;
	cout<<"D - To Display Playlist"<<endl;
	cout<<"H - To halt the music "<<endl;

}
/*************************************************************************************************
 * Function      : status_t getUserInput( char &Input)
 * Description : Function to accept the user input and validate it
 * @param      : char &Input
 * @return      : status_t ( VALID or QUIT)
 *************************************************************************************************/
status_t getUserInput( char &Input)
{
	bool IsValidInput = false ;
	status_t status = VALID;

	while (false == IsValidInput)
	{
		cout<<"Enter  your choice   :  ";
		cin>>Input;
		cout<<endl;

		Input = toupper(Input);

		if ( Input =='C' || Input =='N' || Input =='P' ||  Input =='A' ||  Input =='D')
		{
			IsValidInput = true ;
		}
		else if ( Input == 'H')
		{
			IsValidInput = true ;
			status =QUIT;
			cout<<" Music Player turning off ......";
		}
		else
		{
			cout<<"Invalid Input. Please read the Instructions and enter valid option"<<endl;
		}
	}

	return status ;
}

/*************************************************************************************************
 * Function      : defaultPlaylist( list<CSong> &Playlist)
 * Description : Function to add the default songs to the list
 * @param      :  list<CSong> &Playlist
 * @return      : void
 *************************************************************************************************/
void defaultPlaylist( list<CSong> &Playlist)
{
		CSong S1("Believer","Nigam");
		CSong S2("DiaSoul","Nigam");
		CSong S3("BlueRise","BoysBlue");
		CSong S4("I Dont Care","Jayanth");
		CSong S5("Bengaluru","Shreya");

		addSong(Playlist,S1);
		addSong(Playlist,S2);
		addSong(Playlist,S3);
		addSong(Playlist,S4);
		addSong(Playlist,S5);
}
/************************************************************************************************/
