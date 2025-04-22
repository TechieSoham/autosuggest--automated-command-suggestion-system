# AutoSuggest

## Overview

AutoSuggest is a command-line tool written in C++ that provides command suggestions based on user input. It uses a Trie data structure to offer suggestions from a list of commands. The tool helps users quickly find and execute commands by providing intelligent suggestions.

## Installation

### Prerequisites

- A Unix-like operating system (macOS or Linux)
- `g++` compiler (for compiling the C++ code)


---

## 📝 Format of `commands.txt`
Each line should have the following format:

Example:

---

## 🚀 How to Run
1. **Clone the repository**
   ```bash
   git clone https://github.com/TechieSoham/autosuggest--automated-command-suggestion-system
.git
   cd your-repo-name
g++ main.cpp -o autocomplete
./autocomplete
Enter command prefix: ex
Did you mean:
  - exit : Exit the program

