#include "StdAfx.h"
#include "wave.h"


BOOL LSEnable = FALSE;


int WaveOpenFile(char *pszFileName, HMMIO *phmmioIn, WAVEFORMATEX **ppwfxInfo, MMCKINFO *pckInRIFF)
{
	HMMIO         hmmioIn;
	MMCKINFO      ckIn;           // chunk info. for general use.
	PCMWAVEFORMAT pcmWaveFormat;  // Temp PCM structure to load in.
	WORD          cbExtraAlloc;   // Extra bytes for waveformatex
	int           nError;         // Return value.

	*ppwfxInfo = NULL;
	nError = 0;
	hmmioIn = NULL;

	if ((hmmioIn = mmioOpen(pszFileName, NULL, MMIO_ALLOCBUF | MMIO_READ)) == NULL) {
		nError = ER_CANNOTOPEN;
		goto ERROR_READING_WAVE;
	}

	if ((nError = (int)mmioDescend(hmmioIn, pckInRIFF, NULL, 0)) != 0) {
		goto ERROR_READING_WAVE;
	}

	if ((pckInRIFF->ckid != FOURCC_RIFF) || (pckInRIFF->fccType != mmioFOURCC('W', 'A', 'V', 'E'))) {
		nError = ER_NOTWAVEFILE;
		goto ERROR_READING_WAVE;
	}

	// Search the input file for for the 'fmt ' chunk.
	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if ((nError = (int)mmioDescend(hmmioIn, &ckIn, pckInRIFF, MMIO_FINDCHUNK)) != 0) {
		goto ERROR_READING_WAVE;
	}

	// Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
	// if there are extra parameters at the end, we'll ignore them

	if (ckIn.cksize < (long) sizeof(PCMWAVEFORMAT)) {
		nError = ER_NOTWAVEFILE;
		goto ERROR_READING_WAVE;
	}

	// Read the 'fmt ' chunk into <pcmWaveFormat>.
	if (mmioRead(hmmioIn, (HPSTR)&pcmWaveFormat, (long) sizeof(pcmWaveFormat)) != (long) sizeof(pcmWaveFormat)) {
		nError = ER_CANNOTREAD;
		goto ERROR_READING_WAVE;
	}

	// Ok, allocate the waveformatex, but if its not pcm
	// format, read the next word, and thats how many extra
	// bytes to allocate.
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM) {
		cbExtraAlloc = 0;
	}
	else {
		// Read in length of extra bytes.
		if (mmioRead(hmmioIn, (LPSTR)&cbExtraAlloc, (long)sizeof(cbExtraAlloc)) != (long) sizeof(cbExtraAlloc)) {
			nError = ER_CANNOTREAD;
			goto ERROR_READING_WAVE;
		}
	}

	// Ok, now allocate that waveformatex structure.
	if ((*ppwfxInfo = (WAVEFORMATEX*)GlobalAlloc(GMEM_FIXED, sizeof(WAVEFORMATEX) + cbExtraAlloc)) == NULL) {
		nError = ER_MEM;
		goto ERROR_READING_WAVE;
	}

	// Copy the bytes from the pcm structure to the waveformatex structure
	memcpy(*ppwfxInfo, &pcmWaveFormat, sizeof(pcmWaveFormat));
	(*ppwfxInfo)->cbSize = cbExtraAlloc;

	// Now, read those extra bytes into the structure, if cbExtraAlloc != 0.
	if (cbExtraAlloc != 0) {
		if (mmioRead(hmmioIn, (LPSTR)(((BYTE*)&((*ppwfxInfo)->cbSize)) + sizeof(cbExtraAlloc)), (long)(cbExtraAlloc)) != (long)(cbExtraAlloc)) {
			nError = ER_NOTWAVEFILE;
			goto ERROR_READING_WAVE;
		}
	}

	// Ascend the input file out of the 'fmt ' chunk.
	if ((nError = mmioAscend(hmmioIn, &ckIn, 0)) != 0) {
		goto ERROR_READING_WAVE;
	}
	goto TEMPCLEANUP;

