#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <locale.h>
#include <sstream>
#include <tchar.h>

using namespace std;

int GetMyLogicalDrives();
int RequestName(char* Name);
int GetMyDriveType(char* Name);
void GetMyVolumeInformation(char* Name);
int GetMyDriveFreeSpace(char* Name);
void CreateMyFile();
int CopyMyFile();
int MoveMyFile();
bool FileExists(LPCSTR fname);
void ChaneFileAttributes();
void ChangeCreationTime();
int GetFileInformation();
int GetFileInformation();
void changeFileAttributes();
void changeCreationTime();

int main()
{

    char drive[4] = { ' ', ':', '\\', '\0' };
    int choice;
    string directory;
    int ch;

    do
    {


        cout << endl
            << " 1 - Drives.\n"
            << " 2 - Information about drives.\n"
            << " 3 - Create/delete catalog.\n"
            << " 4 - Create file in new catalog.\n"
            << " 5 - Copy/move between catalogs.\n"
            << " 6 - Analysis and attributes change of files.\n"
            << " 7 - Exit.\n"
            << " Enter your choice and press return: ";
        cin >> choice;

        switch (choice)
        {
        case 1:

            GetMyLogicalDrives();
            break;

        case 2:
            // Запрашиваем диск
            RequestName(drive);
            // Смотрим тип диска
            GetMyDriveType(drive);
            // Получаем информацию о диске
            GetMyVolumeInformation(drive);
            // Получаем занятое и свободное место диска.
            GetMyDriveFreeSpace(drive);
            break;
        case 3:
            int ch1;
            cout << "Enter the path where the directory should be stored: ";
            cin >> directory;
            cout << "1. Create" << endl << "2. Delete" << endl;
            cin >> ch1;
            switch (ch1) {
            case 1:
                if (CreateDirectoryA(directory.c_str(), NULL))
                    cout << "Directory created" << endl;
                else
                    cout << "Error creating directory." << endl;
                break;
            case 2:
                if (RemoveDirectoryA(directory.c_str()))
                    cout << "Directory removed." << endl;
                else
                    cout << "Error removing directory." << endl;
                break;
            default:
                cout << "Not a Valid Choice. \n"
                    << "Choose again.\n";
                break;
                system("pause");
                return 0;
            }
            break;
        case 4:
            CreateMyFile();
            break;
        case 5:
            cout << "1 - Copy file.\n";
            cout << "2 - Move file.\n";
            cin >> ch;
            if(ch == 1) CopyMyFile();
            if(ch == 2) MoveMyFile();
            break;
        case 6:
            cout << "Analysis and attributes change of files.\n";
            cout << "1 - Get file information, 2 - change file attributes, 3 - change creation time.";
            cin >> ch;
            switch (ch) {
                case 1:
                    GetFileInformation();
                    break;
                case 2:
                    changeFileAttributes();
                    break;
                case 3: 
                    changeCreationTime();
                    break;
            }
            break;
        case 7:
            cout << "End of program.\n";
            break;
            break;
        default:
            cout << "Not a Valid Choice. \n"
                << "Choose again.\n";
            break;
        }

    } while (choice != 7);
    return 0;
}

int GetMyLogicalDrives() {
    // Инициализируем массив
    char myDrives[] = "A";

    // Получаем битовую маску
    DWORD myDrivesBit = GetLogicalDrives();

    // Проверяем возвращаемое значение
    if (myDrivesBit == 0) {
        cout << "GetLogicalDrives() failed." << endl;
    }
    else {
        cout << "This computer's logical drives:" << endl;
        while (myDrivesBit) {
            if (myDrivesBit & 1) {
                cout << "drive " << string(myDrives) << endl;
            }
            myDrives[0]++;
            myDrivesBit >>= 1;
        }
    }
    system("pause");
    return 0;
}

int RequestName(char* Name) {
    cout << "Please enter Drive's name: ";
    cin >> Name[0];
    cout << endl;
    //Проверка на корректность ввода
    while (Name[0] < 'A' || Name[0] > 'Z') {
        cout << "Incorrect Drive's name. (Capital A-Z Letters) Please enter another Drive Name: ";
        cin >> Name[0];
        Name[0] = char(Name[0]);
        cout << endl;
    }
    return 0;
}

