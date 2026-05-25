#include "ws2812b.h"
#include "main.h"

extern TIM_HandleTypeDef htim3;

static uint8_t led[RESET_L+24*LED_N+1]={0}; // utworzenie buforu pamieci dla DMA

static void value_to_bytes(uint32_t pos,uint8_t value){
	for(int i=0; i<8;i++){
		if(value & 0x80){ // and sprawdzajacy czy najstarszy bit = 1
			led[pos+i] = BIT_1_T; // jesli tak to ustawia 1 w buforze
		}else{
			led[pos+i]= BIT_0_T;
		}
		value <<=1; // przesuniecie wszystkich bitow w lewo
	}
}



void ws2812b_init(void){
	// przypisanie do diod wartości PWM odpowiadające logcznemu 0
	for(int i=RESET_L; i<RESET_L+24*LED_N;i++){
		led[i]=BIT_0_T;
	}
	//ustawienie bitu stopu
	led[RESET_L+24*LED_N] = 100;

	HAL_TIM_Base_Start(&htim3); // uruchomienie licznika
	ws2812b_update();
}

void ws2812b_update(void){
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t*)led, sizeof(led)); // transfer DMA do rejestru timera
}

void ws2812b_set_color(uint32_t led_n,uint8_t green,uint8_t red,uint8_t blue){
	value_to_bytes(RESET_L + led_n*24,green); // ustawienie koloru zielonego, format bitow jest GRB dlatego zielony jest pierwszy
	value_to_bytes(RESET_L + led_n*24+8,red); // ustawienie niebieskiego na kolejnych 8 bitach
	value_to_bytes(RESET_L + led_n*24+16 ,blue); // ustaiwienie czerwonego
}
