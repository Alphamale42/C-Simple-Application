//list.h


#ifndef list_h
#define list_h



struct ListItem {
	int year;
	double flow;
};

struct Node {
	ListItem item;
	Node *next;
};

class FlowList {
public:
	FlowList();
	~FlowList();
	int create(const ListItem& new_item);
	ListItem get_average(const int& position)const;
	int remove(const int& yr);
	void print() const;
	
private:
	Node *headH;
};
#endif
