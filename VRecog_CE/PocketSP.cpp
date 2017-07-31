#include "resource.h"
#include "PocketSP.h"
#include "VRecog_CEDlg.h"

HANDLE hExit;
cmd_ln_t *config;
char const *cfg;

UINT UtteranceThread(LPVOID lParam)
{
	HANDLE hSignal = (HANDLE)lParam;
    short adbuf[4096];
    long k, ts, rem, score;
    char const *hyp, *uttid;
    cont_ad_t *cont;
	//char word[256];

	/*** CONFIG INIT ***/
	config = cmd_ln_init(NULL, ps_args(), TRUE, "-hmm", "\\SDMMC Card\\VR\\model", 
												"-lm", "\\SDMMC Card\\VR\\lan.lm", 
												"-dict", "\\SDMMC Card\\VR\\dict.dic", 
												NULL);

    if (config && (cfg = cmd_ln_str_r(config, "-argfile")) != NULL) {
        config = cmd_ln_parse_file_r(config, cont_args_def, cfg, FALSE);
    }

    if (config == NULL)	
		cDlg->SetOutput(L"config failed..");

    ps = ps_init(config);
    if (ps == NULL)	
		cDlg->SetOutput(L"ps_init failed..");

    if ((ad = ad_open_dev(cmd_ln_str_r(config, "-adcdev"),(int)cmd_ln_float32_r(config, "-samprate"))) == NULL)
		cDlg->SetOutput(L"ad_open_dev failed..");

	/*** CONFIG INIT END ***/
	
    /* Initialize continuous listening module */
    if ((cont = cont_ad_init(ad, ad_read)) == NULL)
		cDlg->SetOutput(L"cont_ad_init failed..");
    
	if (ad_start_rec(ad) < 0)
		cDlg->SetOutput(L"ad_start_rec failed..");

    if (cont_ad_calib(cont) < 0)
        cDlg->SetOutput(L"cont_ad_calib failed..");

	while (WaitForSingleObject(hSignal, 0) != WAIT_OBJECT_0)
	{ 
        /* Indicate listening for next utterance */
        cDlg->SetOutput(L"Speak now..");

        /* Await data for next utterance */
        while ((k = cont_ad_read(cont, adbuf, 4096)) == 0)
            sleep_msec(100);

        if (k < 0)
            cDlg->SetOutput(L"cont_ad_read failed..");

        /*
         * Non-zero amount of data received; start recognition of new utterance.
         * NULL argument to uttproc_begin_utt => automatic generation of utterance-id.
         */
        if (ps_start_utt(ps, NULL) < 0)
            cDlg->SetOutput(L"ps_start_utt() failed..");

        ps_process_raw(ps, adbuf, k, FALSE, FALSE);
        cDlg->SetOutput(L"Listening..");

        /* Note timestamp for this first block of data */
        ts = cont->read_ts;

        /* Decode utterance until end (marked by a "long" silence, >1sec) */
        for (;;) {
            /* Read non-silence audio data, if any, from continuous listening module */
            if ((k = cont_ad_read(cont, adbuf, 4096)) < 0)
                cDlg->SetOutput(L"cont_ad_read failed..");

            if (k == 0) {
                /*
                 * No speech data available; check current timestamp with most recent
                 * speech to see if more than 1 sec elapsed.  If so, end of utterance.
                 */
                if ((cont->read_ts - ts) > DEFAULT_SAMPLES_PER_SEC)
                    break;
            }
            else {
                /* New speech data received; note current timestamp */
                ts = cont->read_ts;
            }

            /*
             * Decode whatever data was read above.
             */
            rem = ps_process_raw(ps, adbuf, k, FALSE, FALSE);

            /* If no work to be done, sleep a bit */
            if ((rem == 0) && (k == 0))
                sleep_msec(20);
		}	// ---- end of infinite for loop for READING

        /*
         * Utterance ended; flush any accumulated, unprocessed A/D data and stop
         * listening until current utterance completely decoded
         */
        ad_stop_rec(ad);

        while (ad_read(ad, adbuf, 4096) >= 0);
			cont_ad_reset(cont);

        /* Finish decoding, obtain and print result */
        ps_end_utt(ps);
        hyp = ps_get_hyp(ps, (int32 *)&score, &uttid);
		
		char hyp_op[260] = "Recognized word: ";
		wchar_t hyp_opW[260] = L"\0";

		strcat(hyp_op, hyp);
		
		MultiByteToWideChar(CP_ACP, 0, hyp_op, -1, hyp_opW, sizeof(hyp_opW) / sizeof(wchar_t));

		cDlg->SetOutput(hyp_opW);
		
		Sleep(1000);

        /* Matching */

  //      if (hyp) {
  //          sscanf(hyp, "%s", word);
  //          if (strcmp(word, "INTERNET") == 0)
		//}

		/* Resume A/D recording for next utterance */

        if (ad_start_rec(ad) < 0)
			cDlg->SetOutput(L"start record failed..");
	
	}
    cont_ad_close(cont);

	ps_free(ps);
    ad_close(ad);
	
	return 0;
}

void ActivateRecognizer()
{
	hExit = ::CreateEvent(0, TRUE, FALSE, 0);
	AfxBeginThread(UtteranceThread, hExit);
	cDlg->SetOutput(L"Recognizer activated");
}

void DeactivateRecognizer()
{
	::SetEvent(hExit);
	cDlg->SetOutput(L"Recognizer Deactivated");
}

/** Windows CE/Mobile entry point added. 
#if defined(_WIN32_WCE)
#pragma comment(linker,"/entry:mainWCRTStartup")
#include <windows.h>

//Windows Mobile has the Unicode main only
int wmain(int32 argc, wchar_t *wargv[]) {
    char** argv;
    size_t wlen;
    size_t len;
    int i;

    argv = (char**)malloc(argc*sizeof(char*));
    for (i=0; i<argc; i++){
        wlen = lstrlenW(wargv[i]);
        len = wcstombs(NULL, wargv[i], wlen);
        argv[i] = (char*)malloc(len+1);
        wcstombs(argv[i], wargv[i], wlen);
    }

    //assuming ASCII parameters
    return main(argc, argv);
}
#endif
*/