#include "handlers.hpp"

using namespace std;



Response *RandomNumberHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body += "<p>";
  body += "a random number in [1, 10] is: ";
  body += to_string(rand() % 10 + 1);
  body += "</p>";
  body += "<p>";
  body += "SeddionId: ";
  body += req->getSessionId();
  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

SignupHandler::SignupHandler(Manager* m){
  manager = m;
}


Response* SignupHandler::callback(Request* req){
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string repeatPass = req->getBodyParam("repeatPass");

  if(password != repeatPass){
    Response* res = Response::redirect("/signupErrorInput");
    return res;
  }
  string email = req->getBodyParam("email");
  string age = req->getBodyParam("age");
  string publisher = req->getQueryParam("publisher");
  string command = "POST signup ? username " + username + " password " + password;
  command += " email " + email + " age " + age + " publisher " + publisher;

  try{
    manager->processCommand(command);
  }catch(BadRequestException ex){
    Response *res = Response::redirect("/signupError");
    return res;
  }
}


LoginHandler::LoginHandler(Manager* m){
  manager = m;
}

ErrorHandler::ErrorHandler(string address){
  redirectAddress = address;
}

Response* ErrorHandler::callback(Request* req){
  Response *res = Response::redirect(redirectAddress);
  return res;
}



Response *LoginHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string command = "POST signup ? username " + username + "password " + password;
  try{
    manager->processCommand(command);
  }catch(BadRequestException ex){
    Response *res = Response::redirect("/loginError");
    return res;
  }
  if (username == "root")
    throw Server::Exception("Remote root access has been disabled.");
  cout << "username: " << username << ",\tpassword: " << password << endl;
  Response *res = Response::redirect("/rand");
  res->setSessionId("SID");
  return res;
}

Response *UploadHandler::callback(Request *req) {
  string name = req->getBodyParam("file_name");
  string file = req->getBodyParam("file");
  cout << name << " (" << file.size() << "B):\n" << file << endl;
  Response *res = Response::redirect("/");
  return res;
}

ColorHandler::ColorHandler(string filePath) : TemplateHandler(filePath) {}

map<string, string> ColorHandler::handle(Request *req) {
  map<string, string> context;
  string newName = "I am " + req->getQueryParam("name");
  context["name"] = newName;
  context["color"] = req->getQueryParam("color");
  return context;
}
