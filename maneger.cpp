#include "classes.h"
#include <string>
#include <bits/stdc++.h>
#define QUESTION_MARK '?'
#define SPACE ' '
#define EMPTY ""
#define STRING_START 0
#define ZERO 0
#define SPACE_POS 1
#define INFO_POS 2
#define WEAK 0
#define NORMAL 1
#define STRONG 2
#define REPLY 1
#define NEW_FILM 2
#define FOLLOW 3
#define BUY_FILM 4
#define RATE_FILM 5
#define COMMENT 6
#define NOT_FOUND -1

string getThisField(string info, string field){
	int fieldStart = info.find(field);
	string temp = info.substr(fieldStart);
	string temp1 = temp.substr(field.length() + 1);
	string inf = temp1.substr(STRING_START, temp1.find(SPACE));
	return inf;
}

bool checkExistance(string field, string str){
	int index = str.find(field);
	if(index == -1)
		return false;
	else
		return true;
}



string getCommandType(string &input){
	int commandTypeLength = input.find(SPACE);
	string commandType = input.substr(STRING_START, commandTypeLength);
	input.erase(STRING_START, commandTypeLength + 1);
	return commandType;
}

int findUser(string uName, vector<Client*> users){
	int i = 0;
	for(i = 0; i < users.size(); i++){
		if(users[i]->getUserName() == uName)
			return i;
	}
	i++;
	if(i == users.size())
		return -1;
}



int findUserById(int id, vector<Client*> users){
	for(int i = 0; i < users.size(); i++){
		if(users[i]->getId() == id)
			return i;
	}
}

bool compareFilmsByID(Film* f1, Film* f2){
	return (f1->getFilmId() < f2->getFilmId());
}

bool compareFilmsByRating(Film* f1, Film* f2){
	return (f1->getFilmRate() > f2->getFilmRate());
}

int calcPublisherShare(Film* film){
	int status = film->getFilmStatus();
	int price = film->getFilmPrice();
	if(status == WEAK)
		return 0.8 * price;
	else if(status == NORMAL)
		return 0.9 * price;
	else if(status == STRONG)
		return 0.95 * price;
}

Manager::Manager(){
	currentUser = EMPTY;
	Client* admin = new Client;
	admin->setAsAdmin();
	users.push_back(admin);
}

void Manager::setCurrentUser(string usrname){
	currentUser = usrname;
}

bool Manager::usernameExists(string name){
	int i = 0;
	for(i = 0; i < users.size(); i++){
		if(users[i]->getUserName() == name)
			return true;
	}
	i++;
	if(i == users.size())
		return false;
}

void Manager::deleteFilmFromFilmBox(int id){
	int index = 0;
	int i = 0;
	for(i = 0; i < filmBox.size(); i++){
		if(filmBox[i]-> getFilmId() == id){
			index = i;
			filmBox[index]->hide();
			return;
		}
	}
	i++;
	if(i == filmBox.size())
		throw NotFoundException();
}

int Manager::findFilm(int id){
	int i = 0;
	for(i = 0; i < filmBox.size(); i++){
		if(filmBox[i]->getFilmId() == id)
			return i;
	}
	i++;
	if(i == filmBox.size())
		return -1;
}

Client* Manager::getUser(string uName){
	int i = 0;
	for(i = 0; i < users.size(); i++){
		if(users[i]->getUserName() == uName)
			return users[i];
	}
}

void Manager::signupUser(string info){
	if(currentUser != EMPTY)
		throw BadRequestException();
	Client* user = new Client;
	Publisher* publisher = new Publisher;
	if(checkExistance("publisher", info)){
		string temp = getThisField(info, "publisher");
		if(temp == "true"){
			user = publisher;
			user->setPublisherTrue();
		}
	}
	string userNameInput;
	if(usernameExists(userNameInput))
		throw BadRequestException();
	userNameInput = getThisField(info, "username");
	user->setUserInfo(info, *user);
	user->setUserId(users.size() + 1);
	currentUser = user->getUserName();
	users.push_back(user);
	cout << "OK" << endl;
}

void Manager::loginUser(string info){
	if(currentUser != EMPTY)
		throw BadRequestException();
	string userNameInput;
	string passwordInput;
	if(!checkExistance("username", info))
		throw BadRequestException();
	else
		userNameInput = getThisField(info, "username");
	if(!checkExistance("password", info))
		throw BadRequestException();
	else
		passwordInput = getThisField(info, "password");
	int i = 0;
	for(i = 0; i < users.size(); i++){
		if(users[i]->getUserName() == userNameInput && users[i]-> getPassword() == passwordInput){
			currentUser = userNameInput;
			cout << "OK" << endl;
			return;
		}
	}
	if(i == users.size()){
		throw BadRequestException();
	}
}

