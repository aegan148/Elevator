#include"Lift.h"

void get_data(int& person, int& floor) {
	std::cout << "Enter number of persons from 2 to 20\n";
	while (!(std::cin >> person) ||std::cin.peek()!='\n' || person < 2 || person>20) {
		std::cin.clear();
		while (std::cin.get()!='\n');
		std::cout << "Incorrect data!\n" << "Reenter number of persons from 2 to 20\n";
	}
	std::cout << "Ok! Number of persons are " << person << std::endl << std::endl;
	std::cout << "Enter count of floor from 9 to 20\n";
	while (!(std::cin >> floor) || std::cin.peek() != '\n' || floor < 9 || floor>20) {
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Incorrect data!\n" << "Reenter number of floors from 9 to 20\n";
	}
	std::cout << "Ok! Number of floors are " << person << std::endl << std::endl;
	system("cls");
}

int main() {
	int number_of_person=NULL;
	int count_of_stage=NULL;
	get_data(number_of_person,count_of_stage); // ask for requred data
	lift l1(number_of_person, count_of_stage);
	l1.get_startPos(); //set all positin of person
	l1.who_are_you();// show people for a while
	Sleep(2000);
	l1.main_logic_direction_up();
	l1.main_logic_direction_down();
}