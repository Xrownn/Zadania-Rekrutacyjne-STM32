#include "spx25.h"
#include "math.h"

#define Vcc 3.3f
// stałe do obliczeń wiglotności
#define Vmin 0.0f
#define Vmax Vcc
#define Omin 0.0f
#define Omax 100.0f
// stałe do obliczeń pH
#define pH_ref 7.0f
#define V_ref Vcc/2.0f
// stałe do obliczeń temperatury
#define T0 273.0f
#define V0 0.0f
#define k 0.25f/Vcc
// wyniki pomiarów
float soil_moisture = 0;
float soil_pH = 0;
float soil_temp = 0;

// funckja ustawiajaca mierzony parametr
void spx25_set_mode(GPIO_PinState ctrl0, GPIO_PinState ctrl1){
	HAL_GPIO_WritePin(CTRL0_SP_GPIO_Port, CTRL0_SP_Pin, ctrl0);
	HAL_GPIO_WritePin(CTRL1_SP_GPIO_Port, CTRL1_SP_Pin, ctrl1);
}

// funckja interpretująca pomiary
void spx25_measurement_conversion(uint8_t selected_mode,uint16_t Vad_analog_read){

	// przeliczanie odczytu z wejścia analogowego na faktycznie napięcie
	float Vad = ((float)Vad_analog_read/ 4095.0f)*Vcc;

	// przeliczanie wyniku pomiaru na faktyczne wartości
	switch(selected_mode){
	case 1:
		soil_moisture = (Vad-Vmin)/(Vmax-Vmin)*(Omax-Omin)+Omin;
		break;
	case 2:
		soil_pH = pH_ref+ log10f(Vad/V_ref);
		break;
	case 3:
		soil_temp = T0*expf(k*(Vad-V0));
		break;
	}
}