void Manager::submitFilm(string info){
	int userIndex = findUser(currentUser, users);
	if(!users[userIndex]->isPublisher())
		throw PermissionException();
	Client* user = users[userIndex];
	int filmId = filmBox.size() + 1;
	Film* newFilm = user->addFilm(info, currentUser, filmId);
	filmBox.push_back(newFilm);
	cout << "OK" << endl;

}

void Manager::editFilmInfo(int filmId, string info){
	int userIndex = findUser(currentUser, users);
	if(!users[userIndex]->isPublisher())
		throw PermissionException();
	users[userIndex]->editFilmInfo(filmId, info);
	cout << "OK" << endl;
}

void Manager::deleteFilm(string info){
	int userIndex = findUser(currentUser, users);
	if(!users[userIndex]->isPublisher())
		throw PermissionException();
	int filmId;
	if(!checkExistance("film_id", info))
		throw BadRequestException();
	else
		filmId = stoi(getThisField(info, "film_id"));
	users[userIndex]->deleteFilm(filmId);
	deleteFilmFromFilmBox(filmId);
	cout << "OK" << endl;
}

void Manager::showPublisherFilms(string info){
	int userIndex = findUser(currentUser, users);
	if(!users[userIndex]->isPublisher())
		throw PermissionException();
	users[userIndex]->showPublishedFilms(info);
	return;
}

void Manager::showFollowerList(){
	int userIndex = findUser(currentUser, users);
	if(!users[userIndex]->isPublisher())
		throw PermissionException();
	users[userIndex]->showFollowers();
}

void Manager::followUser(string info){
	int id;
	if(!checkExistance("user_id", info))
		throw BadRequestException();
	else
		id = stoi(getThisField(info, "user_id"));
	int userIndex = findUser(currentUser, users);
	int publisherIndex = findUserById(id, users);
	if(publisherIndex == NOT_FOUND)
		throw NotFoundException();
	users[userIndex]->follow(users[publisherIndex]);
	users[publisherIndex]->followed(users[userIndex]);
	string pubName = users[publisherIndex]->getUserName();
	users[publisherIndex]->notify(FOLLOW, id, pubName);
	cout << "OK" << endl;
}

void Manager::financialActivities(string info){
	int userIndex = findUser(currentUser, users);
	int amount = stoi(getThisField(info, "amount"));
	users[userIndex]->payment(amount);
	cout << "OK" << endl;
}

void Manager::rateFilm(string info){
	int userIndex = findUser(currentUser, users);
	int clientId = users[userIndex]->getId();
	float userRate;
	int filmId;
	if(!checkExistance("score", info))
		throw BadRequestException();
	else
		userRate = stof(getThisField(info, "score"));
	if(!checkExistance("film_id", info))
		throw BadRequestException();
	else
		filmId = stoi(getThisField(info, "film_id"));
	int filmIndex = findFilm(filmId);
	if(filmIndex == NOT_FOUND)
		throw NotFoundException();
	string filmName = filmBox[filmIndex]->getFilmName();
	string publisherName = filmBox[filmIndex]->getFilmPublisher();
	int publisherIndex = findUser(publisherName, users);
	if(publisherIndex == NOT_FOUND)
		throw NotFoundException();
	users[publisherIndex]->sendNotif(RATE_FILM, currentUser, clientId, filmName, filmId);
	users[userIndex]->rateThisFilm(filmId, userRate);
	cout << "OK" << endl;
}

void Manager::purchaseFilm(string info){
	int userIndex = findUser(currentUser, users);
	int filmId;
	if(!checkExistance("film_id", info))
		throw BadRequestException();
	else
		filmId = stoi(getThisField(info, "film_id"));
	int filmIndex = findFilm(filmId);
	if(filmIndex == NOT_FOUND)
		throw NotFoundException();
	if(filmBox[filmIndex]->getHiddenStatus())
		throw BadRequestException();
	string filmName = filmBox[filmIndex]->getFilmName();
	int clientId = users[userIndex]->getId();
	string publisherName = filmBox[filmIndex]->getFilmPublisher();
	int publisherIndex = findUser(publisherName, users);
	if(publisherIndex == NOT_FOUND)
		throw NotFoundException();
	users[publisherIndex]->sendNotif(BUY_FILM, currentUser, clientId, filmName, filmId);
	int cost = filmBox[filmIndex]->getFilmPrice();
	int publisherShare = calcPublisherShare(filmBox[filmIndex]);
	networkMoney += (cost - publisherShare);
	filmBox[filmIndex]->earnPublisherShare(publisherShare);
	users[userIndex]->pay(cost);
	users[userIndex]->buyFilm(filmBox[filmIndex]);
	sort(filmBox.begin(), filmBox.end(), compareFilmsByID);
	cout << "OK" << endl;
}

