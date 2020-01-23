#include"windows.h"

class people {
public:
	people() {};
	~people() {};
	void set_stage(const int& size) { start_stage = rand() % size; }
	const int& get_stage() { return start_stage; }
	void set_id(const int& temp_id) { id = temp_id; }
	const int& get_id() { return id; }
	void set_endstage(const int& size) { end_stage = rand() % size; while (start_stage == end_stage) { end_stage = rand() % size; } }
	const int& get_endstage() { return end_stage; }
	void set_direction() { if (start_stage < end_stage) { direction_person = true; } else { direction_person = false; } } //try -need to up, false-down
	void got_necessary_stage() { is_necessary_stage = true; }
	const int& is_finish() { return is_necessary_stage; }
	const int& get_direction_person() { return direction_person; }
private:
	int id=0 ;
	int start_stage = 0;//from?
	int end_stage = 0;//to?
	bool direction_person = true;// mean you going to up
	bool is_necessary_stage = false;//are yo finised?
};
