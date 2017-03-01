#include <iostream>
#include <string>

using namespace std;

class person{

  public:

    virtual string getRole();

};

class faculty : public person{

  public: 
    string getRole(){

      return "Faculty";
    }
};

class gradStudent : public person{

  public:
    string getRole(){

    return "Grad Student";
  }
};

class TA : public faculty, public gradStudent{

};

int main(){

  cout << "Brah" << endl;
  TA chad;
  cout << chad.getRole() << endl;
  return 0;
}
