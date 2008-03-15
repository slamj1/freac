 /* BonkEnc Audio Encoder
  * Copyright (C) 2001-2008 Robert Kausch <robert.kausch@bonkenc.org>
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the "GNU General Public License".
  *
  * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
  * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
  * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE. */

#include <startconsole.h>
#include <joblist.h>
#include <dllinterfaces.h>

using namespace smooth::System;

Int StartConsole(const Array<String> &args)
{
	BonkEnc::debug_out = new BonkEnc::Debug("BonkEnc.log");

	BonkEnc::debug_out->OutputLine("");
	BonkEnc::debug_out->OutputLine("=========================================");
	BonkEnc::debug_out->OutputLine("= Starting BonkEnc command line tool... =");
	BonkEnc::debug_out->OutputLine("=========================================");
	BonkEnc::debug_out->OutputLine("");

	BonkEnc::BonkEncCommandline::Get(args);
	BonkEnc::BonkEncCommandline::Free();

	BonkEnc::debug_out->OutputLine("");
	BonkEnc::debug_out->OutputLine("======================================");
	BonkEnc::debug_out->OutputLine("= Leaving BonkEnc command line tool! =");
	BonkEnc::debug_out->OutputLine("======================================");

	delete BonkEnc::debug_out;

	return 0;
}

BonkEnc::BonkEncCommandline *BonkEnc::BonkEncCommandline::Get(const Array<String> &args)
{
	if (instance == NIL) new BonkEncCommandline(args);

	return (BonkEncCommandline *) instance;
}

Void BonkEnc::BonkEncCommandline::Free()
{
	if (instance != NIL) Object::DeleteObject(instance);
}

