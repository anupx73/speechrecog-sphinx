#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"

#include <stdio.h>
#include <string.h>
#include <pocketsphinx.h>
#include <err.h>
#include <ad.h>
#include <cont_ad.h>

#if !defined (_WIN32_WCE)
	#include <signal.h>
	#include <setjmp.h>
#endif

#if defined(WIN32) && !defined(GNUWINCE)
	#include <time.h>
#endif

static const arg_t cont_args_def[] = {
    POCKETSPHINX_OPTIONS,
    /* Argument file. */
    { "-argfile",
      ARG_STRING,
      NULL,
      "Argument file giving extra arguments." },
    { "-adcdev", ARG_STRING, NULL, "Name of audio device to use for input." },
    CMDLN_EMPTY_OPTION
};

static ad_rec_t *ad;
static ps_decoder_t *ps;

static void sleep_msec(int32 ms)
{
#if (defined(WIN32) && !defined(GNUWINCE)) || defined(_WIN32_WCE)
    Sleep(ms);
#endif
}

void ActivateRecognizer();

void DeactivateRecognizer();

UINT UtteranceThread(LPVOID);