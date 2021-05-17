#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

void split(std::string str, std::string splitBy, std::vector<std::string>& tokens) {
	/* Store the original string in the array, so we can loop the rest
	 * of the algorithm. */
	tokens.push_back(str);

	// Store the split index in a 'size_t' (unsigned integer) type.
	size_t splitAt;
	// Store the size of what we're splicing out.
	size_t splitLen = splitBy.size();
	// Create a string for temporarily storing the fragment we're processing.
	std::string frag;
	// Loop infinitely - break is internal.
	while (true) {
		/* Store the last string in the vector, which is the only logical
		 * candidate for processing. */
		frag = tokens.back();
		/* The index where the split is. */
		splitAt = frag.find(splitBy);
		// If we didn't find a new split point...
		if (splitAt == string::npos) {
			// Break the loop and (implicitly) return.
			break;
		}
		/* Put everything from the left side of the split where the string
		 * being processed used to be. */
		tokens.back() = frag.substr(0, splitAt);
		/* Push everything from the right side of the split to the next empty
		 * index in the vector. */
		tokens.push_back(frag.substr(splitAt + splitLen, frag.size() - (splitAt + splitLen)));
	}
}


class UnitsClass {
	vector<string> m_units;
	vector<vector<int> > m_data;
	vector<int> m_result;
	vector<int> m_order;
	int m_index;
public:
	UnitsClass() {
		m_index = 0;
	}
	~UnitsClass() {

	}
	void getUnits(string unitsline) {
		split(unitsline, " ", m_units);
		for (auto target = m_units.begin(); target != m_units.end(); ++target) {
			m_result.push_back(0);
		}
	}
	void getData(string line) {
		vector<int> linedata;
		vector<string> tmpline;
		split(line, " ", tmpline);
		m_order.push_back(m_index++);
		for (auto target = m_units.begin(); target != m_units.end(); ++target) {
			int value = 0;
			if (!(*target).compare(tmpline[0])) {
				value = 1;
			}
			if (!(*target).compare(tmpline[3])) {
				value = stoi(tmpline[2]);
			}
			linedata.push_back(value);
		}
		m_data.push_back(linedata);
	}

	void printVector(vector<int> data) {
		cout << endl;
		for (auto target = data.begin(); target != data.end(); ++target) {
			cout << (*target) << " ";
		}
	}

	int checkSameItemExist(vector<int> item) {
		int index = 0;
		for (auto target = item.begin(); target != item.end(); ++target) {
			if ((*target) != 0 && m_result[index] != 0) {
				return index;
			}
			index++;
		}
		return 0;
	}

	void multipleRate(vector<int>& data, int rate) {
		for (auto target = data.begin(); target != data.end(); ++target) {
			*target = *target * rate;
		}
	}

	void combineTwo(vector<int> data) {
		int index = 0;
		for (auto target = data.begin(); target != data.end(); ++target) {

			if (m_result[index] == 0 && *target != 0) {
				m_result[index] = *target;
			}

			index++;
		}
	}

	void output() {
		bool flag = true;
		int i = 0;
		while (i != (int)m_order.size()) {
			vector<int> tmp = m_data[m_order[i]];
			if (flag) {
				m_result = tmp;
				flag = false;
			}
			else {
				int sameIndex = checkSameItemExist(tmp);
				if (sameIndex) {
					//multiple
					int rate = 1;
					if (tmp[sameIndex] < m_result[sameIndex]) {
						rate = m_result[sameIndex] / tmp[sameIndex];
						multipleRate(tmp, rate);
					}
					else {
						rate = tmp[sameIndex] / m_result[sameIndex];
						multipleRate(m_result, rate);
					}

					//combine
					combineTwo(tmp);
				}
				else {
					m_order.push_back(m_order[i]);
				}
			}
			i++;
		}

		//sort
		for (int i = 0; i < (int)m_result.size(); i++)
		{
			for (int j = i + 1; j < (int)m_result.size(); j++)
			{
				if (m_result[j] < m_result[i])
				{
					int temp;
					string stemp;

					temp = m_result[i];
					m_result[i] = m_result[j];
					m_result[j] = temp;

					stemp = m_units[i];
					m_units[i] = m_units[j];
					m_units[j] = stemp;
				}
			}
		}

		for (int i = 0; i < (int)m_result.size(); i++)
		{
			if (i == (int)m_result.size() - 1)
			{
				cout << m_result[i] << m_units[i] << endl;
			}
			else {
				cout << m_result[i] << m_units[i] << " = ";
			}
		}
		//printVector(m_result);
	}

};

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *[] argv) {
	freopen(argv[1], "r", stdin);
	freopen(argv[2], "w", stdout);

	char line[256];
	memset(line, 0, 256);
	int num;
	char temp[64];

	int iterator;
	while (cin >> num && num != 0) {
		UnitsClass obj;
		iterator = num;
		for (int i = 0; i < num; i++) {
			memset(line, 0, 256);

			for (int j = 0; j < iterator; j++)
			{
				memset(temp, 0, 64);

				cin >> temp;
				strcat(line, temp);
				if(j != iterator - 1)
				strcat(line, " ");
			}
			
			iterator = 4;

			if (i == 0) {
				obj.getUnits(line);
			}
			else {
				obj.getData(line);
			}
		}
		obj.output();
	}
	return 0;
}
