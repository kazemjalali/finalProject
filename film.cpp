#include "classes.h"
#define WEAK 0
#define NORMAL 1
#define STRONG 2
#define NOT_FOUND -1
string getNext(string field, string info){
	int fieldStart = info.find(field);
	string temp = info.substr(fieldStart);
	string temp1 = temp.substr(field.length() + 1);
	string inf = temp1.substr(STRING_START, temp1.find(SPACE));
	return inf; 
}

int Film::findComment(int cmId){
	int i = 0;
	for(i = 0; i < comments.size(); i++){
		if(comments[i]->getCommentId() == cmId)
			return i; 
	}
	i++;
	if(i == comments.size())
		return -1;
}


int fieldExistance(string field, string str){
	int exist = str.find(field);
	if(exist != -1)
		return 1;
	else
		return -1;
} 


Film::Film(){
	rating = 0;
	rateStatus = WEAK;
	hidden = false;
}

void Film::setFilmId(int id){
	filmId = id;
}

void Film::setFilmInfo(string info){
	name = getNext("name", info);
	year = getNext("year", info);
	hour = stoi(getNext("length", info));
	price = stoi(getNext("price", info));
	summary = getNext("summary", info);
	director = getNext("director", info);
}

void Film::setFilmPublisher(string pub){
	publisher = pub;
}

void Film::showFilmInfo(){
	cout << filmId << " | " << name << " | " << hour << " | " << price << " | " << rating << " | " << year << " | " << director << endl;
}

void Film::showFilmDetails(){
	cout << "Details of Film " << name << endl;
	cout << "Id = " << filmId << endl;
	cout << "Director = " << director << endl;
	cout << "Length = " << hour << endl;
	cout << "Year = " << year << endl;
	cout << "Summary = " << summary << endl;
	cout << "Rate = " << rating << endl;
	cout << "Price = " << price << endl << endl;

}

void Film::editFilmInfo(string info){
	if(fieldExistance("name", info))
		name = getNext("name", info);
	else if(fieldExistance("year", info))
		year = getNext("year", info);
	else if(fieldExistance("length", info))
		hour = stoi(getNext("length", info));
	else if(fieldExistance("summary", info))
		summary = getNext("summary", info);
	else if(fieldExistance("director", info))
		director = getNext("director", info);
}

void Film::submitRate(int score){
	numOfRaters++;
	totalScore += score;
	rating = score / numOfRaters;
	if(rating < 5)
		rateStatus = WEAK;
	else if(rating < 8 && rating >= 5)
		rateStatus = NORMAL;
	else if(rating >= 8 && rating <= 10)
		rateStatus = STRONG;
}

void Film::sendComment(string content, int userId){
	Comment* cm = new Comment;
	cm->setContent(content);
	cm->setCommentId(comments.size() + 1);
	cm->setSenderId(userId);
	cm->setFilmId(filmId);
	comments.push_back(cm);
}

void Film::deleteComment(int id){
	int index = 0;
	int i = 0;
	for(i = 0; i < comments.size(); i++){
		if(comments[i]->getCommentId() == id){
			index = i;
			comments.erase(comments.begin() + index);
			return;
		}
	}
	i++;
	if(i == comments.size())
		throw NotFoundException();
}

void Film::showFilmComments(){
	for(int i = 0; i < comments.size(); i++){
		comments[i]->showComment();
	}
}

void Film::showFilmInfoRec(){
	cout << filmId << " | " << name << " | " << hour << " | " << director << endl;
}

int Film::replyComment(int cmId, string content, int senderId){
	int commentIndex = findComment(cmId);
	if(commentIndex == NOT_FOUND)
		throw NotFoundException();
	int receiverId = comments[commentIndex]->getSender();
	comments[commentIndex]->reply(content, senderId, receiverId);
	return receiverId;
}

void Film::earnPublisherShare(int pubShare){
	publisherMoney += pubShare;
}

void Film::hide(){
	hidden = true;
}


int Film::getPublisherMoney(){
	int temp = publisherMoney;
	publisherMoney = 0;
	return temp;
}
int Film::getFilmId(){ return filmId; }
int Film::getFilmPrice(){return price;}
string Film::getFilmName(){return name;}
string Film::getFilmYear(){return year;}
string Film::getFilmDirector(){return director;}
string Film::getFilmPublisher(){return publisher;}
float Film::getFilmRate(){return rating;}
int Film::getFilmStatus(){return rateStatus;}
bool Film::getHiddenStatus(){return hidden;}


