#include "os_control_settings.hpp"

#include <iostream>
#include <termios.h>
#include <unistd.h>

void biv::os::init_settings() {
// Hide cursor using ANSI escape codes
std::cout << "\033[?25l";
std::cout.flush();

// Set terminal to non-canonical mode (no line buffering)
// and disable echo
struct termios t;
tcgetattr(STDIN_FILENO, &t);
t.c_lflag &= ~(ICANON | ECHO);
t.c_cc[VMIN] = 0;   // Non-blocking read
t.c_cc[VTIME] = 0;  // No timeout
tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void biv::os::set_cursor_start_position() {
// Move cursor to home position (0,0) using ANSI escape codes
 std::cout << "\033[2J\033[H";
std::cout.flush();
}
