#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
void data( stringstream& dat , int& year, int& month, int& day) {
	dat >> year;
	dat.ignore(1);
	dat >> month;
	dat.ignore(1);
	dat >> day;
}
void is_number(const string& date) {
	for (auto i = date.begin(); i != date.end(); ++i) {

		if (!isdigit(*i) && *i != 45 && *i != 43) {
			string buf = "Wrong date format: " + date;
			throw runtime_error(buf);
		}
	}
}
struct Day {
	int value;
	explicit Day(int new_value) {
		if (new_value > 31 || new_value < 1) {
			string buf = "Day value is invalid:" + to_string(new_value);
			throw runtime_error(buf);
		} else value = new_value;
	}
};
struct Year {
	int value;
	explicit Year(int new_value) {

		value = new_value;
	}
};
struct Month {
	int value;
	explicit Month(int new_value) {
		if (new_value > 12 || new_value < 1) {
			string buf = "Month value is invalid: " + to_string(new_value);
			throw runtime_error(buf);
		} else value = new_value;
	}
};
struct Dates {
	int day, month, year;
	Dates(Year year_one, Month month_one, Day day_one) {
		day = day_one.value;
		month = month_one.value;
		year = year_one.value;
	}

};

class BaseData {
public:
	vector<string> Find(const string& date) {
		is_number(date);
		stringstream dat;
		dat << date;
		int year, month, day;
		data(dat,year,month,day);
		vector<string> events;
		if (calendar_of_dates.count({ Year{ year }, Month{ month }, Day{ day } }) == 0) {
			events.push_back("Date not found");
			return events;
		}
		else {
			for(const auto& item: calendar_of_dates[{ Year{ year }, Month{ month }, Day{ day } }]) {
				events.push_back( item);
			}
			return events;
		}

	}
	void Add(const string& date,const string& event) {
		is_number(date);
		stringstream dat;
		dat << date;
		int year,month, day;
		string y, m, d;
		data(dat, year, month, day);
		if (!binary_search(calendar_of_dates[{Year{ year }, Month{ month }, Day{ day }}].begin(), calendar_of_dates[{Year{ year }, Month{ month }, Day{ day }}].end(),event)){
			calendar_of_dates[{Year{ year }, Month{ month }, Day{ day }}].push_back(event);
		}
		sort(calendar_of_dates[{Year{ year }, Month{ month }, Day{ day }}].begin(), calendar_of_dates[{Year{ year }, Month{ month }, Day{ day }}].end());
	}
	void Print() const {
		for (const auto& i : calendar_of_dates) {
			cout << setfill('0');
			cout << setw(4) << i.first.year << '-';
			cout << setfill('0');
			cout << setw(2) << i.first.month << '-';
			cout << setfill('0');
			cout << setw(2) << i.first.day << " ";
			for (const auto& j : i.second) {
				cout << j << " ";
			}
			cout << endl;
		}

	}
	int DelDate(const string& date) {
		is_number(date);
		stringstream dat;
		dat << date;
		int year, month, day;
		data(dat, year, month, day);
		int size = calendar_of_dates[{Year{ year }, Month{ month }, Day{ day }}].size();
		calendar_of_dates.erase({ Year{ year }, Month{ month }, Day{ day } });
		return size;
	}
	bool DelEvent(const string& date, const string& event) {
		is_number(date);
		stringstream dat;
		dat << date;
		int year, month, day;
		data(dat, year, month, day);
		if (calendar_of_dates.count({ Year{ year }, Month{ month }, Day{ day } }) == 0) {
			return 0;
		}
		else {
			vector<string>::iterator itr = find(calendar_of_dates[{ Year{ year }, Month{ month }, Day{ day } }].begin(), calendar_of_dates[{ Year{ year }, Month{ month }, Day{ day } }].end(), event);
			if (itr != calendar_of_dates[{ Year{ year }, Month{ month }, Day{ day } }].end()){
			calendar_of_dates[{ Year{ year }, Month{ month }, Day{ day } }].erase(itr);
			return 1;
			}
			else {
				return 0;
			}
		}
	}
private:
	map<Dates,vector<string>> calendar_of_dates;
};
void command(const string& cm, BaseData& calendar_new) {
	if (cm == "Add") {
		string date, event;
		cin >> date >> event;
		calendar_new.Add(date,event);
	}
	else if (cm == "Find") {
		string date;
		cin >> date;
		for (const auto& item : calendar_new.Find(date)) {
			cout << item << endl;
		};
	}
	else if (cm == "Print") {
		calendar_new.Print();
	}
	else if (cm == "Del") {
		string date, event;
		cin >> date;
		if (cin.peek() == ' ') {
			cin.ignore(1);
		}
		getline(cin, event, '\n');
		if (event == "") {
			cout << "Deleted " << calendar_new.DelDate(date) << " events" << endl;
		}
		else {
			if (calendar_new.DelEvent(date,event)) {
				cout << "Deleted successfully" << endl;
			}
			else {
				cout << "Event not found" << endl;
			}
		}
	}
	else {
			string buf = "Unknown command: " + cm;
			throw runtime_error(buf);
	}
}
bool operator<(const Dates& one, const Dates& two) {
	int first = one.day + one.month * 31 + one.year * 372;
	int second = two.day + two.month * 31 + two.year * 372;
	return first < second;
}

int main() {
	BaseData c;
	while (2 > 1) {
		try {
			string Command;

			cin >> Command;
			command(Command,c);
		}
		catch(exception& ex)
		{
			cout << ex.what();
 			return 0;
		}
	
	}
}
