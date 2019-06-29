#include<iostream>
#include<vector>

using namespace std;
void print(vector<vector<int>>,int,int);
bool solve(vector<vector<int>>,vector<vector<int>>,vector<vector<int>>,int,int);
bool check(vector<vector<int>>,vector<vector<int>>,vector<vector<int>>);
vector<vector<int>> fillTrivial(vector<vector<int>>,vector<vector<int>>,vector<vector<int>>);
vector<vector<int>> checkIfCompleted(vector<vector<int>>,vector<vector<int>>,vector<vector<int>>);
vector<vector<int>> logic(vector<vector<int>>,vector<vector<int>> ,vector<vector<int>>);
int contains(vector<int> ,int);


int main()
{
	vector<vector<int>> board;
	int width,height;
	cin>>width>>height;
	board.resize(height);
	for(int i=0;i<height;i++)
	{
		board[i].resize(width);
	}
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			board[i][j]=0;
		}
	}
	vector<vector<int>>columns;
	vector<vector<int>>rows;
	
	for(int i=0;i<height;i++)
	{
		int p;
		vector<int> row;
		cin>>p;
		while(p>=0)
		{
			row.push_back(p);
			cin>>p;
		}
		rows.push_back(row);
	}
	for(int i=0;i<width;i++)
	{
		int p;
		vector<int> column;
		cin>>p;
		while(p>=0)
		{
			column.push_back(p);
			cin>>p;
			
		}
		columns.push_back(column);
	}
	
	

	print(board,width,height);
	
	board=fillTrivial(rows,columns,board);
	print(board,width,height);
	board=checkIfCompleted(rows,columns,board);
	print(board,width,height);
	board=logic(rows,columns,board);
	board=checkIfCompleted(rows,columns,board);
	print(board,width,height);
	
	
	
	
	cout<<solve(rows,columns,board,0,0)<<endl;
	//cout<<solve(rows,columns,board,0,0)<<endl;
	//print(board,width,height);
	
	
	
	
	
	
	
	
}

void print(vector<vector<int>>board,int width, int height)
{
	for(int i=0;i<height;i++)
	{
		
		for(int j=0;j<width;j++)
		{
			if(board[i][j]==2 || board[i][j]==0)
			{
				cout<<"x";
			}
			else if(board[i][j]==1)
			{
				cout<<"#";
			}
			
		}
		cout<<"\n";
	}
	cout<<endl;
}
bool solve(vector<vector<int>> rows,vector<vector<int>> columns,vector<vector<int>> board,int k,int l)
{
	if(check(rows,columns,board))
	{
		print(board,board[0].size(),board.size());
		cout<<endl;
		return true;
	}
	for(int i=0;i<board.size();i++)
	{
		for(int j=0;j<board[i].size();j++)
		{
			if(board[i][j]==0)
			{
				board[i][j]=1;
		//		print(board,board[0].size(),board.size());
				//cout<<endl;
				if(solve(rows,columns,board,i, j))
				{
					
					return true;
				}
				board[i][j]=0;
			}
		}
		
	}
	
	
	
}

bool check(vector<vector<int>> rows,vector<vector<int>> columns,vector<vector<int>> board)
{
	vector<vector<int>> rows1;
	vector<vector<int>> columns1;
	for(int i=0;i<board.size();i++)//height/rows
	{
		int count =0;
		vector<int>thisRow;
		for(int j=0;j<board[i].size();j++)//each individual row
		{
			if(board[i][j]==1)
			{
				count++;
			}
			else if(count!=0)
			{
				thisRow.push_back(count);
				count=0;
			}
			
		}
		if(count!=0)
		{
			thisRow.push_back(count);
		}
		rows1.push_back(thisRow);
		
		
	}
	
	for(int i=0;i<board[0].size();i++)//width/columns
	{
		int count =0;
		vector<int>thisColumn;
		for(int j=0;j<board.size();j++)//each individual column
		{
			if(board[j][i]==1)
			{
				count++;
			}
			else if(count!=0)
			{
				thisColumn.push_back(count);
				count=0;
			}
			
		}
		if(count!=0)
		{
			thisColumn.push_back(count);
		}
		columns1.push_back(thisColumn);
		
		
	}
	
	for(int i=0;i<rows.size();i++)//check the two sets of vectors
	{
		if(rows[i].size()!=rows1[i].size())
		{
			
			return false;
		}
		else
		{
			for(int j=0;j<rows[i].size();j++)
			{
				if(rows[i][j]!=rows1[i][j])
				{
					
					return false;
				}
			}
		}
		
		
	}
	for(int i=0;i<columns.size();i++)//check the two sets of vectors
	{
		if(columns[i].size()!=columns1[i].size())
		{
			
			return false;
		}
		else
		{
			for(int j=0;j<columns[i].size();j++)
			{
				if(columns[i][j]!=columns1[i][j])
				{
			
					return false;
				}
			}
		}

		
		
	}
	return true;
	
}
vector<vector<int>> fillTrivial(vector<vector<int>>rows,vector<vector<int>> columns,vector<vector<int>>board)
{
	int count=0;
	for(int i=0;i<rows.size();i++)//height/ rows
	{
		for(int j=0;j<rows[i].size();j++)//each row
		{
			
				count+=rows[i][j];
			
		}
		if(count==0)
		{
			for(int k=0;k<board[0].size();k++)
			{
				board[i][k]=2;
			}
		}
		else if(count==board[0].size())
		{
			for(int k=0;k<board[0].size();k++)
			{
				board[i][k]=1;
			}
		}
		else if(count+ rows[i].size()-1==board[0].size())
		{
			int point=0;
			for(int k=0;k<rows[i].size();k++)
			{
				for(int l=0;l<rows[i][k];l++)
				{
					board[i][point]=1;
					point++;
				}
				if(point<board[0].size())
				{
					board[i][point]=2;
				}
				
				point++;
			}
			
		}
		count=0;
		
	}
	for(int i=0;i<columns.size();i++)
	{
		for(int j=0;j<columns[i].size();j++)
		{
			
				count+=columns[i][j];
			
		}
		if(count==0)
		{
			for(int k=0;k<board.size();k++)
			{
				board[k][i]=2;
			}
		}
		else if(count==board.size())
		{
			for(int k=0;k<board.size();k++)
			{
				board[k][i]=1;
			}
		}
		else if(count+ columns[i].size()-1==board.size())
		{
			int point=0;
			for(int k=0;k<columns[i].size();k++)
			{
				for(int l=0;l<columns[i][k];l++)
				{
					board[point][i]=1;
					point++;
				}
				if(point<board.size())
				{
					board[point][i]=2;
				}
					
				point++;
			}
			
		}
		count=0;
		
	}
	
	return board;
	
	
}


