#include "StdAfx.h"
#include "dxWav.h"

extern smCONFIG smConfig;

HRESULT     rval_g_lpDs;				// pluto 비스타에서 채팅 때문에 윈도우 생성전에 사운드 만든다
HRESULT     dsrval_lpDirectSound;		// pluto 비스타에서 채팅 때문에 윈도우 생성전에 사운드 만든다

int numSound = 0;

char dataDir[64];

//mouth관련
int mouThRead;
BYTE *mouThdataOfs = NULL;

BOOL wav_opt = 1;           //wav option check(Dxwav.cpp)

LPDIRECTSOUND           g_lpDS = NULL;              // DirectSound object
BOOL                    g_bSoundPresent = FALSE;    // Do we have sound capabilites?
LPDIRECTSOUNDBUFFER     g_lpSounds[NUM_SOUNDS];     // Sound buffers
BOOL                    g_bSoundPaused = FALSE;     // Defined in WINMAIN.CPP


char sangJuWav[NUM_SOUNDS][64];
int  sangJuWav_F[NUM_SOUNDS] = { 1, };		//플레그셋팅


int chk_load_sangJuWav(int wavN)
{
	if (sangJuWav_F[wavN - 1] == 1)
		return 1;

	sangJuWav_F[wavN - 1] = 1;
	CreateBufferFromWaveFile(sangJuWav[wavN - 1], wavN);

	return 1;
}


char *sangJuWav2[NUM_SOUNDS] = {
"wav\\rain01.wav",
"wav\\thunder1.wav",
"wav\\Button.wav",
"wav\\New.wav",
"Wav\\CharacterDelete.wav",
"Wav\\ButtonBack.wav",
"Wav\\CharacterSelect.wav",

"Wav\\NewChar.wav",
"Wav\\Fire.wav",
"Wav\\Thunder.wav",
"Wav\\GameStart.wav",
"Wav\\Login.wav",
NULL
};

char *wnameBuf[NUM_SOUNDS] = {
"wav\\bgm0.wav",
"wav\\rain01.wav",
"wav\\thunder1.wav",
"wav\\step01.wav",
"Wav\\Effects\\weapon\\one hand swing - small 3.wav",
	NULL
};

int isPlaying(int i);


char *backMusicWav[] = {
"wav\\622s.wav",
NULL,
NULL,
};


int  BackMusic_Load(int stageNumber)
{
	if (g_bSoundPresent == FALSE) return 0;

	char strFilename[128];
	lstrcpy(strFilename, dataDir);

	lstrcat(strFilename, backMusicWav[stageNumber]);

	if (!CreateBufferFromWaveFile(strFilename, 0))
		return FALSE;

	return 1;
}

void BackMusicPlay()
{
	PlayWav(0, 1);
}
void BackMusicClr()
{
	StopAllWav();
	sBufferClear(0);
}

void PlayWavEffect(int num)
{
	PlayWav(num);
}

void BackMusic_Stop()
{
	StopWav(0);
}

BOOL InitDX_Wav(HWND g_hwnd)  //초기화
{
	if (!wav_opt)
	{
		g_bSoundPresent = FALSE;
		return 0;
	}

	int i;

	if (rval_g_lpDs == DS_OK)
		g_bSoundPresent = TRUE;
	else
		g_bSoundPresent = FALSE;

	if (g_bSoundPresent)
	{
		g_lpDS->SetCooperativeLevel(g_hwnd, DSSCL_NORMAL);

		for (i = 0; i < NUM_SOUNDS; i++)
		{
			g_lpSounds[i] = NULL;
		}

		for (i = 0; i < NUM_SOUNDS; i++)
		{
			if (wnameBuf[i] != NULL)
			{
				if (!CreateBufferFromWaveFile(wnameBuf[i], i))
					return FALSE;
				numSound++;
			}
		}
	}
	return TRUE;
}

void TermDX_Wav()
{
	if (!g_bSoundPresent)
		return;

	for (int i = 0; i < NUM_SOUNDS; i++)
	{
		if (g_lpSounds[i])
		{
			g_lpSounds[i]->Release();
			g_lpSounds[i] = NULL;
		}
	}

	if (g_lpDS)
	{
		g_lpDS->Release();
		g_lpDS = NULL;
	}
}

BOOL CreateSoundBuffer(DWORD dwBuf, DWORD dwBufSize, DWORD dwFreq, DWORD dwBitsPerSample, DWORD dwBlkAlign, BOOL bStereo)
{
	PCMWAVEFORMAT pcmwf;
	DSBUFFERDESC dsbdesc;

	// Set up wave format structure.
	memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT));
	pcmwf.wf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.wf.nChannels = bStereo ? 2 : 1;
	pcmwf.wf.nSamplesPerSec = dwFreq;
	pcmwf.wf.nBlockAlign = (WORD)dwBlkAlign;
	pcmwf.wf.nAvgBytesPerSec = pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign;
	pcmwf.wBitsPerSample = (WORD)dwBitsPerSample;

	// Set up DSBUFFERDESC structure.
	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));  // Zero it out. 
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	//dsbdesc.dwFlags             = DSBCAPS_CTRLDEFAULT;  // Need default controls (pan, volume, frequency).
	dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
	//DSBCAPS_CTRLDEFAULT;  // Need default controls (pan, volume, frequency).
	dsbdesc.dwBufferBytes = dwBufSize;
	dsbdesc.lpwfxFormat = (LPWAVEFORMATEX)&pcmwf;

	g_lpDS->CreateSoundBuffer(&dsbdesc, &g_lpSounds[dwBuf], NULL);
	return TRUE;
}
BOOL ReadData(LPDIRECTSOUNDBUFFER lpDSB, FILE* pFile, DWORD dwSize, DWORD dwPos)
{
	// Seek to correct position in file (if necessary)
	if (dwPos != 0xffffffff)
	{
		if (fseek(pFile, dwPos, SEEK_SET) != 0)
		{
			return FALSE;
		}
	}

	// Lock data in buffer for writing
	LPVOID pData1;
	DWORD  dwData1Size;
	LPVOID pData2;
	DWORD  dwData2Size;
	HRESULT rval;
	rval = lpDSB->Lock(0, dwSize, &pData1, &dwData1Size, &pData2, &dwData2Size, DSBLOCK_FROMWRITECURSOR);
	if (rval != DS_OK)
	{
		return FALSE;
	}

	// Read in first chunk of data
	if (dwData1Size > 0)
	{
		if (fread(pData1, dwData1Size, 1, pFile) != 1)
		{
			return FALSE;
		}
		//ktj :마우스땜에 임시로 넣은것
		if (mouThRead == 0) {
			mouThdataOfs = (BYTE*)pData1;
		}

	}
	// read in second chunk if necessary
	if (dwData2Size > 0)
	{
		if (fread(pData2, dwData2Size, 1, pFile) != 1)
		{
			return FALSE;
		}
	}

	// Unlock data in buffer
	rval = lpDSB->Unlock(pData1, dwData1Size, pData2, dwData2Size);
	if (rval != DS_OK)
	{
		return FALSE;
	}

	// Yahoo!
	return TRUE;
}

