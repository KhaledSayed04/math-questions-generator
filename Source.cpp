#include <iostream> 
#include <string> 
using namespace std;

enum enOperationType { Add = 1, Sub, Mult, Div, MixT };
enum enQuestionsLevel { Easy = 1, Mid, Hard, MixL };

int ReadPositiveNumber(string Message)
{
	int Num;
	cout << Message;
	cin >> Num;
	while (cin.fail() || Num < 0)
	{
		if (cin.fail()) //user didn't enter a number
		{ 
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		cout << "Enter A Positive Number !\n";
		cin >> Num;
	}

	return Num;
}

int ReadNumberInRange(int Lower = INT_MIN, int Upper = INT_MAX, string Message = "_")
{
	Message == "_" ? Message = "Enter the number (From " + to_string(Lower) + " to " + to_string(Upper) + ")\n" : Message = Message;
	int Temp;

	cout << Message;
	cin >> Temp;

	while (cin.fail() || Temp < Lower || Temp > Upper)
	{
		if (cin.fail()) //user didn't enter a number
		{ 
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		cout << "Enter A Number ! (From " << Lower << " to " << Upper << ")\n";
		cin >> Temp;
	}

	return Temp;
}

int RandomNumberInRange(int From, int To)//Fn to generate a random number
{
	return (From < To) ? (rand() % (To - From + 1) + From) : (rand() % (From - To + 1) + To);
}

enOperationType GetOperationType()
{
	return (enOperationType)ReadNumberInRange(1, 5, "Enter Qs Operation Type [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix\n");
}

enQuestionsLevel GetQuestionsLvl()
{
	return (enQuestionsLevel)ReadNumberInRange(1, 4, "Enter Qs Lvl [1] Easy , [2] Med , [3] Hard , [4] Mix\n");;
}

int GetRightAns(int Num1, int Num2, enOperationType OpType)
{
	switch (OpType)
	{
	case Add:
		return Num1 + Num2;
	case Sub:
		return Num1 - Num2;
	case Mult:
		return (int)Num1 * Num2;
	default:
		return Num1 / Num2;
	}
}

string PrintOperateType(enOperationType OpType)
{
	switch (OpType)
	{
	case Add:
		return " + ";
	case Sub:
		return " - ";
	case Mult:
		return " * ";
	default:
		return " / ";
	}
}

short Round(enOperationType RoundOpType, enQuestionsLevel RoundLvl)
{
	int Num1, Num2;

	if (RoundLvl == enQuestionsLevel::Easy)
	{
		Num1 = RandomNumberInRange(1, 10), Num2 = RandomNumberInRange(1, 10);
	}
	else if (RoundLvl == enQuestionsLevel::Mid)
	{
		Num1 = RandomNumberInRange(11, 1000), Num2 = RandomNumberInRange(11, 1000);
	}
	else
	{
		Num1 = RandomNumberInRange(1001, 10000), Num2 = RandomNumberInRange(1001, 10000);
	}

	int RightAns = GetRightAns(Num1, Num2, RoundOpType), UserAns;

	cout << endl << Num1 << PrintOperateType(RoundOpType) << Num2 << " = ?\n";
	cin >> UserAns;
	while (cin.fail()) //user didn't enter a number
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Enter A Number !\n";
		cin >> UserAns;
	}

	if (UserAns != RightAns)
	{
		system("color 47");
		cout << "Wrong Answer ! \nThe Result = " << RightAns << "\n_______________________";
		return 0;
	}
	else
	{
		system("color 27");
		cout << "Correct Answer !\n_______________________";
		return 1;
	}
}

void PrintResult(int RoundsCount, int WinsNum, enQuestionsLevel Q_Lvl, enOperationType OpType)
{
	system("cls");
	string Result;
	if ((WinsNum << 1) >= RoundsCount)
	{
		Result = "You Passed :)";
		system("color 27");
	}
	else
	{
		Result = "You Failed :(";
		system("color 47");
	}

	cout << "____________________________\n" << Result;
	cout << "\n____________________________\n";
	cout << "\nNumber of Rounds        : " << RoundsCount;
	cout << "\nLevel of Questions      : ";
	(Q_Lvl == Easy) ? cout << "Easy" : (Q_Lvl == Mid) ? cout << "Mid" : (Q_Lvl == Hard) ? cout << "Hard" : cout << "Mix";
	cout << "\nOperation Type          : ";
	(OpType == Add) ? cout << "Add" : (OpType == Sub) ? cout << "Subtruct" :
		(OpType == Div) ? cout << "Divide" : (OpType == Mult) ? cout << "Multiplication" : cout << "Mix";
	cout << "\nNumber of Right Answers : " << WinsNum;
	cout << "\nNumber of Wrong Answers : " << RoundsCount - WinsNum << "\n\n";

	system("pause > 0");
}

void Game()
{
	int RoundsCount = ReadPositiveNumber("How many Qs do you want to answer ?\n");
	enQuestionsLevel Q_Lvl = GetQuestionsLvl();
	enOperationType OpType = GetOperationType();
	bool IsMixOp = OpType == enOperationType::MixT ? 1 : 0;
	bool IsMixLvl = Q_Lvl == enQuestionsLevel::MixL ? 1 : 0;
	int WinsNum = 0;

	int PrevQLvl = 0, PrevO = 0;
	for (int counter = 0; counter < RoundsCount; counter++)
	{
		enQuestionsLevel RoundLvl = Q_Lvl;
		if (Q_Lvl == MixL)
			while (int(RoundLvl = enQuestionsLevel(RandomNumberInRange(1, 3))) == PrevQLvl);

		enOperationType RoundOpType = OpType;
		if (OpType == MixT)
			while (int(RoundOpType = enOperationType(RandomNumberInRange(1, 4))) == PrevO);

		WinsNum += Round(RoundOpType, RoundLvl);
		PrevQLvl = RoundLvl;
		PrevO = RoundOpType;
	}

	cout << "\n\nPress any key to show The Game Result..";
	system("pause > 0");
	PrintResult(RoundsCount, WinsNum, Q_Lvl, OpType);
}

int main()
{
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));//if you put it in other Fn it will return the same value out of that funtion

	char Continue;
	do
	{
		Game();
		system("cls");
		system("color 07");
		cout << "\nDo you want try again ? (Y / N)\n";
		cin >> Continue;

	} while (tolower(Continue) == 'y');

	system("cls");
	cout << "The Program Ended ! :)\n";

	return 0;
}