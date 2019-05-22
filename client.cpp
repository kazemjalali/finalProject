#include "classes.h"
#include <string>
#define STRING_START 0
#define SPACE ' '
#define NOT_FOUND -1

int findThisFilm(vector<Film*> films, int id){
	int i = 0;
	if(films.size() == 0)
		return -1;
	for(i = 0; i < films.size(); i++){
		if(films[i]->getFilmId() == id){
			return i;
		}
	}
	if(i == films.size())
		return -1;

}

Film* Client::addFilm(string info, string &pub, int id)
{
}

void Client::follow(Client* pub){
	followings.push_back(pub);
}
Client::Client(){
	publisher = false;
}
void Client::editFilmInfo(int filmId, string info){}
void Client::deleteFilm(int filmId){}
void Client::showMyFilms(){}
void Client::showPublishedFilms(string info){}
void Client::showFollowers(){}
void Client::deleteThisFilmComment(int filmId, int commentId){}
int Client::replyToComment(int fId, int cmId, string content){}
void Client::getMoney(){}
void Client::followed(Client* p){}
void Client::setPublisherTrue(){}
bool Client::isPublisher(){return publisher;}
void Client::sendNotif(int type, string userName, int userId, string filmName, int filmId){}

string getNextWord(string info, string field){
	int fieldStart = info.find(field);
	string temp = info.substr(fieldStart);
	string temp1 = temp.substr(field.length() + 1);
	string inf = temp1.substr(STRING_START, temp1.find(SPACE));
	return inf; 
}

bool existstance(string field, string str){
	int index = str.find(field);
	if(index == -1)
		return false;
	else
		return true;
}

void Client::showPersonalInfo(){
	cout << userId << " | " << userName << " | " << email << endl;
}

void Client::setUserInfo(string info , Client &user){
	if(!existstance("email", info))
		throw BadRequestException();
	else
		user.email = getNextWord(info, "email");
	if(!existstance("username", info))
		throw BadRequestException();
	else
		user.userName = getNextWord(info, "username");
	if(!existstance("password", info))
		throw BadRequestException();
	else
		user.password = getNextWord(info, "password");
	if(!existstance("age", info))
		throw BadRequestException();
	else{
		string age = getNextWord(info, "age");
		user.age = stoi(age);
	}
	if(existstance("publisher", info))
		string pub = getNextWord(info, "publisher");
	
}

void Client::payment(int amount){
	money += amount;
}

void Client::rateThisFilm(int id, float score){
	int filmIndex = findThisFilm(purchasedFilms, id);
	if(filmIndex == NOT_FOUND)
		throw NotFoundException();
	purchasedFilms[filmIndex]->submitRate(score);
}

void Client::pay(int cost){
	money -= cost;
}

void Client::buyFilm(Film* film){
	purchasedFilms.push_back(film);
}

void Client::submitComment(int id, string content, int userId){
	int filmIndex = findThisFilm(purchasedFilms, id);
	if(filmIndex == NOT_FOUND)
		throw NotFoundException();
	purchasedFilms[filmIndex]->sendComment(content, userId);
}

void Client::showPurchased(string input){
	string filmNameInput;
	int maxYearInput = 10000;
	int minYearInput = 0;
	int priceInput;
	string directorInput;
	if(existstance("name", input))
		filmNameInput = getNextWord(input, "name");
	if(existstance("max_year", input))
		maxYearInput = stoi(getNextWord(input, "max_year"));
	if(existstance("min_year", input))
		minYearInput = stoi(getNextWord(input, "min_year"));
	if(existstance("price", input))
		priceInput = stoi(getNextWord(input, "price"));
	if(existstance("director", input))
		directorInput = getNextWord(input, "director");
	int filmYear;
	int count = 0;
	cout << "#. Film Id | Film Name | Film Length | Film price | rate | Production Year | Film Director" << endl;
	for(int i = 0; i < purchasedFilms.size(); i++){
		filmYear = stoi(purchasedFilms[i]->getFilmYear());
		if((purchasedFilms[i]-> getFilmName() == filmNameInput)
			|| (purchasedFilms[i]->getFilmDirector() == directorInput) 
			|| (purchasedFilms[i]->getFilmPrice() == priceInput) 
			|| (filmYear <= maxYearInput) && (filmYear >= minYearInput)){
			count++;
			cout << count << ". ";
			purchasedFilms[i]->showFilmInfo();
		}
	}
	maxYearInput = 10000;
	minYearInput = 0;
}

void Client::notify(int type, int publisherId, string publishername){
	Notification* notif = new Notification;
	notif->setType(type);
	notif->setPublisherId(publisherId);
	notif->setPublisherName(publishername);
	notifications.insert(notifications.begin(), notif);
}

void Client::showNotif(){
	int counter = 0;
	cout << "#. Notification Message" << endl;
	for(int i = 0; i < notifications.size(); i++){
		if(!(notifications[i]->getStatus())){
			cout << counter + 1 << ". " << endl;
			notifications[i]->showNotification();
			notifications[i]->markAsRead();
			counter++;
		}
	}
}

void Client::showAllNotif(int limit){
	int counter = 0;
	cout << "#. Notification Message" << endl;
	for(int i = 0; i < limit; i++){
		cout << counter + 1 << ". " << endl;
		notifications[i]->showNotification();
		notifications[i]->markAsRead();
		counter++;
	}	
}

void Client::showMoney(){
	cout << money << endl;
}

void Client::setUserId(int id){
	userId = id;
}
void setAsSAdmin(){
	userName = "admin";
	password = "admin";
}

string Client::getUserName(){ return userName; }
string Client::getPassword(){ return password; }
int Client::getId(){ return userId;}
void Client::getUserInfo(){
	cout << userName << endl << password << endl << age << endl << userId << endl; 
}