ERROR_READING_WAVE:
	if (*ppwfxInfo != NULL) {
		GlobalFree(*ppwfxInfo);
		*ppwfxInfo = NULL;
	}

	if (hmmioIn != NULL) {
		mmioClose(hmmioIn, 0);
		hmmioIn = NULL;
	}

TEMPCLEANUP:
	*phmmioIn = hmmioIn;

	return nError;
}


int WaveStartDataRead(HMMIO *phmmioIn, MMCKINFO *pckIn, MMCKINFO *pckInRIFF)
{
	if ((mmioSeek(*phmmioIn, pckInRIFF->dwDataOffset + sizeof(FOURCC), SEEK_SET)) == -1)
	{
		LSEnable = FALSE;
	}

	pckIn->ckid = mmioFOURCC('d', 'a', 't', 'a');

	return mmioDescend(*phmmioIn, pckIn, pckInRIFF, MMIO_FINDCHUNK);
}

int WaveReadFile(HMMIO hmmioIn, UINT cbRead, BYTE *pbDest, MMCKINFO *pckIn, UINT *cbActualRead)
{
	UINT i;
	MMIOINFO mmioinfoIn;
	UINT     cbDataIn;

	int nError = 0;

	if ((nError = mmioGetInfo(hmmioIn, &mmioinfoIn, 0)) != 0)
	{
		*cbActualRead = 0;
		return nError;
	}

	cbDataIn = cbRead;
	if (cbDataIn > pckIn->cksize)
		cbDataIn = pckIn->cksize;

	pckIn->cksize -= cbDataIn;

	for (i = 0; i < cbDataIn; i++)
	{
		if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
		{
			if ((nError = mmioAdvance(hmmioIn, &mmioinfoIn, MMIO_READ)) != 0)
			{
				*cbActualRead = 0;
				return nError;
			}
			if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
			{
				nError = ER_CORRUPTWAVEFILE;
				*cbActualRead = 0;
				return nError;
			}
		}

		*((BYTE*)pbDest + i) = *((BYTE*)mmioinfoIn.pchNext);

		*mmioinfoIn.pchNext++;
	}

	if ((nError = mmioSetInfo(hmmioIn, &mmioinfoIn, 0)) != 0)
	{
		*cbActualRead = 0;
		return nError;
	}

	*cbActualRead = cbDataIn;
	return nError;
}

int WaveCloseReadFile(HMMIO *phmmio, WAVEFORMATEX **ppwfxSrc)
{
	if (*ppwfxSrc != NULL)
	{
		GlobalFree(*ppwfxSrc);
		*ppwfxSrc = NULL;
	}

	if (*phmmio != NULL)
	{
		mmioClose(*phmmio, 0);
		*phmmio = NULL;
	}

	return 0;
}

