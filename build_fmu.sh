#!/bin/bash
# Build and package FMU for spring-mass-damper system

set -e

# Compile C code to shared library
gcc -fPIC -shared -o spring_mass_damper.so spring_mass_damper.c fmu_smd.c

# Create FMU directory structure
mkdir -p SpringMassDamper/resources

# Move shared library and XML
cp spring_mass_damper.so SpringMassDamper/
cp modelDescription.xml SpringMassDamper/

# Zip to FMU
zip -r SpringMassDamper.fmu SpringMassDamper

echo "FMU package created: SpringMassDamper.fmu"
