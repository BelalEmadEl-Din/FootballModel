#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
int N;
int* nozir;
int* nozic;
int** M;
int** path;
int* RowCover;
int* ColCover;
int path_count = 0;
int path_row_0;
int path_col_0;
int NumberOfPlayers, NumberOfPositions;
void HungarianMethodPrint(string* NamesOfClubs, string* NamesOfPlayers, string* NamesOfSkills, string* NamesOfPositions, string* PlayerTypeOfPreferredFoot, string* UserTypeOfPreferredFoot, float** Cost, int Number1, int Number2);
void step_one(float**& C);
void step_two(float**& C);
void step_three(float**& C);
void step_four(float**& C);
void step_five(float**& C);
void step_six(float**& C);
int main() {
	ifstream UserData;
	ifstream FifaData;
	int NumberOfPlayers;
	cout << "Enter the number of players\n";
	cin >> NumberOfPlayers;
	int NumberOfDetails;
	int NumberOfPositions;
	string Trash;
	const string str = "\n";
	const string str1 = ",";
	int x = 0;
	int z = 0;
	UserData.open("C:/Users/20111/Desktop/Belal/Programs/Project/UserData1.csv");
	if (UserData) {
		getline(UserData, Trash, ',');
		while (getline(UserData, Trash, ',')) {
			x++;

			if (Trash.find(str) != std::string::npos) {

				break;
			}
		}
		NumberOfPositions = x;
		while (getline(UserData, Trash, '\n')) {
			z++;
		}
		NumberOfDetails = z - 2;

	}

	else cout << "Can't open file 1\n";

	UserData.close();
	string* UserTypeOfPreferredFoot;
	UserTypeOfPreferredFoot = new string[NumberOfPositions];
	float** WeightsOfDetailsInPositions = new float* [NumberOfDetails];
	for (int i = 0; i < NumberOfDetails; i++) {
		WeightsOfDetailsInPositions[i] = new float[NumberOfPositions];
	}
	string* NamesOfPositions;
	NamesOfPositions = new string[NumberOfPositions];
	string* PlayerTypeOfPreferredFoot;
	PlayerTypeOfPreferredFoot = new string[NumberOfPlayers];
	float* WeightsOfPositions;
	WeightsOfPositions = new float[N];
	for (int i = 0; i < N; i++) {
		WeightsOfPositions[i] = 0;
	}
	UserData.open("C:/Users/20111/Desktop/Belal/Programs/Project/UserData1.csv");
	if (UserData) {
		getline(UserData, Trash, ',');
		for (int c = 0; c < NumberOfPositions - 1; c++) {
			getline(UserData, NamesOfPositions[c], ',');
		}
		getline(UserData, NamesOfPositions[NumberOfPositions - 1], '\n');
		getline(UserData, Trash, ',');
		for (int c = 0; c < NumberOfPositions - 1; c++) {
			UserData >> WeightsOfPositions[c];
			getline(UserData, Trash, ',');
		}UserData >> WeightsOfPositions[NumberOfPositions - 1];
		getline(UserData, Trash, '\n');
		getline(UserData, Trash, ',');
		for (int c = 0; c < NumberOfPositions - 1; c++) {
			getline(UserData, UserTypeOfPreferredFoot[c], ',');
		}

		getline(UserData, UserTypeOfPreferredFoot[NumberOfPositions - 1], '\n');

		for (int b = 0; b < NumberOfDetails; b++) {
			getline(UserData, Trash, ',');
			for (int c = 0; c < NumberOfPositions - 1; c++) {

				UserData >> WeightsOfDetailsInPositions[b][c];
				getline(UserData, Trash, ',');
			}
			UserData >> WeightsOfDetailsInPositions[b][NumberOfPositions - 1];
			getline(UserData, Trash, '\n');
		}

	}
	else { cout << "Can't open file 1\n"; }
	string UserNameOfClub = " ";
	cout << "Enter the club name\n";
	cin.ignore();
	getline(cin, UserNameOfClub, '\n');
	string* NamesOfClubs;
	NamesOfClubs = new string[NumberOfPlayers + 1];
	string* NamesOfPlayers;
	NamesOfPlayers = new string[NumberOfPlayers + 1];
	x = 0;
	float** DetailsOfPlayers = new float* [NumberOfPlayers];
	for (int i = 0; i < NumberOfPlayers; ++i)
	{
		DetailsOfPlayers[i] = new float[NumberOfDetails];
	}
	float* SkillMoves;
	SkillMoves = new float[NumberOfPlayers];
	float* WeakFoot;
	WeakFoot = new float[NumberOfPlayers];
	float** Benefit;
	if (NumberOfPlayers >= NumberOfPositions) {
		N = NumberOfPlayers;
		M = new int* [N];
		Benefit = new float* [N];
		for (int i = 0; i < N; ++i) {

			Benefit[i] = new float[N];
			M[i] = new int[N];
		}
		nozir = new int[N];
		nozic = new int[N];



	}
	else {
		N = NumberOfPositions;
		Benefit = new float* [N];
		M = new int* [N];
		for (int i = 0; i < N; ++i) {
			M[i] = new int[N];
			Benefit[i] = new float[N];
		}
		nozir = new int[N];
		nozic = new int[N];




	}

	path = new int* [N * 2 + 1];
	for (int i = 0; i < N * 2 + 1; ++i) {
		path[i] = new int[2];
	}

	RowCover = new int[N];
	ColCover = new int[N];
	for (int i = 0; i < N; i++) {
		RowCover[i] = 0;
		ColCover[i] = 0;
	}
	float** PlayerRatingsInPositions = new float* [N];
	for (int i = 0; i < N; ++i)
		PlayerRatingsInPositions[i] = new float[N];
	string* NamesOfSkills;
	NamesOfSkills = new string[NumberOfDetails + 1];

	FifaData.open("C:/Users/20111/Desktop/Belal/Programs/Project/FifaData.csv");
	if (FifaData) {
		getline(FifaData, NamesOfClubs[0], ',');
		getline(FifaData, NamesOfPlayers[0], ',');


		for (int x = 0; x < NumberOfDetails; x++) {
			getline(FifaData, NamesOfSkills[x], ',');
		}

		getline(FifaData, NamesOfSkills[NumberOfDetails], '\n');

		for (int i = 1; i < NumberOfPlayers + 1; i++) {
			if (UserNameOfClub != "any") {
				FifaData.putback(',');
			}

			getline(FifaData, NamesOfClubs[i], ',');
			if (NamesOfClubs[i] == "k") { goto c; }
		h: if (UserNameOfClub == "any") { goto B; }
		else if (NamesOfClubs[i] == UserNameOfClub) {

			goto B;
		}
		else if (NamesOfClubs[i] != UserNameOfClub) {
			while (NamesOfClubs[i] != UserNameOfClub) {
			c:
				Trash = " ";
				getline(FifaData, Trash, '\n');
				getline(FifaData, NamesOfClubs[i], ',');
				goto h;
			}
		}
	B:

		getline(FifaData, NamesOfPlayers[i], ',');

		getline(FifaData, PlayerTypeOfPreferredFoot[i - 1], ',');

		FifaData >> WeakFoot[i - 1];
		getline(FifaData, Trash, ',');
		FifaData >> SkillMoves[i - 1];
		getline(FifaData, Trash, ',');
		DetailsOfPlayers[i - 1][0] = 20 * WeakFoot[i - 1];
		DetailsOfPlayers[i - 1][1] = 20 * SkillMoves[i - 1];

		for (int m = 2; m < NumberOfDetails - 1; m++) {
			FifaData >> DetailsOfPlayers[i - 1][m];
			getline(FifaData, Trash, ',');
		}
		FifaData >> DetailsOfPlayers[i - 1][NumberOfDetails - 1];

		}
	}
	else cout << "Can not open file 2\n";
	FifaData.close();
	for (int i = 0; i < N; i++) {
		for (int x = 0; x < N; x++) {
			PlayerRatingsInPositions[i][x] = 0;
		}
	}
	for (int y = 0; y < NumberOfPlayers; y++) {
		for (int z = 0; z < NumberOfPositions; z++) {
			for (int x = 0; x < NumberOfDetails; x++) {

				PlayerRatingsInPositions[y][z] += DetailsOfPlayers[y][x] * WeightsOfDetailsInPositions[x][z];

			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int x = 0; x < N; x++) {
			Benefit[i][x] = 0;
			M[i][x] = 0;
		}
	}
	for (int x = 0; x < N; x++) {
		for (int i = 0; i < N; i++) {

			Benefit[x][i] += PlayerRatingsInPositions[x][i] * WeightsOfPositions[i];
		}
	}
	for (int i = 0; i < N; ++i) {
		nozic[i] = 0;
		nozir[i] = 0;

	}
	for (int i = 0; i < N; i++) {
		for (int x = 0; x < N; x++) {
			if (UserTypeOfPreferredFoot[x] != PlayerTypeOfPreferredFoot[i] && UserTypeOfPreferredFoot[x] != "any") {
				Benefit[i][x] = 0;
			}
		}
	}
	float max = Benefit[0][0];
	for (int i = 0; i < N; i++) {
		for (int x = 0; x < N; x++) {
			if (max < Benefit[i][x]) {
				max = Benefit[i][x];
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int x = 0; x < N; x++) {
			Benefit[i][x] = max - Benefit[i][x];
		}
	}
	for (int i = 0; i < N; i++) {
		for (int x = 0; x < 2; x++) {
			path[i][x] = 0;
		}
	}
	step_one(Benefit);

	HungarianMethodPrint(NamesOfClubs, NamesOfPlayers, NamesOfSkills, NamesOfPositions, PlayerTypeOfPreferredFoot, UserTypeOfPreferredFoot, Benefit, NumberOfPlayers, NumberOfPositions);
	cin >> Trash;
}
//For each row of the cost matrix, find the smallest element and subtract
		//it from every element in its row.  When finished, Go to Step 2.
void step_one(float**& C)
{
	float min_in_row;

	for (int r = 0; r < N; r++)
	{
		min_in_row = C[r][0];
		for (int c = 0; c < N; c++)
			if (C[r][c] < min_in_row)
				min_in_row = C[r][c];
		for (int c = 0; c < N; c++)
			C[r][c] -= min_in_row;
	}
	step_two(C);
}

//Find a zero (Z) in the resulting matrix.  If there is no starred 
//zero in its row or column, star Z. Repeat for each element in the 
//matrix. Go to Step 3.
void step_two(float**& C)
{
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++)
		{
			if (C[r][c] == 0 && RowCover[r] == 0 && ColCover[c] == 0)
			{
				M[r][c] = 1;
				RowCover[r] = 1;
				ColCover[c] = 1;
			}
		}
	}
	for (int r = 0; r < N; r++)
		RowCover[r] = 0;
	for (int c = 0; c < N; c++)
		ColCover[c] = 0;
	step_three(C);

}