int WaveCreateFile(char *pszFileName, HMMIO *phmmioOut, WAVEFORMATEX *pwfxDest, MMCKINFO *pckOut, MMCKINFO *pckOutRIFF)
{
	DWORD    dwFactChunk;            // Contains the actual fact chunk. Garbage until WaveCloseWriteFile.
	MMCKINFO ckOut1;

	dwFactChunk = (DWORD)-1;
	int nError = 0;

	*phmmioOut = mmioOpen(pszFileName, NULL, MMIO_ALLOCBUF | MMIO_READWRITE | MMIO_CREATE);

	if (*phmmioOut == NULL)
	{
		return ER_CANNOTWRITE;
	}

	pckOutRIFF->fccType = mmioFOURCC('W', 'A', 'V', 'E');
	pckOutRIFF->cksize = 0;

	if ((nError = mmioCreateChunk(*phmmioOut, pckOutRIFF, MMIO_CREATERIFF)) != 0)
	{
		return nError;
	}

	pckOut->ckid = mmioFOURCC('f', 'm', 't', ' ');
	pckOut->cksize = sizeof(PCMWAVEFORMAT);   // we know the size of this ck.
	if ((nError = mmioCreateChunk(*phmmioOut, pckOut, 0)) != 0)
	{
		return nError;
	}

	// Write the PCMWAVEFORMAT structure to the 'fmt ' chunk if its that type.
	if (pwfxDest->wFormatTag == WAVE_FORMAT_PCM)
	{
		if ((UINT)(mmioWrite(*phmmioOut, (HPSTR)pwfxDest, sizeof(PCMWAVEFORMAT))) != sizeof(PCMWAVEFORMAT))
		{
			return ER_CANNOTWRITE;
		}
	}
	else
	{
		// Write the variable length size.
		if ((UINT)mmioWrite(*phmmioOut, (HPSTR)pwfxDest, sizeof(*pwfxDest) + pwfxDest->cbSize) != (sizeof(*pwfxDest) + pwfxDest->cbSize))
		{
			return ER_CANNOTWRITE;
		}
	}

	// Ascend out of the 'fmt ' chunk, back into the 'RIFF' chunk.
	if ((nError = mmioAscend(*phmmioOut, pckOut, 0)) != 0)
	{
		return nError;    // cannot write file, probably
	}

	ckOut1.ckid = mmioFOURCC('f', 'a', 'c', 't');
	ckOut1.cksize = 0;
	if ((nError = mmioCreateChunk(*phmmioOut, &ckOut1, 0)) != 0)
	{
		return nError;
	}

	if ((UINT)mmioWrite(*phmmioOut, (HPSTR)&dwFactChunk, sizeof(dwFactChunk)) != sizeof(dwFactChunk))
	{
		return ER_CANNOTWRITE;
	}

	// Now ascend out of the fact chunk...
	if ((nError = mmioAscend(*phmmioOut, &ckOut1, 0)) != 0)
	{
		return ER_CANNOTWRITE;
	}

	return nError;

}

int WaveStartDataWrite(HMMIO *phmmioOut, MMCKINFO *pckOut, MMIOINFO *pmmioinfoOut)
{
	int nError = 0;

	pckOut->ckid = mmioFOURCC('d', 'a', 't', 'a');
	pckOut->cksize = 0;
	if ((nError = mmioCreateChunk(*phmmioOut, pckOut, 0)) != 0)
	{
		return nError;
	}

	return mmioGetInfo(*phmmioOut, pmmioinfoOut, 0);
}
int WaveWriteFile(HMMIO hmmioOut, UINT cbWrite, BYTE *pbSrc, MMCKINFO *pckOut, UINT *cbActualWrite, MMIOINFO *pmmioinfoOut)
{
	int nError = 0;

	*cbActualWrite = 0;

	for (UINT i = 0; i < cbWrite; i++)
	{
		if (pmmioinfoOut->pchNext == pmmioinfoOut->pchEndWrite)
		{
			pmmioinfoOut->dwFlags |= MMIO_DIRTY;
			if ((nError = mmioAdvance(hmmioOut, pmmioinfoOut, MMIO_WRITE)) != 0)
			{
				return nError;
			}
		}

		*((BYTE*)pmmioinfoOut->pchNext) = *((BYTE*)pbSrc + i);

		*pmmioinfoOut->pchNext++;

		(*cbActualWrite)++;
	}

	return nError;
}

