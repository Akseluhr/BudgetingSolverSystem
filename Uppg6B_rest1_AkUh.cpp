/*
================================================================================
Datorer och programmering, DoP, 10 hsp, termin/år: ST2020

Inlämningsuppgift nr 6b

Namn: Aksel Uhr

Personummer: 19970710-0195

Fyll i (alt. stryk det som INTE är relevant) av nedanstående:

Den fil som jag lämnar in går att kompilera och
programmet fungerar för alla de testdata som finns för uppgiften: Nej
     Om Nej, beskriv vilka testdata som ger problem:

     Allting fungerar forutom att sista raden (transaktionen) i filen ignoreras av programmet
     Forsokte atgardas i funktionen LaesEnTrans.

Jag har använt kompilator/editor (namn/version) GNU GCC compiler, Code::Blocks 13.12

Jag har använt följande dator (t.ex. PC, Mac, Annat):        Mac
      med operativsystemet (t.ex. WindowsXP, Windows7,...) : MacOs High Sierra v. 10.13.6

Jag har arbetat ungefär 15 timmar med denna uppgift (exklusive uppgift 6A)

================================================================================
*/
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <cmath>
#include <sstream>
using namespace std;

class Transaktion
 {
  private:
   string datum;
   string typ;
   string namn;
   double belopp;
   int ant_kompisar;
   string *kompisar; //arrayens namn är en pointer till arrayen själv och pekar på det första elementet
  public:
   Transaktion();
   ~Transaktion();
   Transaktion& operator=( const Transaktion& t);
   string haemta_namn();
   double haemta_belopp();
   int haemta_ant_kompisar();
   bool finnsKompis( string namnet );
   bool laesEnTrans( istream &is );
   void skrivEnTrans( ostream &os );
 };

 class Person
{
    public:
        Person();
        Person(string n, double b, double s);
        virtual ~Person();
        double haemta_betalat();
        double haemta_skyldig();
        string haemta_namn();
        void skrivUt();
    protected:
    private:
        string namn;
        double betalat_andras;   // ligger ute med totalt
        double skyldig;          // skyldig totalt
};

class PersonLista
 {
 private:
   int antal_pers;
   Person *pers;

 public:
   PersonLista();
   ~PersonLista();
    //PersonLista(int s);
    PersonLista& operator=( const PersonLista& t);
    PersonLista(const PersonLista &pl); //kopieringskonstruktor for djup kopiering
//   void assign(const ExtArray &)
   void laggTillEn( Person pny );
   void skrivUtOchFixa();
   double summaSkyldig();
   double summaBetalat();
   bool finnsPerson( const string& namn);
 };

class TransaktionsLista
{
 private:
   Transaktion *trans;
   int antalTrans;

 public:
   TransaktionsLista();
   ~TransaktionsLista();
   void laesin( istream & is );
   void skrivut( ostream & os );
   void laggTill( Transaktion & t );
   double totalkostnad();
   double liggerUteMed( string namnet );
   double aerSkyldig( string namnet );
  // void resize(int num);
   PersonLista FixaPersoner();

 };

