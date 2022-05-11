#include <iostream>
#include <stack>
using namespace std;

struct Leksema //Структура, описывающая любое число или операцию
{
	char type; // 0 для чисел, "+" для операции сложения и т.д.
	double value; //Значение (только для чисел). У операций значение всегда "0"
};

bool Maths(stack <Leksema>& Stack_n, stack <Leksema>& Stack_o, Leksema& item) { //Математическая функция, которая производит расчеты
	//Функция имеет тип bool, чтобы при возникновении какой-либо ошибки возвращать "false"
	double a, b, c;
	a = Stack_n.top().value; //Берется верхнее число из стека с числами
	Stack_n.pop(); //Удаляется верхнее число из стека с числами
	switch (Stack_o.top().type) {  //Проверяется тип верхней операции из стека с операциями
	case '+': //Если тип верхней операции из стека с операциями сложение
		b = Stack_n.top().value;
		Stack_n.pop();
		c = a + b;
		item.type = '0';
		item.value = c;
		Stack_n.push(item); //Результат операции кладется обратно в стек с числами
		Stack_o.pop();
		break;

	case '-':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = b - a;
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;

	case '*':
		b = Stack_n.top().value;
		Stack_n.pop();
		c = a * b;
		item.type = '0';
		item.value = c;
		Stack_n.push(item);
		Stack_o.pop();
		break;

	case '/':
		b = Stack_n.top().value;
		if (a == 0) {
			cerr << "\nдЭбЫл\nНа ноль делить нельзя!\n";
			return false;
		}
		else {
			Stack_n.pop();
			c = (b / a);
			item.type = '0';
			item.value = c;
			Stack_n.push(item);
			Stack_o.pop();
			break;
		}
	default:
		cerr << "\nОшибка!\n";
		return false;
		break;
	}
	return true;
}

int getRang(char Ch) { //Функция возвращает приоритет операции: "1" для сложения и вычитания, "2" для умножения и деления и т.д.
	if (Ch == '+' || Ch == '-')return 1;
	if (Ch == '*' || Ch == '/')return 2;
	else return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "\n   Введи выраженние: ";
	char Ch; //Переменная, в которую будет записываться текущий обрабатываемый символ
	double value;
	bool flag = 1; //Нужен для того, чтобы программа смогла отличить унарный минус (-5) от вычитания (2-5)
	stack <Leksema> Stack_n; //Стек с числами
	stack <Leksema> Stack_o; //Стек с операциями
	Leksema item; //Объект типа Leksema
	while (1) {
		Ch = cin.peek(); //Смотрим на первый символ
		/*cout << Ch << endl;*/
		if (Ch == '\n')break; //Если достигнут конец строки, выходим из цикла
		if (Ch == ' ') { //Игнорирование пробелов
			cin.ignore();
			continue;
		}
		if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1) { //Если прочитано число
			cin >> value;
			item.type = '0';
			item.value = value;
			Stack_n.push(item); //Число кладется в стек с числами
			flag = 0;
			continue;
		}
		if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/') { //Если прочитана операция
			if (Stack_o.size() == 0) { //Если стек с операциями пуст
				item.type = Ch;
				item.value = 0;
				Stack_o.push(item); //Операция кладется в стек с операциями
				cin.ignore();
				continue;
			}
			if (Stack_o.size() != 0 && getRang(Ch) > getRang(Stack_o.top().type)) { //Если стек с операциями НЕ пуст, но приоритет текущей операции выше верхней в стеке с операциями
				item.type = Ch;
				item.value = 0;
				Stack_o.push(item); //Операция кладется в стек с операциями
				cin.ignore();
				continue;
			}
			if (Stack_o.size() != 0 && getRang(Ch) <= getRang(Stack_o.top().type)) {//Если стек с операциями НЕ пуст, но приоритет текущей операции ниже либо равен верхней в стеке с операциями
				if (Maths(Stack_n, Stack_o, item) == false) { //Если функция вернет "false", то прекращаем работу
					system("pause");
					return 0;
				}
				continue;
			}
		}
		if (Ch == '(') { //Если прочитана открывающаяся скобка
			item.type = Ch;
			item.value = 0;
			Stack_o.push(item); //Операция кладется в стек с операциями
			cin.ignore();
			continue;
		}
		if (Ch == ')') { //Если прочитана закрывающаяся скобка
			while (Stack_o.top().type != '(') {
				if (Maths(Stack_n, Stack_o, item) == false) { //Если функция вернет "false", то прекращаем работу
					system("pause");
					return 0;
				}
				else continue; //Если все хорошо	
			}
			Stack_o.pop();
			cin.ignore();
			continue;
		}
		else { //Если прочитан какой-то странный символ
			cout << "\nКакая то торобарщина\n";
			system("pause");
			return 0;
		}
	}
	while (Stack_o.size() != 0) { //Вызываем матем. функцию до тех пор, пока в стеке с операциями не будет 0 элементов
		if (Maths(Stack_n, Stack_o, item) == false) { //Если функция вернет "false", то прекращаем работу
			system("pause");
			return 0;
		}
		else continue; //Если все хорошо	
	}
	cout << "   Ответ: " << Stack_n.top().value << endl; //Выводим ответ
	return 0;
}