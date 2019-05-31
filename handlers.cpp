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

pHomeHandler::pHomeHandler(Manager* m){
  manager = m;
}

Response* pHomeHandler::callback(Request *req){
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  string publisherName = req->getSessionId();
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1 style=\"color:red;\">NetFlix</h1>";
  body += "<form action=\"/searchDirector\" method=\"post\">";
  body += "<input name=\"directorName\" type=\"text\" placeholder=\"Director\"/>";
  body += "<button type=\"submit\" >Search</button>";
  body += "</form>";
  body += "<br>";
  body += "<br>";
  body += "<style> table, th, td {  border: 1px solid black}</style>";
  body += "<table style=\"width:100%\">";
  body += "<tr>";
  body += "<th>Film Name </th>";
  body += "<th>Film Length </th>";
  body += "<th>Film Price </th>";
  body += "<th>Film Rate </th>";
  body += "<th>Film Year </th>";
  body += "<th>Film Director </th>";
  body += "<th> Delete film </th>";
  body += manager->getPubFilmsList(publisherName);
  body += "</table>";
  body += "<br>";
  body += "<a href = \"/submitFilm\"> Submit a new film </a>";

  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

cHomeHandler::cHomeHandler(Manager* m){
  manager = m;
}

Response* cHomeHandler::callback(Request *req){
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  string clientName = req->getSessionId();
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1 style=\"color:red;\">NetFlix</h1>";
  body += "<form action=\"/searchDirector\" method=\"post\">";
  body += "<input name=\"directorName\" type=\"text\" placeholder=\"Director\"/>";
  body += "<button type=\"submit\" >Search</button>";
  body += "</form>";
  body += "<style> table, th, td {  border: 1px solid black}</style>";
  body += "<table style=\"width:100%\">";
  body += "<tr>";
  body += "<th>Film Name </th>";
  body += "<th>Film Length </th>";
  body += "<th>Film Price </th>";
  body += "<th>Film Rate </th>";
  body += "<th>Film Year </th>";
  body += "<th>Film Director </th>";
  body += manager->getFilmsList();
  body += "</table>";
  body += "<br>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

DeleteFilmHandler::DeleteFilmHandler(Manager* m){
  manager = m;
}

Response* DeleteFilmHandler::callback(Request* req){
  string id = req->getQueryParam("id");
  string command = "POST delete_films ? film_id " + id;
  manager->processCommand(command);
  Response *res = Response::redirect("/publisherHome");
  return res;
}

ProfileHandler::ProfileHandler(Manager* m){
  manager = m;
}

Response* ProfileHandler::callback(Request* req){
  Response *res = new Response;
  string clientName = req->getSessionId();
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1 style=\"color:red;\">NetFlix</h1>";
  body += "<form action=\"/rechargeAccount\" method=\"post\">";
  body += "<input name=\"amount\" type=\"text\" placeholder=\"amount\"/>";
  body += "<button type=\"submit\" >recharge my account </button>";
  body += "</form>";
  body += "<style> table, th, td {  border: 1px solid black}</style>";
  body += "<table style=\"width:100%\">";
  body += "<tr>";
  body += "<th>Film Name </th>";
  body += "<th>Film Length </th>";
  body += "<th>Film Price </th>";
  body += "<th>Film Rate </th>";
  body += "<th>Film Year </th>";
  body += "<th>Film Director </th>";
  body += manager->getPurFilmsList(clientName);
  body += "</table>";
  body += "<br>";

  body += "</body>";
  body += "</html>";
}

rechargeAccountHandler::rechargeAccountHandler(Manager* m){
  manager = m;
}

Response* rechargeAccountHandler::callback(Request* req){
  string amount = req->getBodyParam("amount");
  string command = "POST money ? amount " + amount;
  manager->processCommand(command);
  Response *res = Response::redirect("/profile");
  return res;
}

SubmitFilmHandler::SubmitFilmHandler(Manager* m){
  manager = m;
}

Response* SubmitFilmHandler::callback(Request* req){
  string name = req->getBodyParam("filmName");
  string filmLength = req->getBodyParam("filmLength");
  string filmPrice = req->getBodyParam("filmPrice");
  string filmYear = req->getBodyParam("filmYear");
  string filmDirector = req->getBodyParam("filmDirector");
  string filmSummary = req->getBodyParam("filmSummary");
  string command = "POST films ? name " + name + " year " + filmYear;
  command += " length " + filmLength + " price " + filmPrice;
  command += " summary " + filmSummary + " director " + filmDirector;
  manager->processCommand(command);
  Response* res = Response::redirect("/publisherHome");
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
  string publisher = req->getBodyParam("publisher");
  string command = "POST signup ? username " + username + " password " + password;
  command += " email " + email + " age " + age + " publisher " + publisher;

  try{
    manager->processCommand(command);
    string redirectTo;
    if(manager->getUser(username)->isPublisher())
      redirectTo = "/publisherHome";
    else
      redirectTo = "/clientHome";
    Response*res = Response::redirect(redirectTo);
    res->setSessionId(username);
    return res;
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
    string redirectTo;
    if(manager->getUser(username)->isPublisher())
      redirectTo = "/publisherHome";
    else
      redirectTo = "/clientHome";
    Response*res = Response::redirect(redirectTo);
    res->setSessionId(username);
    return res;
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
