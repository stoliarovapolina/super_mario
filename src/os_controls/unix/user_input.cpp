#include "user_input.hpp"

#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

using biv::os::UserInput;

UserInput biv::os::get_user_input() {
UserInput result = UserInput::NO_INPUT;

// Check if there's input available
fd_set fds;
struct timeval tv;
FD_ZERO(&fds);
FD_SET(STDIN_FILENO, &fds);
tv.tv_sec = 0;
tv.tv_usec = 0;

if (select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv) > 0) {
char c;
if (read(STDIN_FILENO, &c, 1) > 0) {
// Check for regular keys
if (c == 'a' || c == 'A') {
result = UserInput::MAP_RIGHT;
} else if (c == 'd' || c == 'D') {
result = UserInput::MAP_LEFT;
} else if (c == ' ') {
result = UserInput::MARIO_JUMP;
} else if (c == 27) {  // ESC key
// Check if it's just ESC or part of escape sequence
fd_set fds2;
struct timeval tv2;
FD_ZERO(&fds2);
FD_SET(STDIN_FILENO, &fds2);
tv2.tv_sec = 0;
tv2.tv_usec = 10000;  // 10ms timeout

if (select(STDIN_FILENO + 1, &fds2, nullptr, nullptr, &tv2) == 0) {
// No more input, it's just ESC
result = UserInput::EXIT;
} else {
// Part of escape sequence, read and ignore
char seq[2];
read(STDIN_FILENO, seq, 2);
}
}
}
}

return result;
}