void Manager::postComment(string info){
	int userIndex = findUser(currentUser, users);
	string content;
	int filmId;
	if(!checkExistance("film_id", info))
		throw BadRequestException();
	else
		filmId = stoi(getThisField(info, "film_id"));

	int filmIndex = findFilm(filmId);
	if(filmIndex == NOT_FOUND)
		throw NotFoundException();
	string filmName = filmBox[filmIndex]->getFilmName();
	if(!checkExistance("content", info))
		throw BadRequestException();
	else
		content = getThisField(info, "content");
	int userId = users[userIndex]->getId();
	string publisherName = filmBox[filmIndex]->getFilmPublisher();
	int publisherIndex = findUser(publisherName, users);
	if(publisherIndex == NOT_FOUND)
		throw NotFoundException();
	users[publisherIndex]->sendNotif(COMMENT, currentUser, userId, filmName, filmId);
	users[userIndex]->submitComment(filmId, content, userId);
	cout << "OK" << endl;
}

void Manager::removeComment(string info){
	int userIndex = findUser(currentUser, users);
	if(!users[userIndex]->isPublisher())
		throw PermissionException();
	int filmId;
	int commentId;
	if(!checkExistance("film_id", info))
		throw BadRequestException();
	else
		filmId = stoi(getThisField(info, "film_id"));
	if(!checkExistance("comment_id", info))
		throw BadRequestException();
	else
		commentId = stoi(getThisField(info, "comment_id"));
	users[userIndex]->deleteThisFilmComment(filmId, commentId);
	cout << "OK" << endl;
}

void Manager::getFilmDetails(string info){
	int filmId;
	if(!checkExistance("film_id", info))
		throw BadRequestException();
	else
		filmId = stoi(getThisField(info, "film_id"));
	int filmIndex = findFilm(filmId);
	if(filmIndex == NOT_FOUND)
		throw NotFoundException();
	filmBox[filmIndex]->showFilmDetails();
	cout << "Comments" << endl;
	filmBox[filmIndex]->showFilmComments();
	cout << endl << "Recommendation Film" << endl;
	cout << "#. Film Id | Film Name | Film Length | Film Director" << endl;
	sort(filmBox.begin(), filmBox.end(), compareFilmsByRating);
	recommendFilm(filmGraph, filmId);
	sort(filmBox.begin(), filmBox.end(), compareFilmsByID);
}

string Manager::getRecommendList(){
	string body;
	sort(filmBox.begin(), filmBox.end(), compareFilmsByRating);
	int recommendationSize = 4;
	if(filmBox.size() < 4)
		recommendationSize = filmBox.size();
	for(int i = 0; i < recommendationSize; i++){
		body += "<tr>";
    string filmName = filmBox[i]->getFilmName();
    string filmDirector = filmBox[i]->getFilmDirector();
    string filmLength = filmBox[i]->getLengthStr();
    body += "<td>" + filmName + "</td>";
    body += "<td>" + filmLength + "</td>";
    body += "<td>" + filmDirector + "</td>";
    body += "</tr>";
	}
	sort(filmBox.begin(), filmBox.end(), compareFilmsByID);
	return body;
}

void Manager::postReplyComment(string info){
	int filmId;
	int commentId;
	string content;
	if(!checkExistance("film_id", info))
		throw BadRequestException();
	else
		filmId = stoi(getThisField(info, "film_id"));
	if(!checkExistance("comment_id", info))
		throw BadRequestException();
	else
		commentId = stoi(getThisField(info, "comment_id"));
	if(!checkExistance("content", info))
		throw BadRequestException();
	else
		content = getThisField(info, "content");
	int userIndex = findUser(currentUser, users);
	int receiverId = users[userIndex]->replyToComment(filmId, commentId, content);
	string publisherName = users[userIndex]->getUserName();
	int publisherId = users[userIndex]->getId();
	int receiverIndex = findUserById(receiverId, users);
	users[receiverIndex]->notify(REPLY, publisherId, publisherName);
	cout << "OK" << endl;
}


void Manager::payPublisherMoney(){
	int userIndex = findUser(currentUser, users);
	if(!users[userIndex]->isPublisher())
		throw PermissionException();
	users[userIndex]->getMoney();
	cout << "OK" << endl;
}

