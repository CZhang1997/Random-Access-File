
//	Churong Zhang


#ifndef RA_FILE_H
#define RA_FILE_H

#include <fstream>
#include <string>
#include <array>
using namespace std;


typedef unsigned long UINT;

class RAFile
	{
	private:
		struct RecInfo
			{
			streamoff		Offset;
			UINT			Length;
			};
	public:
		enum	Exceptions	{OK, FileOpenFailure, FileAlreadyOpen, FileNotOpen, RecordDoesNotExist};
					RAFile		();
					~RAFile		();
		Exceptions	Close		();
		Exceptions	Get			(UINT, string &);
		Exceptions	Insert		(UINT, const string &);
		bool		IsOpen		() const;
		Exceptions	Open		(const string &);
		Exceptions	Replace		(UINT, const string &);
		void		GetSize();
	private:
					RAFile		(const RAFile &);
		RAFile &	operator =	(const RAFile &);
		Exceptions	AddRecord	(UINT, const string &);

		UINT							NumRecords;
		streamoff						EndOfDataRecords;
		array <RecInfo, UINT>	RecInfoArray;
		fstream							File;
	};

inline bool RAFile::IsOpen () const
	{
	return File.is_open ();
	}

#endif
