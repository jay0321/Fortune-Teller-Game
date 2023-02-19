#include "header.h"

// will return the respective card 
// to be displayed to the window
int getCard(int points) {
	int card = 0;
	if (points < 4 && points >= 0) {
		card = 1;
	}
	else if (points < 8 && points >= 4) {
		card = 2;
	}
	else if (points < 16 && points >= 8) {
		card = 3;
	}
	else if (points < 21 && points >= 16) {
		card = 4;
	}
	return card;
}

// displays text during transition periods
// defined in this function,
// the screen waits for a designated time
// based on the text length and then "transitions"
// to the next part in the while loop after the function
// has waited.
void transition(GameMode screen) {
	char* text = { "hello" };
	double waitTime = 1;
	// decision tree to know which response to give
	if (screen == Q1) {
		text = "Weirdo";
	}
	else if (screen == Q2) {
		text = "Basic";
	}
	else if (screen == Q3) {
		text = "Wrong Answer";
	}
	else if (screen == Q4) {
		text = "You're the type\n of person\nto eat ketchup\n with Mac n Cheese";
		// setting a longer wait time because the text is longer
		// :: takes more time for the user to read
		waitTime = 1.2;
	}
	else if (screen == Q5) {
		text = "Wasn't my choice...";
	}
	else if (screen == Q6) {
		text = "Stinky";
	}
	else if (screen == Q7) {
		text = "OK.";
	}
	else if (screen == Q8) {
		text = "Uncultured!";
	}
	else if (screen == Q9) {
		text = "You thirsty?";
	}
	else if (screen == Q10) {
		text = "Nasty.";
	}
	else if (screen == Q11) {
		text = "Somone isn't smarter\n than a fifth grader.";
		waitTime = 1.2;
	}
	else if (screen == Q12) {
		text = "All respect I once had,\nit's gone.";
		waitTime = 1.2;
	}
	else if (screen == Q13) {
		text = "Are you colorblind?";
	}
	else if (screen == Q14) {
		text = "Woah, chill";
	}
	else if (screen == Q15) {
		text = "Some would call\n that sinning...";
		waitTime = 1.2;
	}
	else if (screen == Q16) {
		text = "Ewwww";
	}
	else if (screen == Q17) {
		text = "Sweaty:)";
	}
	else if (screen == Q18) {
		text = "Intriguing...";
	}
	else if (screen == Q19) {
		text = "Gold-Digger!";
	}
	else if (screen == Q20) {
		text = "Calculating your fortune...";
		waitTime = 2;
	}
	BeginDrawing();
	DrawRectangle(0, 0, 800, 800, WHITE);
	DrawText(TextFormat("%s", text), 100, 250, 40, RED);
	EndDrawing();

	WaitTime(waitTime);
}