int WaveCloseWriteFile(HMMIO *phmmioOut, MMCKINFO *pckOut, MMCKINFO *pckOutRIFF, MMIOINFO *pmmioinfoOut, DWORD cSamples)
{
	int nError;

	nError = 0;

	if (*phmmioOut == NULL) return 0;

	pmmioinfoOut->dwFlags |= MMIO_DIRTY;
	if ((nError = mmioSetInfo(*phmmioOut, pmmioinfoOut, 0)) != 0) {
		// cannot flush, probably...
		goto ERROR_CANNOT_WRITE;
	}

	// Ascend the output file out of the 'data' chunk -- this will cause
	// the chunk size of the 'data' chunk to be written.
	if ((nError = mmioAscend(*phmmioOut, pckOut, 0)) != 0)
		goto ERROR_CANNOT_WRITE;    // cannot write file, probably

	// Do this here instead...
	if ((nError = mmioAscend(*phmmioOut, pckOutRIFF, 0)) != 0)
		goto ERROR_CANNOT_WRITE;    // cannot write file, probably

	nError = mmioSeek(*phmmioOut, 0, SEEK_SET);
	if ((nError = (int)mmioDescend(*phmmioOut, pckOutRIFF, NULL, 0)) != 0) {
		goto ERROR_CANNOT_WRITE;
	}

	nError = 0;
	pckOut->ckid = mmioFOURCC('f', 'a', 'c', 't');
	if ((nError = mmioDescend(*phmmioOut, pckOut, pckOutRIFF, MMIO_FINDCHUNK)) == 0) {
		// If it didn't fail, write the fact chunk out, if it failed, not critical, just
		// assert (below).
		nError = mmioWrite(*phmmioOut, (HPSTR)&cSamples, sizeof(DWORD));
		nError = mmioAscend(*phmmioOut, pckOut, 0);
		nError = 0;
	}
	else {
		nError = 0;
		LSEnable = FALSE;
		//        Assert(FALSE);
	}

	// CANTWRITEFACT:
		// Ascend the output file out of the 'RIFF' chunk -- this will cause
		// the chunk size of the 'RIFF' chunk to be written.
		//
	if ((nError = mmioAscend(*phmmioOut, pckOutRIFF, 0)) != 0)
		goto ERROR_CANNOT_WRITE;    // cannot write file, probably

ERROR_CANNOT_WRITE:
	if (*phmmioOut != NULL) {
		mmioClose(*phmmioOut, 0);
		*phmmioOut = NULL;
	}

	return nError;
}
int WaveCopyUselessChunks(HMMIO *phmmioIn, MMCKINFO *pckIn, MMCKINFO *pckInRiff, HMMIO *phmmioOut, MMCKINFO *pckOut, MMCKINFO *pckOutRiff)
{
	int nError;

	nError = 0;
	// First seek to the stinking start of the file, not including the riff header...
	if ((nError = mmioSeek(*phmmioIn, pckInRiff->dwDataOffset + sizeof(FOURCC), SEEK_SET)) == -1) {
		nError = ER_CANNOTREAD;
		goto ERROR_IN_PROC;
	}

	nError = 0;

	while (mmioDescend(*phmmioIn, pckIn, pckInRiff, 0) == 0) {

		//  quickly check for corrupt RIFF file--don't ascend past end!
		if ((pckIn->dwDataOffset + pckIn->cksize) > (pckInRiff->dwDataOffset + pckInRiff->cksize))
			goto ERROR_IN_PROC;

		switch (pckIn->ckid) {
			//  explicitly skip these...
		case mmioFOURCC('f', 'm', 't', ' '):
			break;
		case mmioFOURCC('d', 'a', 't', 'a'):
			break;
		case mmioFOURCC('f', 'a', 'c', 't'):
			break;
		case mmioFOURCC('J', 'U', 'N', 'K'):
			break;
		case mmioFOURCC('P', 'A', 'D', ' '):
			break;
		case mmioFOURCC('c', 'u', 'e', ' '):
			break;
			//  copy chunks that are OK to copy
		case mmioFOURCC('p', 'l', 's', 't'):
			// although without the 'cue' chunk, it doesn't make much sense
			riffCopyChunk(*phmmioIn, *phmmioOut, pckIn);
			break;
		case mmioFOURCC('D', 'I', 'S', 'P'):
			riffCopyChunk(*phmmioIn, *phmmioOut, pckIn);
			break;
			//  don't copy unknown chunks
		default:
			break;
		}
		//  step up to prepare for next chunk..
		mmioAscend(*phmmioIn, pckIn, 0);
	}

ERROR_IN_PROC:
	{
		// Seek back to riff header
		mmioSeek(*phmmioIn, pckInRiff->dwDataOffset + sizeof(FOURCC), SEEK_SET);
	}

	return nError;
}
BOOL riffCopyChunk(HMMIO hmmioSrc, HMMIO hmmioDst, const LPMMCKINFO lpck)
{
	MMCKINFO    ck;
	HPSTR       hpBuf;

	hpBuf = (HPSTR)GlobalAllocPtr(GHND, lpck->cksize);
	if (!hpBuf) return FALSE;

	ck.ckid = lpck->ckid;
	ck.cksize = lpck->cksize;
	if (mmioCreateChunk(hmmioDst, &ck, 0))
	{
		if (hpBuf) GlobalFreePtr(hpBuf);

		return FALSE;
	}

	if (mmioRead(hmmioSrc, hpBuf, lpck->cksize) != (LONG)lpck->cksize)
	{
		if (hpBuf) GlobalFreePtr(hpBuf);

		return FALSE;
	}

	if (mmioWrite(hmmioDst, hpBuf, lpck->cksize) != (LONG)lpck->cksize)
	{
		if (hpBuf) GlobalFreePtr(hpBuf);

		return FALSE;
	}

	if (mmioAscend(hmmioDst, &ck, 0))
	{
		if (hpBuf) GlobalFreePtr(hpBuf);

		return FALSE;
	}

	if (hpBuf) GlobalFreePtr(hpBuf);

	return TRUE;

}