int main(){
        //Variabeldeklaration + objektdeklaration
    int val = -1;
    string transInfo;
    string filNamnFirst;
    string filNamn;
    ifstream in;
    stringstream inp;
    Transaktion test;
    TransaktionsLista test2;
   /*Person test3;
    PersonLista test4; */


while(val != 0){

    in.open("/Users/akseluhr/Documents/Datorer_och_programmering/Uppg6B_AkUh/resa.txt"); //šppnar och laser in en fil
    test2.laesin(in);
    cout << "Valj i menyn nedan: " << endl;
    cout << "0. Avsluta. Alla transaktioner sparas pa fil. " << endl;
    cout << "1. Las in en transaktion fran tangentbordet. " << endl;
    cout << "2. Las in en transaktion fran en fil. " << endl;
    cout << "3. Skriv ut information om alla transaktioner. " << endl;
    cout << "4. Berakna totala kostnaden. " << endl;
    cout << "5. Hur mycket ar en viss person skyldig? " << endl;
    cout << "6. Hur mycket ligger en viss person ute med? " << endl;
    cout << "7. Lista alla personer mm och FIXA!!!" << endl;
    cin >> val;

    switch(val) {
            //Programmet avslutas
        case 0:
            break;
            //Laser in en transaktion fran tangentbordet (bool testa anvandes for kontroll av funktionen laesEnTrans returvarde)
        case 1: {
            cout << "Ange transaktionsdatum, transaktionstyp, betalarens namn, belopp, antal kompisar och kompisarnas namn. " <<endl;
            cin.ignore();
            getline(cin, transInfo);
            inp << transInfo;
            bool testa;
            testa = test.laesEnTrans(inp);
            cout << testa;
            break;
        }
            //Laser in en fil

        case 2: {
            cout << "Ange filnamn: " <<endl;
            cin >> filNamn;
            in.open(filNamn.c_str());
            test2.laesin(in);
            in.close();
            break;
        }
            // Skriver ut

        case 3:{
            ofstream ut;
            filNamn = "/Users/akseluhr/Documents/Datorer_och_programmering/Uppg6B_AkUh/resa.txt";
            ut.open(filNamn.c_str());
            test2.skrivut(ut);
            break;
        }
                    //Beraknar totala utgifter

        case 4:{
            double totKost = test2.totalkostnad();
            cout << "Den totala summan ar : "<< totKost << endl;
            break;
        }
                    //Beraknar vad en given person aer skyldig

        case 5:{
            string namn;
            cout << "Ange namn pa personen: " << endl;
            cin >> namn;
            double aerSkyldig = test2.aerSkyldig(namn);
            cout << namn << " ar skyldig: " << aerSkyldig <<endl;
            break;

        }
                        // Beraknar bad en given person ligger ute med.


        case 6:{
            string namn;
            cout << "Ange namn pa personen: " << endl;
            cin >> namn;
            double liggerUte = test2.liggerUteMed(namn);
            cout << namn << " ligger ute med: " << liggerUte << endl;
            break;
        }
                    //Skriver ut och beraknar allas utgifter och skulder

        case 7:{
            PersonLista personList;
            personList = test2.FixaPersoner();
            personList.skrivUtOchFixa();
            break;
        }
    }
  } return 0;
}


Transaktion::Transaktion()
{
    datum = "";
    typ = "";
    namn = "";
    belopp = 0.0;
    ant_kompisar = 0;
    kompisar = 0;
}

Transaktion::~Transaktion()
{
    delete[ ]kompisar;
    kompisar = 0;
}

Transaktion& Transaktion::operator=( const Transaktion& t){

    if (this != &t)
    {
      delete[] kompisar;
      datum = t.datum;
      typ = t.typ;
      namn = t.namn;
      belopp = t.belopp;
      ant_kompisar = t.ant_kompisar;
      kompisar = new string[ant_kompisar];
      for (int i=0; i < ant_kompisar; i++)
	  kompisar[i] = t.kompisar[i];
    }
  return *this;
}

//Selektioner
string Transaktion::haemta_namn(){
    return namn;
}

int Transaktion::haemta_ant_kompisar(){
    return ant_kompisar;
}

double Transaktion::haemta_belopp(){
    return belopp;
}
//om arrayen kompisar ar likamed namnet som skickas in i funktionen returnerar funk true, ananars false
bool Transaktion::finnsKompis(string namnet){

    for(int i = 0; i < ant_kompisar; i++){
        if(kompisar[i] == namnet){
            return true;
        }
    }return false;
}

