/**
*Author: Juan Carlos Ramirez
*Created to  experiment with in place character writing. This would be useful for cmd/terminal apps
*that print to the console.
*/
#include <iostream>
#include <sstream>
#include <unistd.h>

void writeInPlace(std::string s);

int main(){
	
	std::stringstream s;
	for(int i = 0; i <= 100; i++){
		s << "Loading Application: " << i <<  "%";

		writeInPlace(s.str());
		s.str(std::string());
		s.clear();
		usleep(.01e+6);
	}
	std::cout << std::endl;
	
	
	for(int i = 0; i < 100; i++){
		s.str(std::string());
		s.flush();
		s << (char)('a' + (i%26));
		s << (char)('a' + (i%26));
		s << (char)('a' + (i%26));
		s << (char)('a' + (i%26));
		s << (char)('a' + (i%26));
		s << (char)('a' + (i%26));
		
		writeInPlace(s.str());
		s.str(std::string());
		s.flush();
		usleep(.1e+6);
		
	}
	s <<"MR.MOO" << std::endl;
		writeInPlace(s.str());

	for(int i = 100; i >= 0; i--){
		s.str(std::string());
		s.flush();
		s << "Unloading Application: " << i <<  "%";

		writeInPlace(s.str());
		s.str(std::string());
		s.clear();
		usleep(.01e+6);
	}
	std::cout << std::endl;
	
}

void writeInPlace(std::string s){
	std::cout <<"\r" << s << std::flush;
}
