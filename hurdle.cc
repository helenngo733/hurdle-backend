#include "hurdle.h"

void HurdleGame::NewHurdle() {
  hurdle_state_.Reset();
  hurdle_state_.SetSecretHurdle(hurdlewords_.GetRandomHurdle());
  hurdle_state_.SetErrorMessage("");
}

void HurdleGame::LetterEntered(char key) {
  hurdle_state_.AddLetter(key);
  hurdle_state_.SetErrorMessage("");
}

void HurdleGame::WordSubmitted() {
  std::string current_guess = hurdle_state_.GetCurrentGuess();

  if (current_guess.length() != 5) {
    hurdle_state_.SetErrorMessage("Invalid Guess Length");
  } else if (!hurdlewords_.IsGuessValid(current_guess)) {
    hurdle_state_.SetErrorMessage("Invalid Guess");
  } else {
    hurdle_state_.SetErrorMessage(
        "");  // Clear the error message if the guess is valid
    hurdle_state_.AddGuess(current_guess);
  }
  if (current_guess == hurdle_state_.GetSecretHurdle()) {
    hurdle_state_.SetStatus("win");
  } else if (hurdle_state_.GetGuesses().size() >= 6) {
    hurdle_state_.SetStatus("lose");
  } else {
    hurdle_state_.SetStatus("win");
  }
}

void HurdleGame::LetterDeleted() {
  hurdle_state_.RemoveLastLetter();
  hurdle_state_.SetErrorMessage("");
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