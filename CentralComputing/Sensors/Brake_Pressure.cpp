#include "../Sensor_Package.h"
#include <iostream>

using namespace std;

Brake_Pressure::Brake_Pressure(Sensor_Configuration configuration) : Sensor_Group(configuration) {
	
}

Brake_Pressure::~Brake_Pressure(){
	//do nothing
}

void Brake_Pressure::reset() {
	//TODO: implement resetting
}

void Brake_Pressure::update(Spi * spi) {

	switch(simulation) {
		case 0:
			refresh_data(spi);
			break;
		case 1:
			simulation_1();
			break;
	}
}

void Brake_Pressure::simulation_1() {
	auto start = Sensor_Package::start_time;
	auto now = Sensor_Package::get_current_time();
	auto difference = now - start;
	cout << difference << endl;
	
	//TODO calc some actual value
	
	sensor_group_mutex.lock();
	for(size_t i = 0; i < data.size(); i++) {
		data[i] = i;
	}
	sensor_group_mutex.unlock();
}
