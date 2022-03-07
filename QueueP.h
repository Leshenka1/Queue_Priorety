#pragma once

using namespace std;
#include <exception>
#include <string>
#include <iostream>

enum class PRIORITY {
	LOW = 0,
	MEDIUM,
	HIGH
};
const int count_p = 3;

class QueueP
{
private:

	struct QPItem
	{
		int value;
		PRIORITY priority;
		QPItem* next;
		QPItem(int value, PRIORITY priority, QPItem* next = nullptr)
		{
			this->value = value;
			this->priority = priority;
			this->next = next;
		}
	};

	QPItem* front;
	QPItem* rears[count_p];
	int priority_size[count_p];
	void insert(QPItem*);
	void erase();
	void replace(QPItem*& a, QPItem*& b);

public:
	QueueP();
	QueueP(const QueueP&);
	bool empty() const;
	int get_front_element() const;
	string get_front_priority() const;
	QueueP& operator = (const QueueP&);
	QueueP(QueueP&&) noexcept;
	QueueP& operator = (QueueP&&) noexcept;
	int get_length() const;
	int get_priority_length(PRIORITY priority) const;
	void insert(int value, PRIORITY priority);
	bool pop();
	void clone(const QueueP&);
	ostream& write_on_stream(ostream& s);
	~QueueP();
};