#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Database {
private:
    enum class ColumnType {
        Integer,
        String
    };

    struct Column {
        string name;
        ColumnType type;
    };

    struct Table {
        string name;
        vector<Column> columns;
        vector<vector<string>> rows;
    };

    vector<Table> tables;

public:
    void createTable(string tableName, vector<pair<string, ColumnType>> columnData) {
        Table newTable;
        newTable.name = tableName;
        for (auto& [columnName, columnType] : columnData) {
            Column column;
            column.name = columnName;
            column.type = columnType;
            newTable.columns.push_back(column);
        }
        tables.push_back(newTable);
    }

    void insert(string tableName, vector<string> values) {
        // Find the specified table in the list of tables
        for (Table& table : tables) {
            if (table.name == tableName) {
                // Check that the number of values matches the number of columns
                if (values.size() != table.columns.size()) {
                    cout << "Error: incorrect number of values" << endl;
                    return;
                }

                // Check that the types of the values match the types of the columns
                for (int i = 0; i < values.size(); i++) {
                    if (table.columns[i].type == ColumnType::Integer) {
                        try {
                            stoi(values[i]);
                        } catch (...) {
                            cout << "Error: value is not an integer" << endl;
                            return;
                        }
                    }
                }

                // Add the new row to the table
                table.rows.push_back(values);
                return;
            }
        }

        // If the table was not found, print an error message
        cout << "Error: table " << tableName << " does not exist" << endl;
    }

    vector<vector<string>> select(string tableName, vector<string> columnNames) {
        // Find the specified table in the list of tables
        for (Table& table : tables) {
            if (table.name == tableName) {
                // Filter the rows by column names if provided
                vector<vector<string>> selectedRows;
                for (vector<string> row : table.rows) {
                    if (columnNames.empty()) {
                        // If no column names are specified, select all columns
                        selectedRows.push_back(row);
                    } else {
                        // Otherwise, select only the specified columns
                        vector<string> selectedValues;
                        for (string columnName : columnNames) {
                            for (int i = 0; i < table.columns.size(); i++) {
                                if (table.columns[i].name == columnName) {
                                    selectedValues.push_back(row[i]);
                                    break;
                                }
                            }
                        }
                        selectedRows.push_back(selectedValues);
                    }
                }
                return selectedRows;
            }
        }

        // If the table was not found, return an empty result
        return {};
    }

    void update(string tableName, string columnName, string value) {
        // Find the specified table in the list of tables
        for (Table& table : tables) {
            if (table.name == tableName) {
                // Find the index of the specified column
                int columnIndex = -1;
                for (int i = 0; i < table.columns.size(); i++) {
                    if (table.columns[i].name == columnName) {
                        columnIndex = i;
                        break;
                    }
                }
                if (columnIndex == -1) {
                    cout << "Error: column " << columnName << " does not exist in table " << tableName << endl;
                    return;
                }

                // Update the values in the specified column for all rows
                for (vector<string>& row : table.rows) {
                    row[columnIndex] = value;
                }
                return;
            }
        }
    
        // If the table was not found, print an error message
        cout << "Error: table " << tableName << " does not exist" << endl;
    }

    void remove(string tableName, string columnName, string value) {
        // Find the specified table in the list of tables
        for (Table& table : tables) {
            if (table.name == tableName) {
                // Find the index of the specified column
                int columnIndex = -1;
                for (int i = 0; i < table.columns.size(); i++) {
                    if (table.columns[i].name == columnName) {
                        columnIndex = i;
                        break;
                    }
                }
                if (columnIndex == -1) {
                    cout << "Error: column " << columnName << " does not exist in table " << tableName << endl;
                    return;
                }

                // Remove the rows where the specified value is found in the specified column
                auto it = table.rows.begin();
                while (it != table.rows.end()) {
                    if ((*it)[columnIndex] == value) {
                        it = table.rows.erase(it);
                    } else {
                        it++;
                    }
                }
                return;
            }
        }

        // If the table was not found, print an error message
        cout << "Error: table " << tableName << " does not exist" << endl;
    }
};

int main() {
    // Create a table with two columns
    createTable("students", {"name", "age"});

    // Insert three rows into the table
    insert("students", {"Alice", "20"});
    insert("students", {"Bob", "22"});
    insert("students", {"Charlie", "24"});

    // Print the contents of the table
    select("students");

    // Update the age of Alice to 21
    update("students", "age", "21");

    // Print the contents of the table again to confirm the update
    select("students");

    // Remove the row where Bob is listed
    remove("students", "name", "Bob");

    // Print the contents of the table again to confirm the removal
    select("students");

    return 0;
}
