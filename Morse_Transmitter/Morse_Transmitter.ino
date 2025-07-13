const int UNIT_TIME = 200; // Durata base in millisecondi
const int PIEZO_PIN = 8;   // Pin del piezo
const int TONE_FREQ = 700; // Frequenza del tono

// Mappatura del codice Morse
String getMorseCode(char c) {
  c = toupper(c);
  switch (c) {
    case 'A': return ".-";
    case 'B': return "-...";
    case 'C': return "-.-.";
    case 'D': return "-..";
    case 'E': return ".";
    case 'F': return "..-.";
    case 'G': return "--.";
    case 'H': return "....";
    case 'I': return "..";
    case 'J': return ".---";
    case 'K': return "-.-";
    case 'L': return ".-..";
    case 'M': return "--";
    case 'N': return "-.";
    case 'O': return "---";
    case 'P': return ".--.";
    case 'Q': return "--.-";
    case 'R': return ".-.";
    case 'S': return "...";
    case 'T': return "-";
    case 'U': return "..-";
    case 'V': return "...-";
    case 'W': return ".--";
    case 'X': return "-..-";
    case 'Y': return "-.--";
    case 'Z': return "--..";
    case '0': return "-----";
    case '1': return ".----";
    case '2': return "..---";
    case '3': return "...--";
    case '4': return "....-";
    case '5': return ".....";
    case '6': return "-....";
    case '7': return "--...";
    case '8': return "---..";
    case '9': return "----.";
    case ' ': return " ";
    default: return "";
  }
}

// Comunica un carattere Morse con LED e piezo
void signalMorseChar(String symbols) {
  for (int i = 0; i < symbols.length(); i++) {
    // Accendi LED e produci tono
    digitalWrite(LED_BUILTIN, HIGH);
    tone(PIEZO_PIN, TONE_FREQ);
    
    if (symbols[i] == '.') {
      delay(UNIT_TIME);
    } else if (symbols[i] == '-') {
      delay(3 * UNIT_TIME);
    }
    
    // Spegni LED e interrompi tono
    digitalWrite(LED_BUILTIN, LOW);
    noTone(PIEZO_PIN);
    
    // Pausa tra simboli
    if (i < symbols.length() - 1) {
      delay(UNIT_TIME);
    }
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIEZO_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Inserisci messaggio:");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readString();
    input.trim();
    input.toUpperCase();
    
    Serial.print("Trasmesso: ");
    Serial.println(input);
    
    for (int i = 0; i < input.length(); i++) {
      char c = input[i];
      String morseCode = getMorseCode(c);
      
      if (morseCode == " ") {
        delay(7 * UNIT_TIME); // Pausa tra parole
        Serial.print(" / ");
      } else if (morseCode != "") {
        signalMorseChar(morseCode);
        Serial.print(morseCode);
        Serial.print(" ");
        
        // Pausa tra lettere
        if (i < input.length() - 1 && getMorseCode(input[i+1]) != " ") {
          delay(3 * UNIT_TIME);
        }
      }
    }
    
    Serial.println("\nFine trasmissione!");
    delay(2000);
  }
}
