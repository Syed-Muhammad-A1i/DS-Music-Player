#include <iostream>
#include "Linklist.cpp"
using namespace std;

void Admin(int ID){
	int n; 
	string name;
	Linklist l;
	if(ID==333500||ID==332900||ID==324900)
	{
		cout << "1.Insert New Song\n";
		cin >> n;
		
		switch (n){
			case 1:
				{
					cout<<"Enter the name of the Song : ";
					cin >> name;
					l.Insert(serial_number,name);
				}
			default:
				{
					cout << "Wrong Input";
					return;
				}	
		}
		
	}
	else{
		
		// user should be called here.
	}
	return;
}

int main(){

	Linklist l1;
	l1.file_to_LL();
	l1.
	l1.print();
	int input;
	cin >> input;	
	Admin(input);
//	l1.print();
	return 0;
}
