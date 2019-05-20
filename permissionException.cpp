#include "classes.h"

void PermissionException::what(){
	cout << "Permission Denied" << endl;
}