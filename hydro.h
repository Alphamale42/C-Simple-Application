#ifndef hydro_h
#define hydro_h

// all function prototypes stored below:
int displayHeader();
//int readData(const FlowList& x);
int pressEnter();
int menu();
int readData(FlowList& object);
double average(FlowList& object);
int removeData(FlowList& object);
void saveData(FlowList& object);
int addData(FlowList& object);
void display(FlowList& object);

#endif
