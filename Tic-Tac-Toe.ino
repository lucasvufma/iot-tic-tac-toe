#include <ESP8266WiFi.h>

const char* ssid = "";
const char* password = "";



WiFiServer server(80); //Shield irá receber as requisições das páginas (o padrão WEB é a porta 80)

String HTTP_req; 
String URLValue;

void processaPorta(byte porta, byte posicao, WiFiClient cl);

const byte qtdePinosDigitais = 9;
byte pinosDigitais[qtdePinosDigitais] = {16, 5, 4, 0, 2, 14, 12, 13, 15};
byte modoPinos[qtdePinosDigitais]     = {OUTPUT, OUTPUT,OUTPUT,OUTPUT, OUTPUT,OUTPUT,OUTPUT, OUTPUT,OUTPUT};
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
   
}

void loop()
{

    WiFiClient  client = server.available();


    if (client) { 
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) { 
              //Not a good pattern 
                String build = client.readString();
                Serial.println(build);
                int build1_pos=build.indexOf("P0",0);
                Serial.println(build1_pos);
                String build1 = build.substring(0,build1_pos);
                Serial.println(build1);

                int build2_pos=build.indexOf("P1",build1_pos);
                String build2 = build.substring(build1_pos+4,build2_pos);
                Serial.println(build2_pos);
                Serial.println(build2);
                
                int build3_pos=build.indexOf("P2",build2_pos);
                String build3 = build.substring(build2_pos+4,build3_pos);
                Serial.println(build3);
                Serial.println(build3_pos);
                client.flush();
  

                for(long i=1;i < 4 ;i++){
                  String substring="\"Fase";
                  substring+=i;
                  String substring2=substring+"\"";
                  String substring3=substring2+":\"ON\"";
                    if(build1.indexOf(substring3) != -1){
                      setOn(pinosDigitais[i]);
                      Serial.println(pinosDigitais[i]);
                      Serial.println(" Setando on ");
                    } else {
                      Serial.println(" Setando off");
                      setOff(pinosDigitais[i]);
                    }
            
                  }

                     for(long i=1;i < 4 ;i++){
                  String substring="\"Fase";
                  substring+=i;
                  String substring2=substring+"\"";
                  String substring3=substring2+":\"ON\"";
                    if(build2.indexOf(substring3) != -1){
                      setOn(pinosDigitais[i+3]);
                      Serial.println(pinosDigitais[i+3]);
                      Serial.println(" Setando on ");
                    } else {
                      Serial.println(" Setando off");
                      setOff(pinosDigitais[i+3]);
                    }
            
                  }

                     for(long i=1;i < 4 ;i++){
                  String substring="\"Fase";
                  substring+=i;
                  String substring2=substring+"\"";
                  String substring3=substring2+":\"ON\"";
                    if(build3.indexOf(substring3) != -1){
                      setOn(pinosDigitais[i+6]);
                      Serial.println(pinosDigitais[i+6]);
                      Serial.println(" Setando on ");
                    } else {
                      Serial.println(" Setando off");
                      setOff(pinosDigitais[i+6]);
                    }
            
                  }
          
                  client.stop(); 
               


                
            }
                            
                        
                
             
             
            }
        delay(1);     
        client.stop(); 
    } 
}

void setOn(byte porta){
  digitalWrite(porta,HIGH);
}
void setOff(byte porta){
  digitalWrite(porta,LOW);
}
