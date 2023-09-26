using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Left1;
extern motor Left2;
extern motor Left3;
extern motor Right1;
extern motor Right2;
extern motor Right3;
extern controller Controller1;
extern motor Catapult;
extern digital_out WingsA;
extern digital_out WingsB;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );