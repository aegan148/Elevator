#include <iomanip>
#include"Lift.h"

	lift::lift(int number_of_person, int count_of_stage) : number_people(number_of_person), counter_of_stage(count_of_stage) { mPeople = new people[number_people]; };
	lift::~lift() { delete[] mPeople; }
///////////////////////////////
	void lift::who_are_you() {
		for (int i = 0; i < number_people; i++) {
			std::cout << "I'm " << i << " person and i start from " << mPeople[i].get_stage() << " to " << mPeople[i].get_endstage() << std::endl;
		}
		std::cout << std::endl;
	}
//////////////////////////////
	void lift::get_startPos() {//initialization of persons
		person_on_stage.resize(counter_of_stage);
		person_into_lift.resize(counter_of_stage);
		for (int i = 0; i < number_people; i++) {
			mPeople[i].set_id(i);
			mPeople[i].set_stage(counter_of_stage);
			mPeople[i].set_endstage(counter_of_stage);
			mPeople[i].set_direction();
			person_on_stage[mPeople[i].get_stage()].push_back(mPeople[i]);
		}
	}
/////////////////////// showing
	void lift::show_process(const int&& a) { //rvalue bleaaaa
		system("cls");
		int temp_index_from = 0;
		int temp_index_to = counter_of_stage;
		if (!direction_lift) {
			temp_index_from = counter_of_stage - 1;
			temp_index_to = -1;
		}
		std::cout << std::setw(25) << "| " << a << " |" << std::endl << std::endl;
		while (temp_index_from != temp_index_to) {
			std::cout << "| ";
			if (person_into_lift[temp_index_from].size() == 0) {
				std::cout << " " << "__" << " ";
			}
			for (int j = 0; j < person_into_lift[temp_index_from].size(); j++) {
				std::cout << " " << person_into_lift[temp_index_from][j].get_id() << " ";
			}
			std::cout << " |";
			if (temp_index_from == a) { std::cout << "->"; }
			std::cout << std::setw(19) << "  / " << "stage --> " << temp_index_from << " /......";
			for (int j = 0; j < person_on_stage[temp_index_from].size(); j++) {
				std::cout << " " << person_on_stage[temp_index_from][j].get_id() << " ";
			}
			std::cout << std::endl;
			if (direction_lift) { temp_index_from++; }
			else { temp_index_from--; }
		}
		Sleep(1000);
	}
////////////////////////////////////////////// to up    to next iteration need to unit boof function of direction
	void lift::main_logic_direction_up() {
		bool succes_posadka = false;
		bool succes_visadka = false;
		//start moving to up stair
		for (int i = 0; i < counter_of_stage; i++) {// to up
			succes_posadka = false;
			succes_visadka = false;
			if (i == 0) { show_process(std::move(i)); }//if resalt go to show
			if (!person_into_lift[i].empty()) {//do you need to exit??
				for (int h = 0; h < person_into_lift[i].size();) {
					if (i == person_into_lift[i][h].get_endstage()) {
						person_into_lift[i][h].got_necessary_stage();//i've finished
						person_on_stage[i].push_back(person_into_lift[i][h]);//i'm going to floor
						person_into_lift[i].erase(person_into_lift[i].begin() + h);//i'm deleting from lift
						succes_visadka = true;
					}
					else { h++; }
				}
			}
			if (succes_visadka) { show_process(std::move(i)); }//if resalt go to show
			if (!person_on_stage[i].empty()) {// if you need to the elevator box-just come in
				for (int x = 0; x < person_on_stage[i].size();) {
					if (person_on_stage[i][x].get_direction_person() && direction_lift && i == person_on_stage[i][x].get_stage()) {// all direction is true mean to up
						person_into_lift[i].push_back(person_on_stage[i][x]);//i'm going to the lift box 
						person_on_stage[i].erase(person_on_stage[i].begin() + x);// i'm deleting from floor
						succes_posadka = true;
					}
					else { x++; }
				}
			}
			if (succes_posadka) { show_process(std::move(i)); }//if resalt go to show

			for (int x = 0; x < person_into_lift[i].size();) {// iteration of elevator
				if (i == counter_of_stage - 1) { break; }
				if (!person_into_lift[i].empty()) {
					person_into_lift[i + 1].push_back(std::move(person_into_lift[i][x]));//go to up stairs
					person_into_lift[i].erase(person_into_lift[i].begin() + x);//removing from preview floor
				}
				else { x++; }
			}
			if (i == counter_of_stage - 1) { direction_lift = false; break; }// finish of direction up? go reverse thrust
			show_process(std::move(i + 1));
		};
	}
////////////////////////////////////////// going to down
	void lift::main_logic_direction_down() {
		bool succes_posadka = false; // need for show. if there are smt changes mean true--->
		bool succes_visadka = false;
		//start going to down
		for (int i = counter_of_stage - 1; i >= 0; i--) {// to up
			if (!person_into_lift[i].empty()) {//do you need to exit here??
				for (int h = 0; h < person_into_lift[i].size();) {
					succes_posadka = false;
					succes_visadka = false;
					if (i == person_into_lift[i][h].get_endstage()) {
						person_into_lift[i][h].got_necessary_stage();//goodbay everyone
						person_on_stage[i].push_back(person_into_lift[i][h]);//i'm go to my floor
						person_into_lift[i].erase(person_into_lift[i].begin() + h);//i'm removing from lift box
						succes_visadka = true;
					}
					else { h++; }
				}
			}
			if (succes_visadka) { show_process(std::move(i)); }//if resalt go to show
			if (!person_on_stage[i].empty()) {// if you need to the elevator box-just come in
				for (int x = 0; x < person_on_stage[i].size();) {
					if (!person_on_stage[i][x].get_direction_person() && !person_on_stage[i][x].is_finish() && !direction_lift && i == person_on_stage[i][x].get_stage()) {// all direction is true mean to up
						person_into_lift[i].push_back(person_on_stage[i][x]);//i'm entering into elevator
						person_on_stage[i].erase(person_on_stage[i].begin() + x);// i'm removing from stage
						succes_posadka = true;
					}
					else { x++; }
				}
				if (succes_posadka) { show_process(std::move(i)); }//if resalt go to show
			}
			if (i == 0) {
				finish = true;
				break;
			}//break ,we are finished
			for (int x = 0; x < person_into_lift[i].size();) {// iteration of elevator
				if (i == 0) { break; }
				if (!person_into_lift[i].empty()) {
					person_into_lift[i - 1].push_back(person_into_lift[i][x]);//go to down floor
					person_into_lift[i].erase(person_into_lift[i].begin() + x);//removing from preview floor
				}
				else { x++; }
			}
			show_process(std::move(i - 1));// if resalt go to show
		};
		std::cout << "All person got required floor!\n";
	}