//laser in m.h.a stream
bool Transaktion::laesEnTrans(istream &is){

        int n = 0;

        delete[] kompisar; //tar bort namnet i arrayen, viktigt for funktionen laesIn(). d.v.s frigor minne

        is >> datum >> typ >> namn >> belopp >> ant_kompisar;

        kompisar = new string[ant_kompisar]; //allokerar minne och initialiserar arrayen

        for (int i = 0; i < ant_kompisar; i++){
            is >> kompisar[i];

             /* if(i = ant_kompisar -1){
                     n += i;
                } */

            //kompisar[ant_kompisar-1] += '\n';  forsok till att lagga till radbyte efter sista kompisen i arrayen kompisar

//medan nasta char/chunk i filen ar ' ', fortsatter innehallet i filen att dras ut ur filen (annars fungerar loopen inte nar ett blankslag intraffar).
//om nasta chunk ar en ny rad och darefter slut pa filen, returneras false annars true.
        while(is.peek() == ' '){
                is.get();
        }
        if (is.peek() == '\n')
                break;
        }

        if(is.eof())  {
                return false;
        }
        else return !is.fail();
}
//skriver ut pa konsollen eller filen
void Transaktion::skrivEnTrans( ostream &os ){

    cout << datum <<"  "<< typ <<"  "<< namn <<"  "<< belopp <<"  "<< ant_kompisar<<"  ";

        for (int i = 0; i < ant_kompisar; i++){
            cout << kompisar[i] << "  ";
        }
        cout << endl;

    os << datum <<"  "<< typ <<"  "<< namn <<"  "<< belopp <<"  "<< ant_kompisar<<"  ";

        for (int i = 0; i < ant_kompisar; i++){
            os << kompisar[i] << "  ";
        }
        os << endl;
}

Person::Person()
{
    namn = "";
    betalat_andras = 0;
    skyldig = 0;
}

Person::~Person()
{
    //dtor
}
  //overlagrad konstruktor som kallas pa i en metod langre ned.
  //for att skapa ett personobjekt
Person::Person(string n, double b, double s){
    namn = n;
    betalat_andras = b;
    skyldig = s;

}
//getter

double Person::haemta_betalat(){
    return betalat_andras;
}
//getter
double Person::haemta_skyldig(){
    return skyldig;
}
//getter
string Person::haemta_namn(){
    return namn;
}
//om personen har betalat mer an vad hen ar skyldig ska hen ha fran potten
//om det ar tvartom, ar personen skyldig och ska ge till potten.
void Person::skrivUt(){

    if(betalat_andras > skyldig){
          cout << namn << " ligger ute med: " << betalat_andras << " och ar skyldig " << skyldig << ". Skall ha " << betalat_andras - skyldig << " fran potten." << endl;
    }
    else {

          cout << namn << " ligger ute med: " << betalat_andras << " och ar skyldig " << skyldig << ". Skall lagga " << skyldig - betalat_andras << " till potten." << endl;
    }
}
PersonLista::PersonLista(){

    antal_pers = 0;
    pers = 0;
}
/*PersonLista::PersonLista(const int s) : antal_pers(s.antal_pers){
    if(antal_pers > 0){
        pers = new Person[antal_pers];
    }
    else{
        pers = 0;
    }
} */
PersonLista& PersonLista::operator=( const PersonLista& pl) { //tilldelningskonstruktor

    if(this != &pl){
        delete[ ]pers;
        antal_pers = pl.antal_pers;
        pers = new Person[antal_pers];
        for (int i=0; i < antal_pers; i++)
        pers[i] = pl.pers[i];
    }
    return *this;
}
PersonLista::PersonLista(const PersonLista &pl) : antal_pers (pl.antal_pers){ //kopieringskonstruktor.

    if(antal_pers > 0){

        pers = new Person[antal_pers];

        for(int i = 0; i < antal_pers; i++){
            pers[i] = pl.pers[i];
        }
    }else{
        pers = 0;
    }
}

PersonLista::~PersonLista(){

    delete[]pers;
    pers = 0;
    //dtor
}

//Lagger till ny person i arrayen pers, antal_pers inkrementeras och därmed även arrayens längd
//attributen kopieras over till ett temp-objekt som darefter kopieras over till temp igen. Djup kopiering.
void PersonLista::laggTillEn(Person pny){

    Person *temp = new Person[antal_pers+1];

    for (int i = 0; i < antal_pers; i++){
      temp[i] = pers[i];
    }

  delete[]pers;

  pers = temp;
  antal_pers++;
  pers[antal_pers-1] = pny;

}

bool PersonLista::finnsPerson(const string& namn){

    //Transaktion t;

    for(int i = 0; i < antal_pers; i++){
        if(pers[i].haemta_namn() == namn){
            return true;
        }
    }return false;
}

//Hamtar varje summa for respektive person
double PersonLista::summaBetalat(){

    double resultat = 0;

    for(int i = 0; i < antal_pers; i++){
        resultat += pers[i].haemta_betalat();
    }return resultat;

}
//hamtar vad varje person ar skyldig

