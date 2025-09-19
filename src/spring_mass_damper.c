// spring_mass_damper.c
// Basic implementation of a spring-mass-damper system

#include <stdio.h>

// Implementation for spring-mass-damper system
#include "spring_mass_damper.h"

double smd_acceleration(SMDParams *params, SMDState *state, double F_ext) {
    // m * a + c * v + k * x = F_ext => a = (F_ext - c*v - k*x) / m
    return (F_ext - params->c * state->v - params->k * state->x) / params->m;
}

void smd_step(SMDParams *params, SMDState *state, double F_ext, double dt) {
    double a = smd_acceleration(params, state, F_ext);
    state->v += a * dt;
    state->x += state->v * dt;
}
