 /* BonkEnc Audio Encoder
  * Copyright (C) 2001-2011 Robert Kausch <robert.kausch@bonkenc.org>
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the "GNU General Public License".
  *
  * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
  * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
  * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE. */

#include <config.h>
#include <bonkenc.h>

BonkEnc::Config *BonkEnc::Config::instance = NIL;

const String	 BonkEnc::Config::CategorySettingsID				= "Settings";
const String	 BonkEnc::Config::CategoryJoblistID				= "Joblist";
const String	 BonkEnc::Config::CategoryRipperID				= "Ripper";
const String	 BonkEnc::Config::CategoryPlaylistID				= "Playlist";
const String	 BonkEnc::Config::CategoryTagsID				= "Tags";
const String	 BonkEnc::Config::CategoryFreedbID				= "freedb";

/* Category Settings
 */
const String	 BonkEnc::Config::SettingsFirstStartID				= "FirstStart";
const Bool	 BonkEnc::Config::SettingsFirstStartDefault			= True;

const String	 BonkEnc::Config::SettingsWindowPosXID				= "WindowPosX";
const Int	 BonkEnc::Config::SettingsWindowPosXDefault			= 100;

const String	 BonkEnc::Config::SettingsWindowPosYID				= "WindowPosY";
const Int	 BonkEnc::Config::SettingsWindowPosYDefault			= 100;

const String	 BonkEnc::Config::SettingsWindowSizeXID				= "WindowSizeX";
const Int	 BonkEnc::Config::SettingsWindowSizeXDefault			= 800;

const String	 BonkEnc::Config::SettingsWindowSizeYID				= "WindowSizeY";
const Int	 BonkEnc::Config::SettingsWindowSizeYDefault			= 600;

const String	 BonkEnc::Config::SettingsWindowMaximizedID			= "WindowMaximized";
const Bool	 BonkEnc::Config::SettingsWindowMaximizedDefault		= False;

const String	 BonkEnc::Config::SettingsLanguageID				= "Language";
const String	 BonkEnc::Config::SettingsLanguageDefault			= NIL;

const String	 BonkEnc::Config::SettingsShowTitleInfoID			= "ShowTitleInfo";
const Bool	 BonkEnc::Config::SettingsShowTitleInfoDefault			= True;

const String	 BonkEnc::Config::SettingsShowTooltipsID			= "ShowTooltips";
const Bool	 BonkEnc::Config::SettingsShowTooltipsDefault			= True;

const String	 BonkEnc::Config::SettingsShowTipsID				= "ShowTips";
const Bool	 BonkEnc::Config::SettingsShowTipsDefault			= True;

const String	 BonkEnc::Config::SettingsNextTipID				= "NextTip";
const Int	 BonkEnc::Config::SettingsNextTipDefault			= 0;

const String	 BonkEnc::Config::SettingsDisplayErrorsID			= "DisplayErrors";
const Bool	 BonkEnc::Config::SettingsDisplayErrorsDefault			= True;

const String	 BonkEnc::Config::SettingsEncodingHeuristicsID			= "EnableEncodingHeuristics";
const Bool	 BonkEnc::Config::SettingsEncodingHeuristicsDefault		= True;

const String	 BonkEnc::Config::SettingsCheckForUpdatesID			= "CheckUpdatesAtStartup";
const Bool	 BonkEnc::Config::SettingsCheckForUpdatesDefault		= True;

const String	 BonkEnc::Config::SettingsLastUsedGenreID			= "LastUsedGenre";

const String	 BonkEnc::Config::SettingsLastFilePatternID			= "LastFilePattern";

const String	 BonkEnc::Config::SettingsLastAddedDirID			= "LastAddedDir";
const String	 BonkEnc::Config::SettingsLastAddedDirDefault			= NIL;

const String	 BonkEnc::Config::SettingsLastAddedPatternID			= "LastAddedPattern";
const String	 BonkEnc::Config::SettingsLastAddedPatternDefault		= NIL;

const String	 BonkEnc::Config::SettingsEncodeOnTheFlyID			= "EncodeOnTheFly";
const Bool	 BonkEnc::Config::SettingsEncodeOnTheFlyDefault			= True;

const String	 BonkEnc::Config::SettingsKeepWaveFilesID			= "KeepWaveFiles";
const Bool	 BonkEnc::Config::SettingsKeepWaveFilesDefault			= False;

