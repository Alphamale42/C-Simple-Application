#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

#include "list.h"
#include "hydro.h"
int numRecords;

int main(void) {
	FlowList x;
	
	displayHeader();
	numRecords = readData(x);
	
	int quit = 0;
	
	while(1) {
		switch(menu()) {
			case 1:
				// calls the display function
				display(x);
				pressEnter();
				break;
			case 2:
				// calls the addData function
				numRecords += addData(x);
				pressEnter();
				break;
				
			case 3:
				// calls the saveData function
				saveData(x);
				pressEnter();
				break;
				
			case 4:
				// calls the removeData function
				numRecords -= removeData(x);
				pressEnter();
				break;
				
			case 5:
				cout<<"\nProgram terminated!\n\n";
				quit = 1;
				break;
			default:
				cout<< "\nNot a valid input.\n";
				pressEnter();
		}
		if(quit==1)break;
	}
	
	return 0;
}


int displayHeader() {
	cout << "Program: Flow Studies - Fall 2022" << endl;
	cout << "Version: 1.0" << endl;
	cout << "Lab section: C" << endl;
	cout << "Produced by: Evan Barker" << endl;
	pressEnter();
	return 0;
}

int pressEnter() {
	cout << "\n<<< Press Enter to Continue>>>>\n";
	cin.get();
	return 0;
}
	

int readData(FlowList& object) {
	ifstream obj1("flow.txt");
	ListItem flow_year;
	
	if(obj1.fail()){
		cout << "Error opening file... quitting\n";
		exit(1);
	}
	
	int num_r = 0;
	while(!obj1.eof()) {
		obj1 >> flow_year.year >> flow_year.flow;
		object.create(flow_year);
		num_r++;
	}
	obj1.close();
	return num_r;
}

int menu() {
	int x;
	cout << "Please select on the following operations\n";
	cout << "   1. Display flow list, and the average\n";
	cout << "   2. Add data.\n";
	cout << "   3. Save data iinto the file\n";
	cout << "   4. Remove data\n";
	cout << "   5. Quit\n";
	cout << "   Enter your choice (1, 2, 3, 4 or 5)\n";
	cin.clear();
	cin >> x;
	return x;
}


	
void display(FlowList& object) {
	cout << "Year\tFlow(in billions of cubic meters)" << endl;
	object.print();
	cout << "\nThe annual average flow is: " << average(object) << " billion cubic meters" << endl;
}

double average(FlowList& object) {
	double add = 0;
	for(int i = 1; i <= numRecords; i++) {
		add += object.get_average(i).flow;
	}
	return add / numRecords;
}

int removeData(FlowList& object){
	int y;
	cout << "\nPlease enter the year you want to remove: ";
	cin >> y;
	int valid = object.remove(y);
	if(valid){
		cout << "\nRecord was successfully removed." << endl;
		return 1;
	}
	else{
		cout << "\nError: No such data." << endl;
		return 0;
	}
}

void saveData(FlowList& object){
	ofstream output("flow.txt");
	if(output.fail()){
		cout << "Error opening file\n";
		exit(1);
	}
	for(int i = 1; i <= numRecords; i++){
		output << fixed << setw(10) << left << object.get_average(i).year << setprecision(2) << object.get_average(i).flow << endl;
	}
	output.close();
	cout << "\nData saved into the file." << endl;
}

int addData(FlowList& object) {
	ListItem toadd;
	cout << "\nPlease enter a year: ";
	cin >> toadd.year;
	if(toadd.year < 0 || toadd.year > 2022) {
		cout << "\nError: invalid year." << endl;
		return 0;
	}
	cout << "\nPlease enter the flow: ";
	cin >> toadd.flow;
	int validation = object.create(toadd);
	if(validation){
		cout << "\nNew record inserted successfully." << endl;
		return 1;
	}
	else {
		cout << "\nError: duplicate data." << endl;
		return 0;
	}
}