//Cover each column containing a starred zero.  If K columns are covered, 
//the starred zeros describe a complete set of unique assignments.  In this 
//case, Go to DONE, otherwise, Go to Step 4.
void step_three(float**& C)
{
	int colcount;
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			if (M[r][c] == 1)
				ColCover[c] = 1;

	colcount = 0;
	for (int c = 0; c < N; c++)
		if (ColCover[c] == 1)
			colcount += 1;
	if (colcount >= N)
		return;
	else
		step_four(C);
}

//methods to support step 4
void find_a_zero(int& row, int& col, float**& C)
{
	int r = 0;
	int c;
	bool done;
	row = -1;
	col = -1;
	done = false;
	while (!done)
	{
		c = 0;
		while (true)
		{
			if (C[r][c] == 0 && RowCover[r] == 0 && ColCover[c] == 0)
			{
				row = r;
				col = c;
				done = true;
			}
			c += 1;
			if (c >= N || done)
				break;
		}
		r += 1;
		if (r >= N)
			done = true;
	}
}

bool star_in_row(int row)
{
	bool tmp = false;
	for (int c = 0; c < N; c++)
		if (M[row][c] == 1)
			tmp = true;
	return tmp;
}

void find_star_in_row(int row, int& col)
{
	col = -1;
	for (int c = 0; c < N; c++)
		if (M[row][c] == 1)
			col = c;
}

