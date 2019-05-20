#include "classes.h"
#define REPLY 1
#define NEW_FILM 2
#define FOLLOW 3
#define BUY_FILM 4
#define RATE_FILM 5
#define COMMENT 6

Notification::Notification(){
	seen = false;
}

void Notification::setType(int notifType){ 
	type = notifType;
}
void Notification::setPublisherName(string name){
	publisherName = name;
}
void Notification::setPublisherId(int pubId){
	publisherId = pubId;
}
void Notification::setUserName(string name){
	userName = name;
}
void Notification::setUserId(int uId){
	userId = uId;
}
void Notification::setFilmName(string name){
	filmName = name;
}
void Notification::setFilmId(int fId){
	filmId = fId;
}
void Notification::showNotification(){
	if(type == REPLY)
		cout << "Publisher " << publisherName << " with id " << publisherId << " reply to your comment" << endl;
	else if(type == NEW_FILM)
		cout << "Publisher " << publisherName << " with id " << publisherId << " register new film" << endl;
	else if(type == FOLLOW)
		cout << "User " << userName << " with id " << userId << " follow you" << endl;
	else if(type == BUY_FILM)
		cout << "User " << userName << " with id " << userId << " buy your film " << filmName << " with id " << filmId << endl;
	else if(type == RATE_FILM)
		cout << "User " << userName << " with id " << userId << " rate your film " << filmName << " with id " << filmId << endl;
	else if(type == COMMENT)
		cout << "User " << userName << " with id " << userId << " comment on your film " << filmName << " with id " << filmId << endl;
}
void Notification::markAsRead(){
	seen = true;
}

bool Notification::getStatus(){
	return seen;
}