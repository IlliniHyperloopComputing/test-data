#include "Pod_State.h"

// returns the current state as a E_States enum
Pod_State::E_States Pod_State::get_current_state() {
	return (E_States)StateMachine::getCurrentState();
}

/**
 * User controlled movement events
**/

void Pod_State::move_safety_setup() {

	BEGIN_TRANSITION_MAP							/* Current state */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Pod_Startup */
		TRANSITION_MAP_ENTRY(ST_SAFETY_SETUP)     	/* Safety Setup */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Safe Mode */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Functional test */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Launch ready */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight accel */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight coast */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight brake */
	END_TRANSITION_MAP(NULL)
}

void Pod_State::move_functional_tests(){
	BEGIN_TRANSITION_MAP							/* Current state */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Pod_Startup */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)     	/* Safety Setup */
		TRANSITION_MAP_ENTRY(ST_FUNCTIONAL_TEST)	/* Safe Mode */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Functional test */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Launch ready */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight accel */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight coast */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight brake */
	END_TRANSITION_MAP(NULL)
}

void Pod_State::move_safe_mode() {
	BEGIN_TRANSITION_MAP							/* Current state */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Pod_Startup */
		TRANSITION_MAP_ENTRY(ST_SAFE_MODE)     		/* Safety Setup */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Safe Mode */
		TRANSITION_MAP_ENTRY(ST_SAFE_MODE)			/* Functional test */
		TRANSITION_MAP_ENTRY(ST_SAFE_MODE)			/* Launch ready */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight accel */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight coast */
		TRANSITION_MAP_ENTRY(ST_SAFE_MODE)			/* Flight brake */
	END_TRANSITION_MAP(NULL)
}

void Pod_State::move_launch_ready() {
	BEGIN_TRANSITION_MAP							/* Current state */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Pod_Startup */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)     	/* Safety Setup */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Safe Mode */
		TRANSITION_MAP_ENTRY(ST_LAUNCH_READY)		/* Functional test */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Launch ready */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight accel */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight coast */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight brake */
	END_TRANSITION_MAP(NULL)
}

// it is important all states should move to braking when this function is called, this is for emergencies
void Pod_State::emergency_brake() {
	BEGIN_TRANSITION_MAP							/* Current state */
		TRANSITION_MAP_ENTRY(ST_FLIGHT_BRAKE)		/* SAFE MODE */
		TRANSITION_MAP_ENTRY(ST_FLIGHT_BRAKE)		/* FUNCTIONAL TEST */
		TRANSITION_MAP_ENTRY(ST_FLIGHT_BRAKE)		/* FLIGHT ACCEL */
		TRANSITION_MAP_ENTRY(ST_FLIGHT_BRAKE)		/* FLIGHT COAST */
		TRANSITION_MAP_ENTRY(ST_FLIGHT_BRAKE)		/* FLIGHT BRAKE */
		TRANSITION_MAP_ENTRY(ST_FLIGHT_BRAKE)		/* FLIGHT BRAKE */
		TRANSITION_MAP_ENTRY(ST_FLIGHT_BRAKE)		/* FLIGHT BRAKE */
		TRANSITION_MAP_ENTRY(ST_FLIGHT_BRAKE)		/* FLIGHT BRAKE */
	END_TRANSITION_MAP(NULL)
}

/**
 * Software controlled events
 **/

void Pod_State::accelerate() {
	BEGIN_TRANSITION_MAP							/* Current state */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Pod_Startup */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)     	/* Safety Setup */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Safe Mode */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Functional test */
		TRANSITION_MAP_ENTRY(ST_FLIGHT_ACCEL)			/* Launch ready */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight accel */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight coast */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight brake */
	END_TRANSITION_MAP(NULL)
}
void Pod_State::coast() {
	BEGIN_TRANSITION_MAP							/* Current state */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Pod_Startup */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)     	/* Safety Setup */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Safe Mode */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Functional test */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Launch ready */
		TRANSITION_MAP_ENTRY(ST_FLIGHT_COAST)			/* Flight accel */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight coast */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight brake */
	END_TRANSITION_MAP(NULL)
}

void Pod_State::brake() {
	BEGIN_TRANSITION_MAP							/* Current state */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Pod_Startup */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)     	/* Safety Setup */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Safe Mode */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Functional test */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Launch ready */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight accel */
		TRANSITION_MAP_ENTRY(ST_FLIGHT_BRAKE)			/* Flight coast */
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)			/* Flight brake */
	END_TRANSITION_MAP(NULL)
}


// State Machine State functions
void ST_Pod_Startup() {
	std::cout << "Entering: Pod Startup" << std::endl;
	//std::cout << GetCurrentState() << std::endl;
	// TODO implement here
}

void ST_Safety_Setup() {
	std::cout << "Entering: Safety Setup" << std::endl;
	//std::cout << GetCurrentState() << std::endl;
	// TODO implement here
}

void Pod_State::ST_Safe_Mode() {
	std::cout << "Entering: Safe Mode" << std::endl;
	//std::cout << GetCurrentState() << std::endl;
	// TODO implement here
}

void Pod_State::ST_Functional_Test() {
	std::cout << "Entering: Functional Test" << std::endl;
	// TODO implement here
}

void Pod_State::ST_Launch_Ready() {
	std::cout << "Entering: Launch Ready" << std::endl;
	// TODO implement here
}

void Pod_State::ST_Flight_Accel() {
	std::cout << "Entering: Flight Accel" << std::endl;

	// TODO implement here
}

void Pod_State::ST_Flight_Coast() {
	std::cout << "Entering: Flight Coast" << std::endl;
	
	// TODO implement here
}

void Pod_State::ST_Flight_Brake() {
	std::cout << "Entering: Flight Brake" << std::endl;
	
	// TODO implement here
}
