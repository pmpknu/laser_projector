#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#define MOTOR_X_STEP_PIN 1
#define MOTOR_X_DIR_PIN 3
#define MOTOR_Y_STEP_PIN 13
#define MOTOR_Y_DIR_PIN 12
#define LED_PIN 15

const char *ssid = "nodetest";
const char *password = "nodetest";

ESP8266WebServer server(80);

const int stepsPerPixelX = 10;
const int stepsPerPixelY = 5;
const int stepDelay = 200;
const int sizeX = 10;
const int sizeY = 10;

int pixels[sizeX * sizeY] = {0};
bool work_status = false;

void setup() {
  Serial.begin(115200);
  pinMode(MOTOR_X_STEP_PIN, OUTPUT);
  pinMode(MOTOR_X_DIR_PIN, OUTPUT);
  pinMode(MOTOR_Y_STEP_PIN, OUTPUT);
  pinMode(MOTOR_Y_DIR_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");

  // Route to serve the HTML page
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", generateHTML());
  });

  // Route to handle POST data
  server.on("/update", HTTP_POST, []() {
    if (server.hasArg("plain")) {
      StaticJsonDocument<256> doc;
      DeserializationError error = deserializeJson(doc, server.arg("plain"));

      if (error) {
        server.send(400, "application/json", "{\"status\":\"error\",\"message\":\"Invalid JSON\"}");
        return;
      }

      for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
          pixels[y * sizeX + x] = doc[y][x];
        }
      }

      server.send(200, "application/json", "{\"status\":\"success\"}");
      work_status = true; // Start drawing after receiving new data
    } else {
      server.send(400, "application/json", "{\"status\":\"error\",\"message\":\"No data received\"}");
    }
  });

  server.begin();
  Serial.println("HTTP server started.");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

String generateHTML() {
  String html = "<!DOCTYPE html><html><body><h1>Laser Projector</h1><table>";
  for (int y = 0; y < sizeY; y++) {
    html += "<tr>";
    for (int x = 0; x < sizeX; x++) {
      html += "<td><input type='checkbox' id='c" + String(y) + String(x) + "'/></td>";
    }
    html += "</tr>";
  }
  html += "</table><button onclick='sendData()'>Send</button>";
  html += R"(
    <script>
      function sendData() {
        const data = [];
        for (let y = 0; y < 10; y++) {
          const row = [];
          for (let x = 0; x < 10; x++) {
            row.push(document.getElementById('c' + y + x).checked ? 1 : 0);
          }
          data.push(row);
        }
        fetch('/update', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify(data)
        }).then(response => response.json())
          .then(data => alert('Data sent: ' + JSON.stringify(data)))
          .catch(err => alert('Error: ' + err));
      }
    </script>
  )";
  html += "</body></html>";
  return html;
}

void putPixel(int x, int y) {
  int index = y * sizeX + x;
  int sig = pixels[index];
  digitalWrite(LED_PIN, sig);
}

void stepMotor(int stepPin, int dirPin, int steps, bool direction) {
  digitalWrite(dirPin, direction);

  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
}

void moveToX(int targetX, int currentX) {
  int steps = abs(targetX - currentX) * stepsPerPixelX;
  bool direction = targetX > currentX;
  stepMotor(MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN, steps, direction);
}

void moveToY(int targetY, int currentY) {
  int steps = abs(targetY - currentY) * stepsPerPixelY;
  bool direction = targetY > currentY;
  stepMotor(MOTOR_Y_STEP_PIN, MOTOR_Y_DIR_PIN, steps, direction);
}

void moveToPixel(int x, int y, int &currentX, int &currentY) {
  moveToX(x, currentX);
  currentX = x;

  moveToY(y, currentY);
  currentY = y;
}

void drawLine(int y, int startX, int endX, int &currentX, int &currentY) {
  moveToPixel(startX, y, currentX, currentY);

  if (startX < endX) {
    for (int x = startX; x <= endX; x++) {
      moveToPixel(x, y, currentX, currentY);
      putPixel(x, y);
    }
  } else {
    for (int x = startX; x >= endX; x--) {
      moveToPixel(x, y, currentX, currentY);
      putPixel(x, y);
    }
  }
}

void drawImage(int width, int height) {
  int currentX = 0, currentY = 0;

  for (int y = 0; y < height; y++) {
    if (y % 2 == 0) {
      drawLine(y, 0, width - 1, currentX, currentY);
    } else {
      drawLine(y, width - 1, 0, currentX, currentY);
    }
  }
  moveToPixel(0, 0, currentX, currentY);
}

void loop() {
  server.handleClient();
  if (work_status) {
    drawImage(sizeX, sizeY);
  } else {
    delay(10);
  }
}
