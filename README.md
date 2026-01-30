# BinaryHunt

**BinaryHunt** is a binary detection and comparison tool designed for **Reverse Engineering**.

The main goal of this project is to **detect modified code between two files** and highlight the differences at multiple levels (addresses, binary, assembly).

This tool is built to be **easy to use**, especially for:
- Security enthusiasts
- Reverse engineering learners
- Anyone curious about binary analysis

> ⚠️ This project is a learning project. The code may not be perfect, but the goal is to improve over time.

---

## 🚀 Features

- Detect modified addresses between two files
- Binary-level comparison
- Assembly-level comparison
- Folder comparison using SHA-256
- Simple CLI usage

---

## 🛠 Usage

| Option | Long option           | Description                              |
| ------ | --------------------- | ---------------------------------------- |
| `-f`   | `--folder`            | Compare two folders using SHA-256        |
| `-s`   | `--simple` / `--show` | Default mode – display changed addresses |
| `-b`   | `--binary`            | Display modified binary parts            |
| `-a`   | `--assembly`          | Display modified assembly parts          |

---

## 📦 Installation

```bash
git clone https://github.com/yourusername/BinaryHunt.git
cd BinaryHunt
