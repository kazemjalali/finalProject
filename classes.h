#include <iostream>
#include <vector>
#include <string>
#define SPACE ' '
#define STRING_START 0
using namespace std;


class NotFoundException {
public:
	void what();
};

class BadRequestException {
public:
	void what();
};

class PermissionException {
public:
	void what();
};

class Notification {
public:
	Notification();
	void showNotification();
	void setType(int notifType);
	void setPublisherName(string name);
	void setPublisherId(int pubId);
	void setUserName(string name);
	void setUserId(int uId);
	void setFilmName(string name);
	void setFilmId(int fId);
	void markAsRead();
	bool getStatus();
private:
	int id;
	int type;
	int userId;
	int filmId;
	int publisherId;
	bool seen;
	string content;
	string publisherName;
	string userName;
	string filmName;
};

class Comment {
public:
	int getCommentId();
	int getSender();
	void setContent(string content);
	void setSenderId(int id);
	void setCommentId(int id);
	void setFilmId(int filmId);
	void showComment();
	void reply(string content, int senderId, int receiverId);
private:
	vector<Comment*> repliedComments;
	int commentId;
	int filmId;
	int senderId;
	int receiverId;
	string content;
};

class Film {
public:
	Film();
	int publisherImpart();
	int replyComment(int cmId, string content, int senderId);
	int getFilmId();
	int getFilmPrice();
	int getFilmStatus();
	int findComment(int cmId);
	int getPublisherMoney();
	void setFilmInfo(string info);
	void editFilmInfo(string info);
	void setFilmId(int id);
	void setFilmPublisher(string publisher);
	void showFilmList();
	void deletComment();
	void showFilmDetails(int filmId);
	void showFilmInfo();
	void submitRate(int score);
	void sendComment(string content, int userId);
	void deleteComment(int id);
	void showFilmComments();
	void showFilmDetails();
	void showFilmInfoRec();
	void earnPublisherShare(int money);
	float getFilmRate();
	string getFilmName();
	string getFilmYear();
	string getFilmDirector();
	string getFilmPublisher();
private:
	int filmId;
	int hour;
	int price;
	int publisherMoney;
	int numOfClients;
	int numOfRaters;
	int rateStatus;
	string name;
	string year;
	string summary;
	string director;
	string publisher;
	float totalScore;
	float rating;
	vector<Comment*> comments;
};


class Client {
public:
	Client();
	string getUserName();
	string getPassword();
	int getId();
	void setUserInfo(string info, Client &user);
	void setUserId(int id);
	void setAsAdmin();
	void getUserInfo();
	void follow(Client* pub);
	void rechargeAccount(int amount);
	void search();
	void filmdetail(int filmId);
	void buyFilm(Film* film);
	void rateFilm(int filmId, int score);
	void showPersonalInfo();
	void rateThisFilm(int id, float score);
	void pay(int cost);
	void submitComment(int filmId, string content, int userId);
	void showPurchased(string info);
	void notify(int type, int publisherId, string publishername);
	void showNotif();
	void showAllNotif(int limit);
	bool isPublisher();
	void showMoney();
	virtual Film* addFilm(string info, string &publisher, int id);
	virtual void editFilmInfo(int filmId, string info);
	virtual void deleteFilm(int filmId);
	virtual void deleteThisFilmComment(int filmId, int commentId);
	virtual void payment(int amount);
	virtual void showFollowers();
	virtual void showMyFilms();
	virtual void showPublishedFilms(string info);
	virtual void getMoney();
	virtual void setPublisherTrue();
	virtual void followed(Client* p);
	virtual void sendNotif(int type, string userName, int userId, string filmName, int filmId);
	virtual int replyToComment(int fId, int cmId, string content);
protected:
	int userId;
	int age;
	int money;
	string userName;
	string password;
	string email;
	bool publisher;
	vector<Film*> purchasedFilms;
	vector<Client*> followings;
	vector<Notification*> notifications;
};

class Publisher : public Client {
public:
	Film* addFilm(string info, string &currentUser, int id);
	int getFilmNum();
	int replyToComment(int fId, int cmId, string content);
	void editFilmInfo(int filmId, string info);
	void deleteFilm(int filmId);
	void showPublishedFilms(string info);
	void showFollowers();
	void payment(int amount);
	void getMoney();
	void showNotifications();
	void deleteThisFilmComment(int filmId, int commentId);
	void getPublisherMoney();
	void followed(Client* p);
	void setPublisherTrue();
	void sendNotif(int type, string userName, int userId, string filmName, int filmId);
private:
	vector<Film*> publishedFilms;
	vector<Client*> followers;
};


class Manager {
public:
	Manager();
	void processCommand(string &input);
	void processPostCommands(string command, string info);
	void processGetCommands(string command, string info);
	void processDeleteCommands(string command, string info);
	void processPutCommands(string command, string info);
	void signupUser(string info); 
	void loginUser(string info); 
	void submitFilm(string info);
	void editFilmInfo(int filmId, string info);
	void deleteFilm(string info);
	void showPublisherFilms(string info);
	void showFollowerList();
	void followUser(string info);
	void financialActivities(string info);
	void getFilmDetails(string info);
	void rateFilm(string info);
	void purchaseFilm(string info);
	void payPublisherMoney();
	void postComment(string info);
	void postReplyComment(string info);
	void removeComment(string info);
	void search(string info);
	void showPurchasedFilms(string info);
	void showNotifications();
	void showAllNotifications(string info);
	void deleteFilmFromFilmBox(int id);
	void logoutUser();
	void showUserMoney();
	bool usernameExists(string name);
	int findFilm(int id);
private:
	vector<Client*> users;
	vector<Film*> filmBox;
	int networkMoney;
	string currentUser;
};