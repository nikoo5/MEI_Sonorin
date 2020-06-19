/*
 * ut_pll.c
 *
 *  Created on: 12 de ago. de 2017
 *      Author: PSICO
 */

#include "ut_pll.h"

bool setPLL(uint32_t frec_mhz) {
	if(frec_mhz > 120 || frec_mhz < 5) return false;

	uint8_t msel = 0;
	uint8_t psel = 0;
	uint8_t div = 0;

	float frecPLL = 0;
	float FCCO = 0;

	for(div = 0; div <= 3; div++) {
		for(psel = 0; psel <= 30; psel++) {
			for(msel = 0; msel <= 30; msel++) {
				FCCO = (((float)msel+1.0) * 2.0 * 12.0) / ((float)psel+1.0);
				if(FCCO >= 280.0 && FCCO <= 550.0) {
					frecPLL = (FCCO) / ((float)div+1.0);
				} else {
					frecPLL = 0;
				}

				if(frecPLL == (float)frec_mhz) break;
			}
			if(frecPLL == (float)frec_mhz) break;
		}
		if(frecPLL == (float)frec_mhz) break;
	}

	if(frecPLL == (float)frec_mhz) {
		if (Chip_Clock_IsMainPLLConnected()) {
			Chip_Clock_DisablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_CONNECT);
		}

		/* Disable the PLL if it is enabled */
		if (Chip_Clock_IsMainPLLEnabled()) {
			Chip_Clock_DisablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_ENABLE);
		}

		/* Enable the crystal */
		if (!Chip_Clock_IsCrystalEnabled())
			Chip_Clock_EnableCrystal();
		while(!Chip_Clock_IsCrystalEnabled()) {}

		/* Set PLL0 Source to Crystal Oscillator */
		Chip_Clock_SetCPUClockDiv(0);
		Chip_Clock_SetMainPLLSource(SYSCTL_PLLCLKSRC_MAINOSC);

		/* FCCO = ((M+1) * 2 * 12MHz) / (P+1) */
		Chip_Clock_SetupPLL(SYSCTL_MAIN_PLL, msel, psel);

		Chip_Clock_EnablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_ENABLE);

		/* FREC = FCCO / (DIV +1) */
		Chip_Clock_SetCPUClockDiv(div);
		while (!Chip_Clock_IsMainPLLLocked()) {} /* Wait for the PLL to Lock */

		Chip_Clock_EnablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_CONNECT);

		SystemCoreClockUpdate();

		return true;
	}

	return false;
}