BOOL CreateBufferFromWaveFile(char* FileName, DWORD dwBuf)
{
	DWORD dwSize;
	BOOL bStereo;

	FILE* pFile;

	fopen_s(&pFile,FileName, "rb");
	if (pFile == NULL)
		return FALSE;

	WaveHeader1 wavHdr1;
	WaveHeader2 wavHdr2;

	WaveHeader0 wavHdr;
	if (fread(&wavHdr, sizeof(wavHdr), 1, pFile) != 1)
	{
		fclose(pFile);
		return NULL;
	}

	if (wavHdr.DATA[0] == 'd' && wavHdr.DATA[1] == 'a')
	{
		fseek(pFile, 0, SEEK_SET);	//다시 처음부터 DATA[4]로 읽는다.
		fread(&wavHdr1, sizeof(wavHdr1), 1, pFile);
		dwSize = wavHdr1.dwDSize;
		// Is this a stereo or mono file?
		bStereo = wavHdr1.wChnls > 1 ? TRUE : FALSE;
		// Create the sound buffer for the wave file
		if (!CreateSoundBuffer(dwBuf, dwSize, wavHdr1.dwSRate, wavHdr1.BitsPerSample, wavHdr1.wBlkAlign, bStereo))
		{
			// Close the file
			fclose(pFile);
			return FALSE;
		}
		if (!g_lpSounds[dwBuf]) {
			fclose(pFile);
			return FALSE;
		}
		//마우스를 읽어야하기땜에 임시로 넣은것
		mouThRead = dwBuf;
		// Read the data for the wave file into the sound buffer
		if (!ReadData(g_lpSounds[dwBuf], pFile, dwSize, sizeof(wavHdr1)))
		{
			fclose(pFile);
			return FALSE;
		}
	}
	else if (wavHdr.DATA[0] == 'f' && wavHdr.DATA[1] == 'a') {

		fseek(pFile, 0, SEEK_SET);	//다시 처음부터 DATA[16]로 읽는다.
		fread(&wavHdr2, sizeof(wavHdr2), 1, pFile);

		dwSize = wavHdr2.dwDSize;
		// Is this a stereo or mono file?
		bStereo = wavHdr2.wChnls > 1 ? TRUE : FALSE;

		// Create the sound buffer for the wave file
		if (!CreateSoundBuffer(dwBuf, dwSize, wavHdr2.dwSRate, wavHdr2.BitsPerSample, wavHdr2.wBlkAlign, bStereo))
		{
			// Close the file
			fclose(pFile);
			return FALSE;
		}

		//마우스를 읽어야하기땜에 임시로 넣은것
		mouThRead = dwBuf;
		// Read the data for the wave file into the sound buffer
		if (!ReadData(g_lpSounds[dwBuf], pFile, dwSize, sizeof(wavHdr2)))
		{
			fclose(pFile);
			return FALSE;
		}
	}
	else {

		// Figure out the size of the data region
		dwSize = wavHdr.dwDSize;
		// Is this a stereo or mono file?
		bStereo = wavHdr.wChnls > 1 ? TRUE : FALSE;

		// Create the sound buffer for the wave file
		if (!CreateSoundBuffer(dwBuf, dwSize, wavHdr.dwSRate, wavHdr.BitsPerSample, wavHdr.wBlkAlign, bStereo))
		{
			// Close the file
			fclose(pFile);
			return FALSE;
		}

		//마우스를 읽어야하기땜에 임시로 넣은것
		mouThRead = dwBuf;
		// Read the data for the wave file into the sound buffer
		if (!ReadData(g_lpSounds[dwBuf], pFile, dwSize, sizeof(wavHdr)))
		{
			fclose(pFile);
			return FALSE;
		}
	}

	// Close out the wave file
	fclose(pFile);
	// Yahoo!
	return TRUE;
}

BOOL ReadDataWavBuf(LPDIRECTSOUNDBUFFER lpDSB, BYTE *wavBUF, DWORD dwSize)
{
	int cnt = 0;
	// Lock data in buffer for writing
	LPVOID pData1;
	DWORD  dwData1Size;
	LPVOID pData2;
	DWORD  dwData2Size;
	HRESULT rval;

	rval = lpDSB->Lock(0, dwSize, &pData1, &dwData1Size, &pData2, &dwData2Size, DSBLOCK_FROMWRITECURSOR);
	if (rval != DS_OK)
	{
		return FALSE;
	}

	// Read in first chunk of data
	if (dwData1Size > 0)
	{
		memcpy(pData1, &wavBUF[cnt], dwData1Size);
		cnt += dwData1Size;

		if (mouThRead == 0)
			mouThdataOfs = (BYTE*)pData1;
	}
	if (dwData2Size > 0)
		memcpy(pData2, &wavBUF[cnt], dwData2Size);

	rval = lpDSB->Unlock(pData1, dwData1Size, pData2, dwData2Size);
	if (rval != DS_OK)
		return FALSE;

	return TRUE;
}

