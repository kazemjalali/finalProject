#include "classes.h"
#define NEW_FILM 2
#define NOT_FOUND -1
string getNextwrd(string field, string info){
	int fieldStart = info.find(field);
	string temp = info.substr(fieldStart);
	string temp1 = temp.substr(field.length() + 1);
	string inf = temp1.substr(STRING_START, temp1.find(SPACE));
	return inf;
}

int findFilm(vector<Film*> films, int id){
	int i = 0;
	for(i = 0; i < films.size(); i++){
		if(films[i]->getFilmId() == id)
			return i;
	}
	i++;
	if(i == films.size())
		return -1;
}

bool exists(string field, string str){
	int index = str.find(field);
	if(index == -1)
		return false;
	else
		return true;
}

Film* Publisher::addFilm(string info, string &currentUser, int id){
	Film* film = new Film;
	if(!exists("name", info))
		throw BadRequestException();
	if(!exists("year", info))
		throw BadRequestException();
	if(!exists("length", info))
		throw BadRequestException();
	if(!exists("price", info))
		throw BadRequestException();
	if(!exists("summary", info))
		throw BadRequestException();
	if(!exists("director", info))
		throw BadRequestException();
	film->setFilmInfo(info);
	film->setFilmId(id);
	film->setFilmPublisher(currentUser);
	publishedFilms.push_back(film);
	for(int i = 0; i < followers.size(); i++){
		followers[i]->notify(NEW_FILM, userId, userName);
	}
	return film;
}

void Publisher::editFilmInfo(int id, string info){
	int index = 0;
	int i = 0;
	if(!exists("film_id", info))
		throw BadRequestException();

	for(i = 0; i < publishedFilms.size(); i++){
		if(publishedFilms[i]-> getFilmId() == id){
			index = i;
			publishedFilms[index]->editFilmInfo(info);
			return;
		}
	}
	i++;
	if(i == publishedFilms.size())
		throw NotFoundException();
}

void Publisher::deleteFilm(int id){
	int index = 0;
	int i = 0;
	for(i = 0; i < publishedFilms.size(); i++){
		if(publishedFilms[i]-> getFilmId() == id){
			index = i;
			publishedFilms[index]->hide();
			return;
		}
	}
	i++;
	if(i == publishedFilms.size())
		throw NotFoundException();
}


void Publisher::showPublishedFilms(string input){
	string filmNameInput;
	int maxYearInput = 10000;
	int minYearInput = 0;
	float minRateInput;
	int priceInput;
	string directorInput;
	if(exists("name", input))
		filmNameInput = getNextwrd("name", input);
	if(exists("max_year", input))
		maxYearInput = stoi(getNextwrd("max_year", input));
	if(exists("min_year", input))
		minYearInput = stoi(getNextwrd("min_year", input));
	if(exists("min_rate", input))
		minRateInput = stof(getNextwrd("min_rate", input));
	if(exists("price", input))
		priceInput = stoi(getNextwrd("price", input));
	if(exists("director", input))
		directorInput = getNextwrd("director", input);
	int count = 0;
	int filmYear;
	cout << "#. Film Id | Film Name | Film Length | Film price | rate | Production Year | Film Director" << endl;
	for(int i = 0; i < publishedFilms.size(); i++){
		if(publishedFilms[i]->getHiddenStatus())
			continue;
		filmYear = stoi(publishedFilms[i]->getFilmYear());
		if((publishedFilms[i]-> getFilmName() == filmNameInput)
			|| (publishedFilms[i]->getFilmRate() > minRateInput)
			|| (publishedFilms[i]->getFilmDirector() == directorInput)
			|| (publishedFilms[i]->getFilmPrice() == priceInput)
			|| (filmYear <= maxYearInput) && (filmYear >= minYearInput)){
			count++;
			cout << count << ". ";
			publishedFilms[i]->showFilmInfo();
		}
	}
	maxYearInput = 10000;
	minYearInput = 0;
}

void Publisher::showFollowers(){
	cout << "List of Followers" << endl;
	cout << "#. User Id | User Username | User Email" << endl;
	for(int i = 0; i < followers.size(); i++){
		cout << i + 1 << ". ";
		followers[i]->showPersonalInfo();
	}
}

void Publisher::deleteThisFilmComment(int fId, int cmId){
	int filmIndex = findFilm(publishedFilms, fId);
	if(filmIndex == NOT_FOUND)
		throw NotFoundException();
	publishedFilms[filmIndex]->deleteComment(cmId);
}

int Publisher::replyToComment(int fId, int cmId, string content){
	int filmIndex = findFilm(publishedFilms, fId);
	if(filmIndex == NOT_FOUND)
		throw NotFoundException();
	int receiverId = publishedFilms[filmIndex]->replyComment(cmId, content, userId);
	return receiverId;
}

void Publisher::payment(int amount){

}

void Publisher::getMoney(){
	int sold = 0;
	for(int i = 0; i < publishedFilms.size(); i++){
		sold += publishedFilms[i]->getPublisherMoney();
	}
	money += sold;
}

void Publisher::sendNotif(int type, string userName, int userId, string filmName, int filmId){
	Notification* notif = new Notification;
	notif->setType(type);
	notif->setUserName(userName);
	notif->setUserId(userId);
	notif->setFilmName(filmName);
	notif->setFilmId(filmId);
	notifications.insert(notifications.begin(), notif);
}

string Publisher::getPublishedFilmsList(){
	string body;
	for(int i = 0; i < publishedFilms.size(); i++){
		if(publishedFilms[i]->getHiddenStatus())
			continue;
		body += "<tr>";
    string filmName = publishedFilms[i]->getFilmName();
    string filmDirector = publishedFilms[i]->getFilmDirector();
    string filmYear = publishedFilms[i]->getFilmYear();
    string filmRate = publishedFilms[i]->getRatingStr();
    string filmLength = publishedFilms[i]->getLengthStr();
    string filmPrice = publishedFilms[i]->getPriceStr();
    body += "<td>" + filmName + "</td>";
    body += "<td>" + filmLength + "</td>";
    body += "<td>" + filmPrice + "</td>";
    body += "<td>" + filmRate + "</td>";
    body += "<td>" + filmYear + "</td>";
    body += "<td>" + filmDirector + "</td>";
		body += "<td><a href='deleteThisFilm?id=";
		body += to_string(publishedFilms[i]->getFilmId());
		body += "'>Delete</a></td>";
		body += "</tr>";
	}
	return body;
}

int Publisher::getFilmNum(){
	return publishedFilms.size();
}

void Publisher::followed(Client* pub){
	followers.push_back(pub);
}
void Publisher::setPublisherTrue(){
	publisher = true;
}

/* POST signup ? username kaafjim password 1234 email fuck age 85 publisher true
POST films ? name mamad year 1397 length 120 price 800 summary fuck director m

*/
