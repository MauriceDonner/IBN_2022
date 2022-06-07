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
		string lru;
		int not_loaded;
	};

	// Buffer with c entries, init with a non-page, and pointer to 1st entry
	page buffer[c];
	page* p = &buffer[0];
	for (int i = 0; i<c; i++) {
		buffer[i].pnumber = 0x0A;
		buffer[i].R = 0;
		buffer[i].lru = "";
		buffer[i].not_loaded = 100;
	}

	// Counter for ring buffer and epoch interval
	int counter = 0;
	int epoch = 3;

	// Iterate over the input
	for (const char &entry : refstr) {
		char new_page = entry - '0';
		bool page_set = 0; // Check if a place for the page has been found
		bool page_in_buffer = 0; // Check if the page is loaded already
		int position = 0; // For later string formatting

		// Epoch Implementation
		if (counter%epoch == 0) {
		    for (int i = 0; i<c; i++) {
		    buffer[i].lru+=to_string(buffer[i].R); 
		    buffer[i].R = 0;
		    }	
		//cout << "Epoch analysis [" << buffer[0].lru << "," << buffer[1].lru
		 //  << "," << buffer[2].lru << "]" << endl;
		}

		// Check if page is in buffer
		for (int i = 0; i<c; i++) {
			if (buffer[i].pnumber == new_page) {
				page_in_buffer = 1;
				buffer[i].R = 1;
			}
		}

		if (!page_in_buffer) {
		page_set = 1;

		// Search for the last recently used page
		int oldest = 0;

		// Iterate over the buffer
		for (int i = 0; i<c; i++) {
		// Count 0s from the right to the left
		for (int ii = buffer[i].lru.length()-1; ii>-1; ii--) {
		    if (buffer[i].lru[ii] == '0') buffer[i].not_loaded+=1;
		    else ii = -1;
		}
		// Then remember, which was the last recently used page
		if (buffer[i].not_loaded >= buffer[oldest].not_loaded) {
		    oldest = i;
		}}

		// Exchange the oldest page, and reset the epoch counter
		buffer[oldest].pnumber = new_page;
		buffer[oldest].not_loaded = 0;
		buffer[oldest].lru = "1";
		position = oldest;
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
		counter++;
	}
	return 0;

}
