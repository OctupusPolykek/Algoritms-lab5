#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Date
{
	short day;
	short month;
	short year;
	bool isCorrect();
};

bool Date::isCorrect()
{
	bool result = false;
	if ((day < 1) || (month < 1) || (year < 1))
		result = false;
	else {
		switch (month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
		{
			if ((day <= 31) && (day > 0))
				result = true;
			break;
		}

		case 4:
		case 6:
		case 9:
		case 11:
		{
			if ((day <= 30) && (day > 0))
				result = true;
			break;
		}

		case 2:
		{
			if (year % 4 != 0)
			{
				if ((day <= 28) && (day > 0))
					result = true;
			}
			else
				if (year % 400 == 0)
				{
					if ((day <= 29) && (day > 0))
						result = true;
				}
				else
					if ((year % 100 == 0) && (year % 400 != 0))
					{
						if ((day == 28) && (day > 0))
							result = true;
					}
					else
						if ((year % 4 == 0) && (year % 100 != 0))
							if ((day <= 29) && (day > 0))
								result = true;
			break;
		}

		default:
			result = false;
		}
	}
	return result;
}

struct Programer
{
	string secondname,
		name,
		thirdname,
		sex,
		nationality;
	Date birthday;
	string study;
	int number;
};

void taskEase18()
{
	cout << "\nTask 18 (ease)" << endl;
	/*"Програмист":
		фамилия; имя; отчество; пол национальность; дата рождения(год, месяц, число);
		образование; номер телефона. Вывести сведение о програмистаx, которым меньче 25 лет.*/

    ofstream structFile("taskEase18.txt");
	if (structFile.is_open())
	{
		structFile << "Сокил Михаил Игоревич м Украинец 4 8 2002 Высшее 0958553178\nБаранов Шарль Фёдорович м Украинец 4 8 1980 Высшее 0954894498";
		structFile.close();
	}

    ifstream file("taskEase18.txt");
    if (!file.is_open())
        cout << "Ошибка не удается считать с файла." << endl;
    else {
		int y = 1;

		string line,s;
		cout << "\nИсходные данные:" << endl;
		while (getline(file, line))
		{
			s += line + ' ';
			cout << line << endl;
		}
		file.close();

		for (int i = 0; i < s.length(); i++)//Сколько слов
		{
			if (s[i] == ' ')
				y++;
		}
		y = y / 10;

		Programer* programer = new Programer[y];//Генерирование

		istringstream iss(s);
		for (int i = 0; i < y; i++)
		{
			string secondname,
				name,
				thirdname,
				sex,
				nationality,
				study;
			Date birthday;
			int number;

			while (iss >> secondname >> name >> thirdname >> sex >> nationality >> birthday.day >> birthday.month >> birthday.year >> study >> number)//Заполнение
			{
					programer[i].secondname = secondname;
					programer[i].name = name;
					programer[i].thirdname = thirdname;
					programer[i].sex = sex;
					programer[i].nationality = nationality;

					programer[i].birthday.day = birthday.day;
					programer[i].birthday.month = birthday.month;
					programer[i].birthday.year = birthday.year;

					programer[i].study = study;
					programer[i].number = number;

					if (number > 0)
						break;
			}
		}file.close();

		Date nowday;
		do
		{
			cout << "\nВведите сегодняшнюю дату: ";
			cin.clear();
			cin.ignore(std::cin.rdbuf()->in_avail());
			cin >> nowday.day >> nowday.month >> nowday.year;

		} while (!nowday.isCorrect());

		string a;
		for (int i = 0; i < y; i++)
		{
			if (nowday.year - programer[i].birthday.year < 25)
				a += programer[i].secondname + ' ' + programer[i].name + ' ' + programer[i].thirdname + ' ' + programer[i].sex + ' ' + programer[i].nationality + ' ' + to_string(programer[i].birthday.day) + ' ' + to_string(programer[i].birthday.month) + ' ' + to_string(programer[i].birthday.year) + ' ' + programer[i].study + " 0" + to_string(programer[i].number) + '\n';
		}
		if (a.length() < 1)
			a = "Таких нету";

		ofstream structAnswer("taskEase18Answer.txt");
		if (structAnswer.is_open())
		{
			cout << "Ответ успешно записан." << endl;
			structAnswer << "Програмисты которым меньше 25 лет:\n" << a;
			structAnswer.close();
		}

		delete[] programer;//Удаление

	}
}

void taskMedium18()
{
	cout << "\nTask 18 (medium)\n" << endl;
	/*Дан файл f, компоменты которого являются действительными числами.
	  Найти наименьшее из значений компонент с чётными номерами.*/

	ofstream f("taskMedium18.txt");
	if (f.is_open())
	{
		f << "4 32 -32 2 -300 -321.32 311";
		f.close();
	}

	ifstream file("taskMedium18.txt");
	if (!file.is_open())
		cout << "Ошибка не удается считать с файла." << endl;
	else 
	{
		int y = 1;
		double x;

		string s;
		getline(file, s);

		file.seekg(0, ios::beg);
		file.clear();

		for (int i = 0; i < s.length(); i++)//Сколько чисел
		{
			if (s[i] == ' ')
				y++;
		}

		double* arr = new double[y];
		for (int i = 0; i < y; i++)//Запись
		{
			while (file >> x) 
			{
				arr[i] = x;
				break;
			}
		}

		cout << "Исходные данные: " << endl;//Вывод
		for (int i = 0; i < y; i++)
		{
			cout << arr[i] << " ";
		}
		double min = 0;
		bool minones = true;

		for (int i = 0; i < y; i++)//Нахождение минимального
		{
			if (i % 2 == 0 || i == 0);
			else
			{
				if (minones) 
				{
					min = arr[i];
					minones = false;
				}

				double newmin = arr[i];

				if (newmin < min)
					min = newmin;
			}
		}
		cout << "\n\nНаименьшое значение под четним номером: " << min << endl;
		ofstream fAnswer("taskMedium18Answer.txt");
		if (fAnswer.is_open())
		{
			cout << "\nОтвет успешно записан." << endl;
			fAnswer << "Наименьшое значение под четним номером: " << min;
			fAnswer.close();
		}

		delete[] arr;//Удаление
	}file.close();

}

