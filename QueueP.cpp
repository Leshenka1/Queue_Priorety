#include "QueueP.h"

QueueP::QueueP()
{
	front = nullptr;
	for (int i = 0; i < count_p; i++)
	{
		rears[i] = nullptr;
		priority_size[i] = 0;
	}
}

QueueP::QueueP(const QueueP& other)
{
	front = nullptr;
	for (int i = 0; i < count_p; i++)
	{
		rears[i] = nullptr;
		priority_size[i] = 0;
	}
	clone(other);
}

bool QueueP::empty() const
{
	return (front == nullptr);
}

int QueueP::get_front_element() const
{
	if (!empty()) {
		return front->value;
	}
	else {
		throw exception("error: it's empty\n");
	}
}

string QueueP::get_front_priority() const
{
	if (!empty()) {
		if (int(front->priority) == 0) {
			return "LOW";
		}
		else if (int(front->priority) == 1) {
			return "MEDIUM";
		}
		else if (int(front->priority) == 2) {
			return "HIGH";
		}
	}
	else {
		throw exception("error: it's empty\n");
	}
}

void QueueP::erase()
{
	while (pop())
	{

	}
}

QueueP& QueueP::operator=(const QueueP& other)
{
	if (&other == this)
	{
		return *this;
	}
	else
	{
		erase();
		clone(other);
		return *this;
	}
}

QueueP::QueueP(QueueP&& tmp) noexcept
{
	replace(front, tmp.front);
	for (int i = 0; i < count_p; i++)
	{
		replace(rears[i], tmp.rears[i]);
		priority_size[i] = tmp.priority_size[i];
	}
}

QueueP& QueueP::operator=(QueueP&& other) noexcept
{
	if (&other == this)
	{
		return *this;
	}
	replace(front, other.front);
	for (int i = 0; i < count_p; i++)
	{
		replace(rears[i], other.rears[i]);
		priority_size[i] = other.priority_size[i];
	}
	return *this;
}

int QueueP::get_length() const
{
	int totalSize = 0;
	for (int i = 0; i < count_p; i++)
	{
		totalSize += priority_size[i];
	}
	return totalSize;
}

void QueueP::replace(QPItem*& a, QPItem*& b)
{
	a = b;
	b = nullptr;
}

bool QueueP::pop()
{
	if (get_length() > 0)
	{
		QPItem* temp = front;
		front = front->next;
		priority_size[int(temp->priority)]--;
		if (rears[int(temp->priority)] == temp)
		{
			rears[int(temp->priority)] = nullptr;
		}
		delete temp;
		return true;
	}
	else
	{
		return false;
	}
}

int QueueP::get_priority_length(PRIORITY priority) const
{
	return priority_size[int(priority)];
}

void QueueP::insert(int value, PRIORITY priority)
{
	if (int(priority) >= count_p || int(priority) < 0)
	{
		throw exception("error: incorrect priority\n");
	}
	QPItem* newItem = new QPItem(value, priority, nullptr);
	if (empty())
	{
		front = newItem;
	}
	else
	{
		if (priority > front->priority)
		{
			newItem->next = front;
			front = newItem;
		}
		else
		{
			if (get_priority_length(priority) != 0)
			{
				QPItem* rear = rears[int(priority)];
				newItem->next = rear->next;
				rear->next = newItem;
			}
			else
			{
				QPItem* rearMin = front;
				for (int i = int(priority) + 1; i < count_p; i++)
				{
					if (rears[i] != nullptr)
					{
						rearMin = rears[i];
						break;
					}
				}
				rearMin->next = newItem;
				QPItem* rearNext = nullptr;
				if (int(priority) >= 1)
				{
					rearNext = rears[int(priority) - 1];
				}
				newItem->next = rearNext;
			}
		}

	}
	rears[int(priority)] = newItem;
	priority_size[int(priority)]++;
}

void QueueP::insert(QPItem* qpItem)
{
	insert(qpItem->value, qpItem->priority);
}

void QueueP::clone(const QueueP& other)
{
	if (other.get_length() > 0)
	{
		QPItem* temp = other.front;
		while (temp->next != nullptr)
		{
			insert(temp);
			temp = temp->next;
		}
	}
}

ostream& QueueP::write_on_stream(ostream& s)
{
	if (!empty())
	{
		QPItem* tmp = front;
		while (tmp != nullptr) {
			s << tmp->value << endl;
			if (tmp->next != nullptr) {
				s << "," << endl;
			}
			tmp = tmp->next;
		}
	}
	else
	{
		s << "EMPTY.\n";
	}
	return s;
}

QueueP::~QueueP()
{
	erase();
}