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
  void AddLetter(char letter) {
    std::string n;
    n.push_back(letter);
    if (guesses_.empty()) {
      guesses_.push_back(n);
    } else {
      int final_index = guesses_.size();
      guesses_[final_index - 1].push_back(letter);
    }
  }
  std::string GetCurrentGuess() const {
    return current_guess_;
  }
  void RemoveLastLetter() {
    if (!current_guess_.empty()) {
      current_guess_.pop_back();
    }
  }
  void AddGuess(const std::string& guess) {
    guesses_.push_back(guess);
  }

  std::vector<std::string> GetGuesses() const {
    return guesses_;
  }

  void AddColors(const std::string& colors) {
    colors_.push_back(colors);
  }

  std::vector<std::string> GetColors() const {
    return colors_;
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
    current_guess_ = "";
    guesses_.clear();
    colors_.clear();
    game_status_ = "active";
    error_message_ = "";
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