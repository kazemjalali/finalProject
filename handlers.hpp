#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

class ErrorHandler : public RequestHandler {
public:
  ErrorHandler(string address);
  Response *callback(Request *);
  string redirectAddress;
};

class pHomeHandler : public RequestHandler {
public:
  pHomeHandler(Manager* m);
  Response *callback(Request *);
};

class cHomeHandler : public RequestHandler {
public:
  cHomeHandler(Manager* m);
  Response *callback(Request *);
};

class SubmitFilmHandler : public RequestHandler {
public:
  SubmitFilmHandler(Manager* m);
  Response *callback(Request *);
};

class BuyFilmHandler : public RequestHandler {
public:
  BuyFilmHandler(Manager* m);
  Response *callback(Request *);
};


class RateFilmHandler : public RequestHandler {
public:
  RateFilmHandler(Manager* m);
  Response *callback(Request *);
};

class SubmitScoreHandler : public RequestHandler {
public:
  SubmitScoreHandler(Manager* m);
  Response *callback(Request *);
};

class ProfileHandler : public RequestHandler {
public:
  ProfileHandler(Manager* m);
  Response *callback(Request *);
};

class rechargeAccountHandler : public RequestHandler {
public:
  rechargeAccountHandler(Manager* m);
  Response *callback(Request *);
};

class filmDetailsHandler : public RequestHandler {
public:
  filmDetailsHandler(Manager* m);
  Response *callback(Request *);
};


class DeleteFilmHandler : public RequestHandler {
public:
  DeleteFilmHandler(Manager* m);
  Response *callback(Request *);
};

class SignupHandler : public RequestHandler {
public:
  SignupHandler(Manager* m);
  Response *callback(Request *);
};

class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class LoginHandler : public RequestHandler {
public:
  LoginHandler(Manager* m);
  Response *callback(Request *);
};

class FilterHandler : public RequestHandler {
public:
  FilterHandler(Manager* m);
  Response *callback(Request *);
};

class LogoutHandler : public RequestHandler {
public:
  LogoutHandler(Manager* m);
  Response *callback(Request *);
};


class UploadHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class ColorHandler : public TemplateHandler {
public:
  ColorHandler(std::string filePath);
  std::map<std::string, std::string> handle(Request *req);
};

#endif
