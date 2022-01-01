#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "queue.hpp"
#include "movie.hpp"
#include<iostream>
using namespace std;

class Playlist{
public:
    Queue<Movie*> playlist;

    Movie* search_playlist(string);
    void add_to_playlist(Movie*);
};

Movie* Playlist::search_playlist(string name){
    while(playlist.queue[playlist.front]->title != name)
    {
        Movie* movie = playlist.Dequeue();
        playlist.Enqueue(movie);
    }
    return playlist.queue[playlist.front];
}

void Playlist::add_to_playlist(Movie* movie){

    if(playlist.size <= 10) playlist.Enqueue(movie);
    else cout << "Playlist is full" << endl;
}

#endif