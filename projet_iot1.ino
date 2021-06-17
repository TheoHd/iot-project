// C++ code
//
int LEDpin = 8;
#define PHOTOpin A5
#define TEMPpin A0
float volt; //le voltage du capteur
float temp; // On initialise la variable de température
int PINGpin = 7;
// variable pour le temps entre deux ondes et la distance
long duration, cm;
// valeur brute de la température
int valeur_brute;
//température en degrès celcius
float temperature_celcius;


void setup()
{
  //initialiser le moniteur série
  Serial.begin(9600);
  //initialiser la LED
  pinMode(LEDpin, OUTPUT);
  //initialiser la photorésistance
  pinMode(PHOTOpin, INPUT);
}

void loop()
{
  //lire la valeur de la photorésistance
  int sensor = analogRead(PHOTOpin);
  //afficher cette valeur dans le moniteur
  
  Serial.print(" luminosite: ");
  Serial.print(sensor);
  Serial.println();
  
  valeur_brute = analogRead(TEMPpin);

  temperature_celcius = valeur_brute * (5.0 / 1023.0 * 100.0);

  Serial.print(temperature_celcius);
  Serial.print("°C");
  Serial.println();
  
  if(temperature_celcius < 12){
    Serial.println("chauffage allumé");
  }else{
    Serial.println("Chauffage éteind");
  }
  
   if(sensor < 300 && temperature_celcius < 25 ){
    digitalWrite(LEDpin, HIGH); // la LED s'allume
  }else{
  	digitalWrite(LEDpin, LOW); // la led s'éteind
  }
  
  if(sensor < 300 ) {
    Serial.println("UV allumé");
  }else{
    Serial.println("UV éteind");
  }
  
  // capteur ultrason 
  
  // Morceau de code permettant de réinitialiser le capteur pour l’envoie d’une nouvelle onde
  pinMode(PINGpin, OUTPUT);
  digitalWrite(PINGpin, LOW);
  delayMicroseconds(2);
  digitalWrite(PINGpin, HIGH);
  delayMicroseconds(5);
  digitalWrite(PINGpin, LOW);

  // on utilise pulseIn pour recevoir une durée de type long
  pinMode(PINGpin, INPUT);
  duration = pulseIn(PINGpin, HIGH);

  // On converti la durée en distance grâce à une fonction que vous trouverez plus bas
  cm = microsecondsToCentimeters(duration);

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  if(cm > 170){
    Serial.println("Envoie notif");
  }

  delay(1000);
}

long microsecondsToCentimeters(long microseconds)
{
  // nous divisons la durée par la vitesse et par 2 pour avoir la distance d’un aller simple.
  return microseconds / 29 / 2;
}