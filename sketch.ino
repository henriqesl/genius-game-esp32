#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const uint8_t LED[] = {4, 5, 6, 7};           // LED pins (green, yellow, red, blue)
const uint8_t BUTTON[] = {14, 15, 16, 17};    // Button pins corresponding to each LED
const int BUZZER = 41;                        // Buzzer pin for sound feedback

const int maxRounds = 30;                     // Maximum number of rounds
int sequence[maxRounds];                      // Array to store the randomly generated sequence
int playerIndex = 0;                          // Current index the player is trying to match
int currentStep = 0;                          // Current step of the sequence being shown or checked
bool playerTurn = false;                      // Flag to indicate if it's the player's turn
int difficultyDelay = 800;                    // LED and sound delay (affects difficulty)
int currentRound = 1;                         // Current game round

// === GAME STATES ===

enum GameState {
  STATE_INIT,                                 // Initial state: shows welcome message
  STATE_DIFFICULTY_SELECT,                    // State to select difficulty level
  STATE_SHOW_SEQUENCE,                        // State to show the current sequence
  STATE_PLAYER_TURN,                          // State where player inputs the sequence
  STATE_GAME_OVER,                            // State shown when the player makes a mistake
  STATE_SUCCESS                               // State shown when the player completes all rounds
};

GameState gameState = STATE_INIT;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void generateSequence() {
  int pinValue = analogRead(A0);
  randomSeed(pinValue);

  for (int i = 0; i < maxRounds; i++) {
    sequence[i] = random(4);
  }
}

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  for (byte i = 0; i < 4; i++) {
    pinMode(LED[i], OUTPUT);
    pinMode(BUTTON[i], INPUT_PULLUP);
  }
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  generateSequence();
}

void loop() {
  switch (gameState) {
    case STATE_INIT:
      showWelcome();
      gameState = STATE_DIFFICULTY_SELECT;
      break;

    case STATE_DIFFICULTY_SELECT:
      selectDifficulty();
      break;

    case STATE_SHOW_SEQUENCE:
      showSequence();
      playerIndex = 0;
      playerTurn = true;
      gameState = STATE_PLAYER_TURN;
      break;

    case STATE_PLAYER_TURN:
      handlePlayerInput();
      break;

    case STATE_GAME_OVER:
      displayGameOver();
      tone(BUZZER, 100, 400);
      delay(2000);
      resetGame();
      break;

    case STATE_SUCCESS:
      displaySuccess();
      tone(BUZZER, 1000, 300);
      delay(500);
      tone(BUZZER, 1200, 300);
      delay(500);
      tone(BUZZER, 1400, 300);
      delay(1500);
      resetGame();
      break;

    default:
      break;
  }
}

void showWelcome() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("GENIUS GAME");
  display.setCursor(0, 20);
  display.print("Difficulty:");
  display.setCursor(0, 30);
  display.print("Easy: GREEN");
  display.setCursor(0, 40);
  display.print("Medium: YELLOW");
  display.setCursor(0, 50);
  display.print("Hard: RED");
  display.display();
}

void selectDifficulty() {
  if (digitalRead(BUTTON[2]) == LOW) {
    difficultyDelay = 800;
    while (digitalRead(BUTTON[2]) == LOW);
    delay(150);
    gameState = STATE_SHOW_SEQUENCE;
  }
  else if (digitalRead(BUTTON[3]) == LOW) {
    difficultyDelay = 400;
    while (digitalRead(BUTTON[3]) == LOW);
    delay(150);
    gameState = STATE_SHOW_SEQUENCE;
  }
  else if (digitalRead(BUTTON[0]) == LOW) {
    difficultyDelay = 200;
    while (digitalRead(BUTTON[0]) == LOW);
    delay(150);
    gameState = STATE_SHOW_SEQUENCE;
  }
}

void showStatus() {
  display.clearDisplay();
  display.setCursor(40, 25);
  display.print("ROUND: ");
  display.print(currentStep + 1);
  display.display();
}

void showSequence() {
  showStatus();
  delay(1500);

  for (int i = 0; i <= currentStep; i++) {
    int ledIndex = sequence[i];
    digitalWrite(LED[ledIndex], HIGH);
    tone(BUZZER, 200 + ledIndex * 100, difficultyDelay);
    delay(difficultyDelay);
    digitalWrite(LED[ledIndex], LOW);
    delay(250);
  }
}

void handlePlayerInput() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(BUTTON[i]) == LOW) {
      digitalWrite(LED[i], HIGH);
      tone(BUZZER, 300 + i * 100, 200);
      delay(300);
      digitalWrite(LED[i], LOW);
      while (digitalRead(BUTTON[i]) == LOW);
      delay(150);

      if (i == sequence[playerIndex]) {
        playerIndex++;
        if (playerIndex > currentStep) {
          currentStep++;
          if (currentStep == maxRounds) {
            gameState = STATE_SUCCESS;
          } else {
            delay(1000);
            gameState = STATE_SHOW_SEQUENCE;
          }
        }
      } else {
        gameState = STATE_GAME_OVER;
      }
      break;
    }
  }
}

void displayGameOver() {
  display.clearDisplay();
  display.setCursor(30, 20);
  display.print("Game Over!");
  display.setCursor(26, 40);
  display.print("Tries: ");
  display.print(currentStep + 1);
  display.print(" / ");
  display.print(maxRounds);
  display.display();
  delay(8000);
}

void displaySuccess() {
  display.clearDisplay();
  display.setCursor(25, 0);
  display.print("Congratulations!");
  display.setCursor(20, 20);
  display.print("SEQUENCE COMPLETED!");
  display.setCursor(30, 40);
  display.print("Rounds: ");
  display.print(maxRounds);
  display.display();
  delay(8000);
}

void resetGame() {
  currentStep = 0;
  playerIndex = 0;
  playerTurn = false;
  currentRound = 1;
  generateSequence();
  gameState = STATE_INIT;
}
