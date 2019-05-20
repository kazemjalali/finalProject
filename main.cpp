#include "classes.h"

using namespace std;


int main() {
	string input;
	Manager manager;
	while(true){
		try{
			getline(cin, input);
			manager.processCommand(input);
		}catch(NotFoundException ex){
			ex.what();
		}catch(BadRequestException ex){
			ex.what();
		}catch(PermissionException ex){
			ex.what();
		}	
	}
	return 0;
}
