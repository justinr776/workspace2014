class SimpleDate {
public:
	int getMonth() const;
	int getDay() const;
	int getYear() const;
	int dayOfWeek();
	int compareTo(SimpleDate* other);
	SimpleDate daysFromNow(int n); // throw std::invalid_agument;
	int ordinalDate();
	static const int MIN_YEAR;
	bool isLeapYear(int year);
	bool isLeapYear();
	SimpleDate(int monthin, int dayin, int yearin);

private:
	int month =0;
	int day;
	int year;
	int daysInYear(int year);
	static const int daysInMonths[];
	static const int DAYS_THUS_FAR[];
	static const int NUM_MONTHS;
	static int daysInMonth(int month, int year);
	static bool isValidDate(int month, int day, int year);
	SimpleDate nextDate();

};
