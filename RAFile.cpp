

//	Churong Zhang

#include<iostream>

using namespace std;

#include "RAFile.h"

RAFile::RAFile (): NumRecords (0)
	{
	}

RAFile::~RAFile ()
	{
	//	write RecInfoArray following the Records in the file
	Close ();

	}

RAFile::Exceptions RAFile::AddRecord (UINT Index, const string & Data)
	{
	File.seekp (EndOfDataRecords);
	RecInfoArray [Index].Offset	= EndOfDataRecords;
	RecInfoArray [Index].Length	= Data.length();
	File.write (Data.c_str, Data.length());
	EndOfDataRecords			= File.tellp ();
	return OK;
	}

RAFile::Exceptions RAFile::Close ()
	{
	if (!File.is_open())
		return FileNotOpen;
	else
		{
		File.seekp(0);
		File.write((const char *)&NumRecords, sizeof(NumRecords));
		File.seekp(EndOfDataRecords);
		for (UINT i = 0; i < NumRecords; i++)
			File.write((char *)&RecInfoArray[i], sizeof(RecInfo));
		}
	cout << "Data base is close." << endl;
	File.close();
	return OK;
	//	do normal checking to make sure file is open
	//	write NumRecords back to file
	//	goto EndOfDataRecords and write RecInfoArray back to file starting at that point
	//	close the file
	}
	void RAFile::GetSize()
	{
	cout << "The size is " << NumRecords << endl;
	}
RAFile::Exceptions RAFile::Get (UINT Index, string & Data)
	{
	if (File.is_open ())
			if (Index < NumRecords)
					{
					if (RecInfoArray [Index].Length > 0)
							{
							char *	pChar;

							pChar = new char [RecInfoArray [Index].Length + 1];	// the data in each record does not include the end-of-string mark, only the acutal characters
							File.seekg (RecInfoArray [Index].Offset);
							File.read (pChar, RecInfoArray [Index].Length);
							pChar [RecInfoArray [Index].Length] = '\0';		// add end-of-string mark to the end of the characters
							Data = pChar;
							delete [] pChar;
							}
						else
							Data = "";
					return OK;
					}
				else
					return RecordDoesNotExist;
		else
			return FileNotOpen;
	}

RAFile::Exceptions RAFile::Insert (UINT Index, const string & Data)
	{
	UINT		i;
	if (!File.is_open())
		return FileNotOpen;
	else
	{
		if (Index >= NumRecords)
		{
			Replace(Index, Data);
		}
		else
		{
			for (i = NumRecords - 1; i >= Index; i--)
			{
				RecInfoArray[i + 1] = RecInfoArray[i];
				if (i == 0)
					break;
			}
			RecInfoArray[Index].Offset = EndOfDataRecords;
			RecInfoArray[Index].Length = Data.length();
			File.seekp(EndOfDataRecords);
			File.write(Data.c_str(), Data.length());
			EndOfDataRecords = File.tellp();
			NumRecords++;
		}

		return OK;
	}
	//	do normal checking about file open, etc
	//	if user wants to insert a new index past NumRecords
	//			call Replace
	//		else
	//			generally, we are going to write a loop where
		/*		for (i = NumRecords - 1; i >= Index; i--)
					RecInfoArray [i + 1] = RecInfoArray [i];*/
	//			write the Data to the file
	//			put the offset and length of the data just written into RecInfoArray [Index]
	//			make sure to update NumRecords
	}

RAFile::Exceptions RAFile::Open (const string & FileName)
	{
	if (File.is_open ())
			return FileAlreadyOpen;
		else
			{
			File.open (FileName.c_str(), ios_base::in | ios_base::out | ios_base::binary);
			if (!File.is_open ())	// did the open fail?
					{					// yes
					File.clear ();		// clear error flags
					File.open (FileName.c_str(), ios_base::out | ios_base::binary);	// this will cause the file to be created
					if (!File.is_open ())	//  did the open fail?
							{
							File.clear ();
							return FileOpenFailure;		// yes, return error code
							}
						else
							{
							NumRecords	= 0;
							File.write ((const char *) &NumRecords, sizeof (NumRecords));
							File.close ();
							File.open (FileName.c_str(), ios_base::in | ios_base::out | ios_base::binary);
							if (!File.is_open ())
									{
									File.clear ();
									return FileOpenFailure;
									}
								else;
							}
					}
				else;
			}
	File.seekg (0);		// make sure we are at the beginning of the file
	File.read ((char *) &NumRecords, sizeof (NumRecords));
	if (NumRecords > 0)
			{
			File.seekg (-((long) (NumRecords * sizeof (RecInfo))), ios_base::end);
			EndOfDataRecords	= File.tellg ();
			for (UINT i = 0; i < NumRecords; i++)
				File.read ((char *) &RecInfoArray [i], sizeof (RecInfo));
			}
		else
			EndOfDataRecords	= File.tellg ();
	return OK;
	}

RAFile::Exceptions RAFile::Replace (UINT Index, const string & Data)
	{
	UINT	i;

	if (File.is_open ())
			if (Index >= NumRecords)
					{		// need to add empty records to the data base to fill it out to the needed size
					for (i = NumRecords; i < Index; i++)
						{
						RecInfoArray [i].Offset	= 0;
						RecInfoArray [i].Length	= 0;
						}
					NumRecords	= Index + 1;
					return AddRecord (Index, Data);
					}
				else
					{		// replace a record
					if (Data.length () > RecInfoArray [Index].Length)	// is there enough space where the record is now
							return AddRecord (Index, Data);	// no, need to add it somewhere else
						else
							{	// yes, just overwrite the record
							File.seekp (RecInfoArray [Index].Offset);
							File.write (Data.c_str(), Data.length ());
							RecInfoArray [Index].Length	= Data.length ();
							return OK;
							}
					}
		else
			return FileNotOpen;
	}
