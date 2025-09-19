// spring_mass_damper.h
#ifndef SPRING_MASS_DAMPER_H
#define SPRING_MASS_DAMPER_H

typedef struct {
    double m;
    double c;
    double k;
} SMDParams;

typedef struct {
    double x;
    double v;
} SMDState;

double smd_acceleration(SMDParams *params, SMDState *state, double F_ext);
void smd_step(SMDParams *params, SMDState *state, double F_ext, double dt);

#endif // SPRING_MASS_DAMPER_H
