#include "classes.h"

using namespace std;


int main() {
	string input;
	Manager manager;
	while(getline(cin, input)){
		try{
			manager.processCommand(input);
			input.clear();
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
