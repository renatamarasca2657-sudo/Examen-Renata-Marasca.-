
class SensorUltrasonico {
 public:
   int pinTrig;
   int pinEcho;
   long duracion;
   float distancia;

   SensorUltrasonico(int t, int e) {
     pinTrig = t;
     pinEcho = e;
     pinMode(pinTrig, OUTPUT);
     pinMode(pinEcho, INPUT);
   }

   float medirDistancia() {
     digitalWrite(pinTrig, LOW);
     delayMicroseconds(2);
     digitalWrite(pinTrig, HIGH);
     delayMicroseconds(10);
     digitalWrite(pinTrig, LOW);

     duracion = pulseIn(pinEcho, HIGH);
     distancia = duracion * 0.034 / 2;
     return distancia;
   }
};

class ServoMotor {
 public:
   int pin;
   Servo servo;

   ServoMotor(int p) {
     pin = p;
     servo.attach(pin);
   }

   void mover(int angulo) {
     servo.write(angulo);
   }
};

SensorUltrasonico sensor(23, 22);
ServoMotor servoMotor(9);

void setup() {
 Serial.begin(9600);
}

void loop() {
 float distancia = sensor.medirDistancia();
 Serial.println(distancia);

 if (distancia < 20) {
   servoMotor.mover(90);
 } else {
   servoMotor.mover(0);
 }

 delay(500);
}
