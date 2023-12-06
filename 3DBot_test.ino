#include <math.h>
#include "ABLocks_TimerFreeTone.h"
#include "IRremote.h"

double Temperatura;
double Distancia;
double Iluminacion;
String s_Mando;
boolean b_Sensor_Izquierdo;
boolean b_Sensor_Derecho;
IRrecv ir_rx(11);
decode_results ir_rx_results;

double fnc_3dbot_ntc(int _rawval){
	double adcMax=1023.0;
	double Vs=5.0; //3.3v?
	double R1 = 10000.0;   // voltage divider resistor value
	double Beta = 3950.0;  // Beta value
	double To = 298.15;    // Temperature in Kelvin for 25 degree Celsius
	double Ro = 10000.0;   // Resistance of Thermistor at 25 degree Celsius
	double adc = _rawval;
	double Vout = adc * Vs/adcMax;
	double Rt = R1 * Vout / (Vs - Vout);
	double T = 1/(1/To + log(Rt/Ro)/Beta);    // Temperature in Kelvin
	double Tc = T - 273.15;                   // Celsius
	//double Tf = Tc * 9.0 / 5.0 + 32.0;            // Fahrenheit
return Tc;
}

double fnc_3dbot_distance(int _t, int _e){
	unsigned long dur=0;
	digitalWrite(_t, LOW);
	delayMicroseconds(5);
	digitalWrite(_t, HIGH);
	delayMicroseconds(10);
	digitalWrite(_t, LOW);
	dur = pulseIn(_e, HIGH, 18000);
	if(dur==0)return 999.0;
	return (dur/57);
}

String fnc_ir_rx_decode_txt()
{
	char buff[16];
	buff[0]=0;
	if(ir_rx.decode(&ir_rx_results))
	{
		sprintf(buff,"%08lX",(unsigned long)ir_rx_results.value);
		ir_rx.resume();
	}
	return String(buff);
}

void fnc_3dbot_move(int _t, int _speed){
	switch(_t){
		case 0: //stop
			digitalWrite(9, LOW);
			digitalWrite(10, LOW);
			break;
		case 1: //fw
			digitalWrite(7, LOW);
			digitalWrite(8, HIGH);
			digitalWrite(12, LOW);
			digitalWrite(13, HIGH);
			analogWrite(9,_speed);
			analogWrite(10,_speed);
			break;
		case 2: //bw
			digitalWrite(7, HIGH);
			digitalWrite(8, LOW);
			digitalWrite(12, HIGH);
			digitalWrite(13, LOW);
			analogWrite(9,_speed);
			analogWrite(10,_speed);
			break;
		case 3: //left
			digitalWrite(7, LOW);
			digitalWrite(8, HIGH);
			digitalWrite(12, LOW);
			digitalWrite(13, HIGH);
			analogWrite(9,0);
			analogWrite(10,_speed);
			break;
		case 4: //right
			digitalWrite(7, LOW);
			digitalWrite(8, HIGH);
			digitalWrite(12, LOW);
			digitalWrite(13, HIGH);
			analogWrite(9,_speed);
			analogWrite(10,0);
			break;
		case 5: //rotate left
			digitalWrite(7, HIGH);
			digitalWrite(8, LOW);
			digitalWrite(12, LOW);
			digitalWrite(13, HIGH);
			analogWrite(9,_speed);
			analogWrite(10,_speed);
			break;
		case 6: //rotate right
			digitalWrite(7, LOW);
			digitalWrite(8, HIGH);
			digitalWrite(12, HIGH);
			digitalWrite(13, LOW);
			analogWrite(9,_speed);
			analogWrite(10,_speed);
			break;
		case 7: //left bw
			digitalWrite(7, HIGH);
			digitalWrite(8, LOW);
			digitalWrite(12, HIGH);
			digitalWrite(13, LOW);
			analogWrite(9,0);
			analogWrite(10,_speed);
			break;
		case 8: //right bw
			digitalWrite(7, HIGH);
			digitalWrite(8, LOW);
			digitalWrite(12, HIGH);
			digitalWrite(13, LOW);
			analogWrite(9,_speed);
			analogWrite(10,0);
			break;
	}
}

void setup()
{


	Serial.begin(9600);
	Serial.flush();
	while(Serial.available()>0)Serial.read();

	pinMode(A3, INPUT);
	pinMode(5, INPUT);
	pinMode(A0, OUTPUT);
	pinMode(6, INPUT);
	pinMode(4, OUTPUT);
	pinMode(2, INPUT);
	pinMode(A2, INPUT);
	ir_rx.enableIRIn();
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);

	Serial.println(String("PRUEBA DE COMPONENTES"));
	Serial.println(String("PARA 3DBOT"));
	Temperatura = fnc_3dbot_ntc(analogRead(A3));
	Serial.print(String("Temperatura = "));
	Serial.println(Temperatura);

}


void loop()
{

  	b_Sensor_Izquierdo = (!digitalRead(5));
  	if ((b_Sensor_Izquierdo == true)) {
  		TimerFreeTone(A0,1500,200);
  	}

  	b_Sensor_Derecho = (!digitalRead(6));
  	if ((b_Sensor_Derecho == true)) {
  		TimerFreeTone(A0,1000,200);
  	}

  	Distancia = fnc_3dbot_distance(4,2);
  	if ((Distancia <= 10)) {
  		TimerFreeTone(A0,800,200);
  	}

  	Iluminacion = analogRead(A2);
  	if ((Iluminacion <= 500)) {
  		TimerFreeTone(A0,600,200);
  	}

  	s_Mando = fnc_ir_rx_decode_txt();
  	if (String(s_Mando).equals(String("00FFA857"))) {
  		fnc_3dbot_move(2,220);
  		delay(1000);
  		fnc_3dbot_move(0,220);
  	}

  	if (String(s_Mando).equals(String("00FF629D"))) {
  		fnc_3dbot_move(1,220);
  		delay(1000);
  		fnc_3dbot_move(0,220);
  	}

  	if (String(s_Mando).equals(String("00FFC23D"))) {
  		fnc_3dbot_move(6,220);
  		delay(1000);
  		fnc_3dbot_move(0,220);
  	}

  	if (String(s_Mando).equals(String("00FF22DD"))) {
  		fnc_3dbot_move(5,220);
  		delay(1000);
  		fnc_3dbot_move(0,220);
  	}

}