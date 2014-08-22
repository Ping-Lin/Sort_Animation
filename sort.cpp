#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <cmath>
#include <map>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;
void insertionSort(vector<int>&);
void merge(vector<int>&, int, int, int);
void mergeSort(vector<int>&, int, int);
vector<int> generateRandom(int);
void printVector(vector<int>);
void opencvShow(vector<int>, map<int, int>, int);
const int NUM=100;
const int DELAY=5;
int compN=1;
map<int, int> change;

int main(){
	srand(time(NULL));
	vector<int> A;
	
	/*/insertion sort
	compN=0;
	A = generateRandom(NUM);   //generate 100 random number between 1~100
	opencvShow(A, change, -1);   //-1 means no change index and compare index
	insertionSort(A);*/
	
	//merge sort
	compN=0;
	A = generateRandom(NUM);   //generate 100 random number between 1~100
	opencvShow(A, change, -1);   //-1 means no change index and compare index
	mergeSort(A,0,99);
	waitKey();
	
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
		change.clear();
		change[i]=1;
		++compN;   //add the compare
		opencvShow(A, change, j);
		while(i>=0 && A[i]>key){
			A[i+1] = A[i];
			i = i-1;
			change.clear();
			change[i]=1;
			++compN;   //add the compare
			opencvShow(A, change, j);
		}
		A[i+1] = key;
	}
}
/*
 * merge sort, using recursive function
*/
void mergeSort(vector<int> &A, int p, int r){
	if(p < r){
		int q = floor((p+r)/2);
		mergeSort(A, p, q);
		mergeSort(A, q+1, r);
		merge(A, p, q, r);
	}
}

void merge(vector<int> &A, int p, int q, int r){
	int n1 = q-p+1;
	int n2 = r-q;
	int L[n1+1], R[n2+1];
	for(int i=0; i<n1; i++)
		L[i] = A[p+i];
	for(int i=0; i<n2; i++)
		R[i] = A[q+i+1];
	
	L[n1] = 1e9;
	R[n2] = 1e9;
	int i=0, j=0;
	for(int k=p; k<=r; k++){
		change.clear();
		change[L[i]]=1;
		change[R[j]]=1;
		opencvShow(A, change, k);
		++compN;   //add the comparison
		if(L[i] <= R[j]){
			A[k] = L[i];
			++i;
		}
		else{
			A[k] = R[j];
			++j;
		}
		change.clear();
		change[L[i]]=1;
		change[L[j]]=1;
		opencvShow(A, change, k);
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
void opencvShow(vector<int> A, map<int, int> change, int current){
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
		else if(change[i]==1)
			rectangle(back, s, t, Scalar(0, 0, 255), 2, CV_AA, 0);
		else
			rectangle(back, s, t, Scalar(255, 255, 255), 2, CV_AA, 0);
	}
	stringstream ss;
	ss << "comparison:" << compN;
	ss >> compString;
	putText(back, compString, Point(10, 30), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 2, CV_AA);
	imshow("result", back);
	if(waitKey(DELAY) >= 0) return;
}