//Find a noncovered zero and prime it.  If there is no starred zero 
//in the row containing this primed zero, Go to Step 5.  Otherwise, 
//cover this row and uncover the column containing the starred zero. 
//Continue in this manner until there are no uncovered zeros left. 
//Save the smallest uncovered value and Go to Step 6.
void step_four(float**& C)
{
	int row = -1;
	int col = -1;
	bool done;

	done = false;
	while (!done)
	{
		find_a_zero(row, col, C);
		if (row == -1)
		{
			done = true;
			step_six(C);
		}
		else
		{
			M[row][col] = 2;
			if (star_in_row(row))
			{
				find_star_in_row(row, col);
				RowCover[row] = 1;
				ColCover[col] = 0;
			}
			else
			{
				done = true;
				path_row_0 = row;
				path_col_0 = col;
				step_five(C);
			}
		}
	}
}

// methods to support step 5
void find_star_in_col(int c, int& r)
{
	r = -1;
	for (int i = 0; i < N; i++)
		if (M[i][c] == 1)
			r = i;
}

void find_prime_in_row(int r, int& c)
{
	for (int j = 0; j < N; j++)
		if (M[r][j] == 2)
			c = j;
}
void augment_path()
{
	for (int p = 0; p < path_count; p++)
		if (M[path[p][0]][path[p][1]] == 1)
			M[path[p][0]][path[p][1]] = 0;
		else
			M[path[p][0]][path[p][1]] = 1;
}