void taskHard18()
{
	cout << "\nTask 18 (hard)\n" << endl;
	/*В файле хранится k матриц размерности n х m. Для каждой матрицы из 
	  файла вычислить сумму её отрицательных нечетных элементов. Все
	  матрицы с нечетными суммами записать в другой файл, заменив их в 
	  исходном файле единичными матрицами. Вывести на экран содержи-мое первого и второго файлов.*/

	ofstream MatrixFile("taskHard18.txt");
	if (MatrixFile.is_open())
	{
		MatrixFile << "-2 -2 1 -7\n-7 -9 -2 -12 \n-2 -6 -2 -4\n\n2 -1 -1 7\n7 9 -2 12 \n2 -6 2 4\n\n2 -2 1 7\n7 9 -2 12 \n2 -6 2 6";
		MatrixFile.close();
	}

	ifstream file("taskHard18.txt");
	if (!file.is_open())
		cout << "Ошибка не удается считать с файла." << endl;
	else
	{
		string line, s;
		int zindex = 1, yindex = 0, xindex = 0, num = 0;
		bool lineSpace = true;

		while (getline(file, line))//Количество матриц
		{
			s += line + ' ';
			if (line.length() == 0)
			{
				zindex++;
				lineSpace = false;
			}
			if (lineSpace)
				yindex++;

		}
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == ' ') 
				xindex++;
		}

		xindex++;//Количество знаков в матрице

		int*** arr = new int** [zindex];//Создание

		for (int i = 0; i < zindex; i++) {
			arr[i] = new int* [yindex];

			for (int j = 0; j < yindex; j++) {
				arr[i][j] = new int[xindex];
			}
		}

		istringstream iss(s);
		for (int z = 0; z < zindex; z++)//Заполнения
		{
			for (int y = 0; y < yindex; y++)
			{
				for (int x = 0; x < xindex; x++)
				{
					while (iss >> num)
					{
						arr[z][y][x] = num;
						break;
					}
				}
			}
		}

		cout << "Исходные данные:" << endl;
		for (int z = 0; z < zindex; z++)//Вывод
		{
			for (int y = 0; y < yindex; y++)
			{
				for (int x = 0; x < xindex; x++)
				{
					cout << arr[z][y][x] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}

		int* arrsum = new int[zindex];
		int sm = 0, i = 0;

		for (int z = 0; z < zindex; z++)
		{
			sm = 0;
			for (int y = 0; y < yindex; y++)
			{
				for (int x = 0; x < xindex; x++)
				{
					if (arr[z][y][x] % 2 == -1)
						sm += arr[z][y][x];
				}
			}
			arrsum[i] = sm;//Запись нечетных отрицательных элементов
			i++;
		}

		cout << "Сумма отрицательнчх нечетных элементов матриц:" << endl;
		for (int i = 0; i < zindex; i++)
		{
			cout << arrsum[i] << " ";
		}
		cout <<'\n'<<endl;

		string a1, a2;

		for (int i = 0; i < zindex; i++)//Из второго
		{
			if (arrsum[i] % 2 == -1)
			{
				for (int y = 0; y < yindex; y++)
				{
					for (int x = 0; x < xindex; x++)
					{
						a2 += to_string(arr[i][y][x]) + ' ';
						arr[i][y][x] = 1;
					}
					a2 += '\n';
				}
				a2 += '\n';
			}
		}

		for (int z = 0; z < zindex; z++)//Из первого
		{
			for (int y = 0; y < yindex; y++)
			{
				for (int x = 0; x < xindex; x++)
				{
					a1 += to_string(arr[z][y][x]) + ' ';
				}
				a1 += '\n';
			}
			a1 += '\n';
		}

		cout << "Из первого файла:\n" << a1 << "Из второго файла:\n" << a2;

		ofstream MatrixFile("taskHard18.txt");//a1
		if (MatrixFile.is_open())
		{
			MatrixFile << a1;
			MatrixFile.close();
		}

		if (a2.length() == 0)
			a2 = "Таких матриц нету.";
		ofstream fAnswer("taskHard18Answer.txt");//a2
		if (fAnswer.is_open())
		{
			cout << "Ответ успешно записан." << endl;
			fAnswer << a2;
			fAnswer.close();
		}

		for (int i = 0; i < zindex; i++)//Удаление
			for (int j = 0; j < yindex; j++) delete[] arr[i][j];
		for (int i = 0; i < zindex; i++) delete[] arr[i];
		delete[] arr;
	}file.close();
}

int main()
{
    setlocale(0, "ru");

    taskEase18();
	taskMedium18();
	taskHard18();

	return 0;
}
