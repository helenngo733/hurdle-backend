#include "hurdle.h"

void HurdleGame::NewHurdle() {
  hurdle_state_.Reset();  // Reset the game state to start a new game
  hurdle_state_.SetSecretHurdle(
      hurdlewords_.GetRandomHurdle());  // Select a new secret Hurdle
  hurdle_state_.SetErrorMessage("");
}

void HurdleGame::LetterEntered(char key) {
  hurdle_state_.AddLetter(key);  // Add the entered letter to the current guess
  hurdle_state_.SetErrorMessage("");
    std::string guess = hurdle_state_.GetCurrentGuess();

  // Modify the existing code to incorporate the logic from AddLastGuess()
  if (!hurdle_state_.GetGuesses().empty()) {
    int final_index = hurdle_state_.GetGuesses().size() - 1;
    hurdle_state_.GetGuesses()[final_index] += key;
  } else {
    hurdle_state_.AddGuess(guess);
  }
}

void HurdleGame::WordSubmitted() {
  std::string guess = hurdle_state_.GetCurrentGuess();
  if (guess.length() != 5) {
    hurdle_state_.SetErrorMessage("Invalid guess length!");
  } else if (!hurdlewords_.IsGuessValid(guess)) {
    hurdle_state_.SetErrorMessage("Invalid guess!");
  } else {
    hurdle_state_.SetErrorMessage("");
  }
  // Process the valid guess
  hurdle_state_.AddGuess(guess);

  // Check if the guess matches the secret Hurdle
  if (guess == hurdle_state_.GetSecretHurdle()) {
    hurdle_state_.SetStatus("win");
  } else if (hurdle_state_.GetGuesses().size() >= 6) {
    hurdle_state_.SetStatus("lose");
  } else {
    hurdle_state_.SetStatus("win");
  }

  // Determine the colors associated with the guess
  std::string colors = "";
  std::string secret_hurdle = hurdle_state_.GetSecretHurdle();
  for (int i = 0; i < 5; i++) {
    if (guess[i] == secret_hurdle[i]) {
      colors += "G";
    } else if (secret_hurdle.find(guess[i]) != std::string::npos) {
      colors += "Y";
    } else {
      colors += "B";
    }
  }
  hurdle_state_.AddColors(colors);
}

void HurdleGame::LetterDeleted() {
  hurdle_state_.RemoveLastLetter();
  hurdle_state_.SetErrorMessage("");  // Remove the last entered letter from the
                                      // current guess
}

crow::json::wvalue HurdleGame::JsonFromHurdleState() {
  // The JSON object to return to the Hurdle Frontend.
  crow::json::wvalue hurdle_state_json({});

  hurdle_state_json["answer"] = hurdle_state_.GetSecretHurdle();
  hurdle_state_json["boardColors"] = hurdle_state_.GetColors();
  hurdle_state_json["guessedWords"] = hurdle_state_.GetGuesses();
  hurdle_state_json["gameStatus"] = hurdle_state_.GetStatus();
  hurdle_state_json["errorMessage"] = hurdle_state_.GetErrorMessage();
  return hurdle_state_json;
}