const String	 BonkEnc::Config::SettingsEncodeToSingleFileID			= "EncodeToSingleFile";
const Bool	 BonkEnc::Config::SettingsEncodeToSingleFileDefault		= False;

const String	 BonkEnc::Config::SettingsWriteToInputDirectoryID		= "WriteToInputDirectory";
const Bool	 BonkEnc::Config::SettingsWriteToInputDirectoryDefault		= False;

const String	 BonkEnc::Config::SettingsAllowOverwriteSourceID		= "AllowOverwriteSource";
const Bool	 BonkEnc::Config::SettingsAllowOverwriteSourceDefault		= False;

const String	 BonkEnc::Config::SettingsFilenamesAllowUnicodeID		= "UseUnicodeFilenames";
const Bool	 BonkEnc::Config::SettingsFilenamesAllowUnicodeDefault		= True;

const String	 BonkEnc::Config::SettingsFilenamesReplaceSpacesID		= "FilenamesReplaceSpaces";
const Bool	 BonkEnc::Config::SettingsFilenamesReplaceSpacesDefault		= False;

const String	 BonkEnc::Config::SettingsEncoderID				= "Encoder";
const String	 BonkEnc::Config::SettingsEncoderDefault			= "lame-out";

const String	 BonkEnc::Config::SettingsEncoderOutputDirectoryID		= "EncoderOutDir";
      String	 BonkEnc::Config::SettingsEncoderOutputDirectoryDefault		= NIL;

const String	 BonkEnc::Config::SettingsEncoderFilenamePatternID		= "EncoderFilenamePattern";
const String	 BonkEnc::Config::SettingsEncoderFilenamePatternDefault		= String("<artist> - <album>").Append(Directory::GetDirectoryDelimiter()).Append("<artist> - <album> - <track> - <title>");

const String	 BonkEnc::Config::SettingsLastCustomCharsetID			= "LastCustomCharset";
const String	 BonkEnc::Config::SettingsLastCustomCharsetDefault		= NIL;

/* Category Joblist
 */
const String	 BonkEnc::Config::JoblistFieldsID				= "Fields";
const String	 BonkEnc::Config::JoblistFieldsDefault				= "<artist>,<title>,<track>,<time>,<bytes>";

const String	 BonkEnc::Config::JoblistFieldSizesID				= "FieldSizes";
const String	 BonkEnc::Config::JoblistFieldSizesDefault			= "120,*,50,80,80";

/* Category Ripper
 */
const String	 BonkEnc::Config::RipperActiveDriveID				= "ActiveDrive";
const Int	 BonkEnc::Config::RipperActiveDriveDefault			= 0;

const String	 BonkEnc::Config::RipperEjectAfterRippingID			= "EjectAfterRipping";
const Bool	 BonkEnc::Config::RipperEjectAfterRippingDefault		= False;

const String	 BonkEnc::Config::RipperAutoReadContentsID			= "AutoReadContents";
const Bool	 BonkEnc::Config::RipperAutoReadContentsDefault			= True;

const String	 BonkEnc::Config::RipperAutoRipID				= "AutoRip";
const Bool	 BonkEnc::Config::RipperAutoRipDefault				= False;

const String	 BonkEnc::Config::RipperTimeoutID				= "Timeout";
const Int	 BonkEnc::Config::RipperTimeoutDefault				= 0;

/* Category Playlist
 */
const String	 BonkEnc::Config::PlaylistCreatePlaylistID			= "CreatePlaylist";
const Bool	 BonkEnc::Config::PlaylistCreatePlaylistDefault			= False;

const String	 BonkEnc::Config::PlaylistCreateCueSheetID			= "CreateCueSheet";
const Bool	 BonkEnc::Config::PlaylistCreateCueSheetDefault			= False;

const String	 BonkEnc::Config::PlaylistUseEncoderOutputDirID			= "UseEncoderOutputDir";
const Bool	 BonkEnc::Config::PlaylistUseEncoderOutputDirDefault		= True;

const String	 BonkEnc::Config::PlaylistOutputDirID				= "OutputDir";