int WaveLoadFile(char *pszFileName, UINT *cbSize, DWORD *pcSamples, WAVEFORMATEX **ppwfxInfo, BYTE **ppbData)
{
	HMMIO    hmmioIn;
	MMCKINFO ckInRiff;
	MMCKINFO ckIn;
	int      nError;
	UINT     cbActualRead;

	*ppbData = NULL;
	*ppwfxInfo = NULL;
	*cbSize = 0;

	if ((nError = WaveOpenFile(pszFileName, &hmmioIn, ppwfxInfo, &ckInRiff)) != 0) {
		goto ERROR_LOADING;
	}

	if ((nError = WaveStartDataRead(&hmmioIn, &ckIn, &ckInRiff)) != 0) {
		goto ERROR_LOADING;
	}

	// Ok, size of wave data is in ckIn, allocate that buffer.
	if ((*ppbData = (BYTE *)GlobalAlloc(GMEM_FIXED, ckIn.cksize)) == NULL) {
		nError = ER_MEM;
		goto ERROR_LOADING;
	}

	if ((nError = WaveReadFile(hmmioIn, ckIn.cksize, *ppbData, &ckIn, &cbActualRead)) != 0) {
		goto ERROR_LOADING;
	}

	*cbSize = cbActualRead;
	goto DONE_LOADING;

ERROR_LOADING:
	if (*ppbData != NULL) {
		GlobalFree(*ppbData);
		*ppbData = NULL;
	}
	if (*ppwfxInfo != NULL) {
		GlobalFree(*ppwfxInfo);
		*ppwfxInfo = NULL;
	}

DONE_LOADING:
	// Close the wave file.
	if (hmmioIn != NULL) {
		mmioClose(hmmioIn, 0);
		hmmioIn = NULL;
	}

	return nError;
}
int WaveSaveFile(char *pszFileName, UINT cbSize, DWORD cSamples, WAVEFORMATEX *pwfxDest, BYTE *pbData)
{
	HMMIO     hmmioOut;
	MMCKINFO  ckOut;
	MMCKINFO  ckOutRIFF;
	MMIOINFO  mmioinfoOut;
	UINT      cbActualWrite;
	int       nError = 0;

	if ((nError = WaveCreateFile(pszFileName, &hmmioOut, pwfxDest, &ckOut, &ckOutRIFF)) != 0) {
		return nError;
	}

	if ((nError = WaveStartDataWrite(&hmmioOut, &ckOut, &mmioinfoOut)) != 0) {
		return nError;
	}

	if ((nError = WaveWriteFile(hmmioOut, cbSize, pbData, &ckOut, &cbActualWrite, &mmioinfoOut)) != 0) {
		return nError;
	}

	if ((nError = WaveCloseWriteFile(&hmmioOut, &ckOut, &ckOutRIFF, &mmioinfoOut, cSamples)) != 0) {
		return nError;
	}

	return nError;
}
