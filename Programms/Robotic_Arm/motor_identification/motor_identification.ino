//DC motor identification with arduino nano
///////////////////////////////
//PROGRAMA PARA LA IDENTIFICACIÓN DE UN MOTOR DE CORRIENTE DIRECTA DC
///////////////////////////////
//LIBRERIA PARA UTILIZAR EL TIMER DEL ARDUINO
#include<TimerOne.h>
/////////////////////////////
//Declarar los pines
//Decalración de los pines de la placa de Arduino
//Pin_1A y el Pin_2A para definir el sentido del giro del motor
//Pin_EN para la señal PWM
const int Pin_1A=13;                  //Definir el sentido de giro
const int Pin_2A=12;                  //Definir el sentido de giro
const int Pin_EN=11;
//Declaración del pin de interrupcion externa
const int interruptPin=2;
////////////////////////////////
//Contar pulsos del encoder para caluclar la velocidad del motor
long unsigned int counter=0;        //contador de pulsos del encoder
//Variable de señal PWM
//PWM=voltaje promedio entregado al motor
int PWM=0;
///////////////////////////////
//Variable para almacenar la velocidad del motor en RPM
double velocidad_rpm=0;
/////////////////////////////////
//Variable de tiempo
float tiempo=0.0;
/////////////////////////////////


//Configuración de los modos de operacion de los pines (entradas/salidas)
void setup() {
  // put your setup code here, to run once:
  pinMode(Pin_1A, OUTPUT);
  pinMode(Pin_2A, OUTPUT);
  pinMode(Pin_EN, OUTPUT);
  pinMode(interruptPin, INPUT);
  //Sentido de giro del motor
  digitalWrite(Pin_1A, LOW);
  digitalWrite(Pin_2A, HIGH);
  /////////////////////////////////
  //Interrupcion en el encoder
  //Cada vez que se detecte un flanco de subida se ejecuta la interrupcion
  attachInterrupt(digitalPinToInterrupt(interruptPin),counting,RISING);      //Pin que va a generar la interrupcion, funcion que va a contar los pulsos, RISING=flanco de subida
  //Timer: se dispara cada 0.01 segundos
  Timer1.initialize(20000);
  //Asociar el timer a la interrupcion
  Timer1.attachInterrupt(ISR_RevolucionesPorMinuto);    //rutina de servicio de interrupcion
  //Comunicacion serial de 9600baudios
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  /////////////////////////////////
  //Generacion de la señal PWM
  //Opcion 1 --> entrada constante
  //Señal no aleatoria
  /*PWM=255;
  analogWrite(Pin_EN, PWM);
  delay(1000);
  PWM=0;
  analogWrite(Pin_EN, PWM);
  delay(1000);*/
  //Opcion 2 --> señal aleatoria
  PWM=random(50,255);        //señal pseudoaleatorio
  analogWrite(Pin_EN,PWM);
  delay(random(100,300));  
}

//Funciones de interrupcion y de conteo
//Funcion de conteo
void counting(){
  //Contador
  counter++;
}

//Funcion de velocidad
void ISR_RevolucionesPorMinuto(){
  //velocidad_RPM=(60)*contador/(resolucion_encoder*Ts)
  //Contador=numero de pulsos
  //Ts=periodo de muestreo
  velocidad_rpm=(60)*counter/(11*0.02);
  velocidad_rpm=velocidad_rpm/50;
  tiempo=tiempo+0.02; 
  /////////////////////////
  //Impresion de resultados
  Serial.print(PWM);
  Serial.print("\t");
  Serial.println(velocidad_rpm);
  counter=0;
}
