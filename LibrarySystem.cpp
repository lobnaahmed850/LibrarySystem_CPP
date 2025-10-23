#include <iostream>
using namespace std;
struct Node { //! This struct building LinkedList for Nodes of borrowed books by one user
	int bookID;
	Node* next;
	Node(int id) {
		bookID = id, next = nullptr;
	}
};

class Book {
private:
	int id, quantity, borrowed;
	string name;
public:
	Book() {
		id = -1, quantity = 0, borrowed = 0, name = "";
	}
	Book(int id_, string name_, int quantity_) { //!instead of readBook function
		id = id_, name = name_, quantity = quantity_, borrowed = 0;
	}
	int getID() {
		return id;
	}
	string getName() {
		return name;
	}
	int getQuantity() {
		return quantity;
	}
	int getBorrowed() {
		return borrowed;
	}
	int getAvailable() {
		return quantity - borrowed;
	}
	bool borrowCopy() {
		if (quantity <= borrowed)
			return false;
		borrowed++;
		return true;
	}
	void returnCopy() {
		if (borrowed)
			borrowed--;
	}
	void print() {
		cout << "ID = " << id << " ,name = " << name << " ,total quantity = " << quantity << " ,total borrowed = " << borrowed << "\n";
	}
};
class User { //! class contains LinkedList of borrowed books by user
private:
	int id, countBorrowed;
	string name;
	Node* head;
public:
	User() {
		id = -1, countBorrowed = 0, name = "", head = nullptr;
	}
	User(string name_, int id_) { //! instead of addUser function
		name = name_, id = id_, countBorrowed = 0, head = nullptr;
	}
	int getID() {
		return id;
	}
	string getName() {
		return name;
	}
	int getCount() {
		return countBorrowed;
	}
	void print() {
		cout << "User: " << name << " ,ID: " << id << " ,total borrowed books ids: ";
		Node* temp = head;
		while (temp != nullptr) {
			cout << temp->bookID << " ";
			temp = temp->next;
		}
		cout << "\n";
	}
	bool isEmpty() {
		return head == nullptr;
	}
	void borrowCopy(int ID) {
		Node* newnode = new Node(ID);
		if (isEmpty()) {
			newnode->next = nullptr;
			head = newnode;
		}
		else {
			newnode->next = head;
			head = newnode;
		}
		countBorrowed++;
	}
	bool returnCopy(int ID) {
		if (isEmpty())
			return false;
		Node* delptr;
		if (head->bookID == ID) {
			delptr = head;
			head = head->next;
			delete delptr;
			countBorrowed--;
			return true;
		}
		Node* prev = nullptr;
		delptr = head;
		while (delptr != nullptr && delptr->bookID != ID) {
			prev = delptr;
			delptr = delptr->next;
		}
		if (delptr == nullptr)
			return false;
		//! else: break the while loop because delptr->bookID == ID
		prev->next = delptr->next;
		delete delptr;
		countBorrowed--;
		return true;
	}
	bool searchBook(int ID) {
		bool isFound = false;
		Node* temp = head;
		while (temp != nullptr) {
			if (temp->bookID == ID) {
				isFound = true;
				break;
			}
			temp = temp->next;
		}
		return isFound;
	}

};

struct BookNode {
	Book data;
	BookNode* left;
	BookNode* right;
	BookNode(Book b) {
		data = b, left = right = nullptr;
	}
};
struct UserNode {
	User data;
	UserNode* left;
	UserNode* right;
	UserNode(User u) {
		data = u, left = right = nullptr;
	}
};

class BookManager {
private:
	BookNode* root;
	BookNode* insert(BookNode* r, Book b) {  //! creating new node at empty space
		if (r == nullptr) {
			BookNode* newnode = new BookNode(b);
			r = newnode;
		}
		else if (b.getID() < r->data.getID())
			r->left = insert(r->left, b);
		else if (b.getID() > r->data.getID())
			r->right = insert(r->right, b);
		return r;
	}
	void searchPre(BookNode* r, string prefix, bool& found) {
		if (r == nullptr) //! Base case: tree empty/ item not found
			return;
		string name = r->data.getName();
		if ((int)prefix.size() <= (int)name.size()) {
			bool ismatch = true;
			for (int i = 0; i < (int)prefix.size(); i++) {
				if (prefix[i] != name[i]) {
					ismatch = false;
					break;
				}
			}
			if (ismatch) {
				if (!found)
					cout << "Books found with such prefix (" << prefix << ") :\n";
				r->data.print();
				found = true;
			}
		}
		searchPre(r->left, prefix, found);
		searchPre(r->right, prefix, found);
	}
	void printIDOrder(BookNode* r) {
		if (r == nullptr) //! Base case: end of left/right branch
			return;
		printIDOrder(r->left);
		r->data.print();
		printIDOrder(r->right);
	}
	BookNode* searchId(BookNode* r, int id) {
		if (r == nullptr)
			return nullptr;
		if (id == r->data.getID())
			return r;
		else if (id < r->data.getID())
			return searchId(r->left, id);
		else
			return searchId(r->right, id);
	}
public:
	BookManager() {
		root = nullptr;
	}
	void addBooks(Book b) {
		root = insert(root, b);
	}

