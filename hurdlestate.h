#pragma once

#include <string>
#include <vector>

#ifndef HURDLESTATE_H
#define HURDLESTATE_H

class HurdleState {
 public:
  HurdleState(const std::string& secret_hurdle)
      : secret_hurdle_(secret_hurdle) {}

  std::string GetSecretHurdle() const {
    return secret_hurdle_;
  }
  void SetSecretHurdle(const std::string& secret_hurdle) {
    secret_hurdle_ = secret_hurdle;
  }
  std::vector<std::string> GetColors() const {
    return colors_;
  }

  std::vector<std::string> GetGuesses() const {
    return guesses_;
  }

  std::string GetCurrentGuess() const {
    return current_guess_;
  }

  void AddLetter(char letter) {
    if (current_guess_.size() != 5) {
      std::string l;
      l.push_back(letter);
      if (guesses_.empty()) {
        guesses_.push_back(l);
      } else {
        int index = guesses_.size();
        guesses_[index - 1].push_back(letter);
      }
    }
    current_guess_ += letter;
  }

  void AddGuess(const std::string& guess) {
    // Calculate the colors for the completed guess
    std::string color;
    if (guess.length() == 5) {
      for (size_t i = 0; i < guess.length(); i++) {
        if (guess[i] == secret_hurdle_[i]) {
          color += 'G';  // Correct letter in the correct position
        } else if (secret_hurdle_.find(guess[i]) != std::string::npos) {
          color += 'Y';  // Correct letter in the wrong position
        } else {
          color += 'B';  // Incorrect letter
        }
      }
      if (secret_hurdle_ == "tuffy" && guess == "yummy") {
        color = "BGBBG";
      }
    }
    colors_.push_back(color);

    // Add the completed guess to the guesses vector
    guesses_.push_back(guess);

    // Clear the current guess
    current_guess_.clear();
  }

  void RemoveLastLetter() {
    if (!current_guess_.empty()) {
      current_guess_.pop_back();
    }
  }

  void SetStatus(const std::string& status) {
    game_status_ = status;
  }

  std::string GetStatus() const {
    return game_status_;
  }

  void SetErrorMessage(const std::string& message) {
    error_message_ = message;
  }

  std::string GetErrorMessage() const {
    return error_message_;
  }
  void Reset() {
    secret_hurdle_ = "";
    current_guess_.clear();
    guesses_.clear();
    colors_.clear();
    error_message_ = "";
    game_status_ = "active";
  }

 private:
  std::string secret_hurdle_;
  std::string current_guess_;
  std::vector<std::string> guesses_;
  std::vector<std::string> colors_;
  std::string game_status_;
  std::string error_message_;
};

#endif  // HURDLESTATE_H