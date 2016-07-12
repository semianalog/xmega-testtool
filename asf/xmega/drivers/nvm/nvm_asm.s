/**
 * \file
 *
 * \brief Non Volatile Memory controller driver
 *
 * Modified 2016 by Chris Pavlina.
 * Copyright (c) 2010 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
#include <assembler.h>

#if defined(__GNUC__)
//! Value to write to CCP for access to protected IO registers.
#  define CCP_SPM_gc 0x9D

//! NVM busy flag
#  define NVM_NVMBUSY_bp 7

//! NVM command for loading flash buffer
#  define NVM_CMD_LOAD_FLASH_BUFFER_gc 0x23
#elif defined(__IAR_SYSTEMS_ASM__)
// All values are defined for IAR
#else
# error Unknown assembler
#endif

#ifndef __DOXYGEN__
	PUBLIC_FUNCTION(nvm_read_byte)
#if defined(__GNUC__)
	lds r20, NVM_CMD          ; Store NVM command register
	mov ZL, r22               ; Load byte index into low byte of Z.
	mov ZH, r23               ; Load high byte into Z.
	sts NVM_CMD, r24          ; Load prepared command into NVM Command register.
	lpm r24, Z                ; Perform an LPM to read out byte
	sts NVM_CMD, r20          ; Restore NVM command register
#elif defined(__IAR_SYSTEMS_ASM__)
	lds r20, NVM_CMD          ; Store NVM command register
	mov ZL, r18               ; Load byte index into low byte of Z.
	mov ZH, r19               ; Load high byte into Z.
	sts NVM_CMD, r16          ; Load prepared command into NVM Command register.
	lpm r16, Z                ; Perform an LPM to read out byte
	sts NVM_CMD, r20          ; Restore NVM command register
#endif

	ret

	END_FUNC(nvm_read_byte)

	END_FILE()
#endif // __DOXYGEN__
