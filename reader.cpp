#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unistd.h>

class Reader
{	
	bool isGameOver;
	std::vector<int> cards;
	int prev_poem_index;
	int curr_poem_index;
public:
	Reader()
	{
		cards.resize(100);
		for(int i = 0; i < 100; i++)
		{
			cards[i] = i+1;
		}
		prev_poem_index = -1;
		curr_poem_index = 0;
		isGameOver = false;
	}
	void shuffle()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::shuffle(cards.begin(), cards.end(), gen);
		prev_poem_index = -1;
		curr_poem_index = 0;
	}
	void play()
	{
		//std::cout<<"Number: "<<curr_poem_index<<"\n";
		if(prev_poem_index == -1)
		{
			std::cout<<"inaba_0_01.ogg\n";
			std::cout<<"inaba_0_02.ogg\n";
			std::cout<<"inaba_"<<cards[curr_poem_index]<<"_01.ogg\n";
			std::cout<<"*************************\n";
			prev_poem_index = curr_poem_index;
			curr_poem_index = curr_poem_index + 1;
		}
		else if(prev_poem_index == 98)
		{
			std::cout<<"inaba_"<<cards[prev_poem_index]<<"_02.ogg\n";
                        std::cout<<"inaba_"<<cards[curr_poem_index]<<"_01.ogg\n";
			sleep(5);
			std::cout<<"inaba_"<<cards[curr_poem_index]<<"_02.ogg\n";
                        std::cout<<"*************************\n";
                        isGameOver = true;	
		}
		else
		{
			std::cout<<"inaba_"<<cards[prev_poem_index]<<"_02.ogg\n";
			std::cout<<"inaba_"<<cards[curr_poem_index]<<"_01.ogg\n";
			std::cout<<"*************************\n";
			prev_poem_index = curr_poem_index;
			curr_poem_index = curr_poem_index + 1;
		}
	}
};


int main()
{
	Reader reader;
	reader.shuffle();
	for(int i = 0; i < 100; i++)
	{
		reader.play();
	}
	return 0;
}
