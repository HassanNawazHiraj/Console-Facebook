

struct Comment {
	int CommentId;
	char user[20];
	char comment[80];
};
typedef struct Comment CommentStruct;
static const CommentStruct EmptyCommentStruct = { 0 };
struct WallPost
{
	int PostId;
	char User[20];
	char Post[255];
	int Likes;
	CommentStruct comments[10];
};
typedef struct WallPost WallPostStruct;




void NewLine();
void EqualLine(bool , bool );
const char * EqualLineReturn();
//char * StringCombine(char* , char* );
void EqualLineText(char*);
int CreateMenu(char* , int , int , bool, bool);
void clearscreen();
void MultiInputs(char*, char*, int, int , bool);
void CreateFile1(char*,char*);
void AppendFile(char*, char*, bool, bool);
int FileExists(char*, bool);
void Login(char*, char [3][50]);
void GetWallPost(int, char[20], char [50], char[255],int, int*, CommentStruct [10]);
int GetTotalWallPosts(char[20]);
int GetTotalFriends(char user[20]);
void InDataFolder(char*);
bool AddFriend(char*, char*);
void ShowAllFriends(char[20], char [100][255], int*, int*, int*);
bool FriendExists(char[20], char[20]);
void DisplayWallPosts(char[50], bool);
bool CreatePostOnWall(char[50], char[50], char[255]);
int GetLastIdForWallPost(char[50]);
void PerformLike(int, char[50]);
bool LikePost(int , char [50], char[50]);
bool CreateCommentOnPost(char[50], char[50], char[80], int);
bool UserExistsForLikes(char [20], char [20], int );
void ZalimColor();
void WhiteColor(bool);
void InfoTextColor();
void ErrorColor();
void SuccessColor();
void DeleteAccount(char[50]);
void DeletePost(char[50], int);