#include<iostream>
#include<string>

using namespace std;

class Class {

	struct student {
		string name;
		float score;
	};

public:
	Class() {
		stu = new student[stuSize];
		max = min = 0;
		average = num = 0;
	}

	~Class() {
		delete[] stu;
	}

	bool input() {
		cout << "Please input the number of students" << endl;
		cin >> num;
		if (num == 0 || num > 30) {
			cout << "number error£¡" << endl;
			system("pause");
			return false;
		}

		for (int i = 0; i < num; i++) {
			cin >> stu[i].name >> stu[i].score;
		}
		return true;
	}

	void outputAverage() {

		for (int i = 0; i < num; i++) {
			average += stu[i].score;
		}
		average /= num;
		cout << "average:" << average << endl;
	}

	void outputMaxAndMin() {

		for (int i = 0; i < num; i++) {
			if (stu[i].score > stu[max].score)
				max = i;
			else if (stu[i].score < stu[min].score)
				min = i;
		}

		cout << "max:" << endl << "name:" << stu[max].name << " score:" << stu[max].score << endl;
		if (num > 1) {
			cout << "min:" << endl << "name:***** score:" << stu[min].score << endl;
		}
	}

private:
	const int stuSize = 30;

	student *stu;
	int max, min, num;
	float average;

};



int main(void) {

	Class aclass;

	aclass.input();
	aclass.outputAverage();
	aclass.outputMaxAndMin();

	system("pause");
	return 0;
}