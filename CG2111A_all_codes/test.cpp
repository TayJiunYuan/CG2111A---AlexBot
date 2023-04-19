using namespace std;
#include <iostream>

int i = 4;
int *p = &i;

int main(){
cout << "Valued stored at address of i is " << *p << endl;
cout << "Address of i is" << p << endl;
i = 6;
cout << "New value stored at address of i is" << *p << endl;
cout << "New address of i is" << p << endl;
}

//conclusion: address doesnt change, value updates at the address of variable
