
//This is task from Cisco C++ course, Created by Leonid Nozdrin.

#include <iostream>
#include <iomanip>
#include <fstream>  
#include <string>
#include <map>
#include <string>
using namespace std;

int main()
{
	string strInput = "";
	float totalAmount = 0;

	map<string, float> products;
	map<string, string> productNames;
	map<string, int> productAmount;

	products.insert(make_pair("9002490100773", 0.15f));
	products.insert(make_pair("6415600501781", 0.20f));
	products.insert(make_pair("5410228141266", 0.10f));

	productNames.insert(make_pair("9002490100773", "Red Bull 0,25 litres (0.15 euro)"));
	productNames.insert(make_pair("6415600501781", "Coca-cola 0,5 litres (0.20 euro)"));
	productNames.insert(make_pair("5410228141266", "Stella Artois beer 0.33 litres (0.10 euro)"));

	productAmount.insert(make_pair("9002490100773", 0));
	productAmount.insert(make_pair("6415600501781", 0));
	productAmount.insert(make_pair("5410228141266", 0));

	ofstream outfile("kuitti.txt");

	map<string, float>::iterator it = products.begin();
	while (it != products.end())
	{
		cout << it->first << " :: " << it->second << endl;
		it++;
	}

	while (strInput != "0000000000001")
	{
		cin >> strInput;

		if (strInput == "0000000000001")
		{
			cout << "-------------" << endl;
			cout << "Recycling finished." << endl;
			cout << "Total amount of refund is " << fixed << setprecision(2) << totalAmount << " euros. " << endl; \

				map<string, int>::iterator it = productAmount.begin();
			while (it != productAmount.end())
			{
				string product = it->first;
				int count = it->second;

				string productName = productNames.find(product)->second;

				if (count > 1)
				{
					outfile << count << "X " << productName << std::endl;
				}
				else if (count == 1)
				{
					outfile << productName << std::endl;
				}

				it++;
			}

			outfile << "Total: " << totalAmount << std::endl;
		}

		else if (strInput != "0000000000001" && strInput != "0000000000010" && products.find(strInput) == products.end())
		{
			cout << "EAN code not recognized" << endl;
		}
		else if (strInput == "0000000000010")
		{
			int answer = 0;

			while (answer != 3)
			{
				cout << "-------------" << endl;
				cout << "1) Add new EAN code" << endl;
				cout << "2) Remove existing EAN code" << endl;
				cout << "3) Save changes and return to normal mode" << endl;
				cout << "Choice: ";
				cin >> answer;
				cout << "-------------" << endl;

				if (answer == 1)
				{
					string num;
					string name;
					float price;

					cout << "New EAN code: ";
					cin >> num;
					cout << "Article name: ";
					cin.ignore();
					getline(std::cin, name);
					cout << "Refund price: ";
					cin >> price;

					products.insert(make_pair(num, price));
					productNames.insert(make_pair(num, name));
					productAmount.insert(make_pair(num, 0));
				}

				if (answer == 2)
				{
					string num;

					cout << "EAN code: ";
					cin >> num;
					products.erase(num);
					productNames.erase(num);
				}

				if (answer == 3)
				{
					cout << "-------------" << endl;
					map<string, float>::iterator it = products.begin();
					while (it != products.end())
					{
						cout << it->first << " :: " << it->second << endl;
						it++;
					}
				}

			}
		}
		else
		{
			float value = products.find(strInput)->second;
			totalAmount += value;

			int amoount = productAmount.find(strInput)->second;
			amoount++;
			productAmount.find(strInput)->second = amoount;
		}
	}

	return 0;
}
