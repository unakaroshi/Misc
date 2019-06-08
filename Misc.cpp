#include <iostream>
#include <string>

#include "Signal.hpp"

// Slot as a normal function
void onSignal(const std::string &arg1, int arg2) {
  std::cout << arg1 << ": " << arg2 << std::endl;
}

// Slot in class
class TestClass
{
public:
  void onSignal(const std::string &arg1, int arg2) {
    std::cout << "In class " << arg1 << ": " << arg2 << std::endl;
  }
};

int main()
{        
  // create new signal
  Signal<const std::string&, int> signal;

  auto functionSlot = std::bind(onSignal, std::placeholders::_1,std::placeholders::_2);

  TestClass testClass;
  auto classSlot = std::bind(&TestClass::onSignal, &testClass,
    std::placeholders::_1, std::placeholders::_2);

  signal.connect(functionSlot);
  signal.connect(classSlot);

  signal.connect([](const std::string &arg1, int arg2) {
    std::cout << arg2 << " is " << arg1.c_str() << std::endl;          
  });

  signal.emit("the answer", 42);

  return 0;
}



// Programm ausführen: STRG+F5 oder "Debuggen" > Menü "Ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
