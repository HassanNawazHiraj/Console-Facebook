
void NewLine();
void EqualLine(bool , bool );
const char * EqualLineReturn();
//char * StringCombine(char* , char* );
void EqualLineText(char*);
int CreateMenu(char* , int , int , bool, bool);
void clearscreen();
void MultiInputs(char*, char*, int, int , bool);
void CreateFile(char*,char*);
void AppendFile(char*, char*, bool, bool);
int FileExists(char*, bool);
void Login(char*, char [3][50]);
void GetWallPost(int, char[20], char[255],int);
int GetTotalWallPosts(char[20]);
int GetTotalFriends(char user[20]);
void InDataFolder(char*);
void AddFriend(char*, char*);
void ShowAllFriends(char[20], char [100][255], int*, int*, int*);