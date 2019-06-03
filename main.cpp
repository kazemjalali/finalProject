#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  try {
    Manager* manager = new Manager;
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");
    server.get("/login", new ShowPage("static/logincss.html"));
    server.post("/login", new LoginHandler(manager));
    server.get("/loginError", new ShowPage("static/loginError.html"));
    server.post("/loginError", new ErrorHandler("/"));
    server.get("/signup", new ShowPage("static/signup.html"));
    server.post("/signup", new SignupHandler(manager));
    server.get("/signupError", new ShowPage("static/signupError.html"));
    server.post("/signupError", new ErrorHandler("/signup"));
    server.get("/signupErrorInput", new ShowPage("static/signupErrorInput.html"));
    server.post("/signupErrorInput", new ErrorHandler("/signup"));
    server.get("/publisherHome", new pHomeHandler(manager));
    server.post("/publisherHome", new pHomeHandler(manager));
    server.get("/clientHome", new cHomeHandler(manager));
    server.post("/clientHome", new cHomeHandler(manager));
    server.get("/submitFilm", new ShowPage("static/submitFilm.html"));
    server.post("/submitFilm", new SubmitFilmHandler(manager));
    server.get("/deleteThisFilm", new DeleteFilmHandler(manager));
    server.get("/profile", new ProfileHandler(manager));
    server.post("/profile", new ProfileHandler(manager));
    server.post("/rechargeAccount", new rechargeAccountHandler(manager));
    server.get("/filmDetails", new filmDetailsHandler(manager));
    server.post("/buyFilm", new BuyFilmHandler(manager));
    server.get("/buyFilm", new BuyFilmHandler(manager));
    server.get("/rateFilm", new RateFilmHandler(manager));
    server.post("/rate", new SubmitScoreHandler(manager));
    server.get("/logout", new LogoutHandler(manager));
    server.post("/searchDirector", new FilterHandler(manager));
    server.get("/home.png", new ShowImage("static/home.png"));
    server.get("/", new ShowPage("static/home.html"));
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
