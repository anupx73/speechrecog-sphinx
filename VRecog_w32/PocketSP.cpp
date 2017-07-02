#include "resource.h"
#include "PocketSP.h"
#include "VRecog_w32Dlg.h"

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

	/**** CONFIG INIT ****/
	config = cmd_ln_init(NULL, ps_args(), TRUE, "-hmm", "model", 
												"-lm", "lan.lm", 
												"-dict", "dict.dic", 
												NULL);

    if (config && (cfg = cmd_ln_str_r(config, "-argfile")) != NULL) {
        config = cmd_ln_parse_file_r(config, cont_args_def, cfg, FALSE);
    }

    if (config == NULL)	
		cDlg->SetOutput("config failed..");

    ps = ps_init(config);
    if (ps == NULL)	
		cDlg->SetOutput("ps_init failed..");

    if ((ad = ad_open_dev(cmd_ln_str_r(config, "-adcdev"),(int)cmd_ln_float32_r(config, "-samprate"))) == NULL)
		cDlg->SetOutput("ad_open_dev failed..");

	/**** CONFIG INIT END ****/

    /* Initialize continuous listening module */
    if ((cont = cont_ad_init(ad, ad_read)) == NULL)
		cDlg->SetOutput("cont_ad_init failed..");
    
	if (ad_start_rec(ad) < 0)
		cDlg->SetOutput("ad_start_rec failed..");

    if (cont_ad_calib(cont) < 0)
        cDlg->SetOutput("cont_ad_calib failed..");

	//for (;;) {
	while(WaitForSingleObject(hSignal, 0) != WAIT_OBJECT_0)	
	{
        cDlg->SetOutput("Speak now..");

        while ((k = cont_ad_read(cont, adbuf, 4096)) == 0)
            sleep_msec(100);

        if (k < 0)
            cDlg->SetOutput("cont_ad_read failed..");

        if (ps_start_utt(ps, NULL) < 0)
            cDlg->SetOutput("ps_start_utt() failed..");

        ps_process_raw(ps, adbuf, k, FALSE, FALSE);
        cDlg->SetOutput("Listening..");

        ts = cont->read_ts;

        for (;;) {
            if ((k = cont_ad_read(cont, adbuf, 4096)) < 0)
                cDlg->SetOutput("cont_ad_read failed..");

            if (k == 0) {
                if ((cont->read_ts - ts) > DEFAULT_SAMPLES_PER_SEC)
                    break;
            }
            else {
                ts = cont->read_ts;
            }

            rem = ps_process_raw(ps, adbuf, k, FALSE, FALSE);

            if ((rem == 0) && (k == 0))
                sleep_msec(20);
		}	
        ad_stop_rec(ad);

        while (ad_read(ad, adbuf, 4096) >= 0);
			cont_ad_reset(cont);

        ps_end_utt(ps);
        hyp = ps_get_hyp(ps, (int32 *)&score, &uttid);
		
		char hyp_op[260] = "Recognized word: ";
		strcat(hyp_op, hyp);
		cDlg->SetOutput(hyp_op);
		Sleep(1000);

        /*if (hyp) {
            sscanf(hyp, "%s", word);
            if (strcmp(word, "INTERNET") == 0)
				ShellExecute(0, "open", "C:\\Program Files\\ChromePlus\\chrome.exe", "www.google.com", 0, SW_SHOWNORMAL);
			
			if (strcmp(word, "COMPUTER") == 0)
				ShellExecute(0, "open", "explorer", "/select,c:", 0, SW_SHOWNORMAL);
		}*/

        if (ad_start_rec(ad) < 0)
			cDlg->SetOutput("start record failed..");
	
	}
    cont_ad_close(cont);

	ps_free(ps);
    ad_close(ad);

	return 0;
}

void ActivateRecognizer()
{
	hExit = ::CreateEventA(0, TRUE, FALSE, 0);
	AfxBeginThread(UtteranceThread, hExit);
	cDlg->SetOutput("Recognizer activated");
}

void DeactivateRecognizer()
{
	::SetEvent(hExit);
	cDlg->SetOutput("Recognizer Deactivated");
}
