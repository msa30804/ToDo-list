#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include<algorithm>
#include <sstream> 
#include <vector>
using namespace std;

class todo
{
private:
    ifstream file;
    ofstream dfile;
    void addtask()
    {
        int no;
        int count = 0; // Initialize count to 0
        string Name;

        file.open("todo.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                int taskNumber;
                stringstream ss(line);
                if (ss >> taskNumber) {
                    count = max(count, taskNumber); // Update count if a higher number is found
                }
            }
            file.close();
        }

        cout << "How many tasks you want to add? ";
        cin >> no;
        cin.ignore(); // Clear the newline character from the input buffer

        time_t now = time(0);
        tm* timeinfo = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

        dfile.open("todo.txt", ios::app);
        if (!dfile.is_open()) {
            cerr << "Unable to open the file" << endl;
            return;
        }

        for (int i = 0; i < no; i++)
        {
            count++; // Increment the count
            cout << "Enter Task Name: ";
            getline(cin, Name);

            dfile << count << ": " << Name << " - " << buffer << endl;
            cout << "Task Added successfully" << endl;
        }

        dfile.close();
    }

    void deletetask()
    {
        int Task_Number;
        cout << "Enter the task number you want to delete: ";
        cin >> Task_Number;

        file.open("todo.txt");
        if (!file)
        {
            cerr << "Unable to open the file" << endl;
            return;
        }

        vector<string> tasks;
        string line;
        while (getline(file, line))
        {
            tasks.push_back(line);
        }
        file.close();

        if (Task_Number < 1 || Task_Number > tasks.size())
        {
            cerr << "Invalid task number" << endl;
            return;
        }

        tasks.erase(tasks.begin() + (Task_Number - 1)); // Adjust index for 0-based vector

        dfile.open("todo.txt");
        if (!dfile.is_open())
        {
            cerr << "Unable to open the file" << endl;
            return;
        }

        for (const string& task : tasks)
        {
            dfile << task << endl;
        }
        dfile.close();

        cout << "Task deleted successfully." << endl;

        // Display remaining tasks
        for (size_t i = 0; i < tasks.size(); ++i)
        {
            cout << "Task "  << tasks[i] << endl;
        }
    }
    void completetask()
    {
        int Task_Number;
        cout << "Enter the task number you want to complete: ";
        cin >> Task_Number;

        file.open("todo.txt"); // Open file for reading

        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
         
        }

        vector<string> tasks;
        string line;
        while (getline(file, line)) {
            tasks.push_back(line);
        }

        file.close(); // Close the file

        if (Task_Number >= 1 && Task_Number <= tasks.size()) {
            tasks[Task_Number - 1] = "completed " + tasks[Task_Number - 1];

            dfile.open("todo.txt"); // Open file for writing
            if (!dfile.is_open()) {
                cerr << "Error opening file." << endl;
               
            }

            for (const string& task : tasks) {
               dfile << task << endl;
            }

           dfile.close(); // Close the file
            cout << "Task marked as completed." << endl;
        }
        else {
            cerr << "Invalid task number." << endl;
        }

       
    }
    
    void listtasks()
    {
        char choice;
        cout << "LIST ALL TASKS 'Y' / 'N'" << endl;
        cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            // lists All Tasks
            file.open("todo.txt");
            if (!file)
            {
                cerr << "Unable to open the file" << endl;
            }
            vector<string> tasks;
            string line;
            while (getline(file, line))
            {
                tasks.push_back(line);
            }
            file.close();
            cout << "Tasks in todo.txt:" << endl;
            for (size_t i = 0; i < tasks.size(); ++i) {
                cout << "task "  << tasks[i] << endl;
            }
        }
        else
            // exit
        {
            cout << "Goodbye!\n";
        }
    }

public:
    todo() {}

    void Menu()
    {
        int choice;
        cout << "\t\t" << "<---+++To-Do List Menu+++--->\n";
        cout << "\t\t\t" << "press 1. Add Task\n";
        cout << "\t\t\t" << "press 2. Complete Task\n";
        cout << "\t\t\t" << "press 3. List Tasks\n";
        cout << "\t\t\t" << "press 4. Delete Task\n";
        cout << "\t\t\t" << "press 5. Quit\n";
        cout << "\t\t\t" << "Enter your choice : " << endl;
        cin >> choice;
        do {
            switch (choice)
            {
            case 1:
                addtask();
                break;
            case 2:
                completetask();
                break;
            case 3:
                listtasks();
                break;
            case 4:
                deletetask();
                break;
            case 5:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                cout << "press 1. Add Task\n";
                cout << "press 2. Complete Task\n";
                cout << "press 3. List Tasks\n";
                cout << "press 4. Delete Task\n";
                cout << "press 5. Quit\n";
            }

            if (choice != 5) {
                cout << "Enter your choice : ";
                cin >> choice;
            }
        } while (choice != 5);
    }
   
};
int main()
{
    cout << "\t\t\t\t\t<------TO DO List------>" << endl;
    todo obj;
    obj.Menu();
    return 0;
}