	void searchByPrefix(string prefix) {
		bool found = false;
		searchPre(root, prefix, found);
		if (!found)
			cout << "No books found with such prefix!\n";
	}
	void printByID() {
		printIDOrder(root);
	}
	Book* search(int id) {
		BookNode* found = searchId(root, id);
		if (found != nullptr)
			return &found->data;
		return nullptr;
	}
};
class UserManager {
private:
	UserNode* root;
	UserNode* insert(UserNode* r, User u) {
		if (r == nullptr) {
			UserNode* newnode = new UserNode(u);
			r = newnode;
		}
		else if (u.getID() < r->data.getID())
			r->left = insert(r->left, u);
		else if (u.getID() > r->data.getID())
			r->right = insert(r->right, u);
		return r;
	}
	void print(UserNode* r) { //! print users in ascending order of ID
		if (r == nullptr)
			return;
		print(r->left);
		r->data.print();
		print(r->right);
	}
	UserNode* searchUser(UserNode* r, int id) {
		if (r == nullptr)
			return nullptr;
		if (r->data.getID() == id)
			return r;
		if (r->data.getID() > id)
			return searchUser(r->left, id);
		return searchUser(r->right, id);
	}
	void printBorrowed(UserNode* r, int bookID, bool& isfound) {
		if (r == nullptr)
			return;
		if (r->data.searchBook(bookID)) {
			if (!isfound)
				cout << "Users borrowed this book:\n";
			cout << r->data.getName() << "\n";
			isfound = true;
		}
		printBorrowed(r->left, bookID, isfound);
		printBorrowed(r->right, bookID, isfound);
	}
public:
	UserManager() {
		root = nullptr;
	}
	void addUsers(User u) {
		root = insert(root, u);
	}
	void printUsers() {
		print(root);
	}
	User* search(int id) {
		UserNode* found = searchUser(root, id);
		if (found != nullptr)
			return &found->data;
		return nullptr;
	}
	void printWhoBorrowed(int bookID) {
		bool isfound = false;
		printBorrowed(root, bookID, isfound);
		if (!isfound)
			cout << "No users borrowed this book!\n";

	}
};

class BorrowingService {
private:
	BookManager* bookManager;
	UserManager* userManager;
public:
	BorrowingService(BookManager* bm, UserManager* um) {
		bookManager = bm, userManager = um;
	}
	void userBorrow(int userID, int bookID) {
		User* user = userManager->search(userID);
		Book* book = bookManager->search(bookID);
		if (user == nullptr) {
			cout << "User with ID " << userID << " not found!\n";
			return;
		}
		if (book == nullptr) {
			cout << "Book with ID " << bookID << " not found!\n";
			return;
		}
		if (book->borrowCopy())
			user->borrowCopy(bookID);
		else
			cout << "Sorry, no copies available!\n";
	}

	void userReturn(int userID, int bookID) {
		User* user = userManager->search(userID);
		Book* book = bookManager->search(bookID);
		if (user == nullptr) {
			cout << "User with ID " << userID << " not found!\n";
			return;
		}
		if (book == nullptr) {
			cout << "Book with ID " << bookID << " not found!\n";
			return;
		}
		if (user->returnCopy(bookID))
			book->returnCopy();
		else
			cout << "User didn't borrow this book!\n";
	}
	void printWhoBorrowed(int bookID) {
		userManager->printWhoBorrowed(bookID);
	}
};

class LibrarySystem {
private:
	BookManager bookManager;
	UserManager userManager;
	BorrowingService borrowingService;
public:
	LibrarySystem() : borrowingService(&bookManager, &userManager) {}
	int menu() {
		int choise = -1;
		while (choise == -1) {
			cout << "Enter your menu choise [1-9]: ";
			cin >> choise;
			if (!(choise >= 1 && choise <= 9)) {
				cout << "Invalid option. Try again!\n";
				choise = -1;
			}
		}
		return choise;
	}
	void run() {
		while (true) {
			int choise = menu();
			if (choise == 1) {
				int id, quantity;
				string name;
				cout << "Enter book info: ID & name & total quantity: ";
				cin >> id >> name >> quantity;
				bookManager.addBooks(Book(id, name, quantity));
			}
			else if (choise == 2) {
				string prefix;
				cout << "Enter prefix: ";
				cin >> prefix;
				bookManager.searchByPrefix(prefix);
			}
			else if (choise == 3) {
				int bookID;
				cout << "Enter book ID: ";
				cin >> bookID;
				borrowingService.printWhoBorrowed(bookID);
			}
			else if (choise == 4)
				bookManager.printByID();
			else if (choise == 5) {
				int id;
				string name;
				cout << "Enter user name & national ID: ";
				cin >> name >> id;
				userManager.addUsers(User(name, id));
			}
			else if (choise == 6) {
				int userID, bookID;
				cout << "Enter user ID and book ID: ";
				cin >> userID >> bookID;
				borrowingService.userBorrow(userID, bookID);
			}
			else if (choise == 7) {
				int userID, bookID;
				cout << "Enter user ID and book ID: ";
				cin >> userID >> bookID;
				borrowingService.userReturn(userID, bookID);
			}
			else if (choise == 8) {
				userManager.printUsers();
			}
			else
				break;
		}
	}
};
int main() {

	cout << "Library Menu:\n1) Add book\n2) Search books by prefix\n3) Print who borrowed book by ID";
	cout << "\n4) Print books in ascending order of ID\n5) Add user";
	cout << "\n6) User borrow book\n7) User return book\n8) Print users in ascending order of ID\n9) Exit\n";
	LibrarySystem library;
	library.run();
	return 0;
}