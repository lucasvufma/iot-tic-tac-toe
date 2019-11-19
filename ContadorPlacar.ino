#include <ESP8266WiFi.h>

const char* ssid = "***";
const char* password = "***";

WiFiServer server(80); //Shield irá receber as requisições das páginas (o padrão WEB é a porta 80)

String HTTP_req; 
String URLValue;

void processaPorta(byte porta, byte posicao, WiFiClient cl);

const byte qtdePinosDigitais = 2;
byte pinosDigitais[qtdePinosDigitais] = {0, 2};
byte modoPinos[qtdePinosDigitais]     = {OUTPUT, OUTPUT};
byte resetPort = 16;


void setup()
{         
    Serial.begin(115200);

    //Conexão na rede WiFi
    Serial.println();
    Serial.print("Conectando a ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi conectado!");

    // Inicia o servidor WEB
    server.begin();
    Serial.println("Server iniciado");

    // Mostra o endereco IP
    Serial.println(WiFi.localIP());
    pinMode(resetPort,OUTPUT);

    //Configura o modo dos pinos
    for (int nP=0; nP < qtdePinosDigitais; nP++) {
        pinMode(pinosDigitais[nP], modoPinos[nP]);
    }
    // Porta de Reset dos Contadores
    clockinPort(resetPort);
    clockinPort(resetPort);
}

void loop()
{

    WiFiClient  client = server.available();

    if (client) { 
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) { 
                String req = client.readStringUntil('}');
                Serial.println(req);
                client.flush();
                for (int nL=0; nL < qtdePinosDigitais; nL++) {
                  processaPorta(pinosDigitais[nL], nL, client,req);
                }
            }
                            
                        
                
             
             
            }
        delay(1);     
        client.stop(); 
    } 
}

void clockinPort(byte porta){
  if(porta == resetPort){
      digitalWrite(porta,LOW);
      delay(250);
      digitalWrite(porta,HIGH);
      delay(250);
      digitalWrite(porta,LOW);
    
      
  }
  else{
    digitalWrite(porta,HIGH);
    delay(500);
    digitalWrite(porta,LOW);
  
  }

}

void processaPorta(byte porta, byte posicao, WiFiClient cl,String req)
{
static boolean LED_status = 0;
String cHTML;

    cHTML = "P";
    cHTML += posicao;

     
        if (req.indexOf(cHTML) != -1) { 
           clockinPort(porta);
        } else if(req.indexOf("RESET") != -1){
          clockinPort(resetPort);
        }
        Serial.println(cHTML);
        Serial.println(LED_status);
        Serial.println(porta);
        digitalWrite(porta, LED_status);
        cl.stop();
    
   
}