BonkEnc::BonkEncCommandline::BonkEncCommandline(const Array<String> &arguments) : args(arguments)
{
	currentConfig->enable_console = true;

	if (currentConfig->language == "") i18n->ActivateLanguage("internal");

	i18n->ActivateLanguage(currentConfig->language);

	InitCDRip();

	Bool		 quiet		= ScanForParameter("-quiet", NULL);
	Bool		 cddb		= ScanForParameter("-cddb", NULL);
	Array<String>	 files;
	String		 encoderID	= "LAME";
	String		 helpenc	= "";
	String		 outdir		= ".";
	String		 outfile	= "";
	String		 pattern	= "<artist> - <title>";
	String		 cdDrive	= "0";
	String		 tracks		= "";
	String		 timeout	= "120";

	ScanForParameter("-e", &encoderID);
	ScanForParameter("-h", &helpenc);
	ScanForParameter("-d", &outdir);
	ScanForParameter("-o", &outfile);
	ScanForParameter("-p", &pattern);
	ScanForParameter("-cd", &cdDrive);
	ScanForParameter("-track", &tracks);
	ScanForParameter("-t", &timeout);

	ScanForFiles(&files);

	if (currentConfig->enable_cdrip)
	{
		currentConfig->cdrip_activedrive = cdDrive.ToInt();

		if (currentConfig->cdrip_activedrive >= ex_CR_GetNumCDROM())
		{
			Console::OutputString(String("Warning: Drive #").Append(cdDrive).Append(" does not exist. Using first drive.\n"));

			currentConfig->cdrip_activedrive = 0;
		}

		if (!TracksToFiles(tracks, &files))
		{
			Console::OutputString("Error: Invalid track(s) specified after -track.\n");

			return;
		}
	}
	else if (tracks != NIL)
	{
		Console::OutputString("Error: CD ripping disabled!");
	}

	Console::SetTitle(String("BonkEnc ").Append(BonkEnc::version));

	if (files.Length() == 0 ||
	    helpenc != NIL ||
	    !(encoderID == "LAME" || encoderID == "VORBIS" || encoderID == "BONK" || encoderID == "BLADE" || encoderID == "FAAC" || encoderID == "FLAC" || encoderID == "TVQ" || encoderID == "WAVE" || encoderID == "lame" || encoderID == "vorbis" || encoderID == "bonk" || encoderID == "blade" || encoderID == "faac" || encoderID == "flac" || encoderID == "tvq" || encoderID == "wave") ||
	    (files.Length() > 1 && outfile != ""))
	{
		ShowHelp(helpenc);

		return;
	}

	joblist	= new JobList(Point(0, 0), Size(0, 0));

	bool	 broken = false;

/*	if (((encoderID == "LAME"   || encoderID == "lame")	&& !currentConfig->enable_lame)   ||
	    ((encoderID == "VORBIS" || encoderID == "vorbis")	&& !currentConfig->enable_vorbis) ||
	    ((encoderID == "BONK"   || encoderID == "bonk")	&& !currentConfig->enable_bonk)   ||
	    ((encoderID == "BLADE"  || encoderID == "blade")	&& !currentConfig->enable_blade)  ||
	    ((encoderID == "FAAC"   || encoderID == "faac")	&& !currentConfig->enable_faac)   ||
	    ((encoderID == "FLAC"   || encoderID == "flac")	&& !currentConfig->enable_flac)   ||
	    ((encoderID == "TVQ"    || encoderID == "tvq")	&& !currentConfig->enable_tvq))
	{
		Console::OutputString(String("Encoder ").Append(encoderID).Append(" is not available!\n\n"));

		broken = true;
	}
*/
	if (encoderID == "LAME" || encoderID == "lame")
	{
		String	 bitrate = "192";
		String	 quality = "5";
		String	 mode	 = "VBR";

		ScanForParameter("-b", &bitrate);
		ScanForParameter("-q", &quality);
		ScanForParameter("-m", &mode);

/*		currentConfig->lame_preset = 0;
		currentConfig->lame_set_bitrate = True;

		currentConfig->lame_bitrate    = Math::Max(0, Math::Min(320, bitrate.ToInt()));
		currentConfig->lame_abrbitrate = Math::Max(0, Math::Min(320, bitrate.ToInt()));
		currentConfig->lame_vbrquality = Math::Max(0, Math::Min(9, quality.ToInt()));

		if (mode == "VBR" || mode == "vbr")	 currentConfig->lame_vbrmode = 2;
		else if (mode == "ABR" || mode == "abr") currentConfig->lame_vbrmode = 3;
		else if (mode == "CBR" || mode == "cbr") currentConfig->lame_vbrmode = 0;
*/
		currentConfig->encoderID = "lame-out";
	}
	else if (encoderID == "VORBIS" || encoderID == "vorbis")
	{
		String	 bitrate = "192";
		String	 quality = "60";

/*		if (ScanForParameter("-b", &bitrate))		currentConfig->vorbis_mode = 1;
		else if (ScanForParameter("-q", &quality))	currentConfig->vorbis_mode = 0;
		else						currentConfig->vorbis_mode = 0;

		currentConfig->vorbis_quality = Math::Max(0, Math::Min(100, quality.ToInt()));
		currentConfig->vorbis_bitrate = Math::Max(45, Math::Min(500, bitrate.ToInt()));
*/
		currentConfig->encoderID = "vorbis-out";
	}
	else if (encoderID == "BONK" || encoderID == "bonk")
	{
		String	 quantization = "0.4";
		String	 predictor    = "32";
		String	 downsampling = "2";

		ScanForParameter("-q", &quantization);
		ScanForParameter("-p", &predictor);
		ScanForParameter("-r", &downsampling);

/*		currentConfig->bonk_jstereo	 = ScanForParameter("-js", NULL);
		currentConfig->bonk_lossless	 = ScanForParameter("-lossless", NULL);

		currentConfig->bonk_quantization = Math::Max(0, Math::Min(40, Math::Round(quantization.ToFloat() * 20)));
		currentConfig->bonk_predictor	 = Math::Max(0, Math::Min(512, predictor.ToInt()));
		currentConfig->bonk_downsampling = Math::Max(0, Math::Min(10, downsampling.ToInt()));
*/
		currentConfig->encoderID = "bonk-out";
	}
	else if (encoderID == "BLADE" || encoderID == "blade")
	{
		String	 bitrate = "192";

		ScanForParameter("-b", &bitrate);

//		currentConfig->blade_bitrate = Math::Max(32, Math::Min(320, bitrate.ToInt()));

		currentConfig->encoderID = "blade-out";
	}
	else if (encoderID == "FAAC" || encoderID == "faac")
	{
		String	 bitrate = "64";
		String	 quality = "100";

/*		if (ScanForParameter("-b", &bitrate))		currentConfig->faac_set_quality = False;
		else if (ScanForParameter("-q", &quality))	currentConfig->faac_set_quality = True;
		else						currentConfig->faac_set_quality = True;

		currentConfig->faac_enable_mp4	= ScanForParameter("-mp4", NULL);

		currentConfig->faac_aac_quality	= Math::Max(10, Math::Min(500, quality.ToInt()));
		currentConfig->faac_bitrate	= Math::Max(8, Math::Min(256, bitrate.ToInt()));
*/
		currentConfig->encoderID = "faac-out";
	}
	else if (encoderID == "FLAC" || encoderID == "flac")
	{
		String	 blocksize = "4608";
		String	 lpc = "8";
		String	 qlp = "0";
		String	 rice = "3,3";
		String	 minrice;
		String	 maxrice;

		ScanForParameter("-b", &blocksize);
		ScanForParameter("-l", &lpc);
		ScanForParameter("-q", &qlp);
		ScanForParameter("-r", &rice);

		Int	 i = 0;
		Int	 j = 0;

		for (i = 0; i < rice.Length(); i++)	{ if (rice[i] == ',') break; minrice[i] = rice[i]; }
		for (j = i + 1; j < rice.Length(); j++)	{ maxrice[j - i - 1] = rice[j]; }

/*		currentConfig->flac_preset = -1;

		currentConfig->flac_do_mid_side_stereo		 = ScanForParameter("-m", NULL);
		currentConfig->flac_do_exhaustive_model_search	 = ScanForParameter("-e", NULL);
		currentConfig->flac_do_qlp_coeff_prec_search	 = ScanForParameter("-p", NULL);

		currentConfig->flac_blocksize			 = Math::Max(192, Math::Min(32768, blocksize.ToInt()));
		currentConfig->flac_max_lpc_order		 = Math::Max(0, Math::Min(32, lpc.ToInt()));
		currentConfig->flac_qlp_coeff_precision		 = Math::Max(0, Math::Min(16, qlp.ToInt()));
		currentConfig->flac_min_residual_partition_order = Math::Max(0, Math::Min(16, minrice.ToInt()));
		currentConfig->flac_max_residual_partition_order = Math::Max(0, Math::Min(16, maxrice.ToInt()));
*/
		currentConfig->encoderID = "flac-out";
	}
	else if (encoderID == "TVQ" || encoderID == "tvq")
	{
		String	 bitrate    = "48";
		String	 candidates = "32";

		ScanForParameter("-b", &bitrate);
		ScanForParameter("-c", &candidates);

/*		currentConfig->tvq_presel_candidates = Math::Max(4, Math::Min(32, candidates.ToInt()));
		currentConfig->tvq_bitrate	     = Math::Max(24, Math::Min(48, bitrate.ToInt()));
*/
		currentConfig->encoderID = "twinvq-out";
	}
	else if (encoderID == "WAVE" || encoderID == "wave")
	{
		currentConfig->encoderID = "wave-out";
	}
	else
	{
		Console::OutputString(String("Encoder ").Append(encoderID).Append(" is not supported by BonkEnc!\n\n"));

		broken = true;
	}

	if (!broken)
	{
		currentConfig->enc_outdir = outdir;
		currentConfig->enc_filePattern = pattern;

		currentConfig->enable_auto_cddb = cddb;
		currentConfig->enable_cddb_cache = True;
		currentConfig->cdrip_locktray = False;
		currentConfig->cdrip_timeout = timeout.ToInt();

		currentConfig->encodeToSingleFile = False;
		currentConfig->writeToInputDir = False;

		if (currentConfig->enc_outdir[currentConfig->enc_outdir.Length() - 1] != '\\') currentConfig->enc_outdir.Append("\\");

		for (Int i = 0; i < files.Length(); i++)
		{
			InStream	*in = new InStream(STREAM_FILE, files.GetNth(i), IS_READONLY);
			String		 currentFile = files.GetNth(i);

			if (currentFile.StartsWith("/cda"))
			{
				currentFile = String("Audio CD ").Append(String::FromInt(currentConfig->cdrip_activedrive)).Append(" - Track ").Append(currentFile.Tail(currentFile.Length() - 4));
			}

			if (in->GetLastError() != IO_ERROR_OK && !files.GetNth(i).StartsWith("/cda"))
			{
				delete in;

				Console::OutputString(String("File not found: ").Append(files.GetNth(i)).Append("\n"));

				broken = true;

				continue;
			}
			else
			{
				delete in;
			}

/*			if ((files.GetNth(i).EndsWith(".mp3") && !currentConfig->enable_lame) || (files.GetNth(i).EndsWith(".ogg") && !currentConfig->enable_vorbis) || (files.GetNth(i).EndsWith(".cda") && !currentConfig->enable_cdrip))
			{
				Console::OutputString(String("Cannot process file: ").Append(currentFile).Append("\n"));

				broken = true;

				continue;
			}
*/
			joblist->AddTrackByFileName(files.GetNth(i), outfile);

			if (joblist->GetNOfTracks() > 0)
			{
				if (!quiet) Console::OutputString(String("Processing file: ").Append(currentFile).Append("..."));

				encoder->Encode(joblist, False);

				joblist->RemoveNthTrack(0);

				if (!quiet) Console::OutputString("done.\n");
			}
		}
	}

	delete joblist;
}

