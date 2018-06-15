#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

class object
{
public:
	object();
	virtual ~object();
	void add_child(object* obj);
	bool remove_child(object* obj);

	bool operator==(const object& obj);
	bool operator!=(const object& obj);

	bool think();

	virtual bool think_more();

	unsigned long id() const;

	void empty();
private:
	unsigned long _id;
	static unsigned long _id_counter;
	std::vector<object*> _children;

	void remove_child_by_index(unsigned& i);
};

#endif
