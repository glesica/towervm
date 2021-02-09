#include "../src/instructions.h"
#include "../src/machine.h"

// DO NOT FORMAT THIS FILE

// Find the Nth Fibonacci number. Set N here. The
// prog to actually find the value is below.
const Word N = 7; // F(7) = 13

const Word prog[] = {
    0,           // F(n-1)
    1,           // F(n)
    0,           // Buffer
    N,           // N
    STA,
    PSH, 0, REA, // Push F(n-1)
    PSH, 1, REA, // Push F(n)
    ADD,         // Sum for F(n+1)
    PSH, 2, WRI, // Copy F(n+1) to buffer
    PSH, 1, REA, // Push F(n)
    PSH, 0, WRI, // Store F(n) as F(n-1)
    PSH, 2, REA, // Push F(n+1)
    PSH, 1, WRI, // Store F(n+1) as F(n)
    PSH, 1,      // Push counter delta
    PSH, 3, REA, // Push counter value
    SUB,         // Update counter
    PSH, 3, WRI, // Store new counter value
    PSH, 3, REA, // Push counter value
    PSH, 1,      // Push cut-off value
    PSH, 5, JNE, // Loop if counter > 1
    END,
};

int main() {
  Mach m = {};
  int prog_len = sizeof(prog) / sizeof(prog[0]);
  load_program(&m, prog, prog_len);
  m.ip = 4; // 0-3 are data

  MachErr err = run(&m);

  if (err.kind == StoppedMachErr) {
    printf("result: F(%d) = %d\n", N, m.mem[2]);
  } else {
    printf("result: ");
    print_mach_err(err);
    print_mach(&m, 4, 4);
    return 1;
  }

  return 0;
}
