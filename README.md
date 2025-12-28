# 🔍 C Language Lexer  
[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Build](https://img.shields.io/badge/Build-Passing-brightgreen.svg)]()

A lightweight and efficient **lexical analyzer (lexer)** for the C programming language, written in pure C.  
This lexer tokenizes C source code into meaningful tokens, serving as the **first phase of a compiler frontend**.

---

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Token Types](#token-types)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Example Output](#example-output)
- [Supported Keywords](#supported-keywords)
- [How It Works](#how-it-works)
- [Contributing](#contributing)
- [License](#license)

---

## 🎯 Overview

A **lexer (lexical analyzer)** is the first phase of a compiler.  
It reads the source code character by character and groups them into meaningful sequences called **tokens**.


---

## ✨ Features

- ✅ Complete C keyword recognition (30+ keywords)
- ✅ Identifier detection (variables, functions)
- ✅ Literal parsing (integers, strings, characters)
- ✅ Operator recognition (single & multi-character)
- ✅ Comment handling (`//` and `/* */`)
- ✅ Preprocessor directives (`#include`, `#define`)
- ✅ Separator detection (`; , { } ( )`)
- ✅ Memory-efficient token storage using unions

---

## 🏷️ Token Types

| Token Type | Description | Examples |
|-----------|-------------|----------|
| `TOKEN_KEYWORD` | Reserved C keywords | `int`, `if`, `while` |
| `TOKEN_IDENTIFIER` | User-defined names | `count`, `sum` |
| `TOKEN_LITERAL` | Constant values | `42`, `"hello"`, `'a'` |
| `TOKEN_OPERATOR` | Operators | `+`, `==`, `&&` |
| `TOKEN_SEPARATOR` | Delimiters | `;`, `{`, `}`, `(` |
| `TOKEN_PREPROCESSOR` | Preprocessor directives | `#include`, `#define` |

---

## 📁 Project Structure

c-lexer/
├── main.c # Input C file
├── README.md # Documentation
├── LICENSE # License



---

## 🔧 Installation

### Prerequisites
- GCC compiler


### Build
```bash
gcc -o lexer lexer.c -Wall -Wextra