double PersonLista::summaSkyldig(){

    double resultat = 0;

    for(int i = 0; i < antal_pers; i++){
        resultat += pers[i].haemta_skyldig();
    }return resultat;
}
//skriver ut personlistan.
void PersonLista::skrivUtOchFixa(){

    for(int i = 0; i < antal_pers; i++){
        pers[i].skrivUt();
    }
}

TransaktionsLista::TransaktionsLista()
{
    antalTrans = 0;
    trans = 0;

}

TransaktionsLista::~TransaktionsLista()
{
    delete[]trans;
    trans = 0;
}

/*void TransaktionsLista::resize(int num){

  Transaktion *p = 0;     // Lokal variabel.
    const int blank = 0;

  if ( num > 0 )    // Om ny storlek ej är noll
    {
      p = new Transaktion[num]; // Skapa array med n elem.

        int i;
      for ( i = 0; i < num  && i < antalTrans; i++ ) //fyll på med element
	{
	  p[i] = trans[i];
	}
	    for ( ; i < num; i++ )      // Fyll resten med blanka .
        p[i] = "";
    }


  delete [] trans; // Avallokera minne.
  trans = p;       // Sätt array till nya arrayen.
  antalTrans = num;     // Sätt bufSize till nya storleken.

}} */

//laggertill en parson i listan tills laesentrans returnerar false
void TransaktionsLista::laesin(istream &is){

        Transaktion enTransaktion;

        while ( enTransaktion.laesEnTrans(is) )
        {
            laggTill( enTransaktion );

        }
}

//skriver ut transaktionslistan

void TransaktionsLista::skrivut(ostream & os ){

    cout << "Antal transaktioner: " << antalTrans <<endl;
    for(int i = 0; i < antalTrans; i ++){
        trans[i].skrivEnTrans(os);
    }

}
//lagger till i transaktionslistan
void TransaktionsLista::laggTill(Transaktion &t){

    //resize(antalTrans+1);
  /* trans[antalTrans] = t;
   antalTrans++; */

  Transaktion *temp = 0;
  temp = new Transaktion[antalTrans+1];

  for (int i = 0; i < antalTrans; i++){
      temp[i] = trans[i];

    }

  delete[]trans;

  trans = temp;
  antalTrans++;
  trans[antalTrans-1] = t;

}
//beraknar totala beloppet for exempelvis resa.txt
double TransaktionsLista::totalkostnad(){

        double totKostnad = 0;

        for(int i = 0; i < antalTrans; i++){
            totKostnad += trans[i].haemta_belopp();
        }

        return totKostnad;
}
//beraknar vad respektive person har betalat (+1 eftersom personerna betalar for sig sjalva ocksa)
double TransaktionsLista::liggerUteMed( string namnet ){

    double resultat = 0;

    for(int i = 0; i < antalTrans; i++){
        if (namnet == trans[i].haemta_namn()){
            resultat += trans[i].haemta_belopp() - (trans[i].haemta_belopp() /(trans[i].haemta_ant_kompisar() + 1));
        }
    }return resultat;
}
//beraknar vad respektive person ar skyldig potten
double TransaktionsLista::aerSkyldig( string namnet ){

    double resultat = 0;

    for(int i = 0; i < antalTrans; i++){
        if(trans[i].finnsKompis(namnet)){
            resultat += trans[i].haemta_belopp() /(trans[i].haemta_ant_kompisar() + 1);
        }
    }return resultat;
}
// om personen inte finns, skapas ett nytt objekt till denne m.h.a konstruktorn fran klassen Person.
//d.v.s personens namn, vad hen ligger ute med och aer skyldig.
//Slutligen laggs personen in i personlistan. returen ar viktig vid utsktift.

PersonLista TransaktionsLista::FixaPersoner(){

  PersonLista personlista = PersonLista (); //kallar pŒ konstruktorn
  string namn = "";

  for (int i = 0; i < antalTrans; i++){

      if (!personlista.finnsPerson (trans[i].haemta_namn())){

            namn = trans[i].haemta_namn();
            Person nyp = Person (namn, liggerUteMed(namn), aerSkyldig(namn));
            personlista.laggTillEn(nyp);
      }
    }

  return personlista;
}