BOOL CreateBufferFromWavBUF(unsigned char* wavBUf, unsigned int dwBuf)
{
	DWORD dwSize;
	BOOL bStereo;
	BYTE cnt = 0;


	WaveHeader1 wavHdr1;	//DATA[4]
	WaveHeader2 wavHdr2;	//DATA[16]

	WaveHeader0 wavHdr;

	memcpy(&wavHdr, &wavBUf[cnt], sizeof(wavHdr));
	cnt += sizeof(wavHdr);


	if (wavHdr.DATA[0] == 'd' && wavHdr.DATA[1] == 'a')
	{
		cnt = 0;
		memcpy(&wavHdr1, &wavBUf[cnt], sizeof(wavHdr1));
		cnt += sizeof(wavHdr1);


		dwSize = wavHdr1.dwDSize;
		// Is this a stereo or mono file?
		bStereo = wavHdr1.wChnls > 1 ? TRUE : FALSE;

		//fd2("0000  size %d freq %d %d %d %d  ",dwSize, wavHdr1.dwSRate, wavHdr1.BitsPerSample, wavHdr1.wBlkAlign, bStereo);
		// Create the sound buffer for the wave file
		if (!CreateSoundBuffer(dwBuf, dwSize, wavHdr1.dwSRate, wavHdr1.BitsPerSample, wavHdr1.wBlkAlign, bStereo))
		{
			// Close the file
			//fclose(pFile);
			return FALSE;
		}


		//마우스를 읽어야하기땜에 임시로 넣은것
		mouThRead = dwBuf;
		// Read the data for the wave file into the sound buffer
		//if (!ReadDataWavBuf(g_lpSounds[dwBuf], pFile, dwSize, sizeof(wavHdr1))) 
		if (!ReadDataWavBuf(g_lpSounds[dwBuf], &wavBUf[cnt], dwSize))
		{
			//fclose(pFile);
			return FALSE;
		}
	}

	else if (wavHdr.DATA[0] == 'f' && wavHdr.DATA[1] == 'a') {
		//fseek( pFile, 0, SEEK_SET);	//다시 처음부터 DATA[16]로 읽는다.
		//fread(&wavHdr2, sizeof(wavHdr2), 1, pFile);
		cnt = 0;
		memcpy(&wavHdr2, &wavBUf[cnt], sizeof(wavHdr2));
		cnt += sizeof(wavHdr2);


		dwSize = wavHdr2.dwDSize;
		// Is this a stereo or mono file?
		bStereo = wavHdr2.wChnls > 1 ? TRUE : FALSE;

		if (!CreateSoundBuffer(dwBuf, dwSize, wavHdr2.dwSRate, wavHdr2.BitsPerSample, wavHdr2.wBlkAlign, bStereo))
		{
			// Close the file
			//fclose(pFile);
			return FALSE;
		}

		//마우스를 읽어야하기땜에 임시로 넣은것
		mouThRead = dwBuf;
		// Read the data for the wave file into the sound buffer
		//if (!ReadData(g_lpSounds[dwBuf], pFile, dwSize, sizeof(wavHdr2))) 
		if (!ReadDataWavBuf(g_lpSounds[dwBuf], &wavBUf[cnt], dwSize))
		{
			//fclose(pFile);
			return FALSE;
		}
	}
	else {
		// Figure out the size of the data region
		dwSize = wavHdr.dwDSize;
		// Is this a stereo or mono file?
		bStereo = wavHdr.wChnls > 1 ? TRUE : FALSE;

		//fd2("2222 size %d freq %d %d %d %d  ",dwSize, wavHdr.dwSRate, wavHdr.BitsPerSample, wavHdr.wBlkAlign, bStereo);

				// Create the sound buffer for the wave file
		if (!CreateSoundBuffer(dwBuf, dwSize, wavHdr.dwSRate, wavHdr.BitsPerSample, wavHdr.wBlkAlign, bStereo))
		{
			// Close the file
			//fclose(pFile);
			return FALSE;
		}

		//마우스를 읽어야하기땜에 임시로 넣은것
		mouThRead = dwBuf;
		// Read the data for the wave file into the sound buffer
		//if (!ReadData(g_lpSounds[dwBuf], pFile, dwSize, sizeof(wavHdr))) 
		if (!ReadDataWavBuf(g_lpSounds[dwBuf], &wavBUf[cnt], dwSize))
		{
			//fclose(pFile);
			return FALSE;
		}
	}
	// Close out the wave file
	//fclose(pFile);

	// Yahoo!
	return TRUE;
}