int GetMyDriveType(char* Name) {
    UINT Type;
    Type = GetDriveTypeA(Name);

    switch (Type) {
    case 0: cout << "Type could not be defined." << endl;
        break;
    case 1: cout << "Root directory does not exist." << endl;
        break;
    case DRIVE_REMOVABLE: cout << "Removable Drive." << endl;
        break;
    case DRIVE_FIXED: cout << "Fixed Drive." << endl;
        break;
    case DRIVE_REMOTE: cout << "Network Drive (Remote)." << endl;
        break;
    case DRIVE_CDROM: cout << "CD-ROM." << endl;
        break;
    case DRIVE_RAMDISK: cout << "Virtual RAM DISK." << endl;
        break;
    }
    system("pause");
    return 0;
}

void GetMyVolumeInformation(char* Name) {

    WCHAR newName[MAX_PATH + 1];
    size_t char_conv;
    mbstowcs_s(&char_conv, newName, Name, MAX_PATH + 1);

    TCHAR VolumeNameBuffer[MAX_PATH + 1];
    DWORD VolumeSerialNumber = 0;
    DWORD MaximumComponentLength = 0;
    DWORD FileSystemFlags = 0; //TODO распарсить.
    TCHAR FileSystemNameBuffer[MAX_PATH + 1];

    BOOL b = GetVolumeInformation(newName, VolumeNameBuffer, MAX_PATH + 1, &VolumeSerialNumber, &MaximumComponentLength,
        &FileSystemFlags, FileSystemNameBuffer, MAX_PATH + 1);

    if (b) {
        cout << "Volume serial number: " << VolumeSerialNumber << endl;
        cout << "Volume name:  " << VolumeNameBuffer << endl;
        cout << "FyleSystem: " << FileSystemNameBuffer << endl;
        cout << "File system flags: " << FileSystemFlags << endl;
        if (FileSystemFlags & FILE_CASE_SENSITIVE_SEARCH) {
            cout << "FILE_CASE_SENSITIVE_SEARCH" << endl;
        }
        if (FileSystemFlags & FILE_CASE_PRESERVED_NAMES) {
            cout << "FILE_CASE_PRESERVED_NAMES" << endl;
        }
        if (FileSystemFlags & FILE_UNICODE_ON_DISK) {
            cout << "FILE_UNICODE_ON_DISK" << endl;
        }
        if (FileSystemFlags & FILE_PERSISTENT_ACLS) {
            cout << "FILE_PERSISTENT_ACLS" << endl;
        }
        if (FileSystemFlags & FILE_FILE_COMPRESSION) {
            cout << "FILE_FILE_COMPRESSION" << endl;
        }
        if (FileSystemFlags & FILE_VOLUME_QUOTAS) {
            cout << "FILE_VOLUME_QUOTAS" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_SPARSE_FILES) {
            cout << "FILE_SUPPORTS_SPARSE_FILES" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_REPARSE_POINTS) {
            cout << "FILE_SUPPORTS_REPARSE_POINTS" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_REMOTE_STORAGE) {
            cout << "FILE_SUPPORTS_REMOTE_STORAGE" << endl;
        }
        if (FileSystemFlags & FILE_RETURNS_CLEANUP_RESULT_INFO) {
            cout << "FILE_RETURNS_CLEANUP_RESULT_INFO" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_POSIX_UNLINK_RENAME) {
            cout << "FILE_SUPPORTS_POSIX_UNLINK_RENAME" << endl;
        }
        if (FileSystemFlags & FILE_VOLUME_IS_COMPRESSED) {
            cout << "FILE_VOLUME_IS_COMPRESSED" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_OBJECT_IDS) {
            cout << "FILE_SUPPORTS_OBJECT_IDS" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_ENCRYPTION) {
            cout << "FILE_SUPPORTS_ENCRYPTION" << endl;
        }
        if (FileSystemFlags & FILE_NAMED_STREAMS) {
            cout << "FILE_NAMED_STREAMS" << endl;
        }
        if (FileSystemFlags & FILE_READ_ONLY_VOLUME) {
            cout << "FILE_READ_ONLY_VOLUME" << endl;
        }
        if (FileSystemFlags & FILE_SEQUENTIAL_WRITE_ONCE) {
            cout << "FILE_SEQUENTIAL_WRITE_ONCE" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_TRANSACTIONS) {
            cout << "FILE_SUPPORTS_TRANSACTIONS" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_HARD_LINKS) {
            cout << "FILE_SUPPORTS_HARD_LINKS" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_EXTENDED_ATTRIBUTES) {
            cout << "FILE_SUPPORTS_EXTENDED_ATTRIBUTES" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_OPEN_BY_FILE_ID) {
            cout << "FILE_SUPPORTS_OPEN_BY_FILE_ID" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_USN_JOURNAL) {
            cout << "FILE_SUPPORTS_USN_JOURNAL" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_INTEGRITY_STREAMS) {
            cout << "FILE_SUPPORTS_INTEGRITY_STREAMS" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_BLOCK_REFCOUNTING) {
            cout << "FILE_SUPPORTS_BLOCK_REFCOUNTING" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_SPARSE_VDL) {
            cout << "FILE_SUPPORTS_SPARSE_VDL" << endl;
        }
        if (FileSystemFlags & FILE_DAX_VOLUME) {
            cout << "FILE_DAX_VOLUME" << endl;
        }
        if (FileSystemFlags & FILE_SUPPORTS_GHOSTING) {
            cout << "FILE_SUPPORTS_GHOSTING" << endl;
        }
        cout << "Maximum component length: " << MaximumComponentLength << endl;
    }
    else
    {
        cout << "Error getting information" << endl;
    }
    system("pause");
}

