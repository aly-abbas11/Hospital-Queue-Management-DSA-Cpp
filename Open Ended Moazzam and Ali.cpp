#include<iostream>
using namespace std;

class Case {

public:

	string department;
	string type;
	Case* next;
	int arrivalTime;

	Case(string dep, string typ, int tim) {
		department = dep;
		type = typ;
		arrivalTime = tim;
		next = NULL;
	}
};

int get_priority(string department, string type) {
	int dep_priority = (department == "Emergency") ? 0 : 1;
	int type_priority;

	if (type == "VIP") type_priority = 0;
	else if (type == "Elderly") type_priority = 1;
	else type_priority = 2;

	return dep_priority * 10 + type_priority;
}

class Department {
private:
	Case* head;
	Case* tail;
	string dep_name;

public:
	Department(string dep) {
		head = NULL;
		tail = NULL;
		dep_name = dep;
	}

	void add_patient(string typ, int tim) {
		Case* new_case = new Case(dep_name, typ, tim);

		if (head == NULL) {
			head = new_case;
			tail = new_case;
			return;
		}

		int new_priority = get_priority(dep_name, typ);

		if (new_priority < get_priority(head->department, head->type) ||
		    (new_priority == get_priority(head->department, head->type) && tim < head->arrivalTime)) {
			new_case->next = head;
			head = new_case;
			return;
		}

		Case* current = head;
		while (current->next != NULL) {
			int current_priority = get_priority(current->next->department, current->next->type);
			if (new_priority < current_priority ||
			    (new_priority == current_priority && tim < current->next->arrivalTime)) {
				break;
			}
			current = current->next;
		}
		new_case->next = current->next;
		current->next = new_case;

		if (new_case->next == NULL) tail = new_case;
	}

	void call_patient() {
		if (head == NULL) {
			cout << "\nNo patients to call.\n";
			return;
		}
		Case* temp = head;
		head = head->next;
		cout << "\nCalling Patient - Department: " << temp->department
		     << ", Type: " << temp->type
		     << ", Arrival Time: " << temp->arrivalTime << endl;
		delete temp;
	}

	void display() {
		Case* temp = head;
		if (temp == NULL) {
			cout << "\nNo patients in " << dep_name << " department.\n";
			return;
		}
		cout << "\nPatients in " << dep_name << " Department:\n";
		while (temp != NULL) {
			cout << "Patient Department: " << temp->department << endl;
			cout << "Patient Type: " << temp->type << endl;
			cout << "Time of Arrival: " << temp->arrivalTime << endl << endl;
			temp = temp->next;
		}
	}
};

int main() {
	Department d1("Emergency");
	d1.add_patient("Normal", 10);
	d1.add_patient("Elderly", 120);
	d1.add_patient("VIP", 140);

	d1.display();
	d1.call_patient();
	d1.display();

	Department d2("OPD");
	d2.add_patient("VIP", 20);
	d2.add_patient("Normal", 5);
	d2.add_patient("Elderly", 15);

	d2.display();
	d2.call_patient();
	d2.display();

	return 0;
}