BonkEnc::BonkEncCommandline::~BonkEncCommandline()
{
}

Bool BonkEnc::BonkEncCommandline::ScanForParameter(const String &param, String *option)
{
	for (Int i = 0; i < args.Length(); i++)
	{
		if (args.GetNth(i) == param)
		{
			if (option != NULL) *option = args.GetNth(i + 1);

			return True;
		}
	}

	return False;
}

Void BonkEnc::BonkEncCommandline::ScanForFiles(Array<String> *files)
{
	String	 param;
	String	 prevParam;

	for (Int i = 0; i < args.Length(); i++)
	{
		prevParam	= param;
		param		= args.GetNth(i);

		if (param[0] != '-' && (prevParam[0] != '-' ||
					prevParam == "-quiet" ||
					prevParam == "-cddb" ||
					prevParam == "-js" ||
					prevParam == "-lossless" ||
					prevParam == "-mp4" ||
					prevParam == "-m" ||
					prevParam == "-extc" ||
					prevParam == "-extm ||")) (*files).Add(param);
	}
}

Bool BonkEnc::BonkEncCommandline::TracksToFiles(const String &tracks, Array<String> *files)
{
	if (tracks == "all")
	{
		ex_CR_SetActiveCDROM(currentConfig->cdrip_activedrive);

		ex_CR_ReadToc();

		Int	 numTocEntries = ex_CR_GetNumTocEntries();

		for (Int i = 1; i <= numTocEntries; i++) (*files).Add(String("/cda").Append(String::FromInt(i)));

		return True;
	}

	for (Int i = 0; i < tracks.Length(); i++)
	{
		if ((tracks[i] >= 'a' && tracks[i] <= 'z') ||
		    (tracks[i] >= 'A' && tracks[i] <= 'Z')) return False;
	}

	String	 rest = tracks;

	while (rest.Length() > 0)
	{
		String	 current;

		if (rest.Find(",") != -1)
		{
			Int	 comma = rest.Find(",");

			current = rest.Head(comma);
			rest = rest.Tail(rest.Length() - comma - 1);
		}
		else
		{
			current = rest;
			rest = NIL;
		}

		if (current.Find("-") != -1)
		{
			Int	 dash = current.Find("-");
			Int	 first = current.Head(dash).ToInt();
			Int	 last = current.Tail(current.Length() - dash - 1).ToInt();

			for (Int i = first; i <= last; i++) (*files).Add(String("/cda").Append(String::FromInt(i)));
		}
		else
		{
			(*files).Add(String("/cda").Append(current));
		}
	}

	return True;
}