int GetMyDriveFreeSpace(char* Name) {
    DWORD SectorPerCluster, BytesPerSector, NumberOfFreeClusters, TotalNumberOfClusters;

    GetDiskFreeSpaceA(Name, &SectorPerCluster, &BytesPerSector, &NumberOfFreeClusters, &TotalNumberOfClusters);
    cout << Name[0] << endl;
    cout << SectorPerCluster << " - sectors per cluster." << endl;
    cout << BytesPerSector << " - bytes per sector." << endl;
    cout << NumberOfFreeClusters << " - number of free clusters." << endl;
    cout << TotalNumberOfClusters << " - total number of clusters." << endl;
    cout << "Free space: " << SectorPerCluster * BytesPerSector * NumberOfFreeClusters << " bytes." << endl;
    cout << "Total space: " << SectorPerCluster * BytesPerSector * TotalNumberOfClusters << " bytes." << endl;
    system("pause");
    return 0;
}

void CreateMyFile() {
    string Name;
    cout << "Enter the name: ";
    cin >> Name;
    HANDLE hFile = CreateFileA(Name.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        cout << "File has been created\n";
    }
    else {
        cout << "Error creating file. (CODE ERROR: " << GetLastError() << ") \n";
    }
    CloseHandle(hFile);
    system("pause");
}

int CopyMyFile() {
    string Name1;
    string Name2;
    int ans;
    cout << "Enter the full path and file name: ";
    cin >> Name1;
    cout << "Enter the new path and file name: ";
    cin >> Name2;

    if (FileExists(Name2.c_str())) {
        cout << "File already exists. Rewrite it? 1 - yes, 2 - no." << endl;
        cin >> ans;
        if (ans) {
            int a = CopyFileA(Name1.c_str(), Name2.c_str(), false);
            if (a) {
                cout << "File has been copied successfully." << endl;
            }
            else {
                cout << "Error copying file." << endl;
            }
            system("pause");
            return a;
        }
        return 0;
    }
    else {
        int a = CopyFileA(Name1.c_str(), Name2.c_str(), true);
        if (a) {
            cout << "File has been copied successfully." << endl;
        }
        else {
            cout << "Error copying file." << endl;
        }
        system("pause");
        return a;
    }
}