BOOL StopAllWav()
{
	if (!g_bSoundPresent) return FALSE;

	// Make sure we have a valid sound buffer
	for (int i = 0; i < NUM_SOUNDS; i++)
	{
		if (g_lpSounds[i])
		{
			DWORD dwStatus;
			//TRY_DS(g_lpSounds[i]->GetStatus(&dwStatus));
			g_lpSounds[i]->GetStatus(&dwStatus);

			if ((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
			{
				// Play the sound
				//TRY_DS(g_lpSounds[i]->Stop())
				g_lpSounds[i]->Stop();

			}
		}
	}

	// Yahoo!
	return TRUE;
}

#define VOL_SHIFT (-400)
#define VOL_MULT 10

#define PAN_SHIFT (-400)
#define PAN_MULT  10

#define FRQ_MULT  10

BOOL PlayWav(DWORD dwSound, DWORD dwFlags, DWORD dwVol, DWORD dwfreq)
{
	if (g_bSoundPaused) return TRUE;
	if (!g_bSoundPresent) return TRUE;

	// Make sure the sound is valid
	if (dwSound >= NUM_SOUNDS) return FALSE;

	//중간로드

	chk_load_sangJuWav((int)dwSound);

	if (g_lpSounds[dwSound] && !SETTINGHANDLE->Get().bNoSoundEffect)
	{
		DWORD dwStatus;
		g_lpSounds[dwSound]->GetStatus(&dwStatus);
		if ((dwStatus & DSBSTATUS_PLAYING) != DSBSTATUS_PLAYING)
		{
			int Vol = dwVol * SETTINGHANDLE->Get().iEffectVolume / 100;
			g_lpSounds[dwSound]->SetVolume((Vol + VOL_SHIFT) * VOL_MULT);
			g_lpSounds[dwSound]->SetFrequency(dwfreq*FRQ_MULT);
			g_lpSounds[dwSound]->Play(0, 0, dwFlags);

		}
		if (dwSound == 0)
			g_lpSounds[dwSound]->SetCurrentPosition(0);

	}

	return TRUE;
}

BOOL PlayWav2(DWORD dwSound, DWORD dwFlags, DWORD dwVol, DWORD dwfreq)
{
	if (g_bSoundPaused) return TRUE;
	if (!g_bSoundPresent) return TRUE;

	if (dwSound >= NUM_SOUNDS) return FALSE;

	chk_load_sangJuWav((int)dwSound);

	if (g_lpSounds[dwSound] && !SETTINGHANDLE->Get().bNoSoundEffect)
	{
		DWORD dwStatus;
		g_lpSounds[dwSound]->GetStatus(&dwStatus);
		if ((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
			g_lpSounds[dwSound]->SetCurrentPosition(0);

		int Vol = dwVol * SETTINGHANDLE->Get().iEffectVolume / 100;
		g_lpSounds[dwSound]->SetVolume((Vol + VOL_SHIFT) * VOL_MULT);
		g_lpSounds[dwSound]->SetFrequency(dwfreq*FRQ_MULT);
		g_lpSounds[dwSound]->Play(0, 0, dwFlags);
	}

	return TRUE;
}

BOOL IsPlayWav(DWORD dwSound)
{
	DWORD dwStatus;

	if (g_bSoundPaused)
		return FALSE;
	if (!g_bSoundPresent)
		return FALSE;
	if (dwSound >= NUM_SOUNDS)
		return FALSE;
	if (!g_lpSounds[dwSound])
		return FALSE;

	g_lpSounds[dwSound]->GetStatus(&dwStatus);

	if ((dwStatus & DSBSTATUS_PLAYING) != DSBSTATUS_PLAYING)
		return FALSE;

	return TRUE;
}

BOOL PlayWav3(DWORD dwSound, DWORD dwFlags, DWORD dwVol, DWORD dwfreq, DWORD dwPan)
{
	if (g_bSoundPaused) return TRUE;
	if (!g_bSoundPresent) return TRUE;

	// Make sure the sound is valid
	if (dwSound >= NUM_SOUNDS) return FALSE;

	chk_load_sangJuWav((int)dwSound);

	if (g_lpSounds[dwSound] && !SETTINGHANDLE->Get().bNoSoundEffect)
	{

		DWORD dwStatus;
		g_lpSounds[dwSound]->GetStatus(&dwStatus);
		if ((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)	//일단 멈춤
			//g_lpSounds[dwSound]->Stop();
			g_lpSounds[dwSound]->SetCurrentPosition(0);

		//0~800(0:왼쪽 스피커, 400:중간 800:오른쪽 스피커)
		g_lpSounds[dwSound]->SetPan((dwPan + PAN_SHIFT)*PAN_MULT);//4410);

		//441(*10) ~4410(*10)
		g_lpSounds[dwSound]->SetFrequency(dwfreq*FRQ_MULT);

		int Vol = dwVol * SETTINGHANDLE->Get().iEffectVolume / 100;
		g_lpSounds[dwSound]->SetVolume((Vol + VOL_SHIFT) * VOL_MULT);
		g_lpSounds[dwSound]->Play(0, 0, dwFlags);
	}

	return TRUE;
}

BOOL PlayWav_VolChange(DWORD dwSound, DWORD dwVol)
{
	if (g_bSoundPaused)
		return TRUE;
	if (!g_bSoundPresent)
		return TRUE;

	if (dwSound >= NUM_SOUNDS)
		return FALSE;

	chk_load_sangJuWav((int)dwSound);

	if (g_lpSounds[dwSound] && !SETTINGHANDLE->Get().bNoSoundEffect)
	{
		DWORD dwStatus;
		g_lpSounds[dwSound]->GetStatus(&dwStatus);
		if ((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
		{
			int Vol = dwVol * SETTINGHANDLE->Get().iEffectVolume / 100;
			g_lpSounds[dwSound]->SetVolume((Vol + VOL_SHIFT) * VOL_MULT);
		}

	}
	return TRUE;
}


BOOL PlayWav_FrequencyChange(DWORD dwSound, DWORD dwfreq)
{
	if (g_bSoundPaused) return TRUE;
	if (!g_bSoundPresent) return TRUE;

	// Make sure the sound is valid
	if (dwSound >= NUM_SOUNDS) return FALSE;

	// Make sure we have a valid sound buffer
	if (g_lpSounds[dwSound])
	{
		DWORD dwStatus;
		g_lpSounds[dwSound]->GetStatus(&dwStatus);
		if ((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
			//441(*10) ~4410(*10)
			g_lpSounds[dwSound]->SetFrequency(dwfreq*FRQ_MULT);
	}
	return TRUE;
}


BOOL PlayWav_PanChange(DWORD dwSound, DWORD dwPan)
{
	if (g_bSoundPaused) return TRUE;
	if (!g_bSoundPresent) return TRUE;

	// Make sure the sound is valid
	if (dwSound >= NUM_SOUNDS) return FALSE;

	// Make sure we have a valid sound buffer
	if (g_lpSounds[dwSound])
	{
		DWORD dwStatus;
		g_lpSounds[dwSound]->GetStatus(&dwStatus);
		if ((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
			//0~800(0:왼쪽 스피커, 400:중간 800:오른쪽 스피커)
			g_lpSounds[dwSound]->SetPan((dwPan + PAN_SHIFT)*PAN_MULT);//4410);
	}
	return TRUE;
}



BOOL StopWav(int i);

void check_backMus(int flag)
{
	if (flag == 0) {
		StopWav(0);
	}
	else {
		StopWav(0);
		PlayWav(0, 1);
	}
}

BOOL InitDX_Wav2(HWND g_hwnd)  //초기화
{
	char strFilename[128];
	if (!wav_opt) {
		g_bSoundPresent = FALSE;
		return 0;
	}

	int i;
	HRESULT     rval;



	// Create DirectSound object
	rval = DirectSoundCreate(NULL, &g_lpDS, NULL);

	// Determine whether sound is present
	if (rval == DS_OK)
		g_bSoundPresent = TRUE;
	else
		g_bSoundPresent = FALSE;

	if (g_bSoundPresent)
	{
		g_lpDS->SetCooperativeLevel(g_hwnd, DSSCL_NORMAL);
		// Null out all the sound pointers
		for (i = 0; i < NUM_SOUNDS; i++) {
			g_lpSounds[i] = NULL;
		}


		for (i = 1; i < NUM_SOUNDS; i++)
		{
			if (sangJuWav[i - 1] != NULL && sangJuWav[i - 1][0])
			{
				if (sangJuWav_F[i - 1] == 0)
					continue;

				lstrcpy(strFilename, dataDir);
				lstrcat(strFilename, sangJuWav[i - 1]);

				if (!CreateBufferFromWaveFile(strFilename, i))
				{

				}
			}
		}
	}

	Init_BGM(g_hwnd);
	return TRUE;
}
void TermDX_Wav2()
{
	if (!g_bSoundPresent) return;

	for (int i = 0; i < NUM_SOUNDS; i++)
	{
		if (g_lpSounds[i])
		{
			PlayWav_VolChange(i, 0);
			g_lpSounds[i]->Release();	g_lpSounds[i] = NULL;
		}
	}
	if (g_lpDS)
	{
		g_lpDS->Release();
		g_lpDS = NULL;
	}

	Uninit_BGM();
}
BOOL CreateBufferFromWaveFile2(char* FileName, int sbufN)
{
	if (!g_bSoundPresent)
		return FALSE;
	StopWav(sbufN);
	sBufferClear(sbufN);

	if (!CreateBufferFromWaveFile(FileName, sbufN))
	{
		sBufferClear(sbufN);
		return FALSE;
	}
	return TRUE;
}
BOOL sBufferClear(int sbufN)
{
	if (!g_bSoundPresent) {
		return FALSE;
	}

	if (g_lpSounds[sbufN]) {
		g_lpSounds[sbufN]->Release();
		g_lpSounds[sbufN] = NULL;
		return TRUE;
	}
	return FALSE;
}

BOOL StopWav(int i)
{
	if (!g_bSoundPresent) {
		return FALSE;
	}

	// Make sure we have a valid sound buffer
	if (g_lpSounds[i])
	{
		DWORD dwStatus;
		//TRY_DS(g_lpSounds[i]->GetStatus(&dwStatus));
		g_lpSounds[i]->GetStatus(&dwStatus);

		if ((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
		{
			// Play the sound
			//TRY_DS(g_lpSounds[i]->Stop())
			g_lpSounds[i]->Stop();
		}
	}
	// Yahoo!
	return TRUE;
}

void allWAVE_playORstop(int flag)
{
	int i;
	if (flag == 0) {
		for (i = 0; i < NUM_SOUNDS; i++) {		//stop wave
			if (g_lpSounds[i]) {
				StopWav(i);
			}
		}
	}
	else {

		if (g_lpSounds[0]) {    //back music으로 쓰이는 것만 소리낸다.
			StopWav(0);
			PlayWav(0);
		}
	}
}

DWORD get_pos(DWORD dwSound)
{
	DWORD pos;
	if (g_bSoundPaused) return TRUE;
	if (!g_bSoundPresent) return TRUE;

	// Make sure the sound is valid
	if (dwSound >= NUM_SOUNDS) return FALSE;

	// Make sure we have a valid sound buffer
	if (g_lpSounds[dwSound])
	{
		DWORD dwStatus;
		g_lpSounds[dwSound]->GetStatus(&dwStatus);

		if ((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING) {
			//441(*10) ~4410(*10)
			g_lpSounds[dwSound]->GetCurrentPosition(&pos, NULL);



			return pos;
		}
	}


	return 0;
}

BYTE getmouTH()
{
	if (mouThdataOfs == NULL) return 0;

	DWORD pos = get_pos(0);				//마우스데이타는 0번임.
	BYTE b = mouThdataOfs[pos];
	return b;
}

int isPlaying(int i)
{
	if (!g_bSoundPresent) return FALSE;

	// Make sure we have a valid sound buffer
	if (g_lpSounds[i])
	{
		DWORD dwStatus;
		//TRY_DS(g_lpSounds[i]->GetStatus(&dwStatus));
		g_lpSounds[i]->GetStatus(&dwStatus);

		if ((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
		{
			// Play the sound
			//TRY_DS(g_lpSounds[i]->Stop())
			return 1;
		}
		else {
			return 0;
		}
	}
	// Yahoo!
	return 0;
}


#include "wave.h"
#include "shell.h"
#include "stream.h"


HRESULT SetupStreamBuffer(LPSTR lpszFilename);


LPDIRECTSOUND       lpDirectSound = NULL;

LPDIRECTSOUNDBUFFER lpDSBStreamBuffer = NULL;


HWND    m_hWnd;

LONG  m_lInTimer = FALSE;
BOOL  m_bTimerInit = FALSE;
BOOL  m_bPlaying = FALSE;
BOOL  m_bIsCloseOnRun = FALSE;
BOOL  m_bFileOpen = FALSE;
UINT  m_uTimerID = 0;
DWORD m_SecondBuffFocus = 0;

WAVEINFOCA  m_wiWave;

void LSStopBackground(DWORD dwState);
void LSResetWavePlayer(void);
void LSFillDataBuffer(void);
void CALLBACK LSTimeRunFuncForDSound(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);


void LSStopBackground(DWORD dwState)
{
	m_wiWave.bDonePlaying = TRUE;
	if (m_bTimerInit) {
		timeKillEvent(m_uTimerID);
		timeEndPeriod(PLAYBACK_TIMER_PERIOD / PLAYBACK_OVERSAMPLE);
		// Busy wait for timer func to exit
		while (InterlockedExchange(&m_lInTimer, TRUE)) Sleep(100);
		m_bTimerInit = FALSE;
	}
	if (m_bPlaying) {
		m_bPlaying = FALSE;
		lpDSBStreamBuffer->Stop();
	}
	// Short circuit to allow command-line forced shutdown
	if (!(dwState & DSSTREAM_STOPF_NOREOPEN) && !m_bIsCloseOnRun) {
		LSResetWavePlayer();
		return;
	}
	else {
		if (m_bFileOpen) {
			WaveCloseReadFile(&m_wiWave.hmmio, &m_wiWave.pwfx);
			if (lpDSBStreamBuffer) {
				lpDSBStreamBuffer->Release();
			}

			lpDSBStreamBuffer = NULL;

			m_bFileOpen = FALSE;
		}
	}
}
void LSResetWavePlayer(void)
{
	WaveStartDataRead(&m_wiWave.hmmio, &m_wiWave.mmck, &m_wiWave.mmckInRIFF);
	m_wiWave.bFoundEnd = FALSE;
	m_wiWave.dwBytesRemaining = 0;

	LSFillDataBuffer();

	m_wiWave.bDonePlaying = FALSE;
}
void LSFillDataBuffer(void)
{
	LPBYTE   lpWrite1, lpWrite2;
	DWORD    dwLen1, dwLen2;
	UINT     uActualBytesWritten;
	HRESULT  dsrval;
	dsrval = lpDSBStreamBuffer->Lock(0, m_wiWave.dwBufferSize,
		//&((LPVOID)lpWrite1), 
		(LPVOID*)&lpWrite1,
		&dwLen1,
		//&((LPVOID)lpWrite2), 
		(LPVOID *)&lpWrite2,

		&dwLen2, 0);
	if (dsrval != DS_OK) return;
	//    Assert( NULL == lpWrite2 );
	//    Assert( 0 == dwLen2 );
	if (dwLen1) {
		//        Assert( NULL != lpWrite1 );
		WaveReadFile(m_wiWave.hmmio, (UINT)dwLen1, lpWrite1, &m_wiWave.mmck, &uActualBytesWritten);
		if (uActualBytesWritten < dwLen1) {
			if (m_wiWave.bLoopFile) {
				// If the file is shorter than the buffer and we're looping, we need to
				// read the file in again so that we don't get a block of silence before
				// the timer loops playback.
				LPBYTE lpTemp = lpWrite1;
				DWORD  cbReadLoopTotal = dwLen1;
				do {
					// Continue decrementing our count and moving our temp
					// pointer forward until we've read the file enough times
					// to fill the buffer.  NOTE: It's probably not efficient
					// to bother with the overhead of streaming a file that's
					// not at least as large as the buffer...
					lpTemp += uActualBytesWritten;
					cbReadLoopTotal -= uActualBytesWritten;
					WaveStartDataRead(&m_wiWave.hmmio, &m_wiWave.mmck, &m_wiWave.mmckInRIFF);
					WaveReadFile(m_wiWave.hmmio, (UINT)cbReadLoopTotal, lpTemp, &m_wiWave.mmck, &uActualBytesWritten);
				} while (uActualBytesWritten < cbReadLoopTotal);
			}
			else {
				m_wiWave.bFoundEnd = TRUE;
				m_wiWave.dwBytesRemaining = (DWORD)uActualBytesWritten;
				// Fill in silence
				FillMemory(lpWrite1 + uActualBytesWritten, dwLen1 - uActualBytesWritten,
					(BYTE)(m_wiWave.pwfx->wBitsPerSample == 8 ? 128 : 0));
			}
		}
	}
	dsrval = lpDSBStreamBuffer->Unlock((LPVOID)lpWrite1, dwLen1, (LPVOID)lpWrite2, 0);
	m_wiWave.dwNextWriteOffset = m_wiWave.dwProgress = 0;
}

void CALLBACK LSTimeRunFuncForDSound(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	LPBYTE  lpWrite1, lpWrite2, lpTemp;
	DWORD   dwLen1, dwLen2, dwPlay, dwWrite, dwPlayedLength, dwWriteLength;
	DWORD   dwLeftToRead, dwStatus;
	UINT    uChkErr;
	BOOL    fRefillLostBuffer = FALSE;
	HRESULT dsrval;

	if (InterlockedExchange(&m_lInTimer, TRUE)) return;

	// See if the buffer has been lost
	m_wiWave.lpDSBStreamBuffer->GetStatus(&dwStatus);
	if (DSBSTATUS_BUFFERLOST & dwStatus) {
		// Restore the buffer and set some variables that will cause it
		// to be filled again and replayed
		dsrval = m_wiWave.lpDSBStreamBuffer->Restore();
		if (FAILED(dsrval)) {
			InterlockedExchange(&m_lInTimer, FALSE);
			return;
		}
		m_wiWave.dwNextWriteOffset = 0;
		fRefillLostBuffer = TRUE;
	}

	// Get and print the current position of the play cursor
	m_wiWave.lpDSBStreamBuffer->GetCurrentPosition(&dwPlay, &dwWrite);

	// If the play cursor is at the same spot as the last call, there are two
	// possibilities.  The first is that we were called extremely late and
	// happened to land on an integer number of complete buffer cycles.  This
	// is not very likely.  The other is that the play cursor didn't move.
	// Since we're oversampling, this is very likely.  In this case, we should
	// bail.
	if (dwPlay == m_wiWave.dwNextWriteOffset && !fRefillLostBuffer) {
		InterlockedExchange(&m_lInTimer, FALSE);
		return;
	}
	// Have we found the end of the file and passed the buffer end?
	if (m_wiWave.bFoundEnd && !m_wiWave.dwBytesRemaining) {
		if (!m_wiWave.bDonePlaying) {
			m_wiWave.bDonePlaying = TRUE;
			LSStopBackground(0L);
		}
		InterlockedExchange(&m_lInTimer, FALSE);
		return;
	}

	if (dwPlay < m_wiWave.dwNextWriteOffset) {
		// Calculate how many writeable bytes there are behind the play cursor
		dwPlayedLength = (dwPlay + m_wiWave.dwBufferSize - m_wiWave.dwNextWriteOffset);
	}
	else {
		// Calculate how many writeable bytes there are behind the play cursor
		dwPlayedLength = (dwPlay - m_wiWave.dwNextWriteOffset);
	}

	// If the buffer was lost, then we need to start filling data at the start of
	// the buffer, but we can decrease startup latency by only filling a segment
	// or two this time around.
	if (fRefillLostBuffer) {
		dwWriteLength = 2 * m_wiWave.dwBufferSize / NUM_BUFFER_SEGMENTS;
	}
	else {
		dwWriteLength = dwPlayedLength;
	}

	m_wiWave.dwProgress += dwPlayedLength;

	// If m_wiWave.bFoundEnd == TRUE, then we've finished reading in the file,
	// but we need to wait until the buffer's play cursor passes the point we
	// were at when we found out we were done reading.
	if (m_wiWave.bFoundEnd && m_wiWave.dwBytesRemaining) {
		// Decrement the count of how many bytes we have to wait for before
		// we can kill the timer procedure safely
		if (dwPlayedLength > m_wiWave.dwBytesRemaining) {
			m_wiWave.dwBytesRemaining = 0;
		}
		else {
			m_wiWave.dwBytesRemaining -= dwPlayedLength;
		}
		if (m_wiWave.lpDSBStreamBuffer->Lock(m_wiWave.dwNextWriteOffset, dwWriteLength,
			//&((LPVOID)lpWrite1), 
			(LPVOID *)&lpWrite1,
			&dwLen1,
			//&((LPVOID)lpWrite2), 
			(LPVOID *)&lpWrite2,

			&dwLen2, 0) != 0) {
			OutputDebugString("LSTimeRunFuncForDSound() could not lock DirectSoundBuffer");
			InterlockedExchange(&m_lInTimer, FALSE);
			return;
		}

		// Silence out both parts of the locked buffer
		memset(lpWrite1, m_wiWave.pwfx->wBitsPerSample == 8 ? 128 : 0, dwLen1);

		if (lpWrite2 && dwLen2) {
			memset(lpWrite2, m_wiWave.pwfx->wBitsPerSample == 8 ? 128 : 0, dwLen2);
		}
		m_wiWave.lpDSBStreamBuffer->Unlock((LPVOID)lpWrite1, dwLen1, (LPVOID)lpWrite2, dwLen2);
		// This code is stolen from the end of the routine -- we need to keep
		// zeroing out buffer segments while we're waiting for the play cursor to
		// catch up to the end of the WAVE data.
		m_wiWave.dwNextWriteOffset += dwWriteLength;
		if (m_wiWave.dwNextWriteOffset >= m_wiWave.dwBufferSize) {
			m_wiWave.dwNextWriteOffset -= m_wiWave.dwBufferSize;
		}
		InterlockedExchange(&m_lInTimer, FALSE);
		return;
	}

	// Lock a segment of memory that is behind the play cursor
	if (m_wiWave.lpDSBStreamBuffer->Lock(m_wiWave.dwNextWriteOffset, dwWriteLength,
		//&((LPVOID)lpWrite1), 
		(LPVOID *)&lpWrite1,
		&dwLen1,
		//&((LPVOID)lpWrite2), 
		(LPVOID *)&lpWrite2,
		&dwLen2, 0) != 0) {
		OutputDebugString("LSTimeRunFuncForDSound() could not lock DirectSoundBuffer");
		InterlockedExchange(&m_lInTimer, FALSE);
		return;
	}

	if (dwLen1 && !m_wiWave.bDonePlaying) {
		WaveReadFile(m_wiWave.hmmio, (UINT)dwLen1, lpWrite1, &m_wiWave.mmck, &uChkErr);
		if (uChkErr < (UINT)dwLen1) {
			if (!m_wiWave.bLoopFile) {
				// Zero out the rest of this block
				if (m_wiWave.pwfx->wBitsPerSample == 8) {
					memset(lpWrite1 + uChkErr, 128, ((UINT)dwLen1 - uChkErr));
				}
				else if (m_wiWave.pwfx->wBitsPerSample == 16) {
					memset(lpWrite1 + uChkErr, 0, ((UINT)dwLen1 - uChkErr));
				}

				// Enable play completion detection code at the beginning of the next call
				m_wiWave.bFoundEnd = TRUE;
				if (dwPlay > m_wiWave.dwNextWriteOffset) {
					m_wiWave.dwBytesRemaining = (m_wiWave.dwNextWriteOffset + m_wiWave.dwBufferSize - dwPlay);
				}
				else {
					m_wiWave.dwBytesRemaining = (m_wiWave.dwNextWriteOffset - dwPlay);
				}
			}
			else {
				lpTemp = lpWrite1;
				dwLeftToRead = dwLen1;
				do {
					// Continue decrementing our count and moving our temp
					// pointer forward until we've read the file enough times
					// to fill the buffer.  NOTE: It's probably not efficient
					// to bother with the overhead of streaming a file that's
					// not at least as large as the buffer...
					lpTemp += uChkErr;
					dwLeftToRead -= uChkErr;
					WaveStartDataRead(&m_wiWave.hmmio, &m_wiWave.mmck, &m_wiWave.mmckInRIFF);
					WaveReadFile(m_wiWave.hmmio, (UINT)dwLeftToRead, lpTemp, &m_wiWave.mmck, &uChkErr);
				} while (uChkErr < dwLeftToRead);
			}
		}
	}
	// The bDonePlaying flag is set by the caller if the user stops playback
	// before the end of the WAVE file is encountered.  It tells us to cut this
	// racket out and play nothing in case it takes the caller a couple
	// interrupts to shut off the timer.
	else if (dwLen1 && m_wiWave.bDonePlaying) 
	{
		// Set the appropriate silence value
		_fmemset(lpWrite1, m_wiWave.pwfx->wBitsPerSample == 8 ? 128 : 0, dwLen1);
	}

	if (dwLen2 && !m_wiWave.bDonePlaying) 
	{
		WaveReadFile(m_wiWave.hmmio, (UINT)dwLen2, lpWrite2, &m_wiWave.mmck, &uChkErr);
		if (uChkErr < (UINT)dwLen2) 
		{
			if (!m_wiWave.bLoopFile) 
			{
				// Zero out the rest of this block
				if (m_wiWave.pwfx->wBitsPerSample == 8) {
					memset(lpWrite2 + uChkErr, 128, ((UINT)dwLen2 - uChkErr));
				}
				else if (m_wiWave.pwfx->wBitsPerSample == 16) {
					memset(lpWrite2 + uChkErr, 0, ((UINT)dwLen2 - uChkErr));
				}
				// Enable play completion detection code at the beginning
				// of the next call
				m_wiWave.bFoundEnd = TRUE;
				if (dwPlay > m_wiWave.dwNextWriteOffset) {
					m_wiWave.dwBytesRemaining = (m_wiWave.dwNextWriteOffset + m_wiWave.dwBufferSize - dwPlay);
				}
				else {
					m_wiWave.dwBytesRemaining = (m_wiWave.dwNextWriteOffset - dwPlay);
				}
			}
			else {
				lpTemp = lpWrite2;
				dwLeftToRead = dwLen2;
				do {
					// Continue decrementing our count and moving our temp
					// pointer forward until we've read the file enough times
					// to fill the buffer.  NOTE: It's probably not efficient
					// to bother with the overhead of streaming a file that's
					// not at least as large as the buffer...
					lpTemp += uChkErr;
					dwLeftToRead -= uChkErr;
					WaveStartDataRead(&m_wiWave.hmmio, &m_wiWave.mmck, &m_wiWave.mmckInRIFF);
					WaveReadFile(m_wiWave.hmmio, (UINT)dwLeftToRead, lpTemp, &m_wiWave.mmck, &uChkErr);
				} while (uChkErr < dwLeftToRead);
			}
		}
	}
	else if (lpWrite2 && dwLen2 && m_wiWave.bDonePlaying) 
	{
		// Set the appropriate silence value
		_fmemset(lpWrite2, m_wiWave.pwfx->wBitsPerSample == 8 ? 128 : 0, dwLen2);
	}
	m_wiWave.lpDSBStreamBuffer->Unlock((LPVOID)lpWrite1, dwLen1, (LPVOID)lpWrite2, dwLen2);
	m_wiWave.dwNextWriteOffset += dwWriteLength;
	if (m_wiWave.dwNextWriteOffset >= m_wiWave.dwBufferSize) {
		m_wiWave.dwNextWriteOffset -= m_wiWave.dwBufferSize;
	}
	if (fRefillLostBuffer) 
	{
		m_wiWave.lpDSBStreamBuffer->Play(0, 0, DSBPLAY_LOOPING);
	}
	InterlockedExchange(&m_lInTimer, FALSE);

	return;
}









BOOL OpenBGM(LPSTR lpszFileName)
{
	if (LSEnable == TRUE) 
	{
		if (m_bFileOpen) 
		{
			m_bIsCloseOnRun = FALSE;
			
			LSStopBackground(DSSTREAM_STOPF_NOREOPEN);
		}
		if ((SetupStreamBuffer(lpszFileName)) != DS_OK) 
		{
			return FALSE;
		}
		else 
		{
			m_bFileOpen = TRUE;
		}
	}
	return TRUE;
}

HRESULT SetupStreamBuffer(LPSTR lpszFilename)
{
	DSBUFFERDESC dsbd;
	HRESULT      dsRetVal;

	if (WaveOpenFile(lpszFilename, &m_wiWave.hmmio, &m_wiWave.pwfx, &m_wiWave.mmckInRIFF) != 0) {
		return ERR_WAVE_OPEN_FAILED;
	}

	if (m_wiWave.pwfx->wFormatTag != WAVE_FORMAT_PCM) {
		WaveCloseReadFile(&m_wiWave.hmmio, &m_wiWave.pwfx);
		return ERR_WAVE_INVALID_FORMAT;
	}
	// Seek to the data chunk
	if (WaveStartDataRead(&m_wiWave.hmmio, &m_wiWave.mmck, &m_wiWave.mmckInRIFF) != 0) {
		WaveCloseReadFile(&m_wiWave.hmmio, &m_wiWave.pwfx);
		return ERR_WAVE_CORRUPTED_FILE;
	}

	m_wiWave.dwBufferSize = ((DWORD)m_wiWave.pwfx->nAvgBytesPerSec * (((NUM_BUFFER_SEGMENTS * PLAYBACK_TIMER_PERIOD) / 10)) / 100);

	// Create the secondary DirectSoundBuffer object to receive our sound data.
	memset(&dsbd, 0, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GETCURRENTPOSITION2 | m_SecondBuffFocus;
	dsbd.dwBufferBytes = m_wiWave.dwBufferSize;
	dsbd.lpwfxFormat = m_wiWave.pwfx;

	dsRetVal = lpDirectSound->CreateSoundBuffer(&dsbd, &lpDSBStreamBuffer, NULL);

	if (dsRetVal != DS_OK) {
		return ERR_CREATEDSB_FAILED;
	}

	m_wiWave.lpDSBStreamBuffer = lpDSBStreamBuffer;
	m_wiWave.bFoundEnd = FALSE;
	m_wiWave.dwBytesRemaining = 0;
	m_wiWave.bLoopFile = TRUE;

	LSFillDataBuffer();

	m_wiWave.bDonePlaying = FALSE;

	if (lpDSBStreamBuffer) 
	{
		lpDSBStreamBuffer->SetVolume((((VOL_MAX + VOL_SHIFT) * VOL_MULT)));
		lpDSBStreamBuffer->SetPan(((((PAN_MAX / 2) + PAN_SHIFT) * PAN_MULT)));
		lpDSBStreamBuffer->SetFrequency(m_wiWave.pwfx->nSamplesPerSec);
	}
	return DS_OK;
}
void PlayBGM(void)
{
	if (LSEnable == TRUE && SETTINGHANDLE->Get().bNoMusic == FALSE)
	{
		if (m_bPlaying)
		{
			m_bIsCloseOnRun = FALSE;
			LSStopBackground(0L);
		}
		if (m_bFileOpen && lpDSBStreamBuffer)
		{
			lpDSBStreamBuffer->SetCurrentPosition(0);
			lpDSBStreamBuffer->Play(0, 0, DSBPLAY_LOOPING);
		}
		else
		{
			m_bPlaying = FALSE;
			m_bTimerInit = FALSE;
			return;
		}

		if (timeBeginPeriod(PLAYBACK_TIMER_PERIOD / PLAYBACK_OVERSAMPLE) != 0)
		{
			lpDSBStreamBuffer->Stop();
			m_bPlaying = FALSE;
			m_bTimerInit = FALSE;
			return;
		}
		else
		{
			m_lInTimer = FALSE;
			if ((m_uTimerID = timeSetEvent(PLAYBACK_TIMER_PERIOD / PLAYBACK_OVERSAMPLE, PLAYBACK_TIMER_ACCURACY, LSTimeRunFuncForDSound, (DWORD)0, TIME_PERIODIC)) != 0)
				m_bTimerInit = TRUE;
		}
		m_bPlaying = TRUE;
	}
}

void StopBGM(void)
{
	if (LSEnable == TRUE && m_bPlaying)
		LSStopBackground(0);
}

void SetVolumeBGM(DWORD dwVol)
{
	if (LSEnable == TRUE && m_bPlaying)
		lpDSBStreamBuffer->SetVolume((dwVol + VOL_SHIFT) * VOL_MULT);
}
int GetVolumeBGM(DWORD dwVol)
{
	return dwVol * 350 / 100;
}
BOOL Init_BGM(HWND hwnd)
{
	m_hWnd = hwnd;

	lpDirectSound = NULL;

	lpDSBStreamBuffer = NULL;

	m_lInTimer = FALSE;
	m_bTimerInit = FALSE;
	m_bPlaying = FALSE;
	m_bIsCloseOnRun = FALSE;
	m_bFileOpen = FALSE;
	m_uTimerID = 0;
	m_SecondBuffFocus = 0;

	HRESULT         dsrval;

	dsrval = DirectSoundCreate(NULL, &lpDirectSound, NULL);

	if (SUCCEEDED(dsrval) && (NULL != lpDirectSound)) 
	{
		dsrval = lpDirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);

		if (!SUCCEEDED(dsrval)) 
		{
			dsrval = FALSE;
			lpDirectSound->Release();
			lpDirectSound = NULL;
		}
	}


	if (SUCCEEDED(dsrval)) {
		LSEnable = TRUE;
		return TRUE;
	}
	else {
		LSEnable = FALSE;
		return FALSE;
	}




	LSEnable = TRUE;

	return TRUE;
}


void Uninit_BGM(void)
{
	if (LSEnable == TRUE) {

		LSStopBackground(DSSTREAM_STOPF_NOREOPEN | DSSTREAM_STOPF_NOEXIT);


		if (m_bTimerInit) {
			timeKillEvent(m_uTimerID);
			timeEndPeriod(PLAYBACK_TIMER_PERIOD / PLAYBACK_OVERSAMPLE);
			// Busy wait for timer func to exit
			while (InterlockedExchange(&m_lInTimer, TRUE)) Sleep(100);
			m_bTimerInit = FALSE;
		}


		if (lpDSBStreamBuffer) {
			lpDSBStreamBuffer->Stop();
			lpDSBStreamBuffer->Release();
			lpDSBStreamBuffer = NULL;
		}

		if (lpDirectSound != NULL) {
			lpDirectSound->Release();
			lpDirectSound = NULL;
		}


	}
}
void InitDirectSound()
{
	lpDirectSound = NULL;

	rval_g_lpDs = DirectSoundCreate(NULL, &g_lpDS, NULL);

	dsrval_lpDirectSound = DirectSoundCreate(NULL, &lpDirectSound, NULL);
}