void Manager::search(string input){
	string filmNameInput;
	int maxYearInput = 10000;
	int minYearInput = 0;
	float minRateInput;
	int priceInput;
	string directorInput;
	if(checkExistance("name", input))
		filmNameInput = getThisField(input, "name");
	if(checkExistance("max_year", input))
		maxYearInput = stoi(getThisField(input, "max_year"));
	if(checkExistance("min_year", input))
		minYearInput = stoi(getThisField(input, "min_year"));
	if(checkExistance("min_rate", input))
		minRateInput = stof(getThisField(input, "min_rate"));
	if(checkExistance("price", input))
		priceInput = stoi(getThisField(input, "price"));
	if(checkExistance("director", input))
		directorInput = getThisField(input, "director");
	int count = 0;
	int filmYear;
	cout << "#. Film Id | Film Name | Film Length | Film price | rate | Production Year | Film Director" << endl;
	for(int i = 0; i < filmBox.size(); i++){
		if(filmBox[i]->getHiddenStatus())
			continue;
		filmYear = stoi(filmBox[i]->getFilmYear());
		if((filmBox[i]-> getFilmName() == filmNameInput)
			|| (filmBox[i]->getFilmRate() > minRateInput)
			|| (filmBox[i]->getFilmDirector() == directorInput)
			|| (filmBox[i]->getFilmPrice() == priceInput)
			|| (filmYear <= maxYearInput) && (filmYear >= minYearInput)){
			count++;
			cout << count << ". ";
			filmBox[i]->showFilmInfo();
		}
	}
	maxYearInput = 10000;
	minYearInput = 0;
}

void Manager::showPurchasedFilms(string info){
	int userIndex = findUser(currentUser, users);
	users[userIndex]->showPurchased(info);
}

void Manager::showNotifications(){
	int userIndex = findUser(currentUser, users);
	users[userIndex]->showNotif();
}

void Manager::showAllNotifications(string info){
	int userIndex = findUser(currentUser, users);
	int limit;
	if(!checkExistance("limit", info))
		throw BadRequestException();
	else
		limit = stoi(getThisField(info, "limit"));
	users[userIndex]->showAllNotif(limit);
}

void Manager::logoutUser(){
	currentUser = EMPTY;
	cout << "OK" << endl;
}

void Manager::showNetworkMoney(){
	cout << networkMoney << endl;
}

void Manager::showUserMoney(){
	int userIndex = findUser(currentUser, users);
	string username = users[userIndex]->getUserName();
	if(username == "admin")
		showNetworkMoney();
	else
		users[userIndex]->showMoney();
}

void Manager::recommendFilm(vector<vector<int>> graph, int filmId){
	int row = filmId - 1;
	int recommendationSize = 4;
	if(filmBox.size() < 4)
		recommendationSize = filmBox.size();
	else if(graph[row].size() < 4)
		recommendationSize = graph[row].size();
	int maximum;
	int index = 0;
	for(int j = 0; j < recommendationSize; j++){
		maximum = 0;
		cout << j + 1 << ". 	";
		for(int i = 0; i < graph[row].size(); i++){
			if(graph[row][i] > maximum){
				maximum = graph[row][i];
				index = i;
			}
			else if(graph[row][i] == maximum){
				index = i;
				break;
			}
		}
		graph[row][index] = 0;
		int filmIndex = findFilm(index + 1);
		filmBox[filmIndex]->showFilmInfoRec();
	}
}

string Manager::filterPublishedFilms(string publisher, string directorName){
	int userIndex = findUser(publisher, users);
	return users[userIndex]->filterPubFilms(directorName);
}

string Manager::getPubFilmsList(string username){
	int userIndex = findUser(username, users);
	return users[userIndex]->getPublishedFilmsList();
}

string Manager::getPurFilmsList(string username){
	int userIndex = findUser(username, users);
	return users[userIndex]->getPurchasedFilmsList();
}

string Manager::getFilmsList(){
	string body;
	for(int i = 0; i < filmBox.size(); i++){
		body += "<tr>";
    string filmName = filmBox[i]->getFilmName();
    string filmDirector = filmBox[i]->getFilmDirector();
    string filmYear = filmBox[i]->getFilmYear();
    string filmRate = filmBox[i]->getRatingStr();
    string filmLength = filmBox[i]->getLengthStr();
    string filmPrice = filmBox[i]->getPriceStr();
    body += "<td>" + filmName + "</td>";
    body += "<td>" + filmLength + "</td>";
    body += "<td>" + filmPrice + "</td>";
    body += "<td>" + filmRate + "</td>";
    body += "<td>" + filmYear + "</td>";
    body += "<td>" + filmDirector + "</td>";
		body += "<td><a href='filmDetails?id=";
		body += to_string(filmBox[i]->getFilmId());
		body += "'>See details</a></td>";
    body += "</tr>";
	}
	return body;
}

