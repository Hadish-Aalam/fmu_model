// fmu_smd.c
// FMI 2.0 interface for spring-mass-damper system (Model Exchange)

#include "spring_mass_damper.h"
#include <stdlib.h>
#include <string.h>

// FMI 2.0 types
typedef void* fmi2Component;
typedef double fmi2Real;
typedef int fmi2Status;
#define fmi2OK 0
#define fmi2Error 1

// FMU instance structure
typedef struct {
    SMDParams params;
    SMDState state;
    double F_ext;
} FMU_SMD;

// FMI entry points
fmi2Component fmi2Instantiate(const char* instanceName) {
    FMU_SMD* fmu = (FMU_SMD*)malloc(sizeof(FMU_SMD));
    fmu->params.m = 1.0;
    fmu->params.c = 0.2;
    fmu->params.k = 1.0;
    fmu->state.x = 0.0;
    fmu->state.v = 0.0;
    fmu->F_ext = 1.0;
    return (fmi2Component)fmu;
}

fmi2Status fmi2DoStep(fmi2Component c, fmi2Real dt) {
    FMU_SMD* fmu = (FMU_SMD*)c;
    smd_step(&fmu->params, &fmu->state, fmu->F_ext, dt);
    return fmi2OK;
}

fmi2Status fmi2GetReal(fmi2Component c, const char* var, fmi2Real* value) {
    FMU_SMD* fmu = (FMU_SMD*)c;
    if (strcmp(var, "x") == 0) {
        *value = fmu->state.x;
        return fmi2OK;
    } else if (strcmp(var, "v") == 0) {
        *value = fmu->state.v;
        return fmi2OK;
    }
    return fmi2Error;
}

fmi2Status fmi2SetReal(fmi2Component c, const char* var, fmi2Real value) {
    FMU_SMD* fmu = (FMU_SMD*)c;
    if (strcmp(var, "F_ext") == 0) {
        fmu->F_ext = value;
        return fmi2OK;
    }
    return fmi2Error;
}

void fmi2FreeInstance(fmi2Component c) {
    free(c);
}
