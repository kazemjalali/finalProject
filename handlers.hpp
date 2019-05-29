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