const String	 BonkEnc::Config::PlaylistFilenamePatternID			= "FilenamePattern";
const String	 BonkEnc::Config::PlaylistFilenamePatternDefault		= String("<artist> - <album>").Append(Directory::GetDirectoryDelimiter()).Append("<artist> - <album>");

/* Category Tags
 */
const String	 BonkEnc::Config::TagsCoverArtReadFromTagsID			= "CoverArtReadFromTags";
const Bool	 BonkEnc::Config::TagsCoverArtReadFromTagsDefault		= True;

const String	 BonkEnc::Config::TagsCoverArtReadFromFilesID			= "CoverArtReadFromFiles";
const Bool	 BonkEnc::Config::TagsCoverArtReadFromFilesDefault		= True;

const String	 BonkEnc::Config::TagsCoverArtWriteToTagsID			= "CoverArtWriteToTags";
const Bool	 BonkEnc::Config::TagsCoverArtWriteToTagsDefault		= True;

const String	 BonkEnc::Config::TagsCoverArtWriteToFilesID			= "CoverArtWriteToFiles";
const Bool	 BonkEnc::Config::TagsCoverArtWriteToFilesDefault		= False;

const String	 BonkEnc::Config::TagsCoverArtWriteToFilesWithReferenceID	= "CoverArtWriteToFilesWithReference";
const Bool	 BonkEnc::Config::TagsCoverArtWriteToFilesWithReferenceDefault	= False;

const String	 BonkEnc::Config::TagsCoverArtFilenamePatternID			= "CoverArtFilenamePattern";
const String	 BonkEnc::Config::TagsCoverArtFilenamePatternDefault		= String("<artist> - <album>").Append(Directory::GetDirectoryDelimiter()).Append("<type>");

const String	 BonkEnc::Config::TagsReadChaptersID				= "ReadChapters";
const Bool	 BonkEnc::Config::TagsReadChaptersDefault			= True;

const String	 BonkEnc::Config::TagsWriteChaptersID				= "WriteChapters";
const Bool	 BonkEnc::Config::TagsWriteChaptersDefault			= True;

const String	 BonkEnc::Config::TagsWriteChaptersTypeID			= "WriteChaptersType";
const Int	 BonkEnc::Config::TagsWriteChaptersTypeDefault			= 1;

const String	 BonkEnc::Config::TagsWriteMCDIID				= "WriteMCDI";
const Bool	 BonkEnc::Config::TagsWriteMCDIDefault				= True;

const String	 BonkEnc::Config::TagsPreserveReplayGainID			= "PreserveReplayGain";
const Bool	 BonkEnc::Config::TagsPreserveReplayGainDefault			= True;

const String	 BonkEnc::Config::TagsReplaceExistingCommentsID			= "ReplaceExistingComments";
const Bool	 BonkEnc::Config::TagsReplaceExistingCommentsDefault		= False;

const String	 BonkEnc::Config::TagsDefaultCommentID				= "DefaultComment";

/* Category freedb
 */
const String	 BonkEnc::Config::FreedbDirectoryID				= "Directory";
const String	 BonkEnc::Config::FreedbDirectoryDefault			= String("freedb").Append(Directory::GetDirectoryDelimiter());

const String	 BonkEnc::Config::FreedbServerID				= "Server";
const String	 BonkEnc::Config::FreedbServerDefault				= "freedb.freedb.org";

const String	 BonkEnc::Config::FreedbModeID					= "Mode";
const Int	 BonkEnc::Config::FreedbModeDefault				= 0;

const String	 BonkEnc::Config::FreedbHTTPPortID				= "HTTPPort";
const Int	 BonkEnc::Config::FreedbHTTPPortDefault				= 80;

const String	 BonkEnc::Config::FreedbCDDBPPortID				= "CDDBPPort";
const Int	 BonkEnc::Config::FreedbCDDBPPortDefault			= 8880;

const String	 BonkEnc::Config::FreedbQueryPathID				= "QueryPath";
const String	 BonkEnc::Config::FreedbQueryPathDefault			= "/~cddb/cddb.cgi";

const String	 BonkEnc::Config::FreedbSubmitPathID				= "SubmitPath";
const String	 BonkEnc::Config::FreedbSubmitPathDefault			= "/~cddb/submit.cgi";

const String	 BonkEnc::Config::FreedbEmailID					= "eMail";
const String	 BonkEnc::Config::FreedbEmailDefault				= "cddb@freac.org";