int MoveMyFile() {
    string Name1;
    string Name2;
    int ans;
    cout << "Enter the full path and file name: ";
    cin >> Name1;
    cout << "Enter the new path and file name: ";
    cin >> Name2;

    if (FileExists(Name2.c_str())) {
        cout << "File already exists. Rewrite it? 1 - yes, 2 - no." << endl;
        cin >> ans;
        if (ans) {
            int a = MoveFileExA(Name1.c_str(), Name2.c_str(), MOVEFILE_REPLACE_EXISTING);

            if (a) {
                cout << "File has been moved successfully." << endl;
            }
            else {
                cout << "Error moving file." << endl;
            }
            system("pause");
            return a;
        }
        return 0;
    }
    else {
        int a = MoveFileExA(Name1.c_str(), Name2.c_str(), MOVEFILE_COPY_ALLOWED);
        if (a) {
            cout << "File has been moved successfully." << endl;
        }
        else {
            cout << "Error moving file" << endl;
        }
        system("pause");
        return a;
    }
}

bool FileExists(LPCSTR fname) {
    return::GetFileAttributesA(fname) != INVALID_FILE_ATTRIBUTES;
}

int GetFileInformation() {
    wchar_t fileName[250];
    char charFileName[250];
    cout << "Enter file name: ";
    cin >> charFileName;
    mbtowc(fileName, charFileName, 250);
    ostringstream tempStringStream;

    DWORD fileAttributes;
    fileAttributes = GetFileAttributes(fileName);
    tempStringStream << "0x";
    tempStringStream << hex << fileAttributes << endl;
    cout << "File attributes: " << tempStringStream.str() << endl;
    if (fileAttributes & FILE_ATTRIBUTE_ARCHIVE)
        cout << "FILE_ATTRIBUTE_ARCHIVE:\nA file or directory that is an archive file or directory. Applications typically use this attribute to mark files for backup or removal.\n--\n";
    if (fileAttributes & FILE_ATTRIBUTE_COMPRESSED)
        cout << "FILE_ATTRIBUTE_COMPRESSED:\nA file or directory that is compressed. For a file, all of the data in the file is compressed. For a directory, compression is the default for newly created files and subdirectories.\n--\n";
    if (fileAttributes & FILE_ATTRIBUTE_DEVICE)
        cout << "FILE_ATTRIBUTE_DEVICE:\nThis value is reserved for system use.\n--\n";
    if (fileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        cout << "FILE_ATTRIBUTE_DIRECTORY:\nThe handle that identifies a directory.\n--\n";
    if (fileAttributes & FILE_ATTRIBUTE_ENCRYPTED)
        cout << "FILE_ATTRIBUTE_ENCRYPTED:\nA file or directory that is encrypted. For a file, all data streams in the file are encrypted. For a directory, encryption is the default for newly created files and subdirectories.\n--\n";
    if (fileAttributes & FILE_ATTRIBUTE_HIDDEN)
        cout << "FILE_ATTRIBUTE_HIDDEN:\nThe file or directory is hidden. It is not included in an ordinary directory listing.\n--\n";
    if (fileAttributes & FILE_ATTRIBUTE_INTEGRITY_STREAM)
        cout << "FILE_ATTRIBUTE_INTEGRITY_STREAM:\nThe directory or user data stream is configured with integrity (only supported on ReFS volumes). It is not included in an ordinary directory listing. The integrity setting persists \
			 with the file if it's renamed. If a file is copied the destination file will have integrity set if either the source file or destination directory have integrity set.\n--\n";
    if (fileAttributes & FILE_ATTRIBUTE_NORMAL)
        cout << "FILE_ATTRIBUTE_NORMAL:\nA file that does not have other attributes set. This attribute is valid only when used alone.\n";
    if (fileAttributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)
        cout << "FILE_ATTRIBUTE_NOT_CONTENT_INDEXED:\nThe file or directory is not to be indexed by the content indexing service.\n";
    if (fileAttributes & FILE_ATTRIBUTE_NO_SCRUB_DATA)
        cout << "FILE_ATTRIBUTE_NO_SCRUB_DATA:\nThe user data stream not to be read by the background data integrity scanner (AKA scrubber). When set on a directory it only provides inheritance. This flag is only supported on\
				Storage Spaces and ReFS volumes. It is not included in an ordinary directory listing.\n--\n";
    if (fileAttributes & FILE_ATTRIBUTE_OFFLINE)
        cout << "FILE_ATTRIBUTE_OFFLINE:\nThe data of a file is not available immediately. This attribute indicates that the file data is physically moved to offline storage. This attribute is used by Remote Storage,\
				 which is the hierarchical storage management software. Applications should not arbitrarily change this attribute.\n--\n";
    if (fileAttributes & FILE_ATTRIBUTE_READONLY)
        cout << "FILE_ATTRIBUTE_READONLY:\nA file that is read-only. Applications can read the file, but cannot write to it or delete it. This attribute is not honored on directories.\n--\n";
    if (fileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
        cout << "FILE_ATTRIBUTE_REPARSE_POINT:\nA file or directory that has an associated reparse point, or a file that is a symbolic link.\n--\n";
    if (fileAttributes & FILE_ATTRIBUTE_SPARSE_FILE)
        cout << "FILE_ATTRIBUTE_SPARSE_FILE:\nA file that is a sparse file.\n--\n";
    if (fileAttributes & FILE_ATTRIBUTE_SYSTEM)
        cout << "FILE_ATTRIBUTE_SYSTEM:\nA file or directory that the operating system uses a part of, or uses exclusively.\n--\n";
    if (fileAttributes & FILE_ATTRIBUTE_TEMPORARY)
        cout << "FILE_ATTRIBUTE_TEMPORARY:\nA file that is being used for temporary storage. File systems avoid writing data back to mass storage if sufficient cache memory is available, because typically, an application\
				 deletes a temporary file after the handle is closed. In that scenario, the system can entirely avoid writing the data. Otherwise, the data is written after the handle is closed.\n--\n";
    if (fileAttributes & FILE_ATTRIBUTE_VIRTUAL)
        cout << "FILE_ATTRIBUTE_VIRTUAL:\nThis value is reserved for system use.\n--\n";

    HANDLE hFile = CreateFile(fileName, 0x00, 0x00, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        cout << "Unable to get file handle invalid handle value!\n";
        system("pause");
        return 0;
    }

    if (hFile == NULL) {
        cout << "Unable to get file handle!\n";
        system("pause");
        return 0;
    }

    FILETIME fileCreatedTime;
    SYSTEMTIME fileCreatedSystemTime;
    wchar_t createdLocalDate[255];
    wchar_t createdLocalTime[255];
    FILETIME fileAccessedTime;
    SYSTEMTIME fileAccessedSystemTime;
    wchar_t accessedLocalDate[255];
    wchar_t accessedLocalTime[255];
    FILETIME fileWritedTime;
    SYSTEMTIME fileWritedSystemTime;
    wchar_t writedLocalDate[255];
    wchar_t writedLocalTime[255];

    if (GetFileTime(hFile, &fileCreatedTime, &fileAccessedTime, &fileWritedTime) != 0) {
        FileTimeToLocalFileTime(&fileCreatedTime, &fileCreatedTime);
        FileTimeToLocalFileTime(&fileAccessedTime, &fileAccessedTime);
        FileTimeToLocalFileTime(&fileWritedTime, &fileWritedTime);

        FileTimeToSystemTime(&fileCreatedTime, &fileCreatedSystemTime);
        FileTimeToSystemTime(&fileAccessedTime, &fileAccessedSystemTime);
        FileTimeToSystemTime(&fileWritedTime, &fileWritedSystemTime);

        GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &fileCreatedSystemTime, NULL, createdLocalDate, 255);
        GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &fileAccessedSystemTime, NULL, accessedLocalDate, 255);
        GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &fileWritedSystemTime, NULL, writedLocalDate, 255);

        GetTimeFormat(LOCALE_USER_DEFAULT, 0, &fileCreatedSystemTime, NULL, createdLocalTime, 255);
        GetTimeFormat(LOCALE_USER_DEFAULT, 0, &fileAccessedSystemTime, NULL, accessedLocalTime, 255);
        GetTimeFormat(LOCALE_USER_DEFAULT, 0, &fileWritedSystemTime, NULL, writedLocalTime, 255);

        cout << "Creation date: " << fileCreatedSystemTime.wDay << "." << fileCreatedSystemTime.wMonth << "."
            << fileCreatedSystemTime.wYear << " " << fileCreatedSystemTime.wHour << ":"
            << fileCreatedSystemTime.wMinute << "\n";
        cout << "Last adressed: " << fileAccessedSystemTime.wDay << "." << fileAccessedSystemTime.wMonth << "."
            << fileAccessedSystemTime.wYear << " " << fileAccessedSystemTime.wHour << ":"
            << fileAccessedSystemTime.wMinute << "\n";
        cout << "Last change: " << fileWritedSystemTime.wDay << "." << fileWritedSystemTime.wMonth << "."
            << fileWritedSystemTime.wYear << " " << fileWritedSystemTime.wHour << ":"
            << fileWritedSystemTime.wMinute << "\n";
    }

    BY_HANDLE_FILE_INFORMATION fileinfo;
    if (GetFileInformationByHandle(hFile, &fileinfo)) {
        cout << "\nVolume serial number: " << fileinfo.dwVolumeSerialNumber << endl
            << "Number of links: " << fileinfo.nNumberOfLinks << endl;
    }

    CloseHandle(hFile);
}

