/*----- Use buttons on the left ----*/

ui_event *evt = NULL; // global

...
// in something like void RunPath_r(void) {
	if (chMBFetch(&app_mb, (msg_t*) (&evt), TIME_INFINITE) == MSG_OK) {
		switch (evt->type) {
			case UI_INPUT_BUTTON:
				if (evt->data.button_state == UI_BUTTON_7) {
					debug_display[6]++;
				}
				break;
	//        case UI_STATUSBAR_TICK:
	//          status_bar_redraw();
	//          break;
			default:
				break;
			}
	}

...

/*
  UI_BUTTON_UP,				anti-clockwise rotate
  UI_BUTTON_DOWN,			button 3/clockwise rotate
  UI_BUTTON_LEFT,
  UI_BUTTON_RIGHT,
  UI_BUTTON_ENTER,			button rotor
  UI_BUTTON_BACK,			button 8
  UI_BUTTON_1,				button 1
  UI_BUTTON_7,				button 7
  UI_BUTTON_RESERVED1,
  UI_BUTTON_RESERVED2,
  UI_BUTTON_RESERVED3
*/



/*----- Motor (defined in motor.h) -----*/

typedef struct{
	int16_t SetPoint;
	int16_t Feedback;

	board_status_t Board;
	motor_setting_t Setting;
	const uint8_t id;
	uint8_t Alive;
}MotorObj;

typedef struct{
  int16_t Voltage;      // in mV
  int16_t Current;      // in mA
  int16_t Temperature;  // in Degree Celsius
  int32_t EncoderCounter;
  uint16_t ADCValue;
  uint16_t State;
}__attribute__((packed)) board_status_t;

typedef struct{
    /** 
     *  IDLE  : Motor terminals is left open (not shorted or driven)
     *  BRAKE : Motor terminals are short
	 *  VMODE : Motor is running in V Mode
	 *  PMODE : Motor is running in P Mode
	 *  For VMODE and PMODE, if there is no correct set point command received,
     *  motor will be in brake state
     */
    //enum { IDLE = 0, BRAKE = 1, VMODE = 2, PMODE = 3 } Mode ;
  uint16_t Mode;
  float ScaleFactor;				// PID Controller SetPoint = Input SetPoint * ScaleFactor
  uint16_t AccelerationLimit;	// in Encoder count / CommandCycle
  uint16_t SpeedLimit;		// in Encoder count / CommandCycle
	uint16_t CommandCycle;		// in us
	uint16_t MotorVoltage;		// in mV
	uint16_t CurrentLimit;		// in mA
	int16_t kP;
	int16_t kI;
	int16_t kD;
	int16_t kFF;
}__attribute__((packed)) motor_setting_t;



M[0].SetPoint
M[0].Board.ADCValue



/*----- Servo (defined in servo.h) -----*/
typedef struct{
  int16_t command[8];
  int16_t current;
  uint8_t Alive;
}servo_t;
