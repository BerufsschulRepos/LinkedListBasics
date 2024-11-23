#include <iostream>

using namespace std;

struct List;
struct Element;

struct Element {
	string data;
	Element* prevElement;
	Element* nextElement;

	Element(string data) {
		this->data = data;
		prevElement = nullptr;
		nextElement = nullptr;
	}

	int compare(Element* elementToCompare) {
		return strcmp(this->data.c_str(), elementToCompare->data.c_str());
	}

	int compareData(string data) {
		return strcmp(this->data.c_str(), data.c_str());
	}
};

struct List {

	int size;
	Element* head;
	Element* lastElement;

	List() {
		size = 0;
		head = nullptr;
		lastElement = nullptr;
	}

	void addElement(string data) {

		Element* newElement = new Element(data);

		if (head == NULL) {
			head = newElement;
			lastElement = newElement;
		}
		else {
			newElement->prevElement = lastElement;
			lastElement->nextElement = newElement;
			lastElement = newElement;
		}

		cout << "INFO: addElement(" << data << ") -> Element [" << data << "] wurde hinzugefuegt" << endl;
		size++;
	}

	void removeElementByIndex(int index) {

		Element* elementToRemove = findElementByIndex(index);

		if (elementToRemove == nullptr) {
			cout << "FEHLER: removeElementByIndex(" << index << ") -> Gesuchtes Element existiert nicht" << endl;
		}
		else {
			removeElement(elementToRemove);
			cout << "INFO: removeElementByIndex(" << index << ") -> Element wurde geloescht" << endl;
		}
	}

	void removeElementByData(string data) {

		Element* elementToRemove = findElementByData(data);

		if (elementToRemove == nullptr) {
			cout << "FEHLER: removeElementByData(" << data << ") -> Gesuchtes Element existiert nicht" << endl;
			return;
		}
		else {
			removeElement(elementToRemove);
			cout << "INFO: removeElementByData(" << data << ") -> Element [" << data << "] wurde geloescht" << endl;
		}
	}

	void removeElement(Element* elementToRemove) {

		// 1. Fall: Loeschen des 'ersten' Elementes der Liste
		if (elementToRemove == head) {
			head = elementToRemove->nextElement;

			if (head != nullptr) {
				head->prevElement = nullptr;
			}
		}

		// 2. Fall: Loeschen des 'letzten' Elements der Liste
		else if (elementToRemove == lastElement) {
			lastElement = elementToRemove->prevElement;

			if (lastElement != nullptr) {
				lastElement->nextElement = nullptr;
			}
		}

		// 3. Fall: Loeschen eines Elementes 'innerhalb' der Liste
		else {
			elementToRemove->prevElement->nextElement = elementToRemove->nextElement;
			elementToRemove->nextElement->prevElement = elementToRemove->prevElement;
		}

		// !! Speicher des 'elementToRemove' freigeben !!
		delete elementToRemove;
		size--;
	}

	void updateElementByIndex(int index, string newData) {

		Element* elementToUpdate = findElementByIndex(index);
		string oldData = elementToUpdate->data;

		if (elementToUpdate == nullptr) {
			cout << "FEHLER: updateElementByIndex(" << index << "," << newData << ") -> Gesuchtes Element existiert nicht" << endl;
		}
		else {
			elementToUpdate->data = newData;
			cout << "INFO: updateElementByIndex(" << index << "," << newData << ") -> Element wurde aktualisiert: [" << oldData << "] -> [" << newData << "]" << endl;
		}
	}

	void updateElementByData(string oldData, string newData) {

		Element* elementToUpdate = findElementByData(oldData);

		if (elementToUpdate == nullptr) {
			cout << "FEHLER: updateElementByData(" << oldData << "," << newData << ") -> Gesuchtes Element existiert nicht" << endl;
		}
		else {
			elementToUpdate->data = newData;
			cout << "INFO: updateElementByData(" << oldData << "," << newData << ") -> Element wurde aktualisiert: [" << oldData << "] -> [" << newData << "]" << endl;
		}
	}

	Element* findElementByIndex(int index) {

		Element* wantedElement = nullptr;

		if (index > size || index < 1) {
			cout << "FEHLER: findElementByIndex(" << index << ") -> Index existiert nicht" << endl;
		}
		else {
			int i = 1;
			wantedElement = head;

			while (i < index) {
				wantedElement = wantedElement->nextElement;
				i++;
			}
		}

		return wantedElement;
	}

	Element* findElementByData(string data) {

		Element* wantedElement = nullptr;
		Element* currentElement = head;

		if (head == nullptr) {
			cout << "FEHLER: findElementByData(" << data << ") -> Liste ist leer" << endl;
		}
		else {
			while (currentElement != nullptr) {
				if (currentElement->compareData(data) == 0) {
					wantedElement = currentElement;
					break;
				}
				else {
					currentElement = currentElement->nextElement;
				}
			}
		}

		if (wantedElement == nullptr) {
			cout << "FEHLER: findElementByData(" << data << ") -> Element nicht gefunden" << endl;
		}

		return wantedElement;
	}

	void printList() {

		Element* currentElement = head;

		cout << endl << "---- printList() ----" << endl;

		for (int i = 1; currentElement != nullptr; i++) {
			cout << "[" << i << "] " << currentElement->data << endl;
			currentElement = currentElement->nextElement;
		}

		cout << "---------------------" << endl;
	}
};

int main() {
	List* meineListe = new List;

	meineListe->addElement("1337");
	meineListe->addElement("6969");
	meineListe->addElement("1312");
	meineListe->addElement("47441");

	meineListe->printList();

	meineListe->removeElementByIndex(3);

	meineListe->updateElementByIndex(3, "666");

	meineListe->printList();

	meineListe->removeElementByIndex(2);

	meineListe->updateElementByData("666", "999");

	meineListe->printList();

	meineListe->removeElementByData("1337");

	meineListe->printList();

	return 0;

}