vector<vector<int>> checkIfCompleted(vector<vector<int>>rows,vector<vector<int>> columns,vector<vector<int>>board)
{
	vector<vector<int>> rows1;
	vector<vector<int>> columns1;
	for(int i=0;i<board.size();i++)//height/rows
	{
		int count =0;
		vector<int>thisRow;
		for(int j=0;j<board[i].size();j++)//each individual row
		{
			if(board[i][j]==1)
			{
				count++;
			}
			else if(count!=0)
			{
				thisRow.push_back(count);
				count=0;
			}
			
		}
		if(count!=0)
		{
			thisRow.push_back(count);
		}
		rows1.push_back(thisRow);
		
		
	}
	
	for(int i=0;i<board[0].size();i++)//width/columns
	{
		int count =0;
		vector<int>thisColumn;
		for(int j=0;j<board.size();j++)//each individual column
		{
			if(board[j][i]==1)
			{
				count++;
			}
			else if(count!=0)
			{
				thisColumn.push_back(count);
				count=0;
			}
			
		}
		if(count!=0)
		{
			thisColumn.push_back(count);
		}
		columns1.push_back(thisColumn);
		
		
	}
	
	
	for(int i=0;i<rows.size();i++)//check the two sets of vectors
	{
		bool isRow=true;
		if(rows[i].size()!=rows1[i].size())
		{
			
			isRow=false;
		}
		else
		{
			for(int j=0;j<rows[i].size();j++)
			{
				if(rows[i][j]!=rows1[i][j])
				{
					
					isRow=false;
				}
			}
		}
		if(isRow)
		{
			//go through this specific row and set all blank space to 2
			for(int j=0;j<columns.size();j++)
			{
				if(board[i][j]==0)
				{
					board[i][j]=2;
				}
			}
			
			
		}
		
	}
	for(int i=0;i<columns.size();i++)//check the two sets of vectors
	{
		bool isCol=true;
		if(columns[i].size()!=columns1[i].size())
		{
			
			isCol=false;
		}
		else
		{
			for(int j=0;j<columns[i].size();j++)
			{
				if(columns[i][j]!=columns1[i][j])
				{
			
					isCol=false;
				}
			}
		}
		if(isCol)
		{
			//go through this specific column and set all blank space to 2
			for(int j=0;j<rows.size();j++)
			{
				if(board[j][i]==0)
				{
					board[j][i]=2;
				}
			}
			
			
		}
		
		
	}
	return board;
}

vector<vector<int>> logic(vector<vector<int>>rows,vector<vector<int>> columns,vector<vector<int>>board)
{
	
	int p=0;
	
	//do
	//{
		
		p=0;
		for(int i=0;i<rows.size();i++)
		{
			int sum=0;
			for(int j=0;j<rows[i].size();j++)
			{
				//find all numbers >= width/2 and fill them in
				if(contains(rows[i],2)<columns.size()/2)
				{
					
					
				}
				if(rows[i][j]>columns.size()/2)
				{
					for(int k=columns.size()-rows[i][j];k<rows[i][j];k++)
					{
						board[i][k]=1;
					}
					//cout<<"i: "<<i<<endl;
					p++;
				}
			}
			
			
			
		}
		for(int i=0;i<columns.size();i++)
		{
			int sum=0;
			for(int j=0;j<columns[i].size();j++)
			{
				//find all numbers >= width/2 and fill them in
				//cout<<columns[i][j]<<endl;
				//cout<<rows.size();
				if(columns[i][j]>rows.size()/2)
				{
					for(int k=rows.size()-columns[i][j];k<columns[i][j];k++)
					{
						board[k][i]=1;
					}
					//cout<<"i: "<<i<<endl;
					p++;
				}
			}
			
			
		}
	//}
	//while(p!=0);
	
	
	return board;
	
	
}
 
int contains(vector<int> arr,int x)
{
	for(int i=0;i<arr.size();i++)
	{
		if(arr[i]==x)
		{
			return i;
		}
	}
	return 100000;
}