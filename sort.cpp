#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;
void insertionSort(vector<int>&);
vector<int> generateRandom(int);
void printVector(vector<int>);
void opencvShow(vector<int>, int, int);
const int NUM=100;
int compN=1;

int main(){
	srand(time(NULL));
	vector<int> A;
	A = generateRandom(NUM);   //generate 100 random number between 1~100
	opencvShow(A, -1, -1);   //-1 means no change index and compare index
	insertionSort(A);
	
	return 0;
}

/*
 * generate n random number between 1~n
*/
vector<int> generateRandom(int n){
	vector<int> tmp;
	for(int i=1; i<=n; i++){   //initial
		tmp.push_back(i);
	}
	random_shuffle(tmp.begin(), tmp.end());   //random shuffle
	return tmp;
}

/*
 * insertion sort
*/
void insertionSort(vector<int> &A){
	compN=0;
	int key, i;
	for(int j=1; j<A.size(); j++){
		key = A[j];
		i = j-1;
		++compN;
		opencvShow(A, i, j);
		while(i>=0 && A[i]>key){
			++compN;   //add the compare
			A[i+1] = A[i];
			i = i-1;
			opencvShow(A, i, j);
		}
		A[i+1] = key;
	}
}

/*
 * print out the vector
*/
void printVector(vector<int> A){
	for(vector<int>::iterator it=A.begin(); it!=A.end(); ++it)
		cout << " " << *it;
	cout << endl;
}

/*
 * use opencv to show the sort, 
 * the second parameter is the index when changing, the red color
 * the third parameter is the current index, the green color
*/
void opencvShow(vector<int> A, int change, int current){
	int HEIGHT=768, WIDTH=1024;
	Point s, t;   //the observation we want to see
	//set up the back frame
	Mat back = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);
	string compString;

	s.x=10;
	t.x=10;
	t.y=700;
	for(int i=0; i<NUM; i++){
		s.x+=10;
		t.x+=10;
		s.y=700-A[i]*6;
		if(i==current)
			rectangle(back, s, t, Scalar(0, 255, 0), 2, CV_AA, 0);
		else if(i==change)
			rectangle(back, s, t, Scalar(0, 0, 255), 2, CV_AA, 0);
		else
			rectangle(back, s, t, Scalar(255, 255, 255), 2, CV_AA, 0);
	}
	stringstream ss;
	ss << "comparison:" << compN;
	ss >> compString;
	putText(back, compString, Point(10, 30), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 2, CV_AA);
	imshow("result", back);
	if(waitKey(10) >= 0) return;
}
