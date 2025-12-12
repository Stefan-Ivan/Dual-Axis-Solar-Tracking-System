#include <Servo.h> //declararea bibliotecii servo pentru controlul motoarelor
Servo orizontal; // declararea obiectului orizontal
int pozitie_orizontala = 180; //stabilirea pozitiei initiale a servomotorului orizontal
int pozitie_orizontala_maxima = 180;
int pozitie_orizontala_minima = 65;
Servo vertical; // declararea obiectului vertical
int pozitie_verticala = 45; //stabilirea pozitiei initiale a servomotorului vertical
int pozitie_verticala_maxima = 80;
int pozitie_verticala_minima = 15;
//asocierea fotorezistoarelor catre pinii respectivi
int Fotorezistor_SJ = 0; //Fotorezistor stanga-jos
int Fotorezistor_DJ = 1; //Fotorezistor dreapta-jos
int Fotorezistor_SS = 2; //Fotorezistor stanga-sus
int Fotorezistor_DS = 3; //fotorezistor dreapta-sus
void setup()
{
Serial.begin(9600);
orizontal.attach(9);
vertical.attach(10);
orizontal.write(180);
vertical.write(45);
delay(3000);
}
void loop()

{
int stanga_jos = analogRead(Fotorezistor_SJ); // valoarea fotorezistorului din stanga-jos
int dreapta_jos = analogRead(Fotorezistor_DJ); // valoarea fotorezistorului din dreapta-jos
int stanga_sus = analogRead(Fotorezistor_SS); // valoarea fotorezistorului din stanga-sus
int dreapta_sus = analogRead(Fotorezistor_DS); // valoarea fotorezistorului din dreapta-sus
int viteza = 10; int toleranta = 50; //definirea tolerantei fotorezistoarelor si a vitezei servomotoarelor
int medie_sus = (stanga_sus + dreapta_sus) / 2;
int medie_dreapta = (dreapta_jos + dreapta_sus) / 2;
int medie_stanga = (stanga_jos + stanga_sus) / 2;
int medie_jos = (stanga_jos + dreapta_jos) / 2;
int diferenta_verticala = medie_sus - medie_jos;
int diferenta_orizontala = medie_stanga - medie_dreapta;
//Serial.print(medie_sus);
//Serial.print(" ");
//Serial.print(medie_dreapta);
//Serial.print(" ");
//Serial.print(medie_stanga);
//Serial.print(" ");
//Serial.print(medie_jos);
//Serial.print(" ");
//Serial.print(viteza);
//Serial.print(" ");
//Serial.print(toleranta);
//Serial.println(" ");
if (-1*toleranta > diferenta_verticala || diferenta_verticala > toleranta)
// verificare dacă diferența pe verticală este mai mare decât toleranța și compararea între cele două zone de interes
{
if (medie_sus > medie_jos)
{
pozitie_verticala = ++pozitie_verticala;
if (pozitie_verticala > pozitie_verticala_maxima)
{
pozitie_verticala = pozitie_verticala_maxima;
}
}
else if (medie_sus < medie_jos)
{
pozitie_verticala= --pozitie_verticala;
if (pozitie_verticala < pozitie_verticala_minima)
{
pozitie_verticala = pozitie_verticala_minima;
}
}
vertical.write(pozitie_verticala);
}
if (-1*toleranta > diferenta_orizontala || diferenta_orizontala > toleranta)
// verifică dacă diferența pe orizontală este mai mică decât toleranța și compară cele două zone de interes
{
if (medie_stanga > medie_dreapta)
{
pozitie_orizontala = --pozitie_orizontala;
if (pozitie_orizontala < pozitie_orizontala_minima)
{
pozitie_orizontala = pozitie_orizontala_minima;
}
}
else if (medie_stanga < medie_dreapta)
{
pozitie_orizontala = ++pozitie_orizontala;
if (pozitie_orizontala > pozitie_orizontala_maxima)
{
pozitie_orizontala = pozitie_orizontala_maxima;
}
else if (medie_stanga = medie_dreapta)
{
// exista echilibru deci nu face nimic
}
orizontal.write(pozitie_orizontala);
}
delay(viteza); //Se întârzie iterația cu timpul propus
}
}