/*
================================================================================
Här följer programkörningar för alla testdata:
==============================================

Valj i menyn nedan:
0. Avsluta. Alla transaktioner sparas pa fil.
1. Las in en transaktion fran tangentbordet.
2. Las in en transaktion fran en fil.
3. Skriv ut information om alla transaktioner.
4. Berakna totala kostnaden.
5. Hur mycket ar en viss person skyldig?
6. Hur mycket ligger en viss person ute med?
7. Lista alla personer mm och FIXA!!!
3

Antal transaktioner: 9
050615  transp  Eva  6000  5  Bosse  Kristin  Paul  Torsten  Stina
050721  mat  Eva  300  2  Bosse  Kristin
050721  mat  Paul  400  2  Torsten  Stina
050721  transp  Bosse  5000  3  Eva  Kristin  Paul
050721  transp  Stina  5000  1  Torsten
050722  boende  Kristin  200  1  Eva
050722  mat  Eva  300  2  Kristin  Bosse
050723  mat  Torsten  300  2  Paul  Stina
050724  mat  Paul  200  1  Stina

Valj i menyn nedan:
0. Avsluta. Alla transaktioner sparas pa fil.
1. Las in en transaktion fran tangentbordet.
2. Las in en transaktion fran en fil.
3. Skriv ut information om alla transaktioner.
4. Berakna totala kostnaden.
5. Hur mycket ar en viss person skyldig?
6. Hur mycket ligger en viss person ute med?
7. Lista alla personer mm och FIXA!!!
7

Eva ligger ute med: 5400 och ar skyldig 1350. Skall ha 4050 fran potten.
Paul ligger ute med: 366.667 och ar skyldig 2350. Skall lagga 1983.33 till potten.
Bosse ligger ute med: 3750 och ar skyldig 1200. Skall ha 2550 fran potten.
Stina ligger ute med: 2500 och ar skyldig 1333.33. Skall ha 1166.67 fran potten.
Kristin ligger ute med: 100 och ar skyldig 2450. Skall lagga 2350 till potten.
Torsten ligger ute med: 200 och ar skyldig 3633.33. Skall lagga 3433.33 till potten.

Valj i menyn nedan:
0. Avsluta. Alla transaktioner sparas pa fil.
1. Las in en transaktion fran tangentbordet.
2. Las in en transaktion fran en fil.
3. Skriv ut information om alla transaktioner.
4. Berakna totala kostnaden.
5. Hur mycket ar en viss person skyldig?
6. Hur mycket ligger en viss person ute med?
7. Lista alla personer mm och FIXA!!!
7

Eva ligger ute med: 600 och ar skyldig 0. Skall ha 600 fran potten.

================================================================================
Här skriver du en kort rapport om uppgiften:
- ett eller ett par stycken om vad uppgiften gick ut på,
- vilka svårigheter som fanns,
- vad du tyckte var besvärligt
- och hur du löste problemen.

Uppgiften syfar till att bekanta sig med dynamiska arrayer snarare an statiska. Till detta tillkommer destruktorer, tilldelningsoperatorer och kopieringskonstruktorer, vilket
var saval svart som besvarligt. Det var lange sedan jag var med om sa manga programkrascher och debugging var svart att fa till. Aterigen jobbade jag mig igenom uppgiften genom
att implementera klass for klass. Det var något lattare denna gang eftersom jag visste hur programmet skulle se ut i slutandan. En del research gjorde att jag snubblade in på
"rule of three" vilket underlattade nar jag loste uppgiften.

FRAGOR:

Assignment operator will be called when you want to assign an existing object from another one,
that means you might need to destroy/release some resources which the existing object hold before doing the assignment.



- Tilldelningsoperatorn tilldelar varden till objektets variabler och kallas nar man vill tilldela ett nuvarande objekt fran ett annat. Den kallas pa nar ett nytt transaktions-objekt
    skapas, dvs i laesentrans().

- "This" refererar till den nuvarande instansen av klassen. if (this != &t) bor saledes innebara att om den nuvarande instansen inte ar likamed adressen/referensen till/av t, sa
    genomfors koden nedan.

*/



