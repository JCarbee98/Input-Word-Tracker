#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctype.h>
#include <algorithm>


//Joshua Carbee
//A program that tracks the word, number, and character usage in a file).  

using namespace std;

bool helpSortWord(const pair<string, int> &A, const pair<string, int> &B)
{
	return(A.second > B.second);
}

bool helpSortChar(const pair<char, int> &A, const pair<char, int> &B)
{
	return(A.second > B.second);
}


map<string, int> order;
map<string, int> orderNum;
bool SortedWords(const pair<string, int> &A, const pair<string, int> &B)
{
	if(A.second == B.second)
	{
		if(order.at(A.first) < order.at(B.first))
		return true;
		else
		return false;
	}
	else
	{
		return(A.second > B.second);
	}
	
}

bool SortedNums(const pair<string, int> &A, const pair<string, int> &B)
{
        if(A.second == B.second)
        {
                if(orderNum.at(A.first) < orderNum.at(B.first))
                return true;
                else
                return false;
        }
        else
        {
                return(A.second > B.second);
        }

}


int main()
{

	map<string, int> words;
	map<char, int> characters;
	map<string, int> numbers;

	int counter = 0;
	//map<string, int> order; //places words in map with counter to maker the order they appeared	

	int counterNum = 0;
	//map<string, int> orderNum;
	
	while(cin.eof() == false)
	{
		string Input;
		cin >> Input; //gets input
			
		for(int i =0; i < Input.length(); i++)
		{
		
			auto find = characters.find(Input[i]);
                	if(find != characters.end()) //if it is already in the map
               	 	{
                        	characters.at(Input[i]) = characters.at(Input[i]) + 1;
                	}
                	else
                	characters.insert(pair<char, int>(Input[i], 1)); //inserts word into map 1st time
	
			
			Input[i] = tolower(Input[i]); //converts to lower case
		}
	
		if(isalnum(Input[Input.length()-1]) == false && Input.length() > 1) //gets rid of periods
		Input = Input.substr(0, Input.length()-1);

		if(isalnum(Input[0]) == false && Input.length() > 1)
		Input = Input.substr(1, Input.length());    

		for(int i =0; i < Input.length(); i++)
		{
			if(isdigit(Input[i]) == true)
			{
				string Num(1, Input[i]);
				for(int j = i+1; j < Input.length(); j++)
				{
					if(isdigit(Input[j]) == true)
					{
						string temp(1,Input[j]);
						Num = Num + temp;
						i++;
		
					}
					else
					{
						i++;
						break;
					}
					
				}
				
				auto find = numbers.find(Num);
	                	if(find != numbers.end()) //if it is already in the map
       		        	{
                	        	numbers.at(Num) = numbers.at(Num) + 1;
               			}
                		else
				{
                			numbers.insert(pair<string, int>(Num, 1)); //inserts nums into map 1st time
					orderNum.insert(pair<string,int>(Num,counterNum));
					counterNum++;
				}
			}
		}
	
	

		if(isalpha(Input[Input.length()-1]) == false && Input.length() > 1) //gets rid of periods
                Input = Input.substr(0, Input.length()-1);

                if(isalpha(Input[0]) == false && Input.length() > 1)
                Input = Input.substr(1, Input.length());

	
		for(int i =0; i < Input.length(); i++)
                {
                        if(isalpha(Input[i]) == false) //gets ride of non letter characters and seperates the words
			{
				string Temp;
				Temp = Input.substr(0,i);
				Input = Input.substr(i+1, Input.length()-i); 
			
				
				auto find = words.find(Temp);
                                if(find != words.end()) //if it is already in the map
                                {
                                        words.at(Temp) = words.at(Temp) + 1;
                                }
                                else
				{
                                	words.insert(pair<string, int>(Temp, 1)); //inserts nums into map 1st time
					order.insert(pair<string, int>(Temp, counter));
					counter++;
				}
				i = -1;	
			}
                }
	
		auto find = words.find(Input);
		if(find != words.end()) //if it is already in the map
		{
			words.at(Input) = words.at(Input) + 1;
		}
		else
		{
			words.insert(pair<string, int>(Input, 1)); //inserts word into map 1st time
			order.insert(pair<string, int>(Input, counter));
			counter++;
		}
		
		words.erase("");
	}
	
	vector<pair<string,int>> vecWords;
	for(auto i =words.begin(); i != words.end(); ++i)
	{
		
		pair<string, int> temp;
		temp.first = i->first;
		temp.second = i->second;
		vecWords.push_back(temp);
	}

	
	vector<pair<char,int>> vecCharacters;
        for(auto i = characters.begin(); i != characters.end(); ++i)
        {

                pair<char, int> temp;
                temp.first = i->first;
                temp.second = i->second;
                vecCharacters.push_back(temp);
        }

	vector<pair<string,int>> vecNumbers;
        for(auto i = numbers.begin(); i != numbers.end(); ++i)
        {
                pair<string, int> temp;
                temp.first = i->first;
                temp.second = i->second;
                vecNumbers.push_back(temp);
        }

	
				
	sort(vecWords.begin(), vecWords.end(), helpSortWord); //sorts the vector values in descending order
	sort(vecCharacters.begin(), vecCharacters.end(), helpSortChar);
	sort(vecNumbers.begin(), vecNumbers.end(), helpSortWord);

	sort(vecWords.begin(), vecWords.end(), SortedWords);
	sort(vecNumbers.begin(), vecNumbers.end(), SortedNums);
	
	int stop = 0;
	cout << "Total " << vecCharacters.size() << " different characters, 10 most used characters:" << endl;
	for(int i = 0; i < vecCharacters.size(); i++)
	{
		if(stop ==10)
		break;
		
		if(i != vecCharacters.size()-2)
		{
			if(vecCharacters[i].second == vecCharacters[i+1].second)
			{
				if(int(vecCharacters[i].first) > int(vecCharacters[i+1].first))
				{	
					auto temp = vecCharacters[i];
					vecCharacters[i] = vecCharacters[i+1];
					vecCharacters[i+1] = temp;
					
					int count = i;
					while(count != vecCharacters.size()-2 && vecCharacters[count].second == vecCharacters[count+1].second)
					{
						if(int(vecCharacters[count].first) > int(vecCharacters[count+1].first))
                        			{
                                        		auto temp = vecCharacters[count];
                                        		vecCharacters[count] = vecCharacters[count+1];
                                        		vecCharacters[count+1] = temp;
						}
						
						count++;
					}
				}	
			}
		}
		
		cout << "No. " << i << ": " << vecCharacters[i].first << "\t\t" << vecCharacters[i].second << endl;
		stop++;
	}
	cout << "\n";

	stop  = 0;
	cout << "Total " << vecWords.size() << " different words, 10 most used words:" << endl;	
	for(int i =0; i < vecWords.size(); i++)
        {
		if(stop == 10)
		break;
                cout << "No. " << i << ": " << vecWords[i].first << "\t\t" << vecWords[i].second << endl;
		stop++;
        }
	
	stop = 0;
	cout << "\nTotal " << vecNumbers.size() << " different numbers, 10 most used numbers:" << endl;
	for(int i = 0; i < vecNumbers.size(); i++)
	{
		if(stop == 10)
		break;
		cout << "No. " << i << ": " << vecNumbers[i].first << "\t\t" << vecNumbers[i].second << endl;
		stop++;
	}


	cout << "\n";
	return 0;
}
