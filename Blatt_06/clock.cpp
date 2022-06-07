#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main() {

	int n = 0; // For testing empty input

	string cstr;
	while (true)
	{
	cout << "Number of Frames (default 3): ";
	getline(cin, cstr);
	stringstream s(cstr);
	if (s >> n) break; // If number has been entered - Exit 
	else
		cstr = "3";
		break;
	}
	int c = stoi(cstr); // Number of frames

	string refstr;
	while (true)
	{
	cout << "Reference Set (default 70120304230321201701): ";
	getline(cin, refstr);
	if (!refstr.empty()) break; // If number has been entered - Exit 
	else
		refstr = "70120304230321201701";
		break;
	}


	// We make a struct for entries
	struct page {
		char pnumber;
		bool R;
	};

	// Buffer with c entries, init with a non-page, and pointer to 1st entry
	page buffer[c];
	page* p = &buffer[0];
	for (int i = 0; i<c; i++) {
		buffer[i].pnumber = 0x0A;
		buffer[i].R = 0;
	}
	
	// Counter for ring buffer
	int counter = 0;

	// Iterate over the input
	for (const char &entry : refstr) {
		char new_page = entry - '0';
		bool page_set = 0; // Check if a place for the page has been found
		bool page_in_buffer = 0; // Check if the page is loaded already
		int position = 0; // For later string formatting
		

		// Check if page is in buffer
		for (int i = 0; i<c; i++) {
			if (buffer[i].pnumber == new_page) {
				page_in_buffer = 1;
				buffer[i].R = 1;
			}
		}

		// Go through the buffer and find a place for the page
		while (!page_set && !page_in_buffer) {
			
			// Check if R-Bit has been set
			if (p->R == 1) {
				p->R = 0;
			}
			else {
				p->pnumber = new_page;
				page_set = 1;
				position = counter%c;
			}

			// Go to the next buffer entry
			counter++;
			p = &buffer[0]+counter%c;
		}

		// Console output after each step
		cout << entry << " -> [";
		for (int i = 0; i<c; i++) {
			string Element;
			if (i==position && page_set) {
				Element = "("+to_string(buffer[i].pnumber)+")";
			}
			else {
				Element = " "+to_string(buffer[i].pnumber)+" ";
			}

			if (i==c-1) cout << Element << "]" << endl;
			else cout << Element << ",";
		}
	}
	return 0;

}