const String	 BonkEnc::Config::FreedbProxyID					= "Proxy";
const String	 BonkEnc::Config::FreedbProxyDefault				= "localhost";

const String	 BonkEnc::Config::FreedbProxyUserID				= "ProxyUserName";
const String	 BonkEnc::Config::FreedbProxyUserDefault			= NIL;

const String	 BonkEnc::Config::FreedbProxyPasswordID				= "ProxyPassword";
const String	 BonkEnc::Config::FreedbProxyPasswordDefault			= NIL;

const String	 BonkEnc::Config::FreedbProxyModeID				= "ProxyMode";
const Int	 BonkEnc::Config::FreedbProxyModeDefault			= 0;

const String	 BonkEnc::Config::FreedbProxyPortID				= "ProxyPort";
const Int	 BonkEnc::Config::FreedbProxyPortDefault			= 1080;

const String	 BonkEnc::Config::FreedbEnableLocalID				= "EnableLocalCDDB";
const Bool	 BonkEnc::Config::FreedbEnableLocalDefault			= False;

const String	 BonkEnc::Config::FreedbEnableRemoteID				= "EnableRemoteCDDB";
const Bool	 BonkEnc::Config::FreedbEnableRemoteDefault			= True;

const String	 BonkEnc::Config::FreedbAutoQueryID				= "AutoCDDBQueries";
const Bool	 BonkEnc::Config::FreedbAutoQueryDefault			= True;

const String	 BonkEnc::Config::FreedbEnableCacheID				= "EnableCDDBCache";
const Bool	 BonkEnc::Config::FreedbEnableCacheDefault			= True;

const String	 BonkEnc::Config::FreedbOverwriteCDTextID			= "OverwriteCDText";
const Bool	 BonkEnc::Config::FreedbOverwriteCDTextDefault			= True;

const String	 BonkEnc::Config::FreedbUpdateJoblistID				= "UpdateJoblistOnSubmit";
const Bool	 BonkEnc::Config::FreedbUpdateJoblistDefault			= True;

BonkEnc::Config::Config()
{
	deleteAfterEncoding	= False;
	shutdownAfterEncoding	= False;

	maxActiveJobs		= 2;

	Config::SettingsEncoderOutputDirectoryDefault = S::System::System::GetPersonalFilesDirectory(S::System::PersonalFilesMusic);

	BoCA::Config	*config = BoCA::Config::Get();

	String	 encoderOutputDir  = config->GetStringValue(CategorySettingsID, SettingsEncoderOutputDirectoryID, SettingsEncoderOutputDirectoryDefault);
	String	 playlistOutputDir = config->GetStringValue(CategoryPlaylistID, PlaylistOutputDirID, encoderOutputDir);
	String	 freedbDir	   = config->GetStringValue(CategoryFreedbID, FreedbDirectoryID, FreedbDirectoryDefault);

	if (!encoderOutputDir.EndsWith(Directory::GetDirectoryDelimiter()))  config->SetStringValue(CategorySettingsID, SettingsEncoderOutputDirectoryID, encoderOutputDir.Append(Directory::GetDirectoryDelimiter()));
	if (!playlistOutputDir.EndsWith(Directory::GetDirectoryDelimiter())) config->SetStringValue(CategoryPlaylistID, PlaylistOutputDirID, playlistOutputDir.Append(Directory::GetDirectoryDelimiter()));
	if (!freedbDir.EndsWith(Directory::GetDirectoryDelimiter()))	     config->SetStringValue(CategoryFreedbID, FreedbDirectoryID, freedbDir.Append(Directory::GetDirectoryDelimiter()));
}

BonkEnc::Config::~Config()
{
}

BonkEnc::Config *BonkEnc::Config::Get()
{
	if (instance == NIL)
	{
		instance = new Config();
	}

	return instance;
}

Void BonkEnc::Config::Free()
{
	if (instance != NIL)
	{
		delete instance;

		instance = NIL;
	}
}

Bool BonkEnc::Config::CanChangeConfig()
{
// ToDo: Reactivate this check.
/*	if (BonkEnc::Get()->encoder->IsEncoding())
	{
		Utilities::ErrorMessage("Cannot change settings while encoding!");

		return False;
	}
*/
	return True;
}