void clear_covers()
{
	for (int r = 0; r < N; r++)
		RowCover[r] = 0;
	for (int c = 0; c < N; c++)
		ColCover[c] = 0;
}
void erase_primes()
{
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			if (M[r][c] == 2)
				M[r][c] = 0;
}


//Construct a series of alternating primed and starred zeros as follows.  
//Let Z0 represent the uncovered primed zero found in Step 4.  Let Z1 denote 
//the starred zero in the column of Z0 (if any). Let Z2 denote the primed zero 
//in the row of Z1 (there will always be one).  Continue until the series 
//terminates at a primed zero that has no starred zero in its column.  
//Unstar each starred zero of the series, star each primed zero of the series, 
//erase all primes and uncover every line in the matrix.  Return to Step 3.
void step_five(float**& C)
{
	bool done;
	int r = -1;
	int c = -1;

	path_count = 1;
	path[path_count - 1][0] = path_row_0;
	path[path_count - 1][1] = path_col_0;
	done = false;
	while (!done)
	{
		find_star_in_col(path[path_count - 1][1], r);
		if (r > -1)
		{
			path_count += 1;
			path[path_count - 1][0] = r;
			path[path_count - 1][1] = path[path_count - 2][1];
		}
		else
			done = true;
		if (!done)
		{
			find_prime_in_row(path[path_count - 1][0], c);
			path_count += 1;
			path[path_count - 1][0] = path[path_count - 2][0];
			path[path_count - 1][1] = c;
		}
	}
	augment_path();
	clear_covers();
	erase_primes();
	step_three(C);
}

//methods to support step 6
void find_smallest(float& minval, float**& C)
{
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			if (RowCover[r] == 0 && ColCover[c] == 0)
				if (minval > C[r][c])
					minval = C[r][c];
}

//Add the value found in Step 4 to every element of each covered row, and subtract 
//it from every element of each uncovered column.  Return to Step 4 without 
//altering any stars, primes, or covered lines.
void step_six(float**& C)
{
	float minval = 99999;
	find_smallest(minval, C);
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
		{
			if (RowCover[r] == 1)
				C[r][c] += minval;
			if (ColCover[c] == 0)
				C[r][c] -= minval;
		}
	step_four(C);
}
void HungarianMethodPrint(string* NamesOfClubs, string* NamesOfPlayers, string* NamesOfSkills, string* NamesOfPositions, string* PlayerTypeOfPreferredFoot, string* UserTypeOfPreferredFoot, float** Benefit, int NumberOfPlayers, int NumberOfPositions) {
	int count = 0;
	for (int i = 0; i < N; i++) {
		for (int x = 0; x < N; x++) {
			if (M[i][x] == 1 && x < NumberOfPositions) {
				cout << NamesOfPlayers[i + 1] << "->" << NamesOfPositions[x] << endl;
				count++;

			}
			if (count == NumberOfPlayers || count == NumberOfPositions) {
				return;
			}

		}
	}
	return;
}