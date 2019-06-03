#include "classes.h"

void Comment::setContent(string cont){
	content = cont;
}

void Comment::setCommentId(int id){
	commentId= id;
}

void Comment::setSenderId(int id){
	senderId = id;
}

void Comment::setFilmId(int id){
	filmId = id;
}

int Comment::getCommentId(){
	return commentId;
}

int Comment::getSender(){return senderId;}

string Comment::getContent(){return content;}

void Comment::showComment(){
	cout << commentId << ". " << content << endl;
	for(int i = 0; i < repliedComments.size(); i++){
		repliedComments[i]->showComment();
	}
}

void Comment::reply(string cont, int sender, int receiver){
	int cmId = repliedComments.size() + 1;
	Comment* rep = new Comment;
	rep->senderId = sender;
	rep-> commentId = cmId;
	rep->content = cont;
	rep->receiverId = receiver;
	repliedComments.push_back(rep);
}