string Manager::filterFilms(string directorName){
	string body;
	for(int i = 0; i < filmBox.size(); i++){
		if(filmBox[i]->getFilmDirector() == directorName){
			body += "<tr>";
	    string filmName = filmBox[i]->getFilmName();
	    string filmDirector = filmBox[i]->getFilmDirector();
	    string filmYear = filmBox[i]->getFilmYear();
	    string filmRate = filmBox[i]->getRatingStr();
	    string filmLength = filmBox[i]->getLengthStr();
	    string filmPrice = filmBox[i]->getPriceStr();
	    body += "<td>" + filmName + "</td>";
	    body += "<td>" + filmLength + "</td>";
	    body += "<td>" + filmPrice + "</td>";
	    body += "<td>" + filmRate + "</td>";
	    body += "<td>" + filmYear + "</td>";
	    body += "<td>" + filmDirector + "</td>";
			body += "<td><a href='filmDetails?id=";
			body += to_string(filmBox[i]->getFilmId());
			body += "'>See details</a></td>";
	    body += "</tr>";
			body += "<br>";
			body += "<p align=\"left\"><a href=\"/clientHome\">Home</a></p>";
		}
		return body;
	}
}

string Manager::getThisFilmDetails(int id){
	string body;
	int filmIndex = findFilm(id);
	string filmName = filmBox[filmIndex]->getFilmName();
	string filmDirector = filmBox[filmIndex]->getFilmDirector();
	string filmYear = filmBox[filmIndex]->getFilmYear();
	string filmRate = filmBox[filmIndex]->getRatingStr();
	string filmLength = filmBox[filmIndex]->getLengthStr();
	string filmPrice = filmBox[filmIndex]->getPriceStr();
	string filmSummary = filmBox[filmIndex]->getSummary();
	body += "<tr>";
	body += "<td>" + filmName + "</td>";
	body += "<td>" + filmLength + "</td>";
	body += "<td>" + filmPrice + "</td>";
	body += "<td>" + filmRate + "</td>";
	body += "<td>" + filmYear + "</td>";
	body += "<td>" + filmDirector + "</td>";
	body += "<td>" + filmSummary + "</td>";
	body += "<td><a href='buyFilm?id=";
	body += to_string(id);
	body += "'>Buy This Film </a></td>";
	body += "</tr>";
	return body;
}

string Manager::getFilmComments(int id){
	string body;
	int filmIndex = findFilm(id);
	body = filmBox[filmIndex]->getComments();
	return body;
}





void Manager::processPostCommands(string command, string info){
	if(command == "signup"){
		signupUser(info);
	}
	else if(command == "login")
		loginUser(info);
	else if(command == "films")
		submitFilm(info);
	else if(command == "followers")
		followUser(info);
	else if(command == "money"){
		if(checkExistance("amount", info))
			financialActivities(info);
		else
			payPublisherMoney();
	}
	else if(command == "rate")
		rateFilm(info);
	else if(command == "buy")
		purchaseFilm(info);
	else if(command == "comments")
		postComment(info);
	else if(command == "replies")
		postReplyComment(info);
	else if(command == "put_films"){
		int filmId = stoi(getThisField(info, "film_id"));
		editFilmInfo(filmId, info);
	}
	else if(command == "delete_films")
		deleteFilm(info);
	else if(command == "delete_comments")
		removeComment(info);
	else if(command == "logout")
		logoutUser();
	else
		throw NotFoundException();
}


void Manager::processGetCommands(string command, string info){
	if(command == "published"){
		showPublisherFilms(info);
	}
	else if(command == "followers")
		showFollowerList();
	else if(command == "films")
		if(checkExistance("film_id", info))
			getFilmDetails(info);
		else
			search(info);
	else if(command == "purchased")
		showPurchasedFilms(info);
	else if(command == "notifications")
		showNotifications();
	else if(command == "notifications read")
		showAllNotifications(info);
	else if(command == "money")
		showUserMoney();
	else
		throw NotFoundException();
}



void Manager::processCommand(string &input){
	if(input == "")
		return;
	string commandType = getCommandType(input);
	int qPosition = input.find(QUESTION_MARK);
	string command = input.substr(ZERO, qPosition - SPACE_POS);
	string info = input.substr(qPosition + 2);
	if(commandType == "POST"){
		processPostCommands(command, info);
	}
	else if(commandType == "GET"){
		processGetCommands(command, info);
	}
	else
		throw BadRequestException();
}
