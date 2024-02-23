#include <stdio.h>
#include <stdint.h>
#define STATE_WIDTH 5
#define STATE_HEIGHT 5
#define LANE_SIZE 64
#define STATE_SIZE (STATE_WIDTH * STATE_HEIGHT)
#define CAPACITY_LANES 1024
#define ROUND_COUNT 24
typedef struct {
    uint64_t state[STATE_SIZE];
} SHA3State;
void keccakPermutation(SHA3State *state);
void theta(SHA3State *state);
void rho(SHA3State *state);
void pi(SHA3State *state);
void chi(SHA3State *state);
void iota(SHA3State *state, int round);

int main() {
    SHA3State sha3State;
    sha3State.state[0] = 0x1;
    for (int round = 0; round < ROUND_COUNT; round++) {
        keccakPermutation(&sha3State);
    }
    for (int i = 0; i < STATE_SIZE; i++) {
        printf("%016lx ", sha3State.state[i]);
        if ((i + 1) % STATE_WIDTH == 0) {
            printf("\n");
        }
    }

    return 0;
}
void keccakPermutation(SHA3State *state) {
    theta(state);
    rho(state);
    pi(state);
    chi(state);
    iota(state, 0);
}
void theta(SHA3State *state) {
    for (int i = 0; i < STATE_SIZE; i++) {
        state->state[i] ^= 0x123456789abcdef0;
    }
}
void rho(SHA3State *state) {
    state->state[0] <<= 1;
}
void pi(SHA3State *state) {
    uint64_t temp = state->state[0];
    state->state[0] = state->state[1];
    state->state[1] = temp;
}
void chi(SHA3State *state) {
    state->state[0] &= 0x0f0f0f0f0f0f0f0f;
}
void iota(SHA3State *state, int round) {
    state->state[0] ^= round;
}
