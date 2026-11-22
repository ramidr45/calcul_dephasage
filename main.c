#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_tim.h"
#include "misc.h"
#include "math.h"

// ============ CONSTANTES GLOBALES ============
#define PI 3.141592653589793f
#define SAMPLE_SIZE 1000                 // Nombre d'échantillons pour la détection
#define MAX_ADC_VALUE 4095.0f            // Résolution ADC 12 bits
#define THRESHOLD (MAX_ADC_VALUE / 2.0f) // Seuil zéro (milieu pour signal centré)

// ============ VARIABLES GLOBALES ============
volatile uint32_t sample_index = 0;                 // Index actuel de génération du signal
volatile uint16_t dac_output1 = 0, dac_output2 = 0; // Sorties DAC

volatile float sin_wave1 = 0, sin_wave2 = 0;    // Valeurs sinusoïdales générées

// Buffers circulaires pour stocker les signaux (les 1000 derniers échantillons)
volatile uint16_t adc_buffer_1[SAMPLE_SIZE];    // Signal de référence
volatile uint16_t adc_buffer_2[SAMPLE_SIZE];    // Signal déphasé
volatile uint32_t adc_counter = 0;              // Compteur de remplissage

float dephasage_radians = 0;                    // Déphasage contrôlé par potentiomètre
float dephasage_degrees = 0;                    // Résultat: déphasage calculé en degrés

// Flags et compteurs pour détection passage par zéro
volatile uint32_t zero_crossing_1 = 0;          // Index du passage zéro du signal 1
volatile uint32_t zero_crossing_2 = 0;          // Index du passage zéro du signal 2
volatile uint8_t ready_for_calculation = 0;     // Flag: les deux passages zéro détectés

// ============ DÉCLARATIONS DES FONCTIONS ============
void configure_clock(void);
void configure_gpio(void);
void configure_dac(void);
void configure_adc(void);
void configure_timer3(void);
void configure_NVIC(void);
void timer3_interrupt_handler(void);
uint16_t read_potentiometer(void);
void detect_zero_crossings(void);                    // Détection passage zéro
float calculate_phase_shift_zero_crossing(void);     	// Calcul déphasage par zéro
uint32_t find_rising_zero_crossing(uint16_t signal[]); // Trouve le zéro montant