#include "QueueP.h"
using namespace std;

#include <conio.h>

const int ESC = 27;

int main()
{
	setlocale(LC_ALL, "ru");

	PRIORITY temp_p;

	char working_queue = 0;

	QueueP* temp = new QueueP();
	QueueP* queue1 = new QueueP();
	QueueP* queue2 = new QueueP();

	while (true)
	{
		int value;
		int priority;
		char action = 0;

		cout << "Главное меню :\n" <<
			"Нажать 1 - Выбрать очередь для работы.\n" <<
			"Нажать 2 - Обменять значения очередей.\n" <<
			"Нажать Esc - Выйти из консольного приложения.\n";
		action = _getche();
		switch (action)
		{
		case '1':
			system("cls");
			cout << "Меню очередей :\n"
				<< "Ввести 1 - Выбрать очередь №1\n"
				<< "Ввести 2 - Выбрать очередь №2\n"
				<< "Ввести Esc - Перейти в главное меню\n";
			working_queue = _getche();
			switch (working_queue)
			{
			case '1':
				system("cls");
				temp = queue1;
				break;
			case '2':
				system("cls");
				temp = queue2;
				break;
			case ESC:
				system("cls");
				temp = queue2;
				break;
			default:
				cout << "Неверный номер.\n";
				system("pause");
				system("cls");
				break;
			}
			if (working_queue == '1' || working_queue == '2')
			{

				cout << "Меню операций с очередью :\n"
					<< "Ввод 1 - Проверка очереди на пустоту.\n"
					<< "Ввод 2 - Получить информацию о голове очереди.\n"
					<< "Ввод 3 - Удаление последнего элемента(pop).\n"
					<< "Ввод 4 - Вставка элемента.\n"
					<< "Ввод 5 - Получение общего количества элементов.\n"
					<< "Ввод 6 - Получени информации о конкретном приоритете.\n"
					<< "Ввод Esc - Возвращение в главное меню.\n";

				action = _getche();
				switch (action)
				{
				case '1':
					cout << "\n";
					temp->write_on_stream(cout);
					system("pause");
					system("cls");
					break;
				case '2':
					cout << "\n";
					try
					{
						cout << temp->get_front_element() << " ";
						cout << temp->get_front_priority() << endl;
					}
					catch (exception e)
					{
						cout << e.what();
					}
					system("pause");
					system("cls");
					break;
				case '3':
					temp->pop();
					cout << "Операция выполнена.\n";
					system("pause");
					system("cls");
					break;
				case '4':
					system("cls");
					cout << "Введите значение элемента для вставки.\n";
					cin >> value;
					cout << "Выберите приоритет данного элемента\nВведите 1 - для выбора LOW\nВведите 2 - для выбора MEDIUM\nВведите 3 - для выбора HIGH\n";
					cin >> priority;
					if (priority == 1) temp_p = PRIORITY::LOW;
					else if (priority == 2) temp_p = PRIORITY::MEDIUM;
					else if (priority == 3) temp_p = PRIORITY::HIGH;
					else
					{
						cout << "Приоритет выбран неверно\n";
						system("pause");
						system("cls");
						break;
					}
					temp->insert(value, temp_p);
					cout << "Элемент вставлен.\n";
					system("pause");
					system("cls");
					break;
				case '5':
					system("cls");
					cout << "Общее количество элементов = " << temp->get_length() << endl;
					system("pause");
					system("cls");
					break;
				case '6':
					system("cls");
					cout << "Выберите приоритет по которому хотите получить информацию\nВведите 1 - для выбора LOW\nВведите 2 - для выбора MEDIUM\nВведите 3 - для выбора HIGH\n";
					cin >> priority;
					if (priority == 1) temp_p = PRIORITY::LOW;
					else if (priority == 2) temp_p = PRIORITY::MEDIUM;
					else if (priority == 3) temp_p = PRIORITY::HIGH;
					else
					{
						cout << "Неверный приоритет\n";
						system("pause");
						system("cls");
						break;
					}
					cout << "Количество элементов с данным приоритетом = " << temp->get_priority_length(temp_p);
					system("pause");
					system("cls");
					break;
				case ESC:
					system("cls");
					break;
				default:
					break;
				}
			}
			else
			{
				break;
			}
			break;

		case '2':
			temp = new QueueP(move(*queue1));
			*queue1 = move(*queue2);
			*queue2 = move(*temp);
			cout << "Успешно выполнено.\n";
			system("pause");
			system("cls");
			break;

		case ESC:
			cout << "HРабота завершена.";
			return 0;
			break;
		default:
			break;
		}
	}
}
