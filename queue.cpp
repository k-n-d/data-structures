#include <iostream>
#include <vector>

using std::cout;
using std::endl;

template <class T>
struct link {
private:
	T data;
	link* front;
	link* back;
	~link()
	{
		cout << "link with data member " << data << " is being destroyed! Bye :(\n";
	}
	template <class L>
	friend class queue;
};

template <class T>
class queue {
private:
	link<T>* start;
	link<T>* end;
public:
	queue() :start(NULL), end(NULL) {}
	queue(T dat)
	{
		link<T>* temp = new link<T>;
		temp->data = dat;
		temp->front = temp->back = NULL;
		start = end = temp;
	}

	void push(T dat)
	{
		link<T>* temp = new link<T>;
		temp->data = dat;
		temp->front = start;
		if (start)
			start->back = temp;
		temp->back = NULL;
		start = temp;
		if (!end)
			end = temp;
	}

	T pop()
	{
		if (end) {
			link<T>* temp = end;
			T data = temp->data;
			end = temp->back;
			if (end)
				end->front = NULL;
			else
				start = NULL;
			delete temp;
			return data;
		}
		else {
			return 0;
		}
	}
	
	bool isEmpty() {
		return (start || end) ? false : true;
	}

	~queue()
	{
		if (start && end) {
			link<T>* fwd = start->front;
			while (fwd) {
				delete start;
				start = fwd;
				fwd = start->front;
			}
			delete start;
		}
		else if (start || end) {
			cout << "The queue is corrupted!\n";
		}
	}

};

int main() {
	queue<float> test(7.9F);
	test.push(1.1F);
	test.push(2.2F);
	test.push(3.3F);
	while (!(test.isEmpty())) {
		cout << test.pop() << endl;
	}

	{
		queue<int> test2;
		test2.push(4);
		test2.push(5);
		test2.push(6);
	}
	return 0;
}