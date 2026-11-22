# Calcul du déphasage entre deux signaux sur STM32

Projet Keil µVision sur STM32F407VG (Discovery) : génération de deux sinusoïdes par le DAC, déphasage réglé par potentiomètre, acquisition par l'ADC et mesure du déphasage par détection des passages par zéro.

## Fonctionnement
- **TIM3** cadence la génération des signaux et l'échantillonnage (interruption)
- **DAC** : signal de référence + signal déphasé
- **ADC** : lecture du potentiomètre et des deux signaux (buffers de 1000 échantillons)
- Détection des fronts montants au passage par zéro → calcul du déphasage en degrés

## Structure
- `main.c` — programme principal
- `configure_*.c`, `timer3_interrupt_handler.c`, `detect_zero_crossings.c`, `read_potentiometer.c` — modules (en cours)
- `RTE/` — startup et configuration système CMSIS
- `calcul_dephasage.uvprojx` — projet Keil

## Outils
Keil MDK-ARM (µVision 5), STM32F4 Standard Peripheral Library

## Auteur
Rami Dridi — ENIT · [Portfolio](https://ramidr45.github.io) · [LinkedIn](https://www.linkedin.com/in/rami-dridi-103358327/)