Void BonkEnc::BonkEncCommandline::ShowHelp(const String &helpenc)
{
	if (helpenc == NIL)
	{
		Console::OutputString(String("BonkEnc Audio Encoder ").Append(BonkEnc::version).Append(" command line interface\nCopyright (C) 2001-2008 Robert Kausch\n\n"));
		Console::OutputString("Usage:\tBEcmd [options] [file(s)]\n\n");
		Console::OutputString("\t-e <encoder>\tSpecify the encoder to use (default is LAME)\n");
		Console::OutputString("\t-h <encoder>\tPrint help for encoder specific options\n\n");
		Console::OutputString("\t-d <outdir>\tSpecify output directory for encoded files\n");
		Console::OutputString("\t-o <outfile>\tSpecify output file name in single file mode\n");
		Console::OutputString("\t-p <pattern>\tSpecify output file name pattern\n\n");
		Console::OutputString("\t-cd <drive>\tSpecify active CD drive (0..n)\n");
		Console::OutputString("\t-track <track>\tSpecify input track(s) to rip (e.g. 1-5,7,9 or 'all')\n");
		Console::OutputString("\t-t <timeout>\tTimeout for CD track ripping (default is 120 seconds)\n");
		Console::OutputString("\t-cddb\t\tEnable CDDB database lookup\n\n");
		Console::OutputString("\t-quiet\t\tDo not print any messages\n\n");
		Console::OutputString("<encoder> can be one of LAME, VORBIS, BONK, BLADE, FAAC, FLAC, TVQ or WAVE.\n\n");
		Console::OutputString("Default for <pattern> is \"<artist> - <title>\".\n\n");
	}
	else
	{
		Console::OutputString(String("BonkEnc Audio Encoder ").Append(BonkEnc::version).Append(" command line interface\nCopyright (C) 2001-2008 Robert Kausch\n\n"));

		if (helpenc == "LAME" || helpenc == "lame")
		{
			Console::OutputString("Options for LAME MP3 encoder:\n\n");
			Console::OutputString("\t-m <mode>\t\t(CBR, VBR or ABR, default: VBR)\n");
			Console::OutputString("\t-b <CBR/ABR bitrate>\t(8 - 320, default: 192)\n");
			Console::OutputString("\t-q <VBR quality>\t(0 = best, 9 = worst, default: 5)\n\n");
		}
		else if (helpenc == "VORBIS" || helpenc == "vorbis")
		{
			Console::OutputString("Options for Ogg Vorbis encoder:\n\n");
			Console::OutputString("\t-q <quality>\t\t(0 - 100, default: 60, VBR mode)\n");
			Console::OutputString("\t-b <target bitrate>\t(45 - 500, default: 192, ABR mode)\n\n");
		}
		else if (helpenc == "BONK" || helpenc == "bonk")
		{
			Console::OutputString("Options for Bonk encoder:\n\n");
			Console::OutputString("\t-q <quantization factor>\t(0 - 2, default: 0.4)\n");
			Console::OutputString("\t-p <predictor size>\t\t(0 - 512, default: 32)\n");
			Console::OutputString("\t-r <downsampling ratio>\t\t(1 - 10, default: 2)\n");
			Console::OutputString("\t-js\t\t\t\t(use Joint Stereo)\n");
			Console::OutputString("\t-lossless\t\t\t(use lossless compression)\n\n");
		}
		else if (helpenc == "BLADE" || helpenc == "blade")
		{
			Console::OutputString("Options for BladeEnc encoder:\n\n");
			Console::OutputString("\t-b <bitrate>\t(32, 40, 48, 56, 64, 80, 96, 112, 128,\n");
			Console::OutputString("\t\t\t 160, 192, 224, 256 or 320, default: 192)\n\n");
		}
		else if (helpenc == "FAAC" || helpenc == "faac")
		{
			Console::OutputString("Options for FAAC AAC/MP4 encoder:\n\n");
			Console::OutputString("\t-q <quality>\t\t\t(10 - 500, default: 100, VBR mode)\n");
			Console::OutputString("\t-b <bitrate per channel>\t(8 - 256, default: 64, ABR mode)\n");
			Console::OutputString("\t-mp4\t\t\t\t(use MP4 container format)\n\n");
		}
		else if (helpenc == "FLAC" || helpenc == "flac")
		{
			Console::OutputString("Options for FLAC encoder:\n\n");
			Console::OutputString("\t-b <blocksize>\t\t\t(192 - 32768, default: 4608)\n");
			Console::OutputString("\t-m\t\t\t\t(use mid-side stereo)\n");
			Console::OutputString("\t-l <max LPC order>\t\t(0 - 32, default: 8)\n");
			Console::OutputString("\t-q <QLP coeff precision>\t(0 - 16, default: 0)\n");
			Console::OutputString("\t-extc\t\t\t\t(do exhaustive QLP coeff optimization)\n");
			Console::OutputString("\t-extm\t\t\t\t(do exhaustive model search)\n");
			Console::OutputString("\t-r <min Rice>,<max Rice>\t(0 - 16, default: 3,3)\n\n");
		}
		else if (helpenc == "TVQ" || helpenc == "tvq")
		{
			Console::OutputString("Options for TwinVQ encoder:\n\n");
			Console::OutputString("\t-b <bitrate per channel>\t(24, 32 or 48, default: 48)\n");
			Console::OutputString("\t-c <preselection candidates>\t(4, 8, 16 or 32, default: 32)\n\n");
		}
		else if (helpenc == "WAVE" || helpenc == "wave")
		{
			Console::OutputString("No options can be configured for the WAVE Out filter!\n\n");
		}
		else
		{
			Console::OutputString(String("Encoder ").Append(helpenc).Append(" is not supported by BonkEnc!\n\n"));
		}
	}
}