#include <SPI.h> //Importamos librería comunicación SPI
#include <Ethernet.h> //Importamos librería Ethernet
#include <DHT11.h>


byte mac[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};
EthernetServer servidor(80); //Puerto en el 80
IPAddress dnServer(156, 35, 14 , 2);
IPAddress gateway(192, 168, 61, 13);
IPAddress subnet(255, 255, 255, 0);

// Que cada uno ponga la IP de su grupo 201, 202, 203, que es el de su caja
IPAddress ip(192, 168, 61, 207);

int led = 8;

String static GOOGLE_KEY = "AIzaSyCP6zlYtXAvIBzj3820RHQvNOYf3GwNFlI";
float latitud=43.3579649;
float longitud=-5.8733862;

//Sensor
int pin_sensor = 9;
DHT11 dht11(pin_sensor);

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);
  servidor.begin();
  Serial.println("Setup");
  // Imprimir la IP
  Serial.println(Ethernet.localIP());

  // Inicializar el led
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

}

void loop() {
  EthernetClient cliente = servidor.available();

  // Trata temperaturas **************

  float temperatura, humedad;

  int codigoSalida = dht11.read(humedad, temperatura);

  Serial.println(codigoSalida);
  if (codigoSalida == 0) { // Tiene que retornar 0,
    Serial.println("Temperatura: " + String(temperatura));
    Serial.println("Humedad: " + String(humedad));
    Serial.println("--------------------------------");
  } else {
    // No retorna 0, luego hay un error
    Serial.println("Error:" + String(codigoSalida));
  }

  //delay(2000); // Actualizar cada dos segundos

  //*******************
  Serial.println(String(temperatura) + " Humedad" + String(humedad));
  if (cliente) {
    enviarWeb(cliente, temperatura, humedad);

    Serial.println("Nueva peticion");
    String peticion = "";
    while (cliente.connected()) {
      if (cliente.available()) {

        char c = cliente.read(); //Leer petición carácter a carácter
        peticion.concat(c); // concatenar en un string
        // Ha acabado la peticion http
        // Si contiene index responder con una web

        // la petición ha acabado '\n' y contiene la cadena "index"
        if (c == '\n' && peticion.indexOf("index") != -1) {
          Serial.println("Responder");
          // Serial.println(peticion);

          // contiene la cadena "encender"
          if (peticion.indexOf("encender") != -1) {
            digitalWrite(led, HIGH);
            Serial.println("Encender Led");
          }
          // contiene la cadena "apagar"
          if (peticion.indexOf("apagar") != -1) {
            Serial.println("Apagar led");
            digitalWrite(led, LOW);
          }

          // Enviamos al cliente una respuesta HTTP
          cliente.println("HTTP/1.1 200 OK");
          cliente.println("Content-Type: text/html");
          cliente.println();
          break;
        }
      }
    }

    // Pequeña pausa para asegurar el envio de datos
    delay(1000);
    cliente.stop();// Cierra la conexión
  }
}

void enviarWeb(EthernetClient cliente, int temperatura, int humedad) {
  // Enviamos al cliente una respuesta HTTP
  cliente.println("HTTP/1.1 200 OK");
  cliente.println("Content-Type: text/html");
  cliente.println();
  cliente.println("<html>");
  cliente.println("<head>");
  cliente.println("<style>");
  cliente.println("#map {");
  cliente.println("height: 400px;");
  cliente.println("width: 100%;");
  cliente.println("}");
  cliente.println("</style>");
  cliente.println("</head>");
  cliente.println("<body>");
  cliente.println("<h1>Control de luz por internet</h1>");
  cliente.println("<h2><a href='index.html?p=encender'>Encender</a></h2>");
  cliente.println("<h2><a href='index.html?p=apagar'>Apagar</a></h2>");
  cliente.println("</b>");
  cliente.println("<div id=\"map\"></div>");
  cliente.println("<script>");
  cliente.println("function initMap() {");
  cliente.println("var uluru = {lat: "+String(latitud) +", lng: "+ String(longitud)+"};");
  cliente.println("var map = new google.maps.Map(document.getElementById('map'), {");
  cliente.println("zoom: 4,");
  cliente.println("center: uluru");
  cliente.println("});");
  cliente.println("var marker = new google.maps.Marker({");
  cliente.println("position: uluru,");
  cliente.println("map: map");
  cliente.println("});");
  cliente.println("}");
  cliente.println("</script>");
  cliente.println("<script async defer");
  cliente.println("src=\"https://maps.googleapis.com/maps/api/js?key="+GOOGLE_KEY+"&callback=initMap\">");
  //cliente.println("src=\"https://maps.googleapis.com/maps/api/js?key=AIzaSyCP6zlYtXAvIBzj3820RHQvNOYf3GwNFlI&callback=initMap\">");
  cliente.println("</script>");
  cliente.println("<b>Temperatura " + String(temperatura) + " </b>");
  cliente.println("<b>Humedad " + String(humedad) + " </b>");
  cliente.println("</b></body>");
  cliente.println("</html>");
}