void changeFileAttributes() {
    char fileName[250];
    cout << "Enter file name (no spaces): ";
    cin >> fileName;
    DWORD attrs = GetFileAttributesA(fileName);

    char answer;

    cout << "Make archival? (1/0):";
    cin >> answer;
    if (answer == '1')
        attrs |= FILE_ATTRIBUTE_ARCHIVE;
    else
        attrs &= ~FILE_ATTRIBUTE_ARCHIVE;
    cout << "Make invisible? 1/0 ";
    cin >> answer;
    if (answer == '1')
        attrs |= FILE_ATTRIBUTE_HIDDEN;
    else
        attrs &= ~FILE_ATTRIBUTE_HIDDEN;
    cout << "Make normal? 1/0";
    cin >> answer;
    if (answer == '1')
        attrs |= FILE_ATTRIBUTE_NORMAL;
    else
        attrs &= ~FILE_ATTRIBUTE_NORMAL;
    cout << "Index content? 1/0";
    cin >> answer;
    if (answer == '1')
        attrs |= FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;
    else
        attrs &= ~FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;
    cout << "Available offline? 1/0";
    cin >> answer;
    if (answer == '1')
        attrs |= FILE_ATTRIBUTE_OFFLINE;
    else
        attrs &= ~FILE_ATTRIBUTE_OFFLINE;
    cout << "Make read only? 1/0";
    cin >> answer;
    if (answer == '1')
        attrs |= FILE_ATTRIBUTE_READONLY;
    else
        attrs &= ~FILE_ATTRIBUTE_READONLY;
    cout << "Make system? 1/0";
    cin >> answer;
    if (answer == '1')
        attrs |= FILE_ATTRIBUTE_SYSTEM;
    else
        attrs &= ~FILE_ATTRIBUTE_SYSTEM;
    cout << "Make temporary? 1/0";
    cin >> answer;
    if (answer == '1')
        attrs |= FILE_ATTRIBUTE_TEMPORARY;
    else
        attrs &= ~FILE_ATTRIBUTE_TEMPORARY;

    if (SetFileAttributesA(fileName, attrs))
        cout << "Attributes set successfully!\n";
    else
        cout << "Error occured, attributes haven't been set!\n";
    system("pause");
}

void changeCreationTime() {
    wchar_t filename[250];
    char fileCharName[250];
    cout << "Enter file name: ";
    cin >> fileCharName;
    mbstowcs(filename, fileCharName, 250);
    HANDLE hFile = CreateFile(filename, FILE_WRITE_ATTRIBUTES, 0, NULL, OPEN_EXISTING, 0, NULL);

    FILETIME fileTime;
    SYSTEMTIME systemTimeNow;
    GetSystemTime(&systemTimeNow);
    SystemTimeToFileTime(&systemTimeNow, &fileTime);

    if (SetFileTime(hFile, &fileTime, NULL, NULL))
        cout << "Time set successfully\n" << systemTimeNow.wDay << "." << systemTimeNow.wMonth << "."
        << systemTimeNow.wYear << " " << systemTimeNow.wHour + 3 << ":" << systemTimeNow.wMinute << "\n";
    else
        cout << "Error occured, time hasn't been set.\n";

    CloseHandle(hFile);
    system("pause");
}
