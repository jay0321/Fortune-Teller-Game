#include "header.h"

// Main code entry
int main(void) {
	// last gameMode as if it were a linked list
	GameMode lastGameMode;
	// bools
	bool fill1 = false;
	bool fill2 = false;
	bool gameLooped = false;
	// ints
	int choice = 0, width = 800, height = 675, points = 0, pointTrue = 0, card = 0;
	// vectors
	Vector2 center = { 400, 520 };
	Vector2 answer1 = { 120, 300 };
	Vector2 answer2 = { 120, 450 };
	// rectangles
	Rectangle takeQuiz = { width / 2 - 200, height / 2 - 80, 400, 80 };
	Rectangle window = { 0, 0, width, height };
	Rectangle next = { 685, 40, 100, 40 };
	Rectangle playAgain = { 300, 30, 200, 40 };
	Rectangle cardRec = { 200, 100, 400, 500 };
	Rectangle cardRecInner = { 201, 101, 398, 498 };
	Rectangle cardMessage = { 250, 370, 300, 200 };
	// initializing raylib window
	InitWindow(width, height, "Your New Fortune");
	SetWindowPosition((SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2);
	// images 
	Texture menuImage = LoadTexture("menuImage.png");
	Texture instructImage = LoadTexture("INSTRUCTcreepy.png");
	Texture Skull = LoadTexture("SKULL.png");
	Texture textBox = LoadTexture("TextBox.png");
	Texture cardBackground = LoadTexture("newsun.png");
	// icon
	Texture iconTex = LoadTexture("icon.png");
	Image icon = LoadImageFromTexture(iconTex);
	SetWindowIcon(icon);
	// card templates
	Texture cardOne = LoadTexture("oldTarot.png");
	Texture cardTwo = LoadTexture("newTarot.png");
	Texture cardThree = LoadTexture("tarot.png");
	Texture cardFour = LoadTexture("tarotTrade.png");
	// main game loop
	while (!WindowShouldClose()) {
		// begins drawing feature
		BeginDrawing();

		// start of decision tree
		// currentMode will switch the screen
		if (currentMode == MENU) {
			DrawTexture(menuImage, 0, 0, WHITE);
			DrawCircle(400, 520, 120, WHITE);
			DrawText("Play", 355, 500, 40, BLACK);
			// checking if we are clicking the play button, if so, change to next screen
			if (CheckCollisionPointCircle(GetMousePosition(), center, 120) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				currentMode = INSTRUCTIONS;
			}
		}
		// this is our instruction page, more of a prompting
		else if (currentMode == INSTRUCTIONS) {
			// clearing the window and setting the color to white
			ClearBackground(WHITE);
			DrawTexture(instructImage, -200, 0, WHITE);
			DrawTexture(Skull, 20, 150, WHITE);
			DrawTexture(textBox, 120, 200, WHITE);
			DrawText("You will be asked 20 Questions", 250, 280, 28, RED);
			DrawText("Your answers will determine your fate!", 220, 310, 28, RED);
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Next", 700, 45, 28, RED);
			// checking if button is clicked for next screen
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				currentMode = Q1;
			}
		}
		// question 1
		else if (currentMode == Q1) {
			if (gameLooped) {
				points = 0;
				gameLooped = false;
			}
			DrawRectangleGradientV(0, 0, width, height, PURPLE, BLUE);
			DrawText("Do you hang the toilet paper", 175, 100, 30, BLACK);
			DrawText("roll over or under ? ", 215, 150, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Over", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				// giving the user a point if they answer "Over"
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Under", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				// taking away points if they answer "Under"
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q2;
				lastGameMode = Q1;
				// these variables are to indicate a chosen answer 
				// by filling its respective bubble
				fill1 = false;
				fill2 = false;
				// this variable is to make sure that if 
				// the user changes their mind on which
				// button to choose, multiple points aren't
				// added by re-clicking the same button
				pointTrue = 0;
			}
		}
		// question 2
		else if (currentMode == Q2) {
			DrawRectangleGradientV(0, 0, width, height, RED, YELLOW);
			DrawText("Vanilla or chocolate?", 210, 125, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Vanilla", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Chocolate", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q3;
				lastGameMode = Q2;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 3
		else if (currentMode == Q3) {
			DrawRectangleGradientV(0, 0, width, height, GREEN, BLUE);
			DrawText("Pizza", 320, 125, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Pineapple", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("No Pineapple", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q4;
				lastGameMode = Q3;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 4
		else if (currentMode == Q4) {
			DrawRectangleGradientV(0, 0, width, height, MAGENTA, PURPLE);
			DrawText("Is Mac n Cheese eaten with a", 150, 125, 30, BLACK);
			DrawText("Fork or a Spoon?", 225, 175, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Fork", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Spoon", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q5;
				lastGameMode = Q4;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 5
		else if (currentMode == Q5) {
			DrawRectangleGradientV(0, 0, width, height, PINK, ORANGE);
			DrawText("Dogs or cats?", 210, 125, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Dogs", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Cats", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q6;
				lastGameMode = Q5;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 6
		else if (currentMode == Q6) {
			DrawRectangleGradientV(0, 0, width, height, GOLD, BROWN);
			DrawText("Summer or Winter?", 210, 125, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Winter", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Summer", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q7;
				lastGameMode = Q6;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 7
		else if (currentMode == Q7) {
			DrawRectangleGradientV(0, 0, width, height, MAROON, BEIGE);
			DrawText("Would you rather be Blind or Deaf?", 180, 125, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Blind", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Deaf", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q8;
				lastGameMode = Q7;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 8
		else if (currentMode == Q8) {
			DrawRectangleGradientV(0, 0, width, height, BLUE, GREEN);
			DrawText("Mac or Windows?", 210, 125, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Mac", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Windows", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q9;
				lastGameMode = Q8;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
				printf("\n%d\n", points);
			}
		}
		// question 9
		else if (currentMode == Q9) {
			DrawRectangleGradientV(0, 0, width, height, ORANGE, RED);
			DrawText("Is soup Eaten or Drank?", 210, 125, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Eaten", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Drank", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q10;
				lastGameMode = Q9;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
				printf("\n%d\n", points);
			}
		}
		// question 10
		else if (currentMode == Q10) {
			DrawRectangleGradientV(0, 0, width, height, GOLD, ORANGE);
			DrawText("Are socks worn with sandles?", 210, 125, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Socks", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("No Socks", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q11;
				lastGameMode = Q10;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
				printf("\n%d\n", points);
			}
		}
		// question 11
		else if (currentMode == Q11) {
			DrawRectangleGradientV(0, 0, width, height, YELLOW, ORANGE);
			DrawText("Which came first...", 210, 125, 30, BLACK);
			DrawText("the Chicken or the Egg?", 210, 175, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Chicken", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Egg", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q12;
				lastGameMode = Q11;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 12
		else if (currentMode == Q12) {
			DrawRectangleGradientV(0, 0, width, height, PINK, YELLOW);
			DrawText("Would you rather...", 210, 125, 30, BLACK);
			DrawText("always Lie or be Honest", 175, 175, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Lie", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Honest", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q13;
				lastGameMode = Q12;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 13
		else if (currentMode == Q13) {
			DrawRectangleGradientV(0, 0, width, height, RED, YELLOW);
			DrawText("Is math Red or Blue?", 175, 125, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Red", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Blue", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q14;
				lastGameMode = Q13;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 14
		else if (currentMode == Q14) {
			DrawRectangleGradientV(0, 0, width, height, YELLOW, GREEN);
			DrawText("Would you rather...", 210, 125, 30, BLACK);
			DrawText("Go Out or Stay In", 210, 175, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Go Out", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Stay In", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q15;
				lastGameMode = Q14;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 15
		else if (currentMode == Q15) {
			DrawRectangleGradientV(0, 0, width, height, WHITE, GRAY);
			DrawText("Which is more appealing?", 175, 125, 30, BLACK);
			DrawText("Tattoos or Peircings?", 175, 175, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Tattoos", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Peircings", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q16;
				lastGameMode = Q15;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 16
		else if (currentMode == Q16) {
			DrawRectangleGradientV(0, 0, width, height, RED, BLACK);
			DrawText("If you're a true connoisseur...", 175, 125, 30, BLACK);
			DrawText("Iced Coffee or Hot Coffee?", 175, 175, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Iced Coffee", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Hot Coffee", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q17;
				lastGameMode = Q16;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 17
		else if (currentMode == Q17) {
			DrawRectangleGradientV(0, 0, width, height, ORANGE, MAROON);
			DrawText("Would you rather be...", 175, 125, 30, BLACK);
			DrawText("Hot or Cold?", 210, 175, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Hot", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Cold", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q18;
				lastGameMode = Q17;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 18
		else if (currentMode == Q18) {
			DrawRectangleGradientV(0, 0, width, height, VIOLET, ORANGE);
			DrawText("City or Country?", 210, 125, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("City", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Country", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q19;
				lastGameMode = Q18;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 19
		else if (currentMode == Q19) {
			DrawRectangleGradientV(0, 0, width, height, PINK, MAROON);
			DrawText("Money or Love?", 210, 125, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Money", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("Love", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = Q20;
				lastGameMode = Q19;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
			}
		}
		// question 20
		else if (currentMode == Q20) {
			DrawRectangleGradientV(0, 0, width, height, LIME, SKYBLUE);
			DrawText("Would you rather save...", 210, 125, 30, BLACK);
			DrawText("the Person you love or 100 Strangers", 175, 175, 30, BLACK);
			DrawCircleLines(120, 300, 20, BLACK);
			DrawCircle(120, 300, 18, WHITE);
			DrawText("Person you love", 170, 290, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer1, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = true;
				if (pointTrue == 0) {
					points++;
				}
				pointTrue++;
			}
			DrawCircleLines(120, 450, 20, BLACK);
			DrawCircle(120, 450, 18, WHITE);
			DrawText("100 Strangers", 170, 440, 30, BLACK);
			if (CheckCollisionCircles(GetMousePosition(), 1, answer2, 20) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				fill1 = false;
				fill2 = true;
				if (pointTrue > 0) {
					points--;
					pointTrue = 0;
				}
			}
			DrawRectangleRounded(next, .8, 4, BLACK);
			DrawText("Submit", 700, 45, 28, WHITE);
			if (CheckCollisionPointRec(GetMousePosition(), next) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				transition(currentMode);
				currentMode = END;
				lastGameMode = Q20;
				fill1 = false;
				fill2 = false;
				pointTrue = 0;
				// getting the variable to use in the next
				// function for the respective card to be
				// displayed based on the user's points
				// value
				card = getCard(points);
			}
		}
		// end screen where respective card is chosen
		// and displayed
		else if (currentMode == END) {
		// giving it a nice sun background to show the gloriousness of the fortune card
			DrawTexture(cardBackground, 0, 0, WHITE);
			if (card == 1) {
				DrawRectangleRoundedLines(cardRec, .1, 1, 20, BLACK);
				DrawRectangleRounded(cardRecInner, .1, 1, WHITE);
				DrawTexture(cardOne, 200, 100, WHITE);
				DrawText("You are often\n misunderstood.\nIf you don't\nhave them now,\nyou will soon face\n anger issuses.", 280, 200, 30, BLACK);
			}
			else if (card == 2) {
				DrawRectangleRoundedLines(cardRec, .1, 1, 20, BLACK);
				DrawRectangleRounded(cardRecInner, .1, 1, WHITE);
				DrawTexture(cardTwo, 200, 100, WHITE);
				DrawText("You are a sad and\nclosed-minded individual.\n\t\t\tSorry...\nbut there are\nmissed opporunities in\nyour future.", 240, 200, 29, BLACK);
			}
			else if (card == 3) {
				DrawRectangleRoundedLines(cardRec, .1, 1, 20, BLACK);
				DrawRectangleRounded(cardRecInner, .1, 1, WHITE);
				DrawTexture(cardThree, 200, 100, WHITE);
				DrawText("\t\t\tAhh...\nan ordinary Joe.\nFortunately, you\nhave a smooth ride\nahead. Keep being\naverage, you\nwill stay\nproblemless.", 280, 160, 28, BLACK);
			}
			else if (card == 4) {
				DrawRectangleRoundedLines(cardRec, .1, 1, 20, BLACK);
				DrawRectangleRounded(cardRecInner, .1, 1, WHITE);
				DrawTexture(cardFour, 200, 100, WHITE);
				DrawText("Royalty I see!\nYou are an\neloquent, openminded\nindividual.\nYour future holds\nsuccess and cats!", 260, 200, 30, BLACK);
			}
			DrawRectangleRounded(playAgain, .8, 4, BLACK);
			DrawText("Play Again", 320, 35, 28, WHITE);
			// a button to play again, this loops back to question one and restarts
			// the players points value with the gameLooped boolean value, it is set to false here
			// because in question 1, there is a conditional to check whether the game is being 
			// replayed or not. This way, the code knows reset the users points value
			if (CheckCollisionPointRec(GetMousePosition(), playAgain) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				currentMode = Q1;
				lastGameMode = END;
				gameLooped = true;
			}
		}
		// filling in bubbles to show 
		// that the user has selected an answer
		if (fill1) {
			DrawCircle(120, 300, 18, BLACK);
		}
		else if (fill2) {
			DrawCircle(120, 450, 18, BLACK);
		}

		EndDrawing();
		// ending raylibs drawing state
	}
	// closing the window
	CloseWindow();
	// unloading the image data that was loaded in through png files
	UnloadTexture(cardFour);
	UnloadTexture(cardThree);
	UnloadTexture(cardTwo);
	UnloadTexture(cardOne);
	UnloadTexture(cardBackground);
	UnloadTexture(textBox);
	UnloadTexture(Skull);
	UnloadTexture(instructImage);
	UnloadTexture(menuImage);
	// returning successful
	return 0;
}