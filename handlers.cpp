#include "handlers.hpp"

using namespace std;
#define EMPTY ""


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
  string currentUser = req->getSessionId();
  manager->setCurrentUser(currentUser);
  res->setHeader("Content-Type", "text/html");
  string body;
  string publisherName = req->getSessionId();
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1 style=\"color:red;\">NetFlix</h1>";
  body += "<a href=\"/logout\">Logout</a>";
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
  string currentUser = req->getSessionId();
  manager->setCurrentUser(currentUser);
  res->setHeader("Content-Type", "text/html");
  string body;
  string clientName = req->getSessionId();
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1 style=\"color:red;\">NetFlix</h1>";
  body += "<p align=\"left\"> <a href=\"/logout\">Logout</a></p>";
  body += "<br> <br>";
  body += "<p align=\"left\"><a href=\"/profile\">Profile</a></p>";
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
  body += "<th>Details </th>";
  body += manager->getFilmsList();
  body += "</table>";
  body += "<br>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

FilterHandler::FilterHandler(Manager* m){
  manager = m;
}

Response* FilterHandler::callback(Request* req){
  Response *res = new Response;
  string currentUser = req->getSessionId();
  manager->setCurrentUser(currentUser);
  res->setHeader("Content-Type", "text/html");
  string directorName = req->getBodyParam("directorName");
  string body;
  string clientName = req->getSessionId();
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1 style=\"color:red;\">NetFlix</h1>";
  body += "<p align=\"left\"> <a href=\"/logout\">Logout</a></p>";
  body += "<br> ";
  body += "<p align=\"left\"><a href=\"/profile\">Profile</a></p>";
  body += "<br> ";

  body += "<style> table, th, td {  border: 1px solid black}</style>";
  body += "<table style=\"width:100%\">";
  body += "<tr>";
  body += "<th>Film Name </th>";
  body += "<th>Film Length </th>";
  body += "<th>Film Price </th>";
  body += "<th>Film Rate </th>";
  body += "<th>Film Year </th>";
  body += "<th>Film Director </th>";
  body += "<th>Details </th>";
  if(manager->getUser(clientName)->isPublisher())
    body += manager->filterPublishedFilms(clientName, directorName);
  else
    body += manager->filterFilms(directorName);
  body += "</table>";
  body += "<br>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

ProfileHandler::ProfileHandler(Manager* m){
  manager = m;
}

Response* ProfileHandler::callback(Request* req){
  Response *res = new Response;
  string currentUser = req->getSessionId();
  manager->setCurrentUser(currentUser);
  string clientName = req->getSessionId();
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1 style=\"color:red;\">NetFlix</h1>";
  body += "<a href=\"/logout\">Logout</a>";
  body += "<a href=\"/clientHome\">Home</a>";
  body += "<form action=\"/rechargeAccount\" method=\"post\">";
  body += "<input name=\"amount\" type=\"text\" placeholder=\"amount\"/>";
  body += "<button type=\"submit\" >recharge my account </button>";
  body += "</form>";
  body += "<p align=\"left\"> Purchased Films : </p>";
  body += "<style> table, th, td {  border: 1px solid black}</style>";
  body += "<table style=\"width:100%\">";
  body += "<tr>";
  body += "<th>Film Name </th>";
  body += "<th>Film Length </th>";
  body += "<th>Film Price </th>";
  body += "<th>Film Rate </th>";
  body += "<th>Film Year </th>";
  body += "<th>Film Director </th>";
  body += "<th>Rate</th>";
  body += manager->getPurFilmsList(clientName);
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
  string currentUser = req->getSessionId();
  manager->setCurrentUser(currentUser);
  string command = "POST delete_films ? film_id " + id;
  manager->processCommand(command);
  Response *res = Response::redirect("/publisherHome");
  return res;
}

filmDetailsHandler::filmDetailsHandler(Manager* m){
  manager = m;
}

Response* filmDetailsHandler::callback(Request* req){
  string id = req->getQueryParam("id");
  Response *res = new Response;
  string currentUser = req->getSessionId();
  manager->setCurrentUser(currentUser);
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1 style=\"color:red;\">NetFlix</h1>";
  body += "<p align=\"left\"><a href=\"/logout\">Logout</a></p>";
  body += "<br>";
  body += "<p align=\"left\"><a href=\"/clilenHome\">Home</a></p>";
  body += "<br>";
  body += "<p align=\"left\"><a href=\"/profile\">Profile</a></p>";
  body += "<style> table, th, td {  border: 1px solid black}</style>";
  body += "<table style=\"width:100%\">";
  body += "<tr>";
  body += "<th>Film Name </th>";
  body += "<th>Film Length </th>";
  body += "<th>Film Price </th>";
  body += "<th>Film Rate </th>";
  body += "<th>Film Year </th>";
  body += "<th>Film Director </th>";
  body += "<th>Film Summary </th>";
  body += "<th>Buy Film </th>";
  body += "</tr>";
  body += manager->getThisFilmDetails(stoi(id));
  body += "</table>";

  body += "<br /><br /> <br />";
  body += "<p align=\"left\"> Film  Comments : </p> ";
  body += "<style> table, th, td {  border: 2px solid black}</style>";
  body += "<table style=\"width:100%\">";
  body += "<tr>";
  body += "<th>Num</th>";
  body += "<th>Comment Message </th>";
  body += "</tr>";
  body += manager->getFilmComments(stoi(id));
  body += "</table>";


  body += "<br /><br /> <br />";
  body += "<p align=\"left\"> Recommended Films : </p> ";
  body += "<style> table, th, td {  border: 2px solid black}</style>";
  body += "<table style=\"width:100%\">";
  body += "<tr>";
  body += "<th>Film Name </th>";
  body += "<th>Film Length </th>";
  body += "<th>Film Director </th>";
  body += "</tr>";
  body += manager->getRecommendList();
  body += "</table>";


  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
//

}

BuyFilmHandler::BuyFilmHandler(Manager* m){
  manager = m;
}

Response* BuyFilmHandler::callback(Request* req){
  string id = req->getQueryParam("id");
  string currentUser = req->getSessionId();
  manager->setCurrentUser(currentUser);

  string command = "POST buy ? film_id ";
  command += id;
  manager->processCommand(command);
  Response *res = Response::redirect("/clientHome");
  return res;
}

RateFilmHandler::RateFilmHandler(Manager* m){
  manager = m;
}

Response* RateFilmHandler::callback(Request* req){
  string id = req->getQueryParam("id");
  string currentUser = req->getSessionId();
  manager->setCurrentUser(currentUser);
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1 style=\"color:red;\">NetFlix</h1>";
  body += "<p align=\"left\"><a href=\"/logout\">Logout</a></p>";
  body += "<br>";
  body += "<p align=\"left\"><a href=\"/profile\">Profile</a></p>";
  body += "<br>";
  body += "<p align=\"left\"><a href=\"/clilenHome\">Home</a></p>";
  body += "<form action=\"/rate?id=";
  body += id;
  body += "\" method=\"post\">";

  body += "<input name=\"score\" type=\"text\" placeholder=\"Score\"/>";
  body += "<button type=\"submit\" >Rate</button>";
  body += "</form>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

SubmitScoreHandler::SubmitScoreHandler(Manager* m){
  manager = m;
}

Response* SubmitScoreHandler::callback(Request* req){
  string score = req->getBodyParam("score");
  string filmID = req->getQueryParam("id");


  string currentUser = req->getSessionId();
  manager->setCurrentUser(currentUser);
  string command = "POST rate ? film_id ";
  command += filmID;
  command += " score ";
  command += score;
  manager->processCommand(command);
  Response *res = Response::redirect("/clientHome");
  return res;
}


rechargeAccountHandler::rechargeAccountHandler(Manager* m){
  manager = m;
}

Response* rechargeAccountHandler::callback(Request* req){
  string amount = req->getBodyParam("amount");
  string currentUser = req->getSessionId();
  manager->setCurrentUser(currentUser);
  string command = "POST money ? amount " + amount;
  manager->processCommand(command);
  Response *res = Response::redirect("/profile");
  return res;
}


SubmitFilmHandler::SubmitFilmHandler(Manager* m){
  manager = m;
}

Response* SubmitFilmHandler::callback(Request* req){
  string currentUser = req->getSessionId();
  manager->setCurrentUser(currentUser);
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



Response* LogoutHandler::callback(Request* req){
  manager->setCurrentUser(EMPTY);
  Response *res = Response::redirect("/signup");
  return res;
}

LogoutHandler::LogoutHandler(Manager* m){
  manager = m;
}


ErrorHandler::ErrorHandler(string address){
  redirectAddress = address;
}

Response* ErrorHandler::callback(Request* req){
  Response *res = Response::redirect(redirectAddress);
  return res;
}

LoginHandler::LoginHandler(Manager* m){
  manager = m;
}

Response *LoginHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string command = "POST login ? username " + username + " password " + password;
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
}
