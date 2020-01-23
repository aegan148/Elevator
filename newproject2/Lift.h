#include<vector>
#include<iostream>
#include"Person.h"

class lift {
public:
	lift(int number_of_person, int count_of_stage);
	~lift();
	void who_are_you();
	void get_startPos();
	void show_process(const int&& a);
	void main_logic_direction_up();
	void main_logic_direction_down();
private:
	bool direction_lift = true; //true mean go to up
	bool finish = false;
	const int number_people;
	people* mPeople; 
	const int counter_of_stage;
	std::vector<std::vector<people>> person_on_stage;
	std::vector<std::vector<people>> person_into_lift;
};
