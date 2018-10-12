

//	Churong Zhang


#include <iostream>

using namespace std;

#include <stdlib.h>

#include <string>
#include "RAFile.h"

void main ()
	{
	string		FileName;
	string		Data;
	RAFile			DBase;
	char			command;
	UINT			index;
	cout << "Enter the Database name: ";
	cin >> FileName;
	
	if (DBase.Open (FileName) != RAFile::OK)
			cout << "Open Failed" << endl;
		else
			{
			//	do stuff for the lab
			do
			{
				cout << "Enter one of the following command, G(Get), I(Insert), R(Replace), O(Open), S(Size), C(Close File) and X(Exit) : ";
				cin >> command;
				switch (command)
				{
				case 'G':
				case 'g':
					cout << "What is the index of the data you want: ";
					cin >> index;
					switch (DBase.Get(index, Data))
					{
					case RAFile::Exceptions::OK:
						cout << Data << endl; break;
					case RAFile::Exceptions::RecordDoesNotExist:
						cout << "Record Does Not Exist." << endl; break;
					case RAFile::Exceptions::FileNotOpen:
						cout << "File Not Open." << endl; break;
					default:
						cout << "Error 505." << endl;
						break;
					}
					break;
				case 'I':
				case 'i':
					cout << "What is the index of the data you want to insert: ";
					cin >> index;

					cout << "What is the data you want to insert: ";
					cin >> Data;
					cin >> Data;
					switch (DBase.Insert(index, Data))
					{
					case RAFile::Exceptions::OK:
						cout <<"Inserted"<< endl; break;
					case RAFile::Exceptions::FileNotOpen:
						cout << "File Not Open." << endl; break;
					default:
						cout << "Error 506." << endl;
						break;
					}
					break;
				case 'R':
				case 'r':
					cout << "What is the index of the data you want to replace: ";
					cin >> index;
					
					cout << "What is the data you want to replace: ";
					cin >> Data;
					cin >> Data;
					switch (DBase.Replace(index, Data))
					{
					case RAFile::Exceptions::OK:
						cout << "Replaced" << endl; break;
					case RAFile::Exceptions::FileNotOpen:
						cout << "File Not Open." << endl; break;
					default:
						cout << "Error 507." << endl;
						break;
					}
					break;
				case 'O':
				case 'o':
					cout << "What is the file name you want to open: ";
					cin >> FileName;
					cin >> FileName;
					switch (DBase.Open(FileName))
					{
					case RAFile::Exceptions::OK:
						cout << FileName << " opened." << endl;
						break;
					case RAFile::Exceptions::FileAlreadyOpen:
						cout << "File Already Open" << endl;
						break;
					case RAFile::Exceptions::FileOpenFailure:
						cout << "File Open Failure." << endl; 
						break;
					default:
						cout << "Error 508." << endl;
						break;
					}
			
					break;
				case 'C':
				case 'c':
					switch (DBase.Close())
					{
					case RAFile::Exceptions::OK:
						cout << "File Closed." << endl; break;
					case RAFile::Exceptions::FileNotOpen:
						cout << "File Not Open." << endl; break;
					default:
						cout << "Error 507." << endl;
						break;
					}
					
					break;
				case 'X':
				case 'x':
					cout << "Thank you for using our Data Base." << endl;
					
					break;
				case 's':
				case 'S':
					DBase.GetSize();
					break;
				default:
					cout << "inVaild Command, plz try again." << endl;
				}
			} while (command != 'X' && command != 'x');
			
			DBase.Close ();
			}
	system ("pause");
	}
