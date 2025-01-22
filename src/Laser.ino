#define MOTOR_X_STEP_PIN 1
#define MOTOR_X_DIR_PIN 3
#define MOTOR_Y_STEP_PIN 13
#define MOTOR_Y_DIR_PIN 12
#define LED_PIN 15

const int stepsPerPixelX = 10;
const int stepsPerPixelY = 5;
const int stepDelay = 200;
const int sizeX = 10;
const int sizeY = 10;

int pixels[sizeX * sizeY] = {0};

void setup() {
  pinMode(MOTOR_X_STEP_PIN, OUTPUT);
  pinMode(MOTOR_X_DIR_PIN, OUTPUT);
  pinMode(MOTOR_Y_STEP_PIN, OUTPUT);
  pinMode(MOTOR_Y_DIR_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
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
  change_status();
  if (work_status)
  {
    drawImage(sizeX, sizeY);
  }else{
    delay(10);